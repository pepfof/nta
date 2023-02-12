#include "nta_keyboard.hpp"

int ntakey_global_fd = 0;

void nta_keyserver_start()
{
	struct uinput_setup usetup;

	if (access(NTAKEY_LOCK_FILE, F_OK) == 0)
	{
		nta_report(NTAREP_ERROR, "Refusing to start program with an existing " + string(NTAKEY_LOCK_FILE));
		exit(1);
		//raise(SIGTERM);
	}
	else
	{
		FILE *lfile = fopen(NTAKEY_LOCK_FILE, "w");
		fclose(lfile);
	}

	ntakey_global_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

	/*
	 * The ioctls below will enable the device that is about to be
	 * created, to pass key events, in this case the space key.
	 */
	ioctl(ntakey_global_fd, UI_SET_EVBIT, EV_KEY);
	ioctl(ntakey_global_fd, UI_SET_EVBIT, EV_REP);
	ioctl(ntakey_global_fd, UI_SET_EVBIT, EV_SYN);

	unsigned int i = 0;
	while (i < 256)
	{
		ioctl(ntakey_global_fd, UI_SET_KEYBIT, i);
		i++;
	}

	memset(&usetup, 0, sizeof(usetup));
	usetup.id.bustype = NTAKEY_BUS_TYPE;
	usetup.id.vendor = NTAKEY_ID_VENDOR;   /* sample vendor */
	usetup.id.product = NTAKEY_ID_PRODUCT; /* sample product */
	strcpy(usetup.name, NTAKEY_DEVICE_NAME);

	ioctl(ntakey_global_fd, UI_DEV_SETUP, &usetup);
	ioctl(ntakey_global_fd, UI_DEV_CREATE);
};

void nta_keyserver_end()
{
	remove(NTAKEY_LOCK_FILE);
	ioctl(ntakey_global_fd, UI_DEV_DESTROY);
	close(ntakey_global_fd);
};

void nta_keyserver_emit(int type, int code, int val)
{
	struct input_event ie;

	ie.type = type;
	ie.code = code;
	ie.value = val;
	/* timestamp values below are ignored */
	ie.time.tv_sec = 0;
	ie.time.tv_usec = 0;

	write(ntakey_global_fd, &ie, sizeof(ie));
}

void nta_execute_keysig(string action, vector<int> keylist, unsigned int depth)
{
	unsigned int keycode = 0;
	try
	{
		keycode = stoi(action);
	}
	catch (invalid_argument const &)
	{
		nta_report(NTAREP_ERROR, "Unknown or otherwise incorrect key: " + action);
	}

	int value = depth > keylist.size() ? 0 : keylist[depth];

	/* int i = 0;
	printf("depth: %d\n", depth);
	while (i < keylist.size())
	{
		printf("%d\n", keylist[i]);
		i++;
	}
	printf("value: %d", value); */

	nta_keyserver_emit(EV_KEY, keycode, value);
	nta_keyserver_emit(EV_SYN, SYN_REPORT, 0);

	nta_report(NTAREP_DEBUG, "Button " + to_string(keycode) + ": " + to_string(value));
}

void nta_parse_keysig(string &action_to_parse)
{
	size_t keycode_length = action_to_parse.find(' ');
	string keycode = action_to_parse.substr(0, keycode_length);
	ifstream f_in(KEYCODES_FILE);

	string line;
	string keycode_number = "";

	while (getline(f_in, line))
	{
		size_t keycode_pos;
		smatch m;
		regex r("\\b" + keycode + "\\b");

		if (regex_search(line, m, r))
		{
			keycode_pos = line.find(keycode);
			nta_report(NTAREP_PARSE, keycode);
			nta_report(NTAREP_PARSE, line);
			keycode_number = line.substr(keycode_pos + keycode.length() + 1);
			size_t start = keycode_number.find_first_not_of(WHITESPACE);
			keycode_number = keycode_number.substr(start);
			nta_report(NTAREP_PARSE, keycode_number);
			action_to_parse.clear();
			action_to_parse = keycode_number;
			return;
		}
	}

	action_to_parse = action_to_parse.substr(action_to_parse.find_first_not_of(WHITESPACE));

	return;
}
