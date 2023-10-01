
#include <bits/stdc++.h>
using namespace std;

void fileread(unordered_map<string, int> &max_days, unordered_map<string, string> &primary)
{
    ifstream file;
    file.open("data.csv");
    string line;
    getline(file, line);

    // Primary map maps the Position_Id with name of each person.It is unique.
    string prev_position_id = "";
    int prev = -1, current = 0;
    while (getline(file, line))
    {
        string str = "";
        int count = 0; // it help identifying column.
        string position_id = "", start_date = "", name = "";
        int i = 0;
        while (i < line.length())
        {
            if (line[i] == '"')
            {
                i++;
                string temp = "";
                while (i < line.length() && line[i] != '"')
                {

                    temp += line[i];

                    i++;
                }
                name = temp;
                str = "";
            }
            else if (line[i] == ',')
            {
                if (count == 0)
                {
                    position_id = str;
                }
                else if (count == 2)
                {
                    start_date = str;
                }
                str = "";
                count++;
            }
            else
            {
                str += line[i];
            }
            i++;
        }
        primary[position_id] = name;
        i = 0;
        int val = 0;
        int date = 0;
        count = 0;
        while (i < start_date.length())
        {
            if (start_date[i] == '/')
            {
                if (count == 1)
                {
                    date = val;
                    break;
                }
                val = 0;
                count++;
            }
            else if (start_date[i] == ' ')
            {
                break;
            }
            else
            {
                int v = start_date[i] - '0';
                val = val * 10 + v;
            }
            i++;
        }
        if (max_days.find(position_id) == max_days.end())
        {
            max_days[position_id] = 0;
        }
        if (position_id == prev_position_id)
        {
            if (prev == date)
            {
                // continue;
            }
            else if (prev + 1 == date)
            {
                current++;
            }
            else
            {
                current = 1;
            }
        }
        else
        {
            current = 1;
            prev_position_id = position_id;
        }
        //  cout<<position_id<<" "<<date<<" "<<prev<<" "<<current<<" "<<position_id<<" "<<prev_position_id<<endl;
        prev = date;

        prev_position_id = position_id;
        int max_length = max_days[position_id];
        max_days[position_id] = max(max_length, current);
    }
    file.close();
}

int main()
{
    // Assumption :
    // 1 . Remove 1st row which contain column names.
    // 2. Data sequentially arranged by date of each person.

    unordered_map<string, int> max_days; // max_days store maximum consecutive days by person.
    // maps the position_id with name.
    unordered_map<string, string> primary;
    fileread(max_days, primary);
    for (auto x : max_days)
    {
        if (x.second >= 7)
        {
            cout << x.first << " " << primary[x.first] << endl;
        }
    }
    return 0;
}