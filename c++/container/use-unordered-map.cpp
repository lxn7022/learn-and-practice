#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <string.h>
#include <vector>
#include <ctime>

using namespace std;


class TestUnorderedMap
{
public:
    void use_construtor()
    {
        cout << __FILE__ << ":" << __FUNCTION__ << endl;

        // 默认构造函数：空 unordered_map
        unordered_map<int, string> m1;

        // 列表构造函数
        unordered_map<int, string> m2 = { {1,"This"},{2,"is"} };
        cout << "map.m2:" << endl;
        for (auto &it : m2)
        {
            cout << "key=" << it.first <<" val=" << it.second << endl;
        }

        // 复制构造函数
        unordered_map<int, string> m3 = m2;
        cout << "map.m3:" << endl;
        for (auto &it : m3)
        {
            cout << "key=" << it.first <<" val=" << it.second << endl;
        }

        // 移动构造函数
        unordered_map<int, string> m4 = move(m3);
        cout << "map.m4:" << endl;
        for (auto &it : m4)
        {
            cout << "key=" << it.first <<" val=" << it.second << endl;
        }

        // 范围构造函数, m3被move给m4后，m3变为了空，所以m5也为空
        unordered_map<int, string> m5(m3.begin(), m3.end());
        cout << "map.m5:" << endl;
        for(auto &it: m5){
            cout << "key=" << it.first << "val=" << it.second << endl;
        }
    }

    void use_iteraror()
    {
        cout << __FILE__ << ":" << __FUNCTION__ << endl; 
        unordered_map<int, string> m1 = { {1,"This"},{2,"is"},{3,"an"},{4,"apple"} };

        for (auto it = m1.begin(); it != m1.end(); it++)
        {
        cout << it->first <<"  " <<it->second << endl;
        }
    }

    void use_size()
    {
        cout << __FILE__ << ":" << __FUNCTION__ << endl;  
        unordered_map<int, string> m1 = { {1,"This"},{2,"is"},{3,"an"},{4,"apple"} };

        cout << "m1.empty():" << m1.empty() << endl;
        cout << "m1.size():" << m1.size() << endl;
        cout << "m1.max_size():" << m1.max_size() << endl;
    }

    void use_insert()
    {
        cout << __FILE__ << ":" << __FUNCTION__ << endl;   
        unordered_map<int, string> m1 = { {1,"This"},{2,"is"},{3,"an"},{4,"apple"} };
        unordered_map<int, string> m2;
        m1.insert({ 5,"three" });
        //c++17,insert_or_assign
        //m1.insert_or_assign(6,"windows" );
        m1.emplace(7, "u盘");
        //c++17,try_emplace
        //m1.try_emplace(8, "u盘");

        cout << "m1----------" << endl;
        for (auto it = m1.begin(); it != m1.end(); it++)
        {
            cout << it->first << "-->" << it->second << endl;
        }

        m1.erase(m1.begin());
        cout << "m1----------" << endl;
        for (auto it = m1.begin(); it != m1.end(); it++)
        {
            cout << it->first << "-->" << it->second << endl;
        }

        m1.swap(m2);
        cout << "m1----------" << endl;
        for (auto &it: m1)
        {
            cout << it.first << "-->" << it.second << endl;
        }
        cout << "m2----------" << endl;
        for (auto &it: m2)
        {
            cout << it.first << "-->" << it.second << endl;
        }
        
    }

    void use_find()
    {
        cout << __FILE__ << ":" << __FUNCTION__ << endl; 

        unordered_map<int, string> m1 = { {1,"This"},{2,"is"},{3,"an"},{4,"apple"},{1,"summer"} };

        cout << "m1----------" << endl;
        for (auto it = m1.begin(); it != m1.end(); it++)
        {
            cout << it->first << "-->" << it->second << endl;
        }

        string x = m1.at(1);
        cout << "m1.at(1): " << x << endl;

        m1[1] = "paper";//更新既存值
        m1[6] = "water";//插入新值

        cout << "m1.count(1): " << m1.count(1) << endl;
        
        auto it = m1.find(2);
        cout << it->first << "-->" << it->second << endl;

        auto range = m1.equal_range(1);
        for (it = range.first; it != range.second; ++it) 
        {
            std::cout << it->first << "--->"<< it->second << '\n';
        }

        cout << "m1----------" << endl;
        for (auto it = m1.begin(); it != m1.end(); it++)
        {
            cout << it->first << "-->" << it->second << endl;
        }
        
        if (m1.find(5) != m1.end())
        {
            cout << "success";
        }

    }

    void use_bucket()
    {
        cout << __FILE__ << ":" << __FUNCTION__ << endl;  
        unordered_map<int, string> m1 = { {1,"This"},{2,"is"},{3,"an"},{4,"apple"},{5,"summer"} };

        int n = m1.bucket_count();//返回桶数
        cout << "m1.bucket_count():  " << n << endl;
        
        for (int i = 0; i < n; i++)
        {
            cout << "bucket[" << i << "]" << ".size() " << m1.bucket_size(i) << " contains: ";
            for (auto it = m1.begin(i); it != m1.end(i); it++)
            {
                cout << "[" << it->first << "-->" << it->second << "]";
            }
            cout << endl;
        }
        cout << "1 in the bucket" << m1.bucket(1) << endl;
    }

    void use_load_factor()
    {
        cout << __FILE__ << ":" << __FUNCTION__ << endl;  
        unordered_map<int, string> m1 = { {1,"This"},{2,"is"},{3,"an"},{4,"apple"},{5,"summer"} };

        int n = m1.bucket_count();//返回桶数
        cout << "m1.bucket_count():  " << n << endl;
        
        for (int i = 0; i < n; i++)
        {        
            cout << "buckst's load_factor:(每个桶的平均元素数量) " << m1.load_factor() <<"  ";
            cout << "bucket[" << i << "]" << ".size():" << m1.bucket_size(i) << "contains: ";

            for (auto it = m1.begin(i); it != m1.end(i); it++)
            {
                cout << "[" << it->first << "-->" << it->second << "]";
            }
            cout << endl;
        }

        cout << "1 in the bucket" << m1.bucket(1) << endl;

        m1.rehash(16);
        for (int i = 0; i < n; i++)
        {
            cout << "buckst's load_factor:(每个桶的平均元素数量) " << m1.load_factor() << "  ";
            cout << "bucket[" << i << "]" << ".size()：" << m1.bucket_size(i) ;  
            cout << endl;
        }
    }

    void use_swap()
    {
        cout << __FILE__ << ":" << __FUNCTION__ << endl;   
        unordered_map<int, string> m1 = { {1,"This"},{2,"is"},{3,"an"},{4,"apple"},{5,"summer"} };
        unordered_map<int, string> m2 = { {1,"This"} };

        bool tag = (m1 == m2) ? true : false;
        cout << tag;

        swap(m1, m2);

        cout << "m1---------------" << endl;
        for (auto it = m1.begin(); it != m1.end(); it++)
        {
            cout << it->first << "-->" << it->second << endl;
        }
        
        cout << "m2---------------" << endl;
        for (auto it = m2.begin(); it != m2.end(); it++)
        {
            cout << it->first << "-->" << it->second << endl;
        }
    }


    void testAll(){
        use_construtor();
        use_iteraror();
        use_size();
        use_insert();
        use_find();
        use_bucket();
        use_load_factor();
        use_swap();
    }
};

int main()
{
    TestUnorderedMap test;
    test.testAll();

    return 0;
}

