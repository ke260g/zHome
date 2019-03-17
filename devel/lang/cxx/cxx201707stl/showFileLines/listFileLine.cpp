#include<fstream>
#include<sstream>
#include<string>
#include<iostream>
#include<vector>
#include<list>
#include<algorithm>

using namespace std;

std::vector<std::string> split(const std::string & buf) {
    std::list<std::string> fsList; // file string linked-list

    for(auto delimL = buf.begin(), delimR = delimL; ; delimL = delimR) {
        delimR = find(delimL, buf.end(), '\n');
        fsList.emplace_back(delimL, ++delimR);
        if(delimR == buf.cend())
            break;
    }

    std::vector<std::string> fsVec(fsList.begin(), fsList.end());
    return fsVec;
}

/* read a file and split line into a vector */
std::vector<std::string> readfile(const std::string & filename) {
    std::ifstream inFile(filename);
    //string aline;
    //getline(inFile, aline); cout << aline << endl;
    //getline(inFile, aline); cout << aline << endl;

    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::string fstr = buffer.str();

    return split(fstr);
}

int main( int argc, char **argv ) {
    std::vector<std::string> fsVec = readfile("package.use");

    for(unsigned int i = 0; i < fsVec.size(); i++)
        std::cout << fsVec[i];

    std::cout << "----" << std::endl;
    std::cout << fsVec[2];
    return 0;
}
