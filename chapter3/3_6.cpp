/*
    20-03-03 Enoch Kim
    cpp 교재 <모던 C++입문> 3강
    3.6 템플릿 특수화
*/

#include <iostream>
#include <typeinfo> // to enable c++filt in script
#include <memory>
#include <algorithm>
#include <cmath>
/*
    템플릿이 다양한 이수 타입에 동일한 구현을 사용할 수 있지만
    일부 인수 타입의 경우에 보다 효율적인 구현이 가능하다.
    템플릿 특수화를 사용하면 가능한데, 문제는 이 유연성이 효율성을 가져올지는 모르지만 혼란을 주기쉽기에 신중히 사용해야한다.
*/

// 클래스 특수화

template <typename T>   // 기본 템플릿
    class vector {

    };
class vector_bool_proxy //변경 가능한 접근 연산자를 구현하기 위한 트릭
{
  public:
    vector_bool_proxy(unsigned char& byte, int p) : byte(byte), mask(1 << p) {}
    // 바이트를 가리키는 레퍼런스와 이 바이트 내의 위치가 필요하다.
    // 그래서 추가작업의 간소화를 위해 문제의 위치를 비트 1로 두고 다른 모든 위치를 비트 0으로 두는 마스크를 만든다.

    operator bool() const { return byte & mask; }
    // 읽기 접근은 참조한 바이트를 간단히 마스크하는 곳에서 bool타입으로 변환하는 코드로 구현하면 된다.
    // if byte's bit == 1 byte & mask => true
    // 아래의 operator=에 의해 비트를 설정함으로써 가능하다.

    vector_bool_proxy& operator=(bool b) 
    { 
	if (b)
	    byte|= mask;
	else
	    byte&= ~mask;
	return *this; 
    }

  private:
    unsigned char& byte;
    unsigned char  mask;
};
/*
    벡터 예제를 bool 타입에 대해 특수화 해보자.
    8개의 bool 값을 1바이트로 패킹해 메모리를 정리해보자.
    

    template<>              // 기본 템플릿의 특수화라는 것을 보여주어야 하므로 이게 무조건 필요하다.
    class vector<bool>
    {
        
    };
*/



/*
    만약 다음의 세개의 매개변수를 사용하는 템플릿이 있다고 하자.
    template<typename T1, typename T2, typename T3>
    class some_container<T1, T2, T3>{ ... };
    이 템플릿의 T2를 int에 대해 특수화 하려고 하면 다음과 같이 나머지 두개의 매개변수는 유지해야한다.
    template<typename T1, typename T2, typename T3>
    class some_container<T1, int, T3>{ ... };
*/

template <>
class vector<bool> 
{
  public:
    explicit vector(int size)
      : my_size(size), data(new unsigned char[(my_size+7) / 8]) 
      // 만약 비어있지 않은 벡터를 사용할 때 비트 수를 8로 나눌 수 없는 경우 데이터 크기를 올림해야한다. => bool은 1bit이고 char는 1byte니까 ㅎㅎ
    {}
    // 디폴트 생성자와 기본 템플릿의 생성자가 동일하지만, 메서드는 특수화로 상속하지 않는다.
    // 그러므로 특수화를 작성할 때마다 모든 메서드를 처음부터 정의하거나 공통 베이스 클래스를 사용해야한다.

    vector() : my_size(0) {}


    // 기본 템플릿에서 멤버 함수나 멤버 변수를 생략할 수 있지만, 일관성을 위해 매우 정당한 이유가 있을 때만 생략할 수 있다.
    // 이경우 bool에서는 덧셈 연산이 없기 때문에 operator+를 생략했다.
  
    bool operator[](int i) const { return (data[i/8] >> i%8) & 1; }
    // 상수 접근 연산자는 시프팅과 비트 마스킹을 통해 구현할 수 있다.

    vector_bool_proxy operator[](int i) 
    { return {data[i/8], i%8};   }
    // 변경 가능한 접근 연산자는 단일 비트를 참조할 수 없으므로 구현하기 더 까다롭다. 
    // 이를 해결할 수 있는 트릭으로 단일 비트의 읽기 및 쓰기 작업을 제공하는 프록시(Proxy)를 반환하는 방법이 있다.
    // 중괄호를 리턴하여 두개의 인수로 구성된 생성자를 호출한다. => 이게 정상임??? 알아서 해주는 부분인가... cpp는 난해하군


  private:
    int                              my_size;
    std::unique_ptr<unsigned char[]> data;
};

/*
    다른 형들은 byte단위 이상을 사용하는데 반해 bool은 bit단위만 사용하기에 특수화를 적용해 보았다. 
    중요한 점은 우리가 특수화를 하더라도 기본 템플릿과 유사하게 만들었다는 것이다. 
    일관성 유지가 필요하다.
*/

// 함수 특수화

template<typename Base, typename Exponent>
Base inline power(const Base& x, const Exponent& y){
    // ... 
}

double inline power(double x, double y){
    return std::pow(x, y);
}
/*
    함수는 클래스와 같은 방식으로 특수화할 수 있지만, 불행히도 오버로드 확인에 참여하지 않으며, 
    덜 구체적인 오버로드는 더 구체적인 템플릿 추상화보다 우선한다.
    그러므로 함수 템플릿 특수화는 사용하지 않는 것이 좋다.
    위의 코드같이 오버로드를 구성하면 된다.
*/

template<typename Base, typename Exponent>
Base inline power(const Base& x, const Exponent& y){
    // ...
};
template<typename Base>
Base inline power(const Base& x, int y){
    // ...
};
template<typename Exponent>
double inline power(double x, const Exponent& y){
    // ...
};
/*
    다음에서 power(3.0, 2u)를 선언 시 1번 3번의 것 중 3번이 우선하여 3번이 적용되나,
    power(3.0, 2)를 선언 시 3가지 모두가 적용되며, 컴파일러가 무엇을 우선해야할지 몰라 에러를 띄운다.
    모호함을 해결하려면
    double inline power(double x, int y);를 선언해야한다.
*/

// 부분 특수화 Partial Specialization

/*
    vector에 complex를 특수화해야하는 상황을 고려해보자.
    template<>
    class vector<complex<float> >;
    template<>
    class vector<complex<double> >;
    template<>
    class vector<complex<long double> >; 
    다음과 같이 귀찮고 코드만 길어진다.
    complex클래스가 모든 Real타입을 지원하므로 구현 중복과 새로운 타입의 무지를 피하는 해결책으로 부분 특수화를 고려할 수 있다.
    우리는 모든 complex 인스턴스화에 vector 클래스를 특수화한다.
    template<typename Real>
    class vector<complex<Real> >{
        // ...
    };
    모든 포인터를 특수화할 수도 있다.
    template<typename T>
    class vector<T*>{
        //...
    };

    Type Pattern으로 타입 집합을 표현할 수 있을 때마다 부분 특수화를 적용할 수 있다.
    부분 템플릿 특수화를 정규 템플릿 특수화와 결합할 수 있는데, 이를 용어로 구분하여 완전 특수화(Full Specialization)라고 부른다.
    이 경우 완전 특수화는 부분 특수화보다 우선순위가 높다.
    template<typename Value, typename Parameters>
    class vector<sparse_matrix<Value, Parameters> > {...}; // 부분 특수화

    template<typename Parameters>
    class vector<sparse_matrix<float, Parameters> > {...}; // 완전 특수화
    완전 특수화는 항상 부분 특수화보다 구체적일 수밖에 없기에 우선순위가 높을 수밖에 없다.
*/


// 부분 특수화한 함수
/*
    실제로 함수 템플릿은 부분 특수화할 수 없으나 완전특수화에서는 오버로드를 사용해 특별한 구현을 제공할 수 있다.
    이를 위해 우리는 함수 템플릿이 일치할 때 우선순위가 높도록 보다 구체적인 함수 템플릿을 작성한다.
    예를 들어 모든 complex 인스턴스를 받는 구현으로 제네릭함수인 abs를 오버로드한다.
    template<typename T>
    inline T abs(const T& x){
        return x < T(0) ? -x : x;
    }

    template<typename T>
    inline T abs(const std::complex<T>& x){
        return sqrt(real(x) * real(x) + image(x) * image(x));
    }
    함수 템플릿의 오버로딩은 구현하기 쉽고 합리적으로 잘 동작한다. 
    그러나 대량으로 오버로드된 함수나 대규모 프로젝트의 여러 파일이 분산된 오버로드의 경우 의도한 오버로드를 호출하지 않는다.
    그 이유는 템플릿 함수와 템플릿이 아닌 함수의 혼합으로 인한 오버로드 확인과 쉽지 않은 네임스페이스 확인의 자명하지 않은 상호작용 때문이다.

    예측가능한 특수화 동작을 확인하려면 클래스 템플릿 특수화 측면에서 내부적으로 구현하는 방법이 가장 안전하다.
    이 때, 단일 함수 템플릿을 사용자 인터페이스로 제공해야한다.
    문제는 특수화의 리턴 타입이 서로 다를 때, 이 단일 함수의 반환타입이 무엇이냐는 것인데
    위의 예제에서처럼 제네릭 코드는 인수 타입을 반환하지만 보다 구체적인 complex 버전은 기본값 타입을 반환한다.
    이식성 있는 방법으로도 해결할 수 있으나 cpp14의 decltype과 auto를 사용하면 더 편하다.
    template<typename T> struct abs_functor;
    template<typename T>
    decltype(auto) abs(const T& x){         // cpp11에서는 리턴 타입을 명시적으로 선언해야한다. 
        return abs_functor<T>()(x);
    }
    제네릭 abs 함수는 익명 개체 abs_functor<T>()를 생성하고 인수 x로 연산자 ()를 호출한다.
    따라서 abs_functor의 해당하는 타입에 대한 특수화는 디폴트 생성자 및 T 타입의 인수를 허용하는 단항 함수인 operator()가 필요하다.
    operator()의 리턴 타입은 자동으로 추론된다. abs의 경우 다른 모든 특수화가 값을 반환해야 하기 때문에 리턴 타입을 자동으로 추론할 수 있다.

    cpp11에 적용하기 위해선 리턴 타입을 명시적으로 선언하되 타입 추론을 적용한다.
    template<typename T>
    auto abs(const T& x) -> decltype(abs_functor<T>()(x)){
        return abs_functor<T>()(x);
    }
    여기서 abs_functor<T>()(x)를 중복하여 사용하기 때문에 불일치의 잠재적인 원인이 된다. -> 잘 확인해라

    cpp3에서 리턴 타입에 추론을 사용할 수 없다. 따라서 Functor는 typedef를 통해 result_type이라는 이름의 리턴 타입을 사용해야 한다.

    template<typename T>
    typename abs_functor<T>::result_type
    abs(const T& x){
        return abs_functor<T>()(x);
    }
    여기서 result_type이 operator()의 리턴 타입과 일치한다는 점을 abs_functor를 구현한 사람이 알고 있다고 믿어야한다^^

    마지막으로 complex<T>에 대해 부분 특수화한 펑터를 구현한다.
    template<typename T>
    struct abs_functor{
        typedef T result_type;
        T operator()(const T& x){
            return x < T(0) ? -x : x;
        }
    };

    template<typename T>
    struct abs_functor<std::complex<T> >{
        typedef T result_type;
        T operator()(const std::complex<T>& x){     
            return sqrt(real(x) * real(x) + imag(x) * imag(x));
        }
    }
    이로써 abs의 세가지 구현이 모두 동작하는 cpp3기반 코드를 작성했다. cpp3이 아니라면 typedef를 생략할 수 있다.
    functor는 다음에 더 자세히 알아보자

*/

