#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <unordered_map>

using namespace std;

string trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if(first == string::npos)
    {
        return "";
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (first - last + 1));
}

vector<string> split(string& tosplit, char delimiter)
{
    vector<string> tokens;
    stringstream ss(tosplit);
    string token;
    while(getline(ss, token, delimiter))
    {
        tokens.push_back(trim(token));
    }
    return tokens;
}

int main()
{
    unordered_map<string, int> allowed{{"red", 12}, {"green", 13}, {"blue", 14}};

    // file open and error check
    string filename = "input.txt";
    ifstream file(filename);
    if(!file)
    {
        throw(runtime_error("File not found: " + filename));
    }


    regex pattern(R"((\d+)\s*(blue|red|green))");
    smatch match;

    long long sum{0};
    string line;
    // iterate through every line
    int game = 1;
    while(getline(file, line))
    {
        
        bool valid = true;
        string sub = line.substr(line.find(':') + 1);
        vector<string> cubeset = split(sub, ',');
        for(auto cube : cubeset)
        {
            while(valid && regex_search(cube, match, pattern))
            {
                int number = stoi(match[1].str());
                string color = match[2].str();

                //cout << "Found " << number << " of " << color << endl;
                cube = match.suffix().str();
                if(allowed[color] < number)
                {
                    cout << "For game " << game << " number of " << color << " was too high: " << number << endl;
                    valid = false;
                    break;
                }
            }
        }
        if(valid)
        {
            sum += game;
            cout << "Adding game " << game << ". Sum now: " << sum << endl;
        }
        game++;
    }

    
    cout << "The sum was " << sum << endl;
    return 0;


}
