/*
    20-02-06 김유현
    cpp 교재 <모던 C++입문> 1강
    1.5
*/ 
#include <iostream>

//값에의한 호출 vs 참조에 의한 호출

void increment(int x) {
    ++x;
}

void incrementByRef(int& x){
    ++x;
}

/*참조에 의한 호출 중 벡터공간에 대한 연산에서 벡터의 실수로 변환 위험 방지
double two_norm(vector& v) {

}

double two_norm(const vector& v) {

}
*/

//기본값과 void 

void squar(double x, int n = 2) {
    int squar = 1;
    for(int i=1; i<=n; ++i){
        squar*=x;
        if(n == 5) return;
    }
    std::cout << "x squar n is " << squar << std::endl;
}

// Overloading
void divide (double x, double y) {
    std::cout << "double x divide by y is " << x/y << std::endl;
}

int divide (int x, int y) {
    int d = x/y;
    std::cout << "int x divide by y is " << d << std :: endl;
    return d;
}
    // long divide (int x, int y){} => Signatures of function are same with above!! especially factors of function are same!!

    // void f(int x) {};
void f(int&x) {};
void f(const int& x){};

int main(int argc, char* argv[]) {

    //값에의한 호출 vs 참조에 의한 호출
    int num = 1;

    increment(num);
    std::cout << "num is " << num << std::endl;

    incrementByRef(num);
    std::cout << "num is " << num << std::endl;

    increment(num + 1);
        // incrementByRef(num + 1); => reference value not exist!!

    //기본값과 void 
    squar(3.0, 3);
    squar(3.0, 5);
    squar(3.0);

    //Overloading
    int a = 3, b = 2;
    double c = 3.0, d = 4.0;
    divide(a, b);
    divide(c, d);
        // divide(a,c); => no matched function exist
    std::cout << "a divide by b is " << divide(a,b) << std::endl;
        /*
            a divide by b is int x divide by y is 1
            1
            이렇게 나옴... 연산 수행 순서에 따라
        */
    
    int i = 3;
    const int ci = 4;
        /*
            f(3);
            f(i);
            f(ci);
            => f is ambiguous so delete f(int)
        */
    f(i);
    f(ci);

    // main function
    std::cout << "argc is " << argc << std::endl;
    std::cout << "argv is " << argv << std::endl;
    
    for(int i = 0; i < argc; ++i){
        std::cout << argv[i] << std::endl;
    }
        // vsc 커맨드로하면 /Users/enoc/discovering_modern_cpp/ch1_5.out로 나옴 왜일까

    return 0; // 생략가능 생략시 자동으로 ruturn 0; 생성
}