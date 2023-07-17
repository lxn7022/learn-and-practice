#include <iostream>
#include <memory>

using namespace std;

void UseAutoPtr()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;

    // test copy constructor
    std::auto_ptr<int> sp1(new int(8));
    std::auto_ptr<int> sp2(sp1);
    if (sp1.get() != NULL)
    {
        std::cout << "sp1 is not emptya." << std::endl;
    }
    else
    {
        std::cout << "sp1 is empty." << std::endl;
    }

    if (sp2.get() != NULL)
    {
        std::cout << "sp2 is not empty." << std::endl;
    }
    else
    {
        std::cout << "sp2 is empty." << std::endl;
    }

    // 测试赋值构造
    std::auto_ptr<int> sp3(new int(8));
    std::auto_ptr<int> sp4;
    sp4 = sp3;
    if (sp3.get() != NULL)
    {
        std::cout << "sp3 is not empty." << std::endl;
    }
    else
    {
        std::cout << "sp3 is empty." << std::endl;
    }

    if (sp4.get() != NULL)
    {
        std::cout << "sp4 is not empty." << std::endl;
    }
    else
    {
        std::cout << "sp4 is empty." << std::endl;
    }
}

//------------------------------------------
// c++11不支持make_unique，这里自定义一个
template <typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts &&...params)
{
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}

void UseUniquePtr()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;

    // unique_ptr 与移动构造move
    std::unique_ptr<int> sp1(make_unique<int>(123));
    std::unique_ptr<int> sp2(std::move(sp1));
    std::unique_ptr<int> sp3;
    sp3 = std::move(sp2);

    /************************/

    // 通过unique_ptr持有数组对象，创建10个int类型的堆对象
    // 形式1
    std::unique_ptr<int[]> up1(new int[10]);

    // 形式2
    std::unique_ptr<int[]> up2;
    up2.reset(new int[10]);

    // 形式3, not work.
    // std::unique_ptr<int[]> up3(make_unique<int[]>(10));

    for (int i = 0; i < 10; ++i)
    {
        up1[i] = i;
        up2[i] = i;
        // up3[i] = i;
    }
    for (int i = 0; i < 10; ++i)
    {
        std::cout << up1[i] << "," << up2[i] << "" << std::endl;
    }
}

//----------------------------------------------
class A
{
public:
    A()
    {
        std::cout << "A constructor" << std::endl;
    }
    ~A()
    {
        std::cout << "A destructor" << std::endl;
    }
};

void UseSharedPtr()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;

    // 初始化方式1
    std::shared_ptr<int> sp1(new int(123));

    // 初始化方式2
    std::shared_ptr<int> sp2;
    sp2.reset(new int(123));

    // 初始化方式3
    std::shared_ptr<int> sp3;
    sp3 = std::make_shared<int>(123);

    /*********************/
    // 初始化方式1
    std::shared_ptr<A> shp1(new A());

    std::cout << "use count: " << shp1.use_count() << std::endl;

    // 初始化方式2
    std::shared_ptr<A> shp2(shp1);
    std::cout << "use count: " << shp1.use_count() << std::endl;

    shp2.reset();
    std::cout << "use count:" << shp1.use_count() << std::endl;

    {
        std::shared_ptr<A> shp3 = shp1;
        std::cout << "use count:" << shp1.use_count() << std::endl;
    }

    std::cout << "use count: " << shp1.use_count() << std::endl;
}

void UseWeakPtr()
{
    cout << __FILE__ << ":" << __FUNCTION__ << endl;

    // 创建一个std:sharedptr对象
    std::shared_ptr<int> sp1(new int(123));
    std::cout << "use count:" << sp1.use_count() << std::endl;

    // 通过构造函数得到一个std::weakptr对象
    std::weak_ptr<int> sp2(sp1);
    std::cout << "use count:" << sp1.use_count() << std::endl;

    // 通过赋值运算符得到一个std::weakptr对象
    std::weak_ptr<int> sp3 = sp1;
    std::cout << "use count:" << sp1.use_count() << std::endl;

    // 通过一个std::weak_ptr对象得到另外一个std:weakptr对象 std::weak ptr<int>sp4=sp2;
    std::cout << "use count: " << sp1.use_count() << std::endl;
}

int main()
{
    UseAutoPtr();
    UseUniquePtr();
    UseSharedPtr();
    UseWeakPtr();
    return 0;
}
