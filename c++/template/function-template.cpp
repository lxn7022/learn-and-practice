#include <iostream>
using namespace std;

/*函数模板 类型参数化（作用）
 * C++的另一种编程思想称为 泛型编程 主要利用技术就是模板
 * C++提供两种机制：函数模板 和 类模板
 * 函数模板作用：通过建立一个通用函数，其 返回值类型 和 形参类型 可以不具体制定 用一个虚拟的类型来代表
 * 语法：
 * template<typename T>
 * 函数声明或定义
 * template -- 声明创建模板
 * typename -- 表面其后面的符号是一种数据类型，可以用class代替
 * T -- 通用的数据类型，名称可以替换，通常为大写字母
 */

// 两个整型交换
void swapInt(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

// 交换两个浮点数据
void swapDouble(double &a, double &b)
{
    double temp = a;
    a = b;
    b = temp;
}

// 利用模板实现交换函数
// 声明一个模板 告诉编译器后面代码中紧跟着的T不要报错，T是一个通用数据类型
template <typename T>
void TSwap(T &a, T &b)
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;

    T temp = a;
    a = b;
    b = temp;
}

void test_swap()
{
    int a = 10;
    int b = 20;
    // swapInt(a, b);
    /*利用模板交换
     * 两种方式使用函数模板
     * 1、自动类型推导
     */
    // mySwap(a, b);
    cout << "a = " << a << endl; // 20
    cout << "b = " << b << endl; // 10
    // 2、显式··；··；·：指定类型
    TSwap<int>(a, b);
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    double c = 1.1;
    double d = 2.2;
    // swapDouble(c, d);
    TSwap<double>(c, d);
    cout << "c = " << c << endl; // 2.2
    cout << "d = " << d << endl; // 1.1
}

//---------------------------------
// 选择排序
template <typename T>
void TSort(T arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        int max = i; // 认定最大值的下标
        for (int j = i + 1; j < len; j++)
        {
            // 认定的最大值 比 遍历出的数值 要小，说明 j 下标的元素才是真正的最大值
            if (arr[max] < arr[j])
            {
                max = j; // 更新最大值下标
            }
        }
        if (max != i)
        {
            // 如果最大数下标不是 i ，交换max和i元素
            TSwap(arr[max], arr[i]);
        }
    }
}

// 打印数组模板
template <class T>
void printArray(T arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << "  ";
    }
    cout << endl;
}

void test_TSort()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;

    // 测试char数组
    char charArr[] = "bafsrd";
    int len = sizeof(charArr) / sizeof(char);
    TSort(charArr, len);
    printArray(charArr, len);

    // 测试int数组
    int intArr[] = {7, 5, 1, 3, 9, 2, 4, 6, 8};
    int lens = sizeof(intArr) / sizeof(int);
    TSort(intArr, lens);
    printArray(intArr, lens);
}

//---------------------------------

/*普通函数与函数模板的区别
 * 1、普通函数调用时可以发生自动类型转换（隐式类型转换）
 * 2、函数模板调用时，如果利用自动类型推导，不会发生隐式类型转换
 * 3、如果利用显示指定类型的方式，可以发生隐式类型转换
 */

// 普通函数
int myAdd01(int a, int b)
{
    return a + b;
}

// 函数模板
template <class T>
int myAdd02(T a, T b)
{
    return a + b;
}

void test_MyAdd()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;

    int a = 10;
    int b = 20;
    char c = 'c';

    cout << myAdd01(a, b) << endl; // 30
    // 109=10+99  a - 97  c - 99 自动类型转换
    cout << myAdd01(a, c) << endl;

    // 自动类型推导
    myAdd02(a, b);
    cout << myAdd02(a, b) << endl; // 30
    // myAdd02(a, c);报错，自动类型推倒时，不会发生隐式类型转换
    myAdd02<int>(a, c); // 正确，显示指定类型，可以发生隐式类型转换
}

//---------------------------------

/*普通函数与函数模板的调用规则
 * 1、如果函数模板和普通函数都可以实现，优先调用 普通函数（编译器有关）
 * 2、可以通过 空模板参数列表 来强制调用函数模板
 * 3、函数模板也可以发生 函数重载
 * 4、如果函数模板可以产生更好的匹配 优先调用 函数模板
 */

void myprint(int a, int b)
{
    cout << "调用的是普通函数！" << endl;
}

template <class T>
void myPrint(T a, T b)
{
    cout << "调用函数模板！" << endl;
}

template <class T>
void myPrint(T a, T b, T c)
{
    cout << "函数模板重载！" << endl;
}

void test_myPrint()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;

    int a = 10;
    int b = 20;
    // myPrint(a, b);//1、优先调用函数模板

    // 2、通过空模板参数列表 强制调用函数模板
    myPrint<>(a, b); // 函数模板

    // 3、函数模板 重载
    int c = 30;
    myPrint<>(a, b, c); // 函数模板重载
    myPrint(a, b, c);   // 函数模板重载

    // 4、如果函数模板可以产生更好的匹配 优先调用 函数模板
    char c1 = 'a';
    char c2 = 'b';
    myPrint(c1, c2); // 调用函数模板
}

int main()
{
    test_swap();
    test_TSort();
    test_MyAdd();
    test_myPrint();
    return 0;
}
