/*
    20-02-18 Enoch Kim
    cpp 교재 <모던 C++입문> 3강
    3.1

*/

#include <iostream>
#include <memory>

/*
    Template은 매개변수 (제네릭) 타입에서 동작하는 함수 및 클래스를 만드는 C++의 기능이다.
    결과적으로 함수나 클래스는 각 타입마다 수동으로 재작성하지 않아도 다양한 데이터 타입으로 동작할 수 있다.

    제네릭 프로그래밍이 템플릿 프로그래밍과 동의어로 간주될 때도 있지만, 제네릭은 정확성을 제공하면서 최대한의 적용 가능성을 목표로하는 프로그램 패러다임이다.
    그리고 이 제네릭 프로그래밍의 주요 도구가 바로 템플릿이다. 그러므로 제네릭 프로그래밍이 더 큰 범주에 속한다 할 수 있다.

    제네릭 함수라고도 하는 함수템플릿은 템플릿함수와 동의어로 간주한다.
*/

// 위의 오버로드 함수를 함수템플릿을 사용하면 다음과 같이 간단히 표현 가능하다
// template<typename T>
// T max(T a, T b){
//     if(a > b)
//         return a;
//     else
//         return b;
// }

template<typename T>
T min(T a, T b){
    if(a < b)
        return a;
    else
        return b;
}

template<typename T>
T add(T a, T b) {
    return a + b;
}

/* 
    template<class T> 라고 해도 되지만, 제네릭 함수의 의도를 더 잘표현하는 것은 typename이므로 권장되지 않는다.
*/

/*
    instantiation 
    일반 함수인 경우 컴파일러가 함수의 정의를 읽고 오류를 검사한 뒤 실행 가능한 코드를 생성한다.
    그러나 제네릭 함수의 경우 정의를 처리할 경우에 구문 분석 오류와 같은 매개변수와 독립된 오류만을 검출 할 수있다.
    예를들어
    template<typename T>
    inline T max(T a, T b){
        if a> b => 오류
    }
    같은 구문오류는 검출 가능하다. 그러나
*/
    template<typename T>
    inline T max(T x, T y){
        return x < y ? y.value : x.value; // 이 구문의 오류를 검사할 수 없다.
    }
/*
    함수 템플릿의 경우 그 자체만으로 컴파일 할 수 없고, 호출 됐을 시 코드를 생성한다.
    호출 됐을 때 함수는 주어진 인수 타입에 대해서 오류가 있는지를 철저히 검사한다. 
    결론적으로 템플릿은 호출하는 코드가 존재하고 인수로부터 타입의 매개변수를 추론할 때 인스턴스화 된다.

    우리는 명시적으로 템플릿 매개변수를 치환하는 타입을 선언할 수 있다.
    std::cout << max<float>(8.1, 9.3) << '\n';
    가장 명시적인 형태를 사용하면 함수 호출없이 인스턴스화를 강제할 수 있다.
    template short max<short>(short, short); => 이는 오브젝트 파일을 생성할 때 유용할 수 있으며
    컴파일 단위의 함수 호출에 관계없이 특정 인스턴스가 존재하도록 보장해야한다.

    암시적 인스턴스화 : 간결함을 위해 타입 추론을 통해 인스턴스화 하는 것
    명시적 인스턴스화 : 명시적 타입 선언을 통한 인스턴스화 하는 것

    대부분 암시적 인스턴스화는 예상대로 동작한다. 그러나 명시적 지정은 대부분 모호성 해소와 std::forward와 같은 특수한 용도에 필요하다.
    컴파일러가 타입 치환하는 방법을 알고있으면 템플릿을 깊이 이해하는 데 큰 도움이 된다.
*/

/*
    매개변수의 타입을 추론하는 것은 auto와 같이 변수가 자동 타입으로 선언될 때 더욱 중요하다.
    치환규칙을 설명하기엔 auto보다 함수의 매개변수로 설명하는 것이 더욱 직관적이므로 이 방식으로 알아보자.
    값 매개변수
    위의 max함수를 const와 레퍼런스로 한정하여 사용할 수 있다.
    template<typename T>
    T max(const T& a, const T& b){
        ...
    }

    (일반화의 손실 없이) 단항 void 함수 f를 나타내보자.
    template<typename TPara>
    void f(FPara p);
    여기서 FPara는 TPara를 포함한다. 컴파일러는 f(arg)를 호출할 때 매개변수 p를 arg로 초기화할 수 있도록 TPara 타입을 추론해야한다.

    TPara가 FPara와 동등한 경우
    template<typename TPara>
    void f1(TPara p);
    이는 함수 매개변수가 인수의 지역 복사본이라는 것을 의미한다. int 리터럴, int 변수, 변경가능한 int 레퍼런스, 상수 int 레퍼런스로 f1을 호출해보자
*/
template<typename TPara>
void f1(TPara p) {
    p = 3;
    std::cout << "p is " << p << std::endl;
}

/*
    TPara가 int& 혹은 const int&로 치환되는 경우 인수도 함께 전달할 수 있으나, 위와같이 p를 수정하면 함수 인수에 영향을 줄 수 있으므로 값의 의미가 없다.
    그러므로 함수 매개변수가 한정이 없는 타입 매개변수인 경우 TPara는 모든 한정자가 제거된 인수타입이 된다. => const int&를 넣더라도 그냥 int로 들어간다.

    위의 템플릿 함수는 복사할 수 있는 모든 인수를 허용한다. unique_ptr의 경우 삭제된 복사 생성자를 가지며 함수에 Rvalue로만 전달할 수 있다.

*/
template<typename TPara>
void f2(TPara p) {
    std::cout << "p is " << p << std::endl;
}

/* 
    진짜 모든 인수를 받을 수 있도록 상수 레퍼런스를 매개변수로 사용할 수 있다.
*/
template<typename TPara>
void f3( TPara& p) {
    p = 3;
    std::cout << "p is " << p << std::endl;
}
/*
    이 함수는 모든 리터럴과 임시 변수는 참조 될 수 없기 때문에 거부한다. 
    타입 치환의 관점에서 TPara&를 int&&가 되도록 하는 TPara 타입이 없기 때문에 임시 변수를 거부한다.


*/

/*
    포워드 레퍼런스 (유니버셜 레퍼런스)
    T&&의 형태의 타입 매개변수를 사용하는 Rvalue레퍼런스는 Lvalue도 허용한다. 즉 모든 경우를 허용
    Lvalue도 허용할 수 있는 이유는 단항 함수의 타입 치환 떄문이다.
    TPara&&는 -&가 들어올때, TPara&로 붕괴된다.
    반면 TPara&는 -&&가 들어오더라도 TPara&를 유지한다.
*/
template<typename TPara>
void f4(TPara&& p){
    std::cout << "p is " << p << std::endl;
}

/*
    템플릿이 아닌 Rvalue가 Lvalue를 허용하지 않는 이유는 타입 치환 부족 때문이다. 
    함수 매개변수가 Lvalue일 수 있는 이유는 Lvalue레퍼런스가 치환을 통해 전달되기 때문이다.
    그러므로 평범한 함수는 치환이 없기에 레퍼런스가 붕괴되자 않는다.
*/

/*
    퍼펙트 포워딩
    move를 통해 Lvalue를 Rvalue로 변환할 수 있다. 그러나 포워드 레퍼런스 매개변수는 Rvalue도 사실 이름을 가지고있기에
    매개변수로 다른 함수로 전달될 때 Lvalue로 전달된다. move를 통해 Rvalue를 Rvalue로서 전달할 수는 있지만,
    문제는 Lvalue도 Rvalue도 전달이 된다는 것이다.
    이 문제를 해결하기 위해 우리는 forward를 사용한다.
*/
template<typename TPara>
void f5(TPara&& p) {
    f4(std::forward<TPara>(p));
}

/*
    이렇게 함으로써 우리는 Rvalue를 Rvalue로서, Lvalue를 Lvalue로서 f4에 전달할 수 있다.
    forward도 move와 마찬가지로 순수한 변환이며 단일 기계 연산을 생성하지 않는다. 사람들은 이를 "move는 이동하지 않고 forward는 전달하지 않는다."라 표현한다.
    forward는 인수들을 이동하거나 전달할 수 있도록 변환하는 역할만 한다.
    
*/  


int main() {
    {   
        // std::cout << "The maximum of 3 and 5 is " << max(3, 5) << '\n';         // int max(int, int)
        // std::cout << "The maximum of 3 and 5 is " << max(3l, 5l) << '\n';       // long max(long, long)
        // std::cout << "The maximum of 3 and 5 is " << max(3.0f, 5.0f) << '\n';   // float max(float, float)
        // unsigned u1 = 4294967295, u2 = 8;
        // std::cout << "The maximum of 3 and 5 is " << add(u1, u2) << '\n';   // unsigned int max(unsigned int, unsigned int)
        // // std::cout << "The maximum of 3 and 5 is " << max(u1, -3) << '\n';   // signed int max(unsigned int, signed int) => 형이 달라 안됌
        // std::cout << "The maximum of 3 and 5 is " << max(3.0f, float(u1)) << '\n';   // float max(float, float)
        // std::cout << "The maximum of 3 and 5 is " << max(3.0f, u2 * 3.0f) << '\n';   // float max(float, float)
    }

    {
        std::cout << "---------------------------------------------------" << std::endl;
        int i = 0;
        int& j = i;
        const int& k = i;
        f1(3);
        std::cout << "i is " << i << std::endl;
        f1(i);
        std::cout << "i is " << i << std::endl;
        f1(j);
        std::cout << "i is " << i << std::endl;
        f1(k);
        std::cout << "i is " << i << std::endl;

        std::unique_ptr<int> up;
        // f1(up); => error: call to implicitly-deleted copy constructor of 'std::__1::unique_ptr<int,std::__1::default_delete<int> >'
        f2(move(up)); // 이건 됌
        
    }
    {
        std::cout << "---------------------------------------------------" << std::endl;
        // f3(4);  => const TPara& 의 경우 허용되지만 TPara&의 경우 안된다.
        int i = 0;
        int& j = i;
        const int& k = i;

        f3(i);  // TPara&가 int& 로 치환되어 i를 참조
        std::cout << "i is " << i << std::endl;
        f3(j);  // TPara&가 int& 로 치환되어 i를 참조 (위와 동일)
        std::cout << "i is " << i << std::endl;
        // f3(k);  
        // TPara&가 const int& 로 치환되어 i를 참조 => TPara&는 변경가능한 레퍼런스로 제한하지 않음 그러나 문제는 p를 변경했으므로 에러 발생
        std::cout << "i is " << i << std::endl;
    }
    {
        std::cout << "---------------------------------------------------" << std::endl;
        int i = 0;
        int& j = i;
        const int& k = i;
        std::unique_ptr<int> up;
        f4(3);
        // f4(move(i)); => 왜 안되지...
        f4(move(up));
    }
}