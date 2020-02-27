/*
    20-02-27 Enoch Kim
    cpp 교재 <모던 C++입문> 3강
    3.4  타입 추론과 정의
    3.5 컨셉
    https://github.com/gilbutITbook/006828/blob/master/c%2B%2B14/value_range_vector.cpp 참고
*/

#include <iostream>
#include <typeinfo> // to enable c++filt in script


/*
    auto 변수타입 (cpp11)
    auto를 사용하면 컴파일러가 처음 타입을 할당한다. (이는 파이썬의 동적 할당과는 다르다)
    auto a = f(g(x, y, z) + 3 * x); 
    위의 a 타입은 f의 결과 타입과 같을 것이다. 즉 표현식의 결과 타입과 동일하다.
    중요한 점은 auto형을 여러번 선언할 때, 각 표현식의 결과타입이 동일해야한다는 것이다.
    auto i = 2 * 7.5, j = std::sqrt(3.7);   // ok double
    auto i = 2 * 4, j = std::sqrt(3.7);     // error because both types are different form each other
    auto i = 2 * 4, j;                      // error, j is not allocated
    auto v = g(x, y, z);                    // ok g's type
    여기서 g의 반환값이 레퍼런스여도 v는 레퍼런스가 아닌 변수이다.

    레퍼런스와 const를 통해 한정할 수 았다.
    auto& ri = i;           // reference of i
    const auto& cri = i;    // const reference of i
    auto&& ur = g(x, y, z); // forward reference of g's result
    g의 반환값이 Lvalue라면 ur은 Lvalue 레퍼런스이다.
*/

/*
    표현식의 타입 decltype (cpp11)
    auto a = f(g(x, y, z) + 3 * x); 를 decltype으로 표현하면 다름과 같다.
    decltype(f(g(x, y, z) + 3 * x)) a = f(g(x, y, z) + 3 * x);
    물론 이건 쓸데없이 사용한 것이다... 이런 경우보다는 명시적 활용에 사용한다.
    클래스템플릿의 템플릿 매개변수로 사용하는 경우가 있다.
    template<typename Vector1, typename Vector2>
    auto operator+(const Vector& v1, const Vector2& v2)
        -> vector<decltype(v1[0] + v2[0]);      // vector의 합을 타입추론하여 넣었다.
    여기에는 리턴 타입 추적(Trailing Return Type)을 사용했다. cpp11에서는 모든함수의 리턴 타입을 선언해야한다.
    이 경우 decltype을 사용하면 함수 인수로 표현 할 수 있고, 리턴 타입의 선언을 인수 뒤로 옮길 수 있다.

    decltype의 중요한 점은 표현식의 타입만을 추론하고, 계산은 진행하지 않는다는 것이다.
    그렇게 때문에 decltype(v1[0] + v2[0])의 v1[0]이 빈 벡터라 하더라도 오류를 발생시키지 않는다.

    decltype과 auto는 적용하는 곳도 다르고 타입 추론방식도 다르다.
    auto의 경우 레퍼런스로 선언하지 않는 이상 레퍼런스를 반환받아도 값을 갖지만,
    decltype의 경우 레퍼런스를 반환받으면 변수도 레퍼런스가 된다.
*/

/*
    decltype(auto)
    decltype(f(g(x, y, z) + 3 * x)) = f(g(x, y, z) + 3 * x);    // 장황한 코드의 중복
    decltype(auto) = f(g(x, y, z) + 3 * x);                     // 간결하다.
    이 두 표현식은 동일한 의미가 된다. 훨씬 간결함을 줄 수 있기에 후자가 사용된다.

    vector 의 operator[]를 통해 벡터의 요소에 접근한 뒤 정확히 같은 한정자를 사용해 범위를 검사한 후 반환하기 위해서는
    decltype(auto) operator[](size_type i){
        decltype(auto) value = vref[i];
        if(value < minv) throw too_small{};
        if(value > maxv) throw too_large{};
        return value;
    }
    다음과 같이 리턴 타입과 vref의 요소의 타입을 동일하게 하고, 
    decltype(auto) val = w[i];
    와 같이 실제 검사에서도 한번 사용해야한다. 
    이 중 하나라도 그저 auto로 설정하면 val의 타입이 다르게 된다.
*/

/*
    타입 정의
    타입을 정의하는 방법은 typedef와 using이 있는데, 만약 cpp11이상의 컴파일러만 사용한다면 using만 사용해라
    using이 더 읽기 쉽고 강력하다. 간단한 타입 정의의 경우에는 사실 순서 문제이다.
    typedef double value_type;
    using value_type = double;
    그러나 배열 같은 것을 선언할 때 차이가 보인다.
    typedef double da1[10]; // double과 [10]부분이 나뉘어 가독성이 나쁘다.
    using da2 = double[10];

    함수 혹은 포인터 타입에서 차이점은 더 명확하다(물론 함수 혹은 포인터 타입은 타입 정의에서 사용하지 않는다...)
    typedef float float_fun1(float, int);
    using float float_fun2 = float(float, int);
    위와 같이 using은 타입의 이름과 정의를 명확하게 구분한다.

    템플릿 에일리어스 (Template Alias)
    타입매개변수를 갖는 템플릿 에일리어스의 경우 using 선언을 통해 이루어진다.
    다음과 같이 벡터와 행렬을 각각 1차 텐서와 2차 텐서에 도입할 수 있다.
    
*/
template<unsigned Order, typename Value>
class tensor{};

template<typename Value>
using vector = tensor<1, Value>;

template<typename Value>
using matrix = tensor<2, Value>;



int main () {
    std::cout << "type of vector<float> is " << (typeid(vector<float>)).name() << '\n'; // tensor <1u, float> 를 예상했지만 6tensorILJ1EfE가 나온다.
    std::cout << "type of matrix<float> is " << (typeid(matrix<float>)).name() << '\n'; // tensor <2u, float> 를 예상했지만 6tensorILJ2EfE가 나온다.
    
}

/*
    컨셉
    템플릿 매개변수가 모든 타입으로 대체할 수 있다고 오해할 수 있지만, 사실 템플릿 인수가 수행하는 연산으로 허용되는 타입의 인수가 정해져있다.
    예를 들어 accumulate의 경우 
    1. T는 복사 생성이 가능하다. 즉, b의 타입이 T일 때 T a(b);가 컴파일 가능해야 한다.
    2. T는 덧셈 할당이 가능하다. 즉, a와 b의 타입이 T일 떄 a +=b;가 컴파일 가능해야한다.
    3. T는 int에서 구성될 수 있다. 즉, T a(0);가 컴파일 가능해야 한다.
    이런 타입 요구사항의 집합을 컨셉이라고 한다.
    컨셉 C의 모든 요구사항과 추가할 수 있는 한 요구 사항을 포함하는 컨셉 CR을 C의 개량(refinement)이라고 한다. 
    컨셉 C의 모든 요구사항을 충족하는 타입 t를 C의 모델이라고 한다. 예를 들어 덧셈 할당이 가능한 타입으로는 intm float, double, string 등이 있다.
    http://www.sgi.com/tech/stl을 보면 표준 템플릿 라이브러리의 함수에 필요한 컨셉목록이 나온다.
    미래의 cpp에 컨셉이 중요하게 쓰일 가능성이 크다...
*/