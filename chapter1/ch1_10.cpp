/*
    20-02-12 Enoch Kim
    cpp 교재 <모던 C++입문> 1강
    1.10
*/


#include <iostream>
#include <fstream>
#include <typeinfo>
#include <memory>
#include <vector>


int main () {

    {    
        // Question 1
        std::string name;
        unsigned int age;
        std::string answer;
        bool confirmed = false;
        std::ofstream age_file;

        while(!confirmed) {
            std::cout << "당신의 이름은 무엇입니까?" << std::endl;
            std::cin >> name;
            std::cout << "당신의 나이는 무엇입니까? (자연수로 입력해주세요. 장난하지 마시구요^^)" << std::endl;
            std::cin >> age;
            std::cout << "당신의 이름은 " << name << " 이고, 나이는 " << age << "살이 맞습니까? (맞으면 yes를 입력해주세요.)" << std::endl;
            std::cin >> answer;

            if(answer == "yes")
                confirmed = true;
            else {
                name = "";
                age = 0;
                answer = "";
            }
        }

        age_file.open("Question1.txt");
        age_file << "이름 : " << name << ", 나이 : " << age << "살" << std::endl;
        age_file.close();
    }

    {
        // Question 2

        char *latter;
        int integer[10];
        int *integer_ptr = new int[10];
        char *word_ptr = new char[10];
        char *word_ptr_ptr = word_ptr;
        const int z = 10;
        const int *z_ptr = &z;
        const int *integer_ptr = integer;

        // 나머지는... 어쩌라는거지 헤더파일이나 설명이 더 필요하겠는데...

    }

    return 0;
}