#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <map>
#include <functional>
#include <memory>

using namespace std;

class Foo
{
public:
    Foo() = default;
    ~Foo() = default;
    Foo(const Foo& foo) = delete;
    Foo(Foo&& foo) = default;
    Foo& operator = (const Foo& foo) = delete;
    Foo& operator = (Foo&& foo) = default;
};

int main()
{
    Foo foo;
    //Foo foo1(foo)；    // 编译报错，因为Foo(const Foo& foo) = delete;删除了
    //Foo foo2 = foo     // 编译报错，因为Foo& operator = (const Foo& foo) = delete;

    return 0;
}
