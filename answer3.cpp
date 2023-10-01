#include <bits/stdc++.h>
using namespace std;

void fileread(unordered_map<string, string> &primary, unordered_set<string> &st)
{
    ifstream file;
    file.open("data.csv");
    string line;
    getline(file, line);

    while (getline(file, line))
    {
        string str = "";
        int count = 0; // it help identifying column.
        string position_id = "", total_time = "", name = "";
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
                else if (count == 4)
                {
                    total_time = str;
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
        // val1 store hours and val2 stores minute of total_time.
        int val1 = 0, val2 = 0, val = 0;
        i = 0;
        string temp = "";
        while (i < total_time.length())
        {
            if (total_time[i] == ':')
            {
                val1 = val;
                val = 0;
            }
            else
            {
                int v = total_time[i] - '0';
                val = val * 10 + v;
            }
            i++;
        }
        val2 = val;
        if (val1 > 14)
        {
            st.insert(position_id);
        }
        else if (val1 == 14)
        {
            if (val2 > 0)
            {
                st.insert(position_id);
            }
        }
    }
    file.close();
}

int main()
{
    // Assumption :
    // 1 . Remove 1st row which contain column names.
    // 2. To calculate the answer of 3rd question only total_time_hours,position_id, name column is useful and skip other column.
    //
    unordered_map<string, string> primary;
    unordered_set<string> st;
    fileread(primary, st);
    for (auto x : st)
    {
        cout << x << " " << primary[x] << endl;
    }
    return 0;
}