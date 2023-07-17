#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>

using namespace std;

struct Goods
{
    string _name;  // 名字
    double _price; // 价格
    int _evaluate; // 评价

    Goods(const char *str, double price, int evaluate)
        : _name(str), _price(price), _evaluate(evaluate)
    {
    }
};

ostream &operator<<(ostream &os, Goods &g)
{
    os << g._name << ": " << g._price << ": " << g._evaluate << endl;
    return os;
}

struct Compare1
{
    bool operator()(const Goods &gl, const Goods &gr)
    {
        return gl._evaluate < gr._evaluate;
    }
};

struct ComparePriceLess
{
    bool operator()(const Goods &gl, const Goods &gr)
    {
        return gl._price < gr._price;
    }
};

struct ComparePriceGreater
{
    bool operator()(const Goods &gl, const Goods &gr)
    {
        return gl._price > gr._price;
    }
};

int main()
{

    std::vector<Goods> v = {Goods("苹果", 2.1, 5), {"香蕉", 3, 4}, {"橙子", 2.2, 3}, {"菠萝", 1.5, 4}};
    for (auto n : v)
        cout << n;
    // sort(v.begin(), v.end()); 自定义类型没重载<不能用less或者greater
    // 1.正常用仿函数写
    std::sort(v.begin(), v.end(), Compare1());
    std::sort(v.begin(), v.end(), ComparePriceLess());
    std::sort(v.begin(), v.end(), ComparePriceGreater());

    // 2.用lambda代替仿函数：
    // （1）常规写法
    auto com1 = [](const Goods &g1, const Goods &g2)
    { return g1._price < g2._price; };
    sort(v.begin(), v.end(), com1);

    // （2）匿名对象写法
    std::sort(v.begin(), v.end(), [](const Goods &g1, const Goods &g2)
              { return g1._price < g2._price; });
    cout << endl;
    for (auto n : v)
        cout << n;

    sort(v.begin(), v.end(), [](const Goods &g1, const Goods &g2)
         { return g1._price > g2._price; });
    cout << endl;
    for (auto n : v)
        cout << n;

    sort(v.begin(), v.end(), [](const Goods &g1, const Goods &g2)
         { return g1._evaluate < g2._evaluate; });
    cout << endl;

    sort(v.begin(), v.end(), [](const Goods &g1, const Goods &g2)
         { return g1._evaluate > g2._evaluate; });
    cout << endl;

    return 0;
}