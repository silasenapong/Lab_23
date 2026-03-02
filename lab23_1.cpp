#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

char score2grade(int score)
{
    if (score >= 80)
        return 'A';
    if (score >= 70)
        return 'B';
    if (score >= 60)
        return 'C';
    if (score >= 50)
        return 'D';
    else
        return 'F';
}

string toUpperStr(string x)
{
    string y = x;
    for (unsigned i = 0; i < x.size(); i++)
        y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades)
{
    ifstream read(filename);
    string textline;

    char format[] = "%[^:]:%d %d %d";

    while (getline(read, textline))
    {
        char name[100];
        int score1, score2, score3;

        sscanf(textline.c_str(), format, name, &score1, &score2, &score3);

        int total_score = score1 + score2 + score3;

        names.push_back(name);
        scores.push_back(total_score);
        grades.push_back(score2grade(total_score));
    }

    read.close();
}

void getCommand(string &command, string &key)
{
    string input;
    command = "";
    key = "";

    cout << "Please input your command:\n";

    if (getline(cin, input))
    {
        stringstream ss(input);

        if (ss >> command)
        {
            getline(ss >> ws, key);
        }
    }
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key)
{
    int size = scores.size();
    bool is_found = false;

    for (int i = 0; i < size; i++)
    {
        if (toUpperStr(names[i]) == key)
        {
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            cout << "---------------------------------\n";
            is_found = true;
            break;
        }
    }

    if (!is_found)
    {
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
    }
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key)
{
    int size = scores.size();
    bool is_found = false;

    cout << "---------------------------------\n";

    for (int i = 0; i < size; i++)
    {
        if (grades[i] == key[0])
        {
            cout << names[i] << " (" << scores[i] << ")\n";
            is_found = true;
        }
    }

    if (!is_found)
    {
        cout << "Cannot found.\n";
    }

    cout << "---------------------------------\n";
}

int main()
{
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades;
    importDataFromFile(filename, names, scores, grades);

    do
    {
        string command, key;
        getCommand(command, key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if (command == "EXIT")
            break;
        else if (command == "GRADE")
            searchGrade(names, scores, grades, key);
        else if (command == "NAME")
            searchName(names, scores, grades, key);
        else
        {
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    } while (true);

    return 0;
}
