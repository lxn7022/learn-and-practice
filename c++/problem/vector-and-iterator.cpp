#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

struct Point
{
    /* data */
    uint32_t x;
    uint32_t y;
    uint32_t z;

    friend std::ostream &operator<<(std::ostream &stream, const Point &p)
    {
        stream << "Point("
               << p.x << "," << p.y << "," << p.z << ")";
        return stream;
    }
};

/*
*  问题：给定一个vector，保留每个元素的迭代器指针，
*  如果vector中的元素被删除后，是否还能通过迭代器指针访问到？
*/

// visit the deleted elem by iterator
void visit_deleted_elem()
{

    vector<Point> vec_of_point;
    vector<vector<Point>::iterator> vec_of_iter;

    auto p = Point{1, 2, 3};
    cout << p << endl;

    for (uint32_t i = 0; i < 5; i++)
    {
        vec_of_point.push_back(Point{i, i, i});
    }
    // display
    for (auto &it : vec_of_point)
    {
        cout << it;
    }
    cout << endl;
    // 保留迭代器
    for (vector<Point>::iterator it = vec_of_point.begin(); it != vec_of_point.end(); it++)
    {
        vec_of_iter.push_back(it);
    }
    // 删除一个元素
    vec_of_point.pop_back();
    // display vec_of_point
    for (auto &it : vec_of_point)
    {
        cout << it;
    }
    cout << endl;
    // display vec_of_iter,验证被删除元素是否能被访问
    for (auto &it : vec_of_iter)
    {
        cout << (*it);
    }
    cout << endl;
}

int main()
{
    visit_deleted_elem();
}