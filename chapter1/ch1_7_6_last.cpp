/*
    20-02-07 Enoch Kim
    cpp 교재 <모던 C++입문> 1강
    1.7.6의 마지막 예문
*/ 

#include <iostream>
#include <fstream>
#include <iomanip>

void with_io_exceptions(std::ios& io){
    io.exceptions(std::ios_base::badbit | std::ios_base::failbit);
}

int main () {

    std::ofstream outfile;
    with_io_exceptions(outfile);
    outfile.open("f.txt");
    double o1 = 5.2, o2 = 6.2;
    outfile << o1 << o2 << std::endl;           // 구분자 없음
    outfile.close();
    std::ifstream infile;
    with_io_exceptions(infile);
    infile.open("f.txt");
    int i1, i2;
    char c;
    infile >> i1 >> c >> i2;                    // 타입 불일치
    std::cout << "i1 = " << i1 << ", i2 = " << i2 << ".\n";

    /*
        숫자는 공백으로 나누자, 작성한 타입과 동일한 타입으로 읽자.
    */ 

    return 0;
}

