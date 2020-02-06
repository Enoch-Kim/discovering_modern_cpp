/*
    20-02-06 김유현
    cpp 교재 <모던 C++입문> 1강
    1.4 ~ 

    컴파일 명령어 make ch1_4 && ./ch1_4
*/ 
#include <iostream>

int main() {
    
    // 표현식 
    int a = abs(3 > 4 ? 3 : 4); // 중첩

    std::cout << "a is " << a << std::endl;
    

    return 0;
}
