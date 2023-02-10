#include "nta_expand.hpp"

int _extract_tag(string &_s, string tag, vector<pair<size_t, unsigned int>> &output)
{
    size_t tagpos;
    unsigned int tagval;
    while ((tagpos = _s.find(tag)) != string::npos)
    {
        _s.erase(tagpos, tag.length());
        int nfound = sscanf(_s.substr(tagpos).c_str(), "%d ", &tagval);
        if (nfound != 1)
        {
            return 1;
        }
        _s.erase(tagpos, to_string(tagval).length());
        output.push_back(make_pair(tagpos, tagval));
        nta_report(NTAREP_EXPAND, _s + ", " + tag + " at " + to_string(tagpos) + ": " + to_string(tagval));
    }
    return 0;
}

int nta_expand(string input_string, string &output_string, vector<int> keylist)
{
    if (!input_string.empty())
    {

        output_string = input_string;
        int got_layer = -1;
        string temp_output_string = output_string;

        nta_report(NTAREP_EXPAND, "Expanding: " + temp_output_string);

        vector<pair<size_t, unsigned int>> key_tags;

        if (_extract_tag(temp_output_string, "NTA#", key_tags))
        {
            nta_report(NTAREP_EXPAND, "Invalid integer in NTA#, passing nothing");
        }
        else
        {
            size_t pos_offset = 0;
            size_t i = 0;
            while (i < key_tags.size())
            {
                if (key_tags[i].second < keylist.size())
                {
                    temp_output_string.insert(key_tags[i].first + pos_offset, to_string(keylist[key_tags[i].second]));
                    pos_offset += to_string(keylist[key_tags[i].second]).length();
                }
                i++;
            }
        }

        nta_report(NTAREP_EXPAND, "After NTA# pass: " + temp_output_string);

        key_tags.clear();
        if (_extract_tag(temp_output_string, "NTA~", key_tags))
        {
            nta_report(NTAREP_EXPAND, "Invalid integer in NTA~, not switching layer");
        }
        else
        {
            if (!key_tags.empty())
            {
                got_layer = key_tags.front().second;
                nta_report(NTAREP_EXPAND, "Got layer: " + to_string(got_layer));
            }
        }

        nta_report(NTAREP_EXPAND, "After NTA~ pass: " + temp_output_string);
        output_string = temp_output_string;

        return got_layer;
    }
    return -1;
};