/*
    20-02-07 Enoch Kim
    cpp 교재 <모던 C++입문> 1강
    1.7
*/ 

#include <iostream>
#include <fstream>
#include <iomanip>


int main(){
    
    // 표준 출력
    std::cout << "11 * 19 = " << 11 * 19 << std::endl;

    int age = 79;
    std::cout << (age > 65 ? "I'm a wise guy.\n" : "I am still half-baked.\n");
        // 비교, 조건부, 논리, 비트 연산자는 괄호로 감싸야함 

    // 표준 입력
    std::cin >> age;
    std::cout << (age > 65 ? "I'm a wise guy.\n" : "I am still half-baked.\n");
    
    int width, height;
    std::cin >> width >> height;
    // std::cin >> width; std::cin >> height; 와 동일

    // 파일 입출력
    std::ofstream file1_7;
    file1_7.open("ch1_7.txt"); // if there no exist file, make new one. else cover exist one
    for(int i=0; i < 10; ++i)
        file1_7 << i << "^2 = " << i*i << std::endl;
    file1_7.close();

    // 위와 동일한 코드 => main 함수 끝날 때(scope가 끝날 때) 같이 close 함 => 특별한 경우 아니면 더 선호
    std::ofstream file1_7_3("ch1_7_3.txt");
    for(int i = 0; i < 10; ++i)
        file1_7_3 << i << "^2 = " << i*i << std::endl;

    // 서식 지정
    double pi = 3.1415926535389793;
    std::cout << "pi is " << pi << '\n';
    std::cout << "pi is " << std::setprecision(10) << pi << '\n';   // 모든 세팅 변경
    std::cout << "pi is " << std::setw(20) << pi << '\n';           // 다음 세팅만 변경
    std::cout << "pi is " << pi << '\n';
    std::cout << "pi is " << std::setfill('-') << std::left << std::setw(20) << pi << '\n'; // 왼쪽부터 채우고 빈공간 대신 '-'채움
    std::cout.setf(std::ios_base::showpos);                         // 플래그 강제
    std::cout << "pi is " << std::scientific << pi << '\n';         // 과학적 표기법 강제
    
    std::cout << "63 octal is" << std::oct << 63 << ".\n";
    std::cout << "63 hexadecimal is" << std::hex << 63 << ".\n";
    std::cout << "63 octal is" << std::dec << 63 << ".\n";

    std::cout << "pi < 3 is " << (pi < 3) << '\n';
    std::cout << "pi < 3 is " << std::boolalpha << (pi < 3) << '\n';

    // 서식 재설정
    int old_precision = std::cout.precision();
    std::cout << std::setprecision(13);
    std::cout.unsetf(std::ios_base::adjustfield | std::ios_base::basefield | std::ios_base::floatfield 
        | std::ios_base::showpos | std::ios_base::boolalpha);
    std::cout.precision(old_precision);

    // I/O Error control
    /*
        std::ifstream infile("some_mission_file.xyz");
        int i;
        double d;
        infile >> i >> d;
        std::cout << "i is " << i << ", d is " << d << '\n';
        infile.close();
    */
    std::ifstream infile;
    std::string filename("some_mission_file.xyz");
    bool opened = false;
    while(!opened){
        infile.open(filename);
        if(infile.good()){
            opened = true;
        }
        else {
            std::cout << "The file " << filename << "doesn't exist, give a new file name.";
            std::cin >> filename;
        }
    }
    int i;
    double d;
    infile >> i >> d;
    if(infile.good())
        std::cout << "i is " << i << ", d is " << d << '\n';
    else
        std::cout << "Could not correctly read the content.\n";\
    infile.close();



    return 0;
}