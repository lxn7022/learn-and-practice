#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <random>
#include <string.h>
#include <vector>
#include <ctime>

using namespace std;


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
    void push_and_sort(){

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

    void testAll(){
        push_and_sort();
    }
};

int main()
{
    TestVector test;
    test.testAll();

    return 0;
}
