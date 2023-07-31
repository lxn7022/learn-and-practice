#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class TestFstream{
public:

    void readline(){
        cout << __FILE__ << ":" << __FUNCTION__ << endl;

        fstream file("./use-fstream.cpp", ios::in);
        if(!file){
            cout << "无法找到这个文件！" << endl;
            return; 
        }

        /**********
        fstream file;
        file.open("./use-fstream.cpp", ios::in);
        if (!file.is_open())
        {
            cout << "无法找到这个文件！" << endl;
            return;
        }
        **********/
        string line;
        while (getline(file, line)) //getline是<string>中的函数
        {
            cout << line <<endl;
        }
        file.close();

    }

    void readchar(){
        cout << __FILE__ << ":" << __FUNCTION__ << endl;

        fstream file("./use-fstream.cpp", ios::in);
        if(!file){
            cout << "无法找到这个文件！" << endl;
            return; 
        }
 
        string context;
        char ch;
        while(file.get(ch)){
            context += ch;
        }
        file.close();
        cout << context;
    }

    void writeline(){
        cout << __FILE__ << ":" << __FUNCTION__ << endl;

        fstream file1("./use-fstream.cpp", ios::in);
        if(!file1){
            cout << "无法找到这个文件!" << endl;
            return; 
        }

        fstream file2("./use-fstream.output", ios::out | ios::trunc);
        if(!file2){
            cout << "无法找到这个文件！" << endl;
            return; 
        }

        string line;
        while (getline(file1, line)) //getline是<string>中的函数
        {
            // 给每一行增加前缀
            file2 << ">>>>>" << line <<endl;
        }
        file1.close();
        file2.close();
    }

    void testAll(){
        TestFstream test;
        test.readline();
        test.readchar();
        test.writeline();

    }
};

int main()
{
    TestFstream test;
    test.testAll();
 
}