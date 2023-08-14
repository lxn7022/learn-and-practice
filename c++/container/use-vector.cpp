#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <random>
#include <string.h>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

template<class T>
void Print(const vector<T>& vec)
{
	cout << "capacity:" << vec.capacity() << endl;
	cout << "size:" << vec.size() << endl;
	typename vector<T>::const_iterator it = vec.begin();

	for (; it != vec.end(); it++)
	{
		cout << setw(4) << *it;
	}

	cout << endl;
}

int randint()
{
    int min = 0;
    int max = 1000;
    // 加上static，只初始化一次
    static default_random_engine e(time(NULL));
    uniform_int_distribution<int> u(min, max);
    return u(e);
}

struct Elem{
    int a;
    int b;

    //bool operator()(const Elem &e1, const Elem &e2);

    friend std::ostream &operator<<(std::ostream &stream, const Elem &e)
    {
        stream << "Elem("
               << e.a << "," << e.b  << ")";
        return stream;
    }
};

struct elem_gt{
    bool operator()(const Elem &e1, const Elem &e2){
        // todo
        return true;
    }
};



class TestVector
{
public:

    void use_constructor()
    {
        cout << __FILE__ << ":" << __FUNCTION__ << endl; 
        int ar[] = { 1,2,3,4,5,6,7,8,9 };
        int n = sizeof(ar) / sizeof(ar[0]);

        vector<int> va;
        vector<int> vb(10);
        vector<int> vc(10,5);
        vector<int> vd(ar, ar + n);
        vector<int> ve(vd);
        vector<int> vf = { 1,2,3,4,5 };

        vector<string> vv = { "hello","world","This","is" };
        vector<string> vg;
        vector<string> vh;

        vg = vv;
        vh.assign(3, "This");

        Print(va);
        Print(vb);
        Print(vc);
        Print(vd);
        Print(ve);
        Print(vf);
        Print(vg);
        Print(vh);
    }

    void use_iterator()
    {
        cout << __FILE__ << ":" << __FUNCTION__ << endl; 

        vector<string> va = { "Hello","World","This","Is" };
        Print(va);

        vector<string>::iterator s1 = va.begin();
        vector<string>::iterator s2 = va.end() - 1;
        vector<string>::const_reverse_iterator s3 = va.rbegin();
        vector<string>::const_reverse_iterator s4 = va.rend() - 1;

        cout << "va.begin()：" << *s1 << endl;
        cout << "va.end()：" << *s2 << endl;
        cout << "va.rbegin()：" << *s1 << endl;
        cout << "va.rend()：" << *s2 << endl;
    }

    void push_and_sort()
    {
        cout << __FILE__ << ":" << __FUNCTION__ << endl; 
        vector<Elem> vec;
        for (int i = 0; i < 10; i++){
            vec.push_back(Elem{randint(), randint()});
        }
        for(auto &it:vec){
            cout << it <<endl;
        }
        cout << "--------" << endl;
        // sort by lambda
        auto cmp = [](const Elem &e1, const Elem &e2)
        {
            if( e1.a > e2.a ){
                return true;
            }
            if (e1.a < e2.a ){
                return false;
            }
            // e1.a == e2.a
            if( e1.b > e2.b ){
                return true;
            }
            if (e1.b < e2.b ){
                return false;
            }
            // e1==e2
            return true;   
 
        };
        std::sort(vec.begin(), vec.end(), cmp);
        for(auto &it:vec){
            cout << it <<endl;
        }
        
    }

    void use_size()
    {
        cout << __FILE__ << ":" << __FUNCTION__ << endl;  
        vector<int> va = { 1,2,3,4,5,6,7,8,9 };
        
        cout << "va.empty()：" << va.empty() << endl;
        cout << "va.max_size()：" << va.max_size() << endl;
        cout << "va.size()：" << va.size() << endl;
        cout << "va.capacity()：" << va.capacity() << endl;
    }

    void use_insert()
    {
        cout << __FILE__ << ":" << __FUNCTION__ << endl;   
        vector<int> va = { 1,2,3,4,5,6,7,8,9 };      
        Print(va);

        va.clear();
        Print(va);

        va.insert(va.begin(), 11, 3);
        Print(va);
    }

    void use_at()
    {
        cout << __FILE__ << ":" << __FUNCTION__ << endl;  
        vector<int> va = { 1,2,3,4,5,6,7,8,9 };
        
        cout << "va.at(1)：" << va.at(1) << endl;
        cout << "va[1]：" << va[1] << endl;
        cout << "va.front()：" << va.front() << endl;
        cout << "va.back()：" << va.back() << endl;
        cout << "*va.data()：" << *va.data() << endl;
    }

    void testAll(){
        use_constructor();
        use_iterator();
        use_size();
        use_insert();
        use_at();
        push_and_sort();
    }
};

int main()
{
    TestVector test;
    test.testAll();

    return 0;
}
