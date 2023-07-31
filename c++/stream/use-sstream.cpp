#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <strstream>

using namespace std;


class TestSstream{
public:

    void readfield(){
        std::fstream fin("split.txt", std::ios::in);
        char line[1024]={0};
        std::string x = "";
        std::string y = "";
        std::string z = "";
        while(fin.getline(line, sizeof(line)))
        {
            std::stringstream word(line);
            word >> x;
            word >> y;
            word >> z;
            std::cout << "x: " << x << std::endl;
            std::cout << "y: " << y << std::endl;
            std::cout << "z: " << z << std::endl;
        }
        fin.clear();
        fin.close();

    }

    void strconcat(){
        cout << __FILE__ << ":" << __FUNCTION__ << endl;

        stringstream line;
        line << "alice"
             << "," << 123 << ","
             << "female";
        cout << line.str() << endl;
    }

    void testAll(){
        readfield();
        strconcat();
    }
};

class TestStrstream{
public:
    void readfield(){
        cout << __FILE__ << ":" << __FUNCTION__ << endl;

        const char *row = "alice 13 female";
        istrstream ins(row);
        string name;
        int age;
        string gender;

        ins >> name >> age >> gender;

        cout << "name:" << name << "--"
             << "age:" << age << "--"
             << "gender:" << gender << endl;
    }

    void testAll(){
        readfield();
    }
};

int main()
{
    TestSstream test;
    test.testAll();

    TestStrstream testt;
    testt.testAll();

}
