#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <string.h>

using namespace std;

/**************
 1. 在64位linux, GCC开发环境下, 定义:
   char s[] = {1, 2, 3, 0, 6, 0};
   char* p = s + 3;
   那么:
    sizeof(s) = ______
    strlen(s) = ______
    sizeof(p) = ______
    strlen(p) = ______
**************/

/**************
2. 有二进制文件input.data,将其每一个字节都视为一个8位无符号整数,
编写代码,找出其中出现次数最多(可能并列)的值,
输出其数值和出现次数,编程语言限go/c/c++,需注重代码效率.
**************/

void FindMaxCount()
{
    ifstream srcFile("input.data");
    if (!srcFile)
    {
        cout << "openfile failed" << endl;
    }
    char x;
    std::map<char, int> cntmap;
    while (srcFile >> x)
    {
        if (cntmap.count(x) == 0)
        {
            cntmap.insert({x, 1});
        }
        else
        {
            cntmap[x] = cntmap[x] + 1;
        }
    }

    for (auto it : cntmap)
    {
        cout << it.first << ": " << it.second << endl;
    }

    auto maxValue = max_element(cntmap.begin(), cntmap.end(), [](pair<char, int> left, pair<char, int> right)
                                { return left.second < right.second; });

    for (auto it : cntmap)
    {
        if (it.second == maxValue->second)
        {
            cout << it.first << ": " << it.second << endl;
        }
    }
}

void FindMaxCount2()
{
    ifstream srcFile("input.data");
    if (!srcFile)
    {
        cout << "openfile failed" << endl;
    }
    char x;
    std::map<char, int> cntmap;
    int maxcnt = 0;
    std::vector<char> maxchars;

    while (srcFile >> x)
    {
        if (cntmap.count(x) == 0)
        {
            cntmap.insert({x, 1});
        }
        else
        {
            cntmap[x] = cntmap[x] + 1;
        }

        if (cntmap[x] > maxcnt)
        {
            maxcnt = cntmap[x];
            maxchars.clear();
            maxchars.push_back(x);
        }
        else if (cntmap[x] == maxcnt)
        {
            maxchars.push_back(x);
        }
    }
    srcFile.close();

    cout << maxcnt << ": ";
    for (auto it : maxchars)
    {
        cout << it << ", ";
    }
    cout << endl;
}

void FindMaxCount3()
{
    ifstream srcFile("input.data");
    if (!srcFile)
    {
        cout << "openfile failed" << endl;
    }
    char x;
    int32_t cntmap[256] = {0};
    int maxcnt = 0;
    std::vector<char> maxchars;

    while (srcFile >> x)
    {
        cntmap[x] += 1;
        if (cntmap[x] > maxcnt)
        {
            maxcnt = cntmap[x];
            maxchars.clear();
            maxchars.push_back(x);
        }
        else if (cntmap[x] == maxcnt)
        {
            maxchars.push_back(x);
        }
    }
    srcFile.close();

    cout << maxcnt << ": ";
    for (auto it : maxchars)
    {
        cout << it << ", ";
    }
    cout << endl;
}

int main()
{
    char s[] = {1, 2, 3, 0, 6, 0};
    char *p = s + 3;
    cout << sizeof(s) << ", " << strlen(s) << ", " << sizeof(p) << ", " << strlen(p) << endl;
    FindMaxCount();
    FindMaxCount2();
    FindMaxCount3();
    return 0;
}
