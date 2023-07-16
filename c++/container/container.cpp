#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

void UseMap()
{
    std::map<int, string> players{{10001, "alice"}, {10002, "bob"}, {10003, "mark"}};
    for (auto it : players)
    {
        cout << it.first << ": " << it.second << endl;
    }
}

int main()
{
    UseMap();
}