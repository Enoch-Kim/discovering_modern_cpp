/*
    20-01-21 김유현
    cpp 교재 <모던 C++입문> 1강
    1.1 ~ 1.2

    컴파일 명령어 make chapter1 && ./chapter1
*/ 
#include <iostream>
#include <complex>

const double pi = 3.141592;

int main()
{
    std::cout << "The answer to the Ultimate Question of Life, \n"
              << "the Universe, and Everything is: "
              << std::endl << 6*7 << std::endl;

    unsigned char a = '3';
    unsigned short s = 12312;
    std::cout << s;
    std::cout << "what's the matter" << std:: endl;
    
    std::complex<float> z(1.3, 2.4), z2;
    z2 = 2.0f*z;
    std::cout << z  << "\n"
              << z2 << z+z2 << std::endl;

    long double b1 = 0.3333333333333333;
    long double b2 = 0.3333333333333333l;

    std::cout << b1 << std::endl
              << b2 << std::endl;

    int i1 = 3.14;
    int i2 =  3.14 ;
    // float f3 = { 3.14};

    std::cout << i1 << std::endl
              << i2 << std::endl;
            //   << f3 << std::endl;

    unsigned u2 = 3;
    // unsigned u2n = { -3 };

    std::cout << u2 << std::endl;
            //   << u2n << std::endl;

    // unsigned ut = {3};
    // int it = {2};
    // unsigned u4 = {it};
    // int i3={ut};

    // std::cout << ut << std::endl
            //   << it << std::endl
            //   << u4 << std::endl
            //   << i3 << std::endl;

    std::string ss = "fsfsdfsdfs";

    bool bo = true;
    std::cout << "bo's " << bo << std::endl;

    signed int count = -1221;
    std::cout << "count is " << count << std::endl;

    const std::string co = "constants always declare with initialize";
    std::cout << co << std::endl;

    long double three1 = 0.33333333333333;
    long double three2 = 0.33333333333333l;
    std :: cout << three1 << std::endl
                << three2 << std::endl;

    
    int o1 = 034;
    int o2 = 0xfa;
    int o3 = 0b111011;
    int o4 = 12123;
    std::cout << o1 << std::endl
              << o2 << std::endl
              << o3 << std::endl
              << "o4 is " << o4 << std::endl;

    std::cout << "pi is " << pi << std::endl;

    int pi = 3.14;

    std::cout << "pi is " << pi << std::endl;

    return 0;
}