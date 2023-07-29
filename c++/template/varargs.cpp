#include <iostream>
using namespace std;

template <typename T>
T foo(const T &a, const T b)
{
    return a * b;
}

template <typename T>
T foo(T a, T b, T c)
{
    return a * b * c;
}

template <typename T>
T foo(T a, T b, T c, T d)
{
    return a * b * c * d;
}

template <typename T>
T foo(T a, T b, T c, T d, T e)
{
    return a * b * c * d * e;
}

//--------------------------
//

template <typename T>
T bar(const T &m)
{
    return m;
}

template <typename T, typename... Args>
T bar(const T &m, const Args &...args)
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;

    return m * bar(args...);
}

//--------------------

void test_foo()
{

    std::cout << foo(1, 2) << std::endl;          // 2
    std::cout << foo(1, 2, 3) << std::endl;       // 6
    std::cout << foo(1, 2, 3, 4) << std::endl;    // 24
    std::cout << foo(1, 2, 3, 4, 5) << std::endl; // 120
}

void test_bar()
{

    std::cout << bar(1) << std::endl;                      // 1
    std::cout << bar(1, 2) << std::endl;                   // 2
    std::cout << bar(1, 2, 3) << std::endl;                // 6
    std::cout << bar(1, 2, 3, 4) << std::endl;             // 24
    std::cout << bar(1, 2, 3, 4, 5) << std::endl;          // 120
    std::cout << bar(1, 2, 3, 4, 5, 6) << std::endl;       // 720
    std::cout << bar(1, 2, 3, 4, 5, 6, 7) << std::endl;    // 5040
    std::cout << bar(1, 2, 3, 4, 5, 6, 7, 8) << std::endl; // 40320
}

int main()
{
    test_foo();
    test_bar();

    return 0;
}
