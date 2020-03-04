/*
    20-03-04 Enoch Kim
    cpp 교재 <모던 C++입문> 3강
    3.8 펑터(Functor)

*/

#include <cassert>
#include <iostream>
#include <cmath>
#include <algorithm>

/*
    펑터 or 함수개체 (Functor or Functional Object) 펑터는 클래스를 참조하는 개체 / 함수 개체는 개체 참조하는 놈
    함수 개체는 일반 함수와 다르게 새로운 함수 개체의 생성을 허용하면서 함수 개체가 서로 또는 자기 자신에게 더 유연하게 적용할 수 있다.
    람다와 메타프로그래밍에서 매우 중요한 개념이다.
*/

double fin_diff(double f(double), double x, double h){
    return (f(x+h) - f(x)) / h;
}

double sin_plus_cos(double x) {
    return sin(x) + cos(x);
}

/*
    여기서 문제는 2차 도함수를 계산하려고 할 때 발생한다.
    우리는 fin_diff를 도함수의 인수로 넘기고 싶으나 fin_diff(f, 1., 0.003)은 사실 하나의 매개변수를 갖는
    자체 함수 포인터 매개변수와 일치하지 않아 인수로 호출할 수 없다. (함수 포인터를 인자로 가지고 있어 불가능)

    위의 문제점을 펑터를 통해서 해결하는데 펑터는 애플리케이션에게 operator()를 제공해 해당 개체를 함수처럼 호출한다.
    위의 sin_plus_cos을 다음과 같이 펑터를 읽는 동작으로 구현한다.
*/
struct sc_f{
    double operator() (double x) const {
        return sin(x) + cos(x);
    }
};
/* 
    보는바와 같이 펑터는 매개변수를 내부 상태로 유지한다. 그래서 sin함수에서 x를 a로 크기 조정할 수 있다.
    즉, sin ax + cos x로 만들 수 있다.
*/
class psc_f{
    public :
        psc_f(double alpha) : alpha(alpha){}

        double operator() (double x) const {
            return sin(alpha * (x) + cos(x));
        }

    private :
        double alpha;
};
/*
    표기법
    functor타입은 접미사 _f를 붙이고 그 개체는 _o를 붙인다.
    근사화된 도함수는 접두사 d_를 붙이고 2차 도함수는 dd_를 붙이며 고계도함수는 d7_과 같이 d 다음에 차수를 붙인다.
*/

/*
    펑터 타입을 정의한 뒤에 해야할 일은 함수에 그 목적을 전달할 방법을 찾는 것이다.
    우린 이전에 정의한 sc_f와 psc_f를 지원하고 싶다고 하자. 이를 해결할 방법은 상속과 템플릿이 있는데
    우리는 적용가능성과 성능 명에서 우수한 제네릭 접근 방식(템플릿)을 적용해 볼 것이다.
    
*/
template<typename F, typename T>
T inline fin_diff(F f, const T& x, const T& h){
    return (f(x+h) - f(x)) / h;
}

/*
    우리는 f에 다양한 타입이 올 수 있다는 것을 볼 수 있었다.
    중요한 것은 우리가 코드를 작성하면서 f가 오직 하나의 인수를 받는 함수라는 것을 추론한다는 것이다.
    STL에서는 이러한 요구 사항을 UnaryFunction이라는 개념으로 도입한다.
    1. f는 F의 타입이라 하자.
    2. x는 T의 타입이라 하자. 여기서 T는 F의 인수 타입이다.                 // 모든 계산을 타입 T의 값으로 수행하므로 f의 반환 타입이 T가 된다.
    3. f(x)는 하나의 인수를 갖는 f를 호출하고 결과 타입으로 개체를 반환한다.
*/

/*
    펑터 합성
    고계 함수를 만들기 위해서 fin_diff와 펑터 하나 만으로는 부족하다.
    fin_diff는 삼항 함수인 반면 인수로 단항 함수가 필요하므로 우리는 
    도함수를 수행하는 함수와 간격 크기를 내부 사앹로 두는 단항 펑터를 정의해서 이러한 불일치를 극복할 수 있다.
*/
template<typename F, typename T>
class derivative {
    public :
        derivative(const F& f, const T& h) : f(f), h(h) {}

        T operator()(const T& x) const{
            return (f(x + h)-f(x)) / h;
        }
    private :
        const F& f;
        T   h;
};
/*
    이제 도함수에 대한 정규 함수 인자로 x만 전달하면 된다. 
    이 펑터는 f(x)를 나타내는 펑터로 인스턴스화할 수 있으며 결과는 근사화된 f'(x)를 나타내는 펑터다.

    아래의 dd_psc_f의 경우 psc_f에 대한 2계 도함수만을 다루기 때문에 
    만약 여러 함수에서 2계도함수를 만들고자 한다면.
    다음과 같은 펑터를 하나 더 만들면 된다.
*/
template <typename F, typename T>
class second_derivative
{
  public:
    second_derivative(const F& f, const T& h) : h(h), fp(f, h) {}

    T operator()(const T& x) const
    {
	return ( fp(x+h) - fp(x) ) / h;
    }    
  private:
    T        h;
    derivative<F, T> fp;        // 1계 도함수를 미리 가지고 있는다 => 이로써 여러 함수에서 가능하다.
};

/*
    n게 도함수를 구현하기 위해 재귀적 방법을 사용한다.

*/

template <typename F, typename T, unsigned N>
class nth_derivative
{
    using prev_derivative= nth_derivative<F, T, N-1>;   // 재귀 방식 선언
  public:
    nth_derivative(const F& f, const T& h) : h(h), fp(f, h) {}

    T operator()(const T& x) const
    {
	return ( fp(x+h) - fp(x) ) / h;
    }    
  private:
    T        h;
    prev_derivative fp;
};

/*
    문제는 위의 재귀함 수는 무한 재귀를 포함하기 때문에 다음과 같은 에러를 띄운다.
    fatal error : recursive template instantiation exceeded maximum depth of 1024
    그러므로 우리는 특수화를 통해 재귀를 종료한다.
*/

// template <typename F, typename T>
// class nth_derivative<F, T, 1>   // 특수화를 통해 1계에 도달하면 재귀를 중단시킨다.
// {
//   public:
//     nth_derivative(const F& f, const T& h) : f(f), h(h) {}

//     T operator()(const T& x) const
//     {
// 	return ( f(x+h) - f(x) ) / h;
//     }   
//   private:
//     const F& f;
//     T        h;
// };


//    위의 코드는 결국 derivative 펑터와 동일한 코드를 가지고있다. 그러므로 다음과 같이 대체할 수 있다.
template <typename F, typename T>
class nth_derivative<F, T, 1> 
    : public derivative<F,T>    // 파생을 통한 클래스 기능 유지
{
    using derivative<F, T>::derivative;
};

// 책의 근사치 향상 관련은 생략... 수학적인 내용일 뿐이다.

/*
    우리는 불필요한 인수의 중복을 사용하고 있다.
    nth_derivative<psc_f, double, 7> d7_psc_o(psc_o, 0.000001);
    nth_derivative의 처음 두 인수는 정확히 생성자 인수의 타입과 동일하다. 
    타입 추론하는 방식을 사용하여 이를 해결할 수 있다. (auto와 decltype은 효율적이지 않다. 
    그대신 생성자 인수를 취해 다음과 같이 타입을 추론하는 생성 함수를 만드는 방법이 있다.)

    // auto d7_psc_o= nth_derivative<psc_f, double, 7>(psc_o, 0.00001);
    // nth_derivative<decltype(psc_o), decltype(0.00001), 7> d7_psc_o(psc_o, 0.00001); => 비효율
*/

template <unsigned N, typename F, typename T>   // 여기서 중요한 점은 N을 앞에 두어 F와 T를 명시하지 않도록 한것이다.
nth_derivative<F, T, N> 
make_nth_derivative(const F& f, const T& h)
{
    return nth_derivative<F, T, N>(f, h);
}

/*
    제네릭 축소
    accumulate함수에 BinaryFunction을 도입해
    시퀀스의 모든 요소에서 축소가 가능하다.
    여기서 값을 추가하기위해 값의 타입에 따라 매개변수화 된 펑터를 구현할 수도 있고,
    클래스 대신 operator()를 매개변수화 할 수도 있다.
    이를 통해 컴파일러가 값 타입을 추론할 수 있다는 장점을 얻는다.
*/
template <typename Iter, typename T, typename BinaryFunction>
T accumulate(Iter it, Iter end, T init, BinaryFunction op)
{
    for (; it != end; ++it)
	init= op(init, *it);
    return init;
}

template <typename T>           // class 매개변수화
struct add
{
    T operator()(const T& x, const T& y) const { return x + y; }
};

struct times
{
    template <typename T>       // operator 매개변수화
    T operator()(const T& x, const T& y) const { return x * y; }    
};

/*
    vector v= {7.0, 8.0, 11.0};
    double s= accumulate(v.begin(), v.end(), 0.0, add<double>{});   // add 펑터는 벡터의 값 타입으로 인스턴스화 해야한다.
    double p= accumulate(v.begin(), v.end(), 1.0, times{});         // times 펑터는 템플릿 클래스가 아니며 애플리케이션에서 인수 타입이 추론된다.
*/

int main() {

    using namespace std;

    psc_f psc_o(1.0);
    cout << fin_diff(psc_o, 1., 0.001) << endl;         // psc의 개체가 생성된 상태에서 템플릿 인수로 전달
    cout << fin_diff(psc_f(2.0), 1., 0.001) << endl;    // 즉석에서 psc개체를 생성해 전달
    cout << fin_diff(sin_plus_cos, 0., 0.001) << endl; 
     
    using d_psc_f = derivative<psc_f, double>;  // 1계 미분 함수를 정의 했다.
    d_psc_f d_psc_o(psc_o, 0.0001);
    // 이렇게 x=0일 때, 미분계수를 계산할 수 있다.
    cout << "der. of sin(0) + cos(0) is " << d_psc_o(0.0) << '\n';
    using dd_psc_f = derivative<d_psc_f, double>;
    dd_psc_f dd_psc_o(d_psc_o, 0.0001);
    cout << "2nd der. of sin(0) + cos(0) is " << dd_psc_o(0.0) << '\n';

    sc_f sc_o;
    second_derivative<sc_f, double> dd_sc_o(sc_o, 0.001);           // sc_f의 2계 가능
    second_derivative<psc_f, double> dd_psc_2_o(psc_f(1.0), 0.001); // psc_f의 a값이 다른 함수의 2계도 가능

    nth_derivative<psc_f, double, 2> dd_psc_3_o(psc_f(1.0), 0.001);
    cout << "2nd der. of sin(0) + cos(0) is " << dd_psc_3_o(0.0) << '\n';

    nth_derivative<psc_f, double, 6> d6_psc_o(psc_f(1.0), 0.00001);
    cout << "6th der. of sin(0) + cos(0) is " << d6_psc_o(0.0) << '\n';

    nth_derivative<psc_f, double, 12> d12_psc_o(psc_f(1.0), 0.00001);
    cout << "12th der. of sin(0) + cos(0) is " << d12_psc_o(0.0) << '\n';

    nth_derivative<psc_f, double, 22> d22_psc_o(psc_f(1.0), 0.00001);

    auto d7_psc_o= make_nth_derivative<7>(psc_o, 0.00001);
    // 왼쪽의 명시적 선언된 매개변수(int)가 나오고 나머지 매개변수들은 괄호 안의 인자들로 부터 추론된다.

}