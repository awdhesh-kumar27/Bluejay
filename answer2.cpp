
#include <bits/stdc++.h>
using namespace std;

bool time_diff(string stime, string smer, string etime, string emer)
{
    int h1 = 0, h2 = 0, m1 = 0, m2 = 0;
    int val = 0;
    int i = 0;
    while (i < stime.length())
    {
        if (stime[i] == ':')
        {
            h2 = val;
            val = 0;
        }
        else
        {
            int v = stime[i] - '0';
            val = val * 10 + v;
        }
        i++;
    }
    m2 = val;
    i = 0;
    val = 0;
    while (i < etime.length())
    {
        if (etime[i] == ':')
        {
            h1 = val;
            val = 0;
        }
        else
        {
            int v = etime[i] - '0';
            val = val * 10 + v;
        }
        i++;
    }
    m1 = val;
    int diff_h = 0, diff_m = 0;
    if (emer == smer && smer == "AM")
    {
        diff_h = h2 - h1;
        if (m2 < m1)
        {
            m2 += 60;
            diff_h -= 1;
        }
        diff_m = m2 - m1;
    }
    else if (emer == smer && smer == "PM")
    {
        h1 = h1 % 12;
        h2 = h2 % 12;
        diff_h = h2 - h1;
        if (m2 < m1)
        {
            m2 += 60;
            diff_h -= 1;
        }
        diff_m = m2 - m1;
    }
    else if (emer == "AM" && smer == "PM")
    {
        if (h2 < 12)
        {
            h2 += 12;
        }
        if (m2 < m1)
        {
            m2 += 60;
            diff_h -= 1;
        }
        diff_h += h2 - h1;
        diff_m = m2 - m1;
    }
    if (diff_m >= 60)
    {
        diff_h += diff_m / 60;
        diff_m = diff_m % 60;
    }
    //  cout<<diff_h<<" "<<diff_m<<" ";
    if (diff_h >= 1 && diff_h < 10)
    {
        if (diff_h == 1)
        {
            return diff_m > 0;
        }
        return true;
    }
    return false;
}
bool helper(string end_date, string start_date)
{
    int i = 0;
    int val = 0;
    string stime = "", smer = "", sdate = "", temp = "";
    string etime = "", emer = "", edate = "";
    int count = 0;
    while (i < start_date.length())
    {
        if (start_date[i] == ' ')
        {
            if (count == 0)
            {
                sdate = temp;
            }
            else if (count == 1)
            {
                stime = temp;
            }
            count++;
            temp = "";
        }
        else
        {
            temp += start_date[i];
        }
        i++;
    }
    smer = temp;
    temp = "";
    count = 0;
    i = 0;
    while (i < end_date.length())
    {
        if (start_date[i] == ' ')
        {
            if (count == 0)
            {
                edate = temp;
            }
            else if (count == 1)
            {
                etime = temp;
            }
            count++;
            temp = "";
        }
        else
        {
            temp += end_date[i];
        }
        i++;
    }
    emer = temp;
    temp = "";
    //  cout<<sdate<<" "<<edate<<endl;
    if (sdate == edate)
    {
        //   cout<<etime<<" "<<emer<<" "<<stime<<" "<<smer<<" ";
        bool ans = time_diff(stime, smer, etime, emer);
        //   cout<<endl;
        return ans;
    }
    return false;
}

void fileread(unordered_map<string, int> &max_days, unordered_map<string, string> &primary, unordered_set<string> &st)
{
    ifstream file;
    file.open("data.csv");
    string line;
    getline(file, line);

    // Primary map maps the Position_Id with name of each person.It is unique.
    string prev_position_id = "";
    string prev_start = "", prev_end = "", prev_date = "";
    while (getline(file, line))
    {
        string str = "";
        int count = 0; // it help identifying column.
        string position_id = "", start_date = "", end_date = "", name = "";
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
                else if (count == 3)
                {
                    end_date = str;
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

        if (position_id == prev_position_id)
        {
            if (prev_end.length() != 0 && start_date.length() != 0)
            {
                //  cout<<position_id<<" ";
                bool ans = helper(prev_end, start_date);
                //    cout<<endl;
                if (ans)
                {
                    // cout<<position_id<<" "<<start_date<<endl;
                    st.insert(position_id);
                }
            }
        }
        //   cout<<position_id<<" "<<start_date<<" "<<end_date<<endl;
        prev_position_id = position_id;
        prev_end = end_date;
        prev_start = start_date;
    }
    file.close();
}

int main()
{
    // Assumption :
    // 1 . Remove 1st row which contain column names.
    // 2.  2-shifts per day and time difference of shifts of same day considered.
    //   not considering the shifts difference if they start of different dates.
    unordered_map<string, int> max_days;
    unordered_map<string, string> primary;
    unordered_set<string> st;
    fileread(max_days, primary, st);

    for (auto x : st)
    {
        cout << x << " " << primary[x] << endl;
    }
    return 0;
}
