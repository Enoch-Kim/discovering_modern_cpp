/*
    20-02-07 Enoch Kim
    cpp 교재 <모던 C++입문> 1강
    1.6
*/ 

// #define NDEBUG
#include <iostream>
#include <cassert> // 단정


int main() {

    // 단정

    int l = 2;
    switch(l){
        case 1 :
            std::cout << "l is 1" << "\n";
            break;
        case 2 :
            std::cout << "l is 2" << "\n";
        case 3 :
            assert(l == 3);
            std::cout << "l is 3" << "\n";
            break;
        default :
            std::cout << "l is not 1 or 2 or 3" << "\n";
    }

    /* 오류코드 검출
        int read_matrix_file(const char* fname){
            fstream f(fname);
            if(!f.is_open())
                return 1;
            return 0;
        }
    */

    /* throw error
        int read_matrix_file(const char* fname){
            fstream f(fname);
            if(!f.is_open())
                throw "Can't open file";
            return 0;
        }
    */

    /* throw method
        int read_matrix_file(const char* fname){
            fstream f(fname);
            if(!f.is_open())
                throw cannot_open_file{};   // 빈 클래스
            return 0;
        }
    */

    // std::exception 계층구조 ??? 

    /* try - catch => 다형성의 경우 타입에 맞는 첫번째 catch문 적용
        try {

        }catch (e1_type& e1){

        }catch (e2_type& e2){

        }catch (...){ // 다른 모든 예외 처리

        }
    */

   /* 1. 위험성 있는 예외의 경우 => <cstdlib> 헤더의 exit 함수 사용
        이 함수는 main함수 밖에서도 프로그램을 종료 => 신중히 선택하자
      2. 나중에 처리할 수 있는 예외를 다시 던져 문제가 되는 부분을 알리거나 부분적인 복구조치 계속함
            => throw e;  ||  throw; 해놓고 나중에 함
      3. 예외 무시 => 빈블록 사용
        catch(cannot_open_file){}
      4. 사용자에게 조르기
        bool keep_trying = true;
        do {
            ...
            try {

                keep_trying = false;
            }catch(cannot_open_file& e) {
                std::cout << "Could not open file. Try another one! \n";
            }catch(...) {
                std::cout << "Something fishing here. Try another one! \n";
            }
        }while(keep_trying);
   */

    /* noexcept 지정자 => 이 함수에서 예외가 발생하면 프로그램을 종료
        double square_root(double x) noexcept {...}
    */

    return 0;
}
