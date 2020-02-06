/*
    20-01-21 김유현
    cpp 교재 <모던 C++입문> 1강
    1.3 ~ 

    컴파일 명령어 make ch1_3 && ./ch1_3
*/ 
#include <iostream>


int main () {

    const float r1 = 3.5, r2 = 7.3, pi = 3.14159;
    std::cout << "pi is " << pi << "\n";
    float area1 = r1 * r2 * pi;
    std::cout << "A circle of radius" << r1 << " has area "
              << area1 << "." << std::endl;
    std::cout << "The average of " << r1 << " and " << r2 << " is "
              << (r1 + r2) / 2 << "." << std::endl;

    // (3+5)++; 

    long l = 123456789012;
    long l2 = l + 1.0f - 1.0;
    long l3 = l + (1.0f - 1.0);

    std::cout << l << "\n" << l2 << "\n" << l3 << std::endl;

    -l;
    std::cout << l << "\n" << -l << std::endl;
    l = -l;
    std::cout << l << std::endl;

    int i = 1;
    int t = 3*(i++) + 4*(i++);
    std::cout << "i is " << i << std::endl
              << "t is " << t << std::endl
              << "t's beat is " << ~t << std::endl
              << (t << 3) << "\n" << (t <<= 7) << "\n";

    int k = 1;
    int j = k;
    std::cout << (k=j, ++k) << std::endl;

    

    return 0;
}