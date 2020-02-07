/*
    20-02-06 Enoch Kim
    cpp 교재 <모던 C++입문> 1강
    1.4 

    컴파일 명령어 make ch1_4 && ./ch1_4
*/ 
#include <iostream>

int sum(int a, int b){
    int sum = a + b;
    return sum;
}
    

int main() {
    
    // 1.4.1 표현식 
    int a = abs(3 > 4 ? 3 : 4); // 중첩

    std::cout << "a is " << a << std::endl;
    
    // 1.4.2 문장 
    {
        int x = -1, y = 2;
        x + y;
        std :: cout << "x + y is " << x+y << std:: endl;
        {
            std :: cout << "x + y is " << x+y << std:: endl;
        }
    }
    

    // 1.4.3 분기문 
    {
        int x = -1, y = 3;
        if(x > 0)
            int abs_x = x;
        else
            int abs_x = -x;
            // std :: cout << "absx is " << absx << std::endl; => out of scope
        int abs_x;
        x > 0 ? abs_x = x : abs_x = -x;
        std :: cout << "abs_x is " << abs_x << std::endl;

        std :: cout << "abs sumation x and y is " << sum((x >= 0 ? x : -x), (y >= 0 ? y : -y)) << std::endl;
    }
    int k = 3;
    switch(k){
        case 1 :
            std::cout << "k is 1" << "\n";
            break;
        case 2 :
            std::cout << "k is 2" << "\n";
        case 3 :
            std::cout << "k is 3" << "\n";
            break;
        default :
            std :: cout << "k is not 1 or 2 or 3" << "\n";
    }

    int l = 2;
    switch(l){
        case 1 :
            std::cout << "l is 1" << "\n";
            break;
        case 2 :
            std::cout << "l is 2" << "\n";
        case 3 :
            std::cout << "l is 3" << "\n";
            break;
        default :
            std::cout << "l is not 1 or 2 or 3" << "\n";
    }
    {
        int x = 3;
        int i = 1;
        while(x != 1){                              // 콜라츠 급수
            x = (x%2==0) ? (x / 2) : (3 * x + 1);
            std:: cout << i << "times calculated x is " << x << std::endl;
            ++i;
        }

        x = 3;
        i = 1;
        do {
            

            if(x == 3)
                std::cout << "first value of x is " << x << std::endl;
            else{
                std:: cout << i << "times calculated x is " << x << std::endl;
                i++;
            }
            x = (x%2==0) ? (x / 2) : (3 * x + 1);
        
        } while (x != 1);
    }
    {
        // 테일러 급수의 e의 제곱승 10번째 항까지의 전개
        double x = 2.0, numerator, exp_x;
        unsigned long denominator;
        for(unsigned long n = 0, end = 10; n <= end; ++n){
            if(n == 0) {
                numerator = 1;
                denominator = 1;
                exp_x = numerator / denominator;
                continue;
            }
            numerator *= x;
            denominator *= n;
            exp_x += numerator / denominator;
        } 
        std::cout << "exp_x is " << exp_x << std::endl;
    }
    
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19};
    for(int i : primes){
        if(i % 2 == 1)
            std::cout << i << "\n";
        if(i == 5)
            break;
    }
    

    return 0;
}
