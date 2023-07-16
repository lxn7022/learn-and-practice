#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

void forrange()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;
    // use auto on for range
    std::vector<int> vec(10);
    std::iota(vec.begin(), vec.end(), 19); // 19为初始值
    // c++11: for range
    for (auto n : vec)
        std::cout << n << ' ';
    cout << endl;
    // before c++11
    for (auto iter = vec.begin(); iter != vec.end(); iter++)
    {
        cout << *iter << ' ';
    }
    cout << endl;
}

void algo()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;

    std::vector<int> v = {3, 9, 1, 4, 2, 5, 9};
    auto result = std::minmax_element(v.begin(), v.end());
    std::cout << "min element at: " << *(result.first) << '\n';
    std::cout << "max element at: " << *(result.second) << '\n';
}

int main()
{
    forrange();
    algo();
    return 0;
}