#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <map>
#include <functional>
#include <memory>

using namespace std;

void UseAutoDecltype()
{
}

//-----------------------------------------------
struct Foo
{
    Foo(int num) : num_(num) {}
    void print_add(int i) const { std::cout << num_ + i << '\n'; }
    int num_;
};

void print_num(int i) { std::cout << i << '\n'; }

struct PrintNum
{
    void operator()(int i) const { std::cout << i << '\n'; }
};

void UseFunction()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;

    // 存储自由函数
    std::function<void(int)> f_display = print_num;
    f_display(-9);

    // 存储 lambda
    std::function<void()> f_display_42 = []()
    { print_num(42); };
    f_display_42();

    // 存储到 std::bind 调用的结果
    std::function<void()> f_display_31337 = std::bind(print_num, 31337);
    f_display_31337();

    // 存储到成员函数的调用
    std::function<void(const Foo &, int)> f_add_display = &Foo::print_add;
    const Foo foo(314159);
    f_add_display(foo, 1);
    f_add_display(314159, 1);

    // 存储到数据成员访问器的调用
    std::function<int(Foo const &)> f_num = &Foo::num_;
    std::cout << "num_: " << f_num(foo) << '\n';

    // 存储到成员函数及对象的调用
    using std::placeholders::_1;
    std::function<void(int)> f_add_display2 = std::bind(&Foo::print_add, foo, _1);
    f_add_display2(2);

    // 存储到成员函数和对象指针的调用
    std::function<void(int)> f_add_display3 = std::bind(&Foo::print_add, &foo, _1);
    f_add_display3(3);

    // 存储到函数对象的调用
    std::function<void(int)> f_display_obj = PrintNum();
    f_display_obj(18);
}

//-------------------------------------
void f(int n1, int n2, int n3, const int &n4, int n5)
{
    std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << std::endl;
}

int g(int n1) { return n1; }

struct Foo2
{
    void print_num(int n1, int n2) { std::cout << n1 + n2 << std::endl; }
    int data = 10;
};

void UseBind()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;

    using namespace std::placeholders; // 针对 _1, _2, _3...

    // nd演示参数重排序和按引用传递
    int n = 7;
    // （ _1 与 _2 来自 std::placeholders ，并表示将来会传递给 f1 的参数）
    auto f1 = std::bind(f, _2, 42, _1, std::cref(n), n);
    n = 10;
    f1(1, 2, 1001); // 1 为 _1 所绑定， 2 为 _2 所绑定，不使用 1001
                    // 进行到 f(2, 42, 1, n, 7) 的调用

    // 嵌套 bind 子表达式共享占位符
    auto f2 = std::bind(f, _3, std::bind(g, _3), _3, 4, 5);
    f2(10, 11, 12); // 进行到 f(12, g(12), 12, 4, 5); 的调用

    // 绑定指向成员函数指针
    Foo2 foo;
    auto f3 = std::bind(&Foo2::print_num, &foo, 95, _1);
    f3(5);

    // 绑定指向数据成员指针
    auto f4 = std::bind(&Foo2::data, _1);
    std::cout << f4(foo) << std::endl;

    // 智能指针亦能用于调用被引用对象的成员
    std::cout << f4(std::make_shared<Foo2>(foo)) << std::endl;
}

//-------------------------------------

void UseForAuto()
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
void UseLambda()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;

    std::vector<int> v = {3, 9, 1, 4, 2, 5, 9};
    for_each(v.begin(), v.end(),
             [](int n)
             { cout << n << " "; });
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
    UseFunction();
    UseBind();
    UseLambda();
    UseForAuto();
    algo();
    return 0;
}