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


class TestMap
{
public:
    void use_map(){

    // 初始化-----------------------------------------------------------------------------------
        pair<string, string> p1("sc0301","小杨");	            // 方式一，创建一个pair名为p1
        pair<string, string> p2 = make_pair("sc0302", "小马");	// 方式二，make_pair函数返回一个用"sc0302"和 "小马"初始化的pair
        pair<string, string> p3("sc0303", "小王");
        pair<string, string> p4("sc0304", "小何");

        map<string, string> m1;                 // 创建一个空map
        map<string, string> m2{ p1,p2,p3,p4 };  // 创建一个包含键值对p1、p2、p3、p4的map
        map<string, string> m3{ {"sc0301","小杨"},{"sc0302", "小马"},{"sc0303", "小王"},{"sc0304", "小何"} }; // 效果同上一句
        map<string, string> m4(m2);   // 创建一个map，m4中包含和m2一样的元素
        map<string, string> m5 = m2;  // 创建一个map，m5中包含和m2一样的元素

	// 访问元素-----------------------------------------------------------------------------------
        string p2_name = m2["sc0302"];	   // 得到学号（关键字）"sc0302"对应的姓名（值）	
        string p3_name = m2.at("sc0303");  // 得到学号"sc0303"对应的姓名	      
        
        map<string, string>::iterator it1 = m2.begin();	 // 得到指向m2首元素的迭代器
        map<string, string>::iterator it2 = m2.end();    // 得到指向m2尾元素的下一个位置的迭代器
        pair<string, string> p11 = *it1;   // 得到m2的首元素{"sc0301","小杨"}
        string p1_ID = it1->first;         // 得到m2的首元素{"sc0301","小杨"}的fisrt成员
        string p1_name = it1->second;	   // 得到m2的首元素{"sc0301","小杨"}的second成员

	// 遍历容器-----------------------------------------------------------------------------------
        for (auto it_b = m2.begin(), it_e = m2.end(); it_b != it_e;++it_b) {
            pair<string, string> current = *it_b;
            cout << "学号：" << it_b->first << "; 姓名:" << it_b->second << endl;
            // 上面这一句等同于下面这一句
            cout << "学号：" << current.first << "; 姓名:" << current.second << endl;
        }

        for (auto p : m2) {
            cout << "学号：" << p.first << "; 姓名:" << p.second << endl;
        }

	// 添加、修改元素-----------------------------------------------------------------------------------
        m1.insert(p1);	                   // 在map中插入已有的pair
        m1.insert({ "sc0302", "小马" });   // 插入键值对{ "sc0302", "小马" }
        m1.insert(pair<string, string> ("sc0303", "小王"));  // 创建一个无名pair对象，并插入到map中	
        m1.insert(make_pair("sc0303", "小王"));              // 要插入的关键字已在容器中，emplace/insert什么都不做
        m1.insert(map<string, string>::value_type("sc0303", "小王"));   // 要插入的关键字已在容器中，emplace/insert什么都不做
        m1["sc0304"] = "小何";             // 如果key不存在则插入该键值对，如果key已存在则修改该key对应的value。

        m1.emplace(p1);			                             // 要插入的关键字已在容器中，emplace/insert什么都不做
        m1.emplace(pair<string, string>("sc0303", "小王"));  // 要插入的关键字已在容器中，emplace/insert什么都不做

	// 删除元素-----------------------------------------------------------------------------------
        m1.erase("sc0301");		  // 删除关键字为"sc0301"的元素
        auto iter = m1.begin();   // 指向m2的首元素的迭代器
        m1.erase(iter);           // 删除迭代器指向的元素
        auto iter1 = m1.begin(), iter2 = m1.end();
        m1.erase(iter1, iter2);   // 删除迭代器iter1、iter2指向的范围中的元素
        m2.clear();               // 删除容器中的全部元素

	// 大小-----------------------------------------------------------------------------------
        int s = m3.size();    // 获得m1的大小
        bool e = m3.empty();  // 若m1为空返回值为true，否则返回值为false

	// 查找-----------------------------------------------------------------------------------
        map<string, string>::iterator it = m4.find("sc0301");  // 查找关键字为"sc0301"的元素,返回一个迭代器
        if (it == m4.end()) {         // 若"sc0301"不在容器中，则it等于尾后迭代器
            cout << "未找到！" << endl;
        }
        else {
            pair<string, string> result1 = *it;	// 找到了
        }
        
        {
            // 下面的写法更简单
            auto it = m4.find("sc0303");
            if(it != m4.end()){
                cout << "Found: " << it->first << ": " << it->second << endl;
            }else{
                cout << "Not Found! " << endl;
            }
        }
        
        int result2 = m4.count("sc0305");  // 查找关键字为"sc0301"的元素,返回关键字等于"sc0301"的元素数量
        if (result2==0) {
            cout << "未找到！" << endl;
        }
        else {
            cout << "找到了！" << endl;
        }

        map<string, string>::iterator it_up = m4.upper_bound("sc0301");  // 返回一个迭代器，指向第一个关键字大于"sc0301"的元素
        pair<string, string> result3 = *it_up;

    }


    void testAll(){
        use_map();

    }
};

int main()
{
    TestMap test;
    test.testAll();

    return 0;
}

