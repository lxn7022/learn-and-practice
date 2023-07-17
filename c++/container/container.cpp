#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <list>
#include <deque>
#include <unordered_map>

using namespace std;

void UseVector()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;
    // befor c++11
    vector<int> vec;
    for (int i = 10; i < 20; i++)
        vec.push_back(i);

    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << " ";
    cout << endl;
    // c++11
    vector<int> vec2{1, 2, 3, 4, 5};
    for (auto it : vec2)
        cout << it << " ";
    cout << endl;
}

void UseDeque()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;

    deque<float> dequeTemp;

    for (int i = 0; i < 6; i++)
        dequeTemp.push_back(i);

    for (int i = 0; i < dequeTemp.size(); i++)
        cout << dequeTemp[i] << " "; // 输出：0 1 2 3 4 5

    cout << endl;
}

void UseList()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;

    list<char> listTemp;

    for (char c = 'a'; c <= 'z'; ++c)
        listTemp.push_back(c);

    while (!listTemp.empty())
    {
        cout << listTemp.front() << " ";
        listTemp.pop_front();
    }
    cout << endl;
}
struct People
{
    string name;
    int age;

    bool operator<(const People p) const
    {
        return age < p.age;
    }
};

void UseSet()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;

    set<int> setTemp;

    setTemp.insert(3);
    setTemp.insert(1);
    setTemp.insert(2);
    setTemp.insert(1);

    set<int>::iterator it;
    for (it = setTemp.begin(); it != setTemp.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    // c++11
    for (auto it : setTemp)
        cout << it << " ";
    cout << endl;

    // element in set is struct
    set<People> setTemp2;

    setTemp2.insert({"张三", 14});
    setTemp2.insert({"李四", 16});
    setTemp2.insert({"隔壁老王", 10});
    for (auto it : setTemp2)
        cout << it.name << ": " << it.age << endl;
    cout << endl;
}

void UseMap()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;
    std::map<int, string> players{{10001, "alice"}, {10002, "bob"}, {10003, "mark"}};
    players.insert({10004, "lark"});
    for (auto it : players)
    {
        cout << it.first << ": " << it.second << endl;
    }
}

void UseMultiMap()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;
    // ref: http://c.biancheng.net/view/518.html
    std::multimap<std::string, size_t> people{{"Ann", 25}, {"Bill", 46}, {"Jack", 77}, {"Jack", 32}, {"Jill", 32}, {"Ann", 35}};
    std::string name{"Bill"};
    auto iter = people.find(name);
    if (iter != std::end(people))
        std::cout << name << " is " << iter->second << std::endl;
    iter = people.find("Ann");
    if (iter != std::end(people))
        std::cout << iter->first << " is " << iter->second << std::endl;
    // find repeated elements
    auto iter1 = people.lower_bound("Ann");
    auto iter2 = people.lower_bound("Ann");
    if (iter1 != std::end(people))
    {
        for (auto iter = iter1; iter != iter2; ++iter)
            std::cout << iter->first << " is " << iter->second << std::endl;
    }
    // count repeated element
    auto n = people.count("Jack"); // Returns 2
    cout << "count of Jack: " << n << endl;
}

void UseUnorderedMap()
{

    cout << __FILE__ << ":" << __FUNCTION__ << endl;

    string name = "alice";
    int id = 10001;
    std::unordered_map<string, int> unomap; // 创建一个key为string类型，value为int类型的unordered_map
    unomap.emplace(name, id);               // 使用变量方式，插入一个元素
    unomap.emplace("bob", 10002);           // 也可以直接写上key和value的值
    unomap.insert({"kitty", 10003});

    for (auto x : unomap) // 遍历整个map，输出key及其对应的value值
        cout << x.first << ": " << x.second << endl;

    for (auto x : unomap) // 遍历整个map，并根据其key值，查看对应的value值
        cout << x.first << ": " << unomap[x.first] << endl;
}

int main()
{
    UseVector();
    UseDeque();
    UseList();
    UseSet();
    UseMap();
    UseMultiMap();
    UseUnorderedMap();

    return 0;
}