/*
    20-03-05 Enoch Kim
    cpp 교재 <모던 C++입문> 3강
    3.10 가변 템플릿 (Variadic Template)
*/

#include <cassert>
#include <iostream>
#include <cmath>
#include <algorithm>

/*
    함수 템플릿과 클래스 템플릿의 인수 개수가 다양할 때(최댓값이 없을 때) 함수 템플릿과 클래스 템플릿이 가변이라고 한다.
    이 템플릿은 인수가 최소 몇개 이상이어야 하는지는 정하지만, 최대 몇개여야 하는지는 정하지 않는다.
    또한, 템플릿 인수는 다른 타입 (또는 정수 타입의 상수)이 될 수 있다.
    가변 템플릿을 활용하면 타입 세이프한 printf 함수의 구현, 다양한 종류의 축소, 그리고 모든 형태의 제네릭 포워딩 함수가 있다.
    sum 함수를 보자
*/
template<typename T>
inline T sum(T t) {
    return t;
}

template<typename T, typename ...P>
inline T sum(T t, P ...p){
    return t + sum(p...);
}
/*
    가변 템플릿은 재귀를 통해 처리한다.
    우리는 소위 매개변수 팩(Parameter Pack)을 분해하고 그 부분 집합을 다룬다.
    일반적으로 하나의 요소를 분리해 나머지 요소의 결과와 합친다.

    가변 템플릿은 ...으로 표시된 새로운 줄임표 연산자를 도입한다. 
    왼쪽에 ... 연산자가 있으면 패킹을 의미하고, 오른쪽에 ... 연산자가 있으면 언패킹을 의미한다.
    위 코드의 서로 다른 줄임표 연산자의 해석이다.
    1. typename ...P : 복수의 타입 인수를 타입 팩 P에 패킹한다.
    2. <P...> : 클래스나 함수 템플릿을 인스턴스화할 때 P를 언패킹한다.
    3. P ...p : 변수 팩 p에 여러 함수 인수를 패킹한다.
    4. sum(p...) : 변수 팩 p를 언패킹하고 여러 인수로 sum함수를 호출한다.
    여기서 중요한 점은 sum함수의 재귀를 끝내기 위해서는 단일 인수에 대한 오버로드를 작성해야한다는 것이다.
    또한, 0을 int로 반환하는 인자없는(nullary) 함수를 위한 오버로드를 작성할 수도 있다.

    위의 sum함수의 문제는 함수의 return타입이 첫번째 인자에 의해 결정된다는 것이다.
    이를 해결하기 위해서는 더 적절한 리턴 타입을 고려해야한다.

    우리는 컴파일 타임에 매개변수 팩의 인수 개수를 계산하기 위해 함수와 같은 표현식 sizeof...을 사용할 수 있다.

    이러한 가변 템플릿은 메타 프로그래밍에서 빛을 발한단다.
*/
template<typename ...P>
void count(P ...p){
    std::cout << "You have " << sizeof...(P) << " parameters.\n";
}



int main () {
    using namespace std;
    auto s = sum(-7, 3.7f, 9u, -2.6);
    cout << "s is " << s << " and its type is " << typeid(s).name() << '\n'; // s is 2 and its type is i
    // 올바른 결과는 3.1이지만 첫 번째 인수 -7의 타입인 int로는 저장할 수 없다.
    auto s2 = sum(-7, 3.7f, 9u, -42.6);
    cout << "s2 is " << s2 << " and its type is " << typeid(s2).name() << '\n'; // s2 is -2147483648 and its type is i
    // 9 - 42.6 => unsigned로 변환 시 오버플로 된다.
    count(-7, 3.7f, 9u, -42.6);
    return 0;
}