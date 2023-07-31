#include <iostream>
using namespace std;


namespace A {
    int a = 100;
}
namespace B {
    int a = 200;
}

namespace A {
    namespace C {
        int a = 2000;
    }

    void func();
}

void A::func()//成员函数 在外部定义的时候 记得加作用域
{
    //访问命名空间的数据不用加作用域
    cout<<"func遍历a = "<<a<<endl;
}

void test_Namespace()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;

    //A::a  a是属于A中
    cout<<"A中a = "<<A::a<<endl;//100
    cout<<"B中a = "<<B::a<<endl;//200
    cout << "A::B::a= " << A::C::a << endl; //2000

    A::func();
}

int main()
{
    test_Namespace();
}
