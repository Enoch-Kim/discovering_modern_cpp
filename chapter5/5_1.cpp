/*
    20-04-18 Enoch Kim
    cpp 교재 <모던 C++입문> 4강
    5.1 컴파일러가 계산하도록 만들기
*/
#include <string>
#include <iostream>
#include <math.h>

constexpr long fibonacci(long n){
    return n <= 2 ? 1 : fibonacci(n-1) + fibonacci(n-2);
}

/*
    constexpr문은 대부분ㅇ 단일 리턴문이다. 
    계산이 없는 특정문장을 넣으려면 비어있는 문장, (특정) static_assert, 타입 정의, using선언 및 지시자 등이 있다.
    정규함수롸 비교하면 constexpr에 들어가는 문장은 제한적이다.
    
    1. 함수 외부에는 아무것도 읽거나 쓸 수 없다. 즉, 사이드 이펙트가 없다.
    2. 변수를 포함할 수 없다.
    3. if 또는 for와 같은 제어문을 포함할 수 없다.
    4. 단일 계산문만 포함할 수 있다.
    5. constexpr인 함수만 호출할 수 있다.

    반면 템플릿 메타 함수와 비교하면 constexpr은 좀 더 융통성이 있다고 할 수 있다.
    
    1. 부동소수점 타입을 전달할 수 있다.
    2. (컴파일 타임에 처리할 수 있는 경우) 사용자 정의 타입을 처리할 수도 있다.
    3. 타입 검출을 사용할 수 있따.
    4. 멤버 함수를 정의할 수 있다.
    5. (특수화보다 간단한) 조건문을 사용할 수 있다.
    6. 런타임 인수를 사용해 함수를 호출할 수 있다.
*/  

constexpr double square(double x){
    return x*x;
}

/*
    부동소수점 타입은 템플릿 인수로 사용할 수 없으며, cpp11 이전에는 부동소수점을 사용해 컴파일 타임계산을 수행할 수 없었다.
    그러나 cpp11 부터는 constexpr 덕분에 가능하다
*/

template <typename T>
constexpr T square(T x) {
    return x*x;
}

/*
    일반화된 함수는 특정 조건에서 사용자 타입을 받아들인다. 타입이 constexpr 함수에 적합한지 여부는
    미묘한 세부 사항에 따라 달라진다. 간단히 말해서, 타입 정의는 런타임에 크기가 조정된 volatile멤버 또는
    배열을 포함해 컴파일 타임에서의 개체 생성을 방해하지 않는다
    
    cpp 표준 위원회는 constexpr 함수에서 타입을 사용할 수 있는 조건을 정의하려고 했었다. 
    하지만 타입이 어떻게 사용되는지에 따라 다르므로 타입 속성으로 정의할 수 없다는 사실을 알게 되었다.
    좀 더 정확히 말하자면, 고려된 constexpr 함수에서 어떤 생성자를 호출하는지에 따라 달려있다.

    constexpr 함수의 정말 멋진 기능은 컴파일 타임과 런타임에서의 편리함이다. 

    constexpr함수의 하이브리드 적용 범위는 해당 매개변수를 차례대로 constexpr 함수에만 전달할 수 있다.
    정규함수에 매개변수를 전달하면 컴파일 타임에서의 사용을 방해한다.
    반대로 static_assert와 같이 컴파일 타임에 계산하는 함수에 함수 매개변수를 전달할 수는 없다.
    왜냐하면 런타임 호출을 막기 때문이다.
    cpp11에서는 못썼지만, 최신 컴파일러들은 assert를 cpp14의 constexpr로 제공하므로 매개변수를 사용할 수 있다.

    cpp표준은 표준라이브러리에 있는 함수 중 어떤 함수가 constexpr로 구현해야하는지를 규정한다.
    일부 라이브러리에서는 추가함수를 constexpr로 구현한다. 그 예로 다음 함수는 g++ 4.7~4.9에서 지원한다.
    constexpr long floor_sqrt(long n){
        return floor(sqrt(n));
    }
*/

/*
    cpp 14에서는 다음의 조건들까지 constexpr가 확장되었다.
    
    1. void 함수 
        constexpr void square(int& x) {
            x *= x;
        }
    2. 다음 조건을 만족하는 지역변수
        - 초기화되어 있다.
        - static도 아니고, thread 저장 기간도 없다.
        - 리터럴 타입을 갖는다.

    3. 다음을 제외한 제어문
        -  goto
        -  어셈블리 코드. 예를들어 asm 블록
        -  try 블록
    다음 예제는 cpp14에서는 컴파일 되지만 11에서는 컴파일 되지 않는다.
*/

template <typename T>
constexpr T power(const T&, int n){
    T r(1);
    while(--n>0)
        r *= n;
    return r;
}

/*
    확자된 문장을 사용하면 컴파일 타임 함수를 거의 제네릭 함수처럼 표현할 수 있다. 
    좀 더 기술적인 예로서, 이진 데이터에서 비트가 1인 개수를 세는 (population count) popcount 함수를 구현해보자.
*/
// constexpr size_t popcount(size_t x){    // cpp 14 이상
//     int count = 0;
//     for(; x!=0; ++count)
//         x &= x-1;
//     return count;
// }

constexpr size_t popcount (size_t x){       // cpp11 
    return x==0 ? 0 : popcount(x&x-1) + 1;
}

/*
    소수판정을 컴파일하는도중 계산할 수 있다.
*/

// constexpr bool is_prime(long long i){
//     if(i == 1)
//         return false;
//     if(i % 2 == 0)
//         return i == 2;
//     for(long long j = 3; j < i; j+=2)
//         if(i%j == 0)
//             return false;
//     return true;
// }
constexpr bool is_prime(long long i) {  // g++ 4.7 ~ 4.9 에서만...
    if(i==1)
        return false;
    if(i%2==0)
        return i == 2;
    long long max_check = static_cast<long long>(sqrt(i)) + 1;
    for(long long j=3; j < max_check; j += 2)
        if(i%j == 0)
            return false;
    return true;
}

// constexpr int square_root(int x){        // 새로 만들어줘야함
//     double r = x, dx = x;
//     while(const_abs((r*r) - dx) > 0.1){
//         r = (r + dx/r) /2;
//     }
//     return static_cast<int>(r);
// }

// constexpr bool is_prime(int i){
//     if(i == 1)
//         return false;
//     if(i%2 == 0)
//         return i == 2;
//     int max_check = square_root(i) + 1;
//     for(int j = 3; j < max_check; j+=2)
//         if(i%j == 0)
//             return false;
//     return true;
// }

// cpp 11 을 위한 코드 => 특수 케이스 판별 함수와 실제 소수판별 함수 따로 만들어야함
constexpr bool is_prime_aux(int i, int div){
    return div == i ? true : (i % div == 0 ? false : is_prime_aux(i, div+2));
}
constexpr bool is_prime(int i){
    return i==1 ? false : (i%2 == 0 ? i == 2 : is_prime_aux(i,3));
}

/*
    상수의 불변상태
    const int i = something;

    여기서 두가지의 불변성 설정이 가능하다

    1. 프로그램 실행 중에 개체를 변경할 수 없다.(항상 그렇다)
    2. 컴파일 타임에 이 값을 이미 알고있다. (경우에 따라 다르다)

    컴파일 타임에 계산에 활용할 수 있는 경우
    1. const long i = 7; //리터럴
    2. template<long N>
        struct static_long{
            struct const long value = N;
        }
        // 템플릿 매개변수
    3. const long k = i+j;
        static_long<k> sk;
        // 컴파일 타임 상수로 이뤄진 간단한 표현식

    안되는 경우
        long ll;
        cin >> ll;
        const long cl = ll;
        static_long<cl> scl; // 오류
        // allocate variable into const object

    프로그램 소스에서 어떤 종류의 상수를 갖고 있는지 말할 수 없는 경우가 있다. 
    const long ri = floor(sqrt(i));
    static_long<ri> sri; // g++ 4.7~4.9 에서 가능
    ri 는 표준 라이브러리에 있는 sqrt와 floor가 constexpr인 경우 컴파일 하는 동안 알 수 있다.
    => 컴파일러 의존

    constexpr long ri = floor(sqrt(i)); // 상수가 컴파일 타임 값을 갖게된다.

    constexpr 는 함수보다 변수에 더 엄격하다. constexpr변수는 컴파일 타임 값만을 허용하고 
    constexpr함수는 컴파일 타임 및 런타임 인자를 모두 허용한다.
*/

int main() {   
    using namespace std;

    // char* s = new char[10];
    // cin.getline(s, 4);
    // long n = atoi(s);
    long n = 2020l;
    long long i = (1l<<61) - 1;

    cout << i << '\n';
    cout << "Fibonacci(" << 2020 << ") = " << fibonacci(30) << '\n';  // 왜 안되지?;;; => 42 정도 까지만 컴파일러가 계산할 수 있음...
    cout << "number 2^61-1 prime number is " << is_prime(31) << '\n'; // 숫자가 너무 커서 안된다... ㅠㅠ
    // cout << "Fibonacci(" << n << ") = " << fibonacci(n) << '\n'; 
    // 인수는 런타임에 결정되므로 컴파일 타임에 함수를 계산할 수 없다.
    // 모든 함수의 인수가 컴파일 타임에 사용할 수 있어야 한다.


}