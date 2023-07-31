#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

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
    void testAll(){
        readfield();
    }
};

int main()
{
    TestSstream test;
    test.testAll();
 
}
