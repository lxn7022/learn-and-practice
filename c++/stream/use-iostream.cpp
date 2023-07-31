#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;


class TestIostream{
public:

    void multiread(){
        string name;
        int age;
    
        // Take multiple input using cin
        cin >> name >> age;
    
        // Print output
        cout << "Name : " << name << endl;
        cout << "Age : " << age << endl;
    
    }

    void readline(){
        char line[1024] = {0};
    
        while (cin.getline(line, sizeof(line)))
        {
            // Print output
            cout <<"input>>:" <<line << endl;

            string strline = line;
            if(strline.find("EOF")!=strline.npos){
                break;
            }
        }
    }

    void testAll(){
        multiread();
        readline();
    }
};

int main()
{
    TestIostream test;
    test.testAll();
 
}