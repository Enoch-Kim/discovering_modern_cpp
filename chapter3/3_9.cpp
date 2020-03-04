/*
    20-03-04 Enoch Kim
    cpp 교재 <모던 C++입문> 3강
    3.9 람다Lambda
    https://github.com/gilbutITbook/006828/blob/master/c%2B%2B11/lambda.cpp 참고
*/

#include <cassert>
#include <iostream>
#include <cmath>
#include <algorithm>

/*
    람다(Lambda)
    람다는 cpp11에 도입된 프로그램을 간결하고 이해하기 쉽게 만들어주는 펑터의 약어이다.
    특히 간단한 계산의 경우 코드가 다른 곳에 있는 함수를 호출하는 대신 사용하는 곳에서 구현 코드를 보는게 더 명확하다.
    이전 sc_f 사코 펑터의 람다 표현식은 다음과 같다.
    [](double x) { return sin(x) + cos(x);}

    또한, 람다 표현식을 개체를 정의할 뿐만 아니라 개체를 즉시 생성하기 때문에 함수를 인수로 즉시 전달할 수 있다.
    fin_diff([](double x) { return sin(x) + cos(x); }, 1., 0.001));

    람다 표현식에 매개변수를 직접 포함할 수 있다. 펑터 psc_f에서 했던 것처럼 곱셈에 삽입하고 여전히 단항 함수 개체를 얻어 sin 인수의 값을 제어할 수 있다.
    fin_diff([](double x) { return sin(2.5*x) + cos(x); }, 1., 0.001);
    
    람다 표현신을 재사용하기 위해 변수에 할당할 수 있다.
    auto sc_l = [](double x){ return sin(x) + cos(x) };
    리턴타입을 추론할 수 없거나 명시적으로 표현하고 싶다면 다음 방식을 쓴다.
    [](double x) -> double { return sin(x) + cos(x); };
    
    우린 이로써 함수 개체를 즉석에서 생성할 수 있고 개체의 타입을 고민할 필요가 없어졌다.
    이를 통해 7계 도함수를 계산하는 함수를 하나의 표현식으로 생성하면 다음과 같다.
    auto d7_psc_l = make_nth_derivative<7>([](double x) { return sin(2.5*x) + cos(x); };, 0.0001);
*/

/*
    캡처 capture
    단순한 연산을 삽입해 람다를 매개변수화 했었지만 매개변수가 많은 경우에는 별로 생산적이지 못하다.
    a= fin_diff([](double x){ return sin(2.5 * x); }, 1., 0.001);
    b= fin_diff([](double x){ return sin(3.0 * x); }, 1., 0.001);
    c= fin_diff([](double x){ return sin(3.5 * x); }, 1., 0.001);
    
    불행하게도 다음과 같은 스코프에서 벗어나느 변수나 상수에 접근할 수 없다.
    double phi = 2.5;
    auto sin_phi = [](double x) {return sin(phi * x); } // error
    => 람다 표현식은 자체 매개변수 또는 이전에 캡처된 매개변수만 사용할 수 있다. 
*/ 

/*
    값에 의한 캡처
    phi를 사용하려면 먼저 phi를 캡처해야한다.
    double phi = 2.5; xi = 0.2;
    auto sin_phi = [phi](double x) { return sin(phi*x); }; // [] 안에 phi를 캡처했다.
    auto sin2 = [phi, xi](double x) { return sin(phi*x) + cos(xi * x);}; // 여러 변수를 캡처하고 싶다면 값 목록을 쉼표로 구분해준다.
    이 매개변수는 복사되지만, 값으로 전달된 함수 매개변수와는 달리 매개변수를 수정할 수 없다.
    위의 sin2에 사용된 람다를 펑터 클래스로 작성하면 다음과 같다.
*/
struct lambda_f{
    // 기본 퍼블릭
    lambda_f(double phi, double xi) : phi(phi), xi(xi) {}
    double operator()(double x) const{
        return sin(phi * x) + cos(xi * x);
    }

    private :
        const double phi, xi;
};
/*
    결과적으로 나중에 캡처된 변수를 수정하더라도 람다에는 영향을 미치지 않는다.
    double phi = 2.5; xi = 0.2;
    auto px = [phi, xi](double x) { return sin(phi*x) + cos(xi * x);}; 
    phi = 3.5; xi = 1.2;
    a = fin_diff(px, 1., 0.001);        // 여전히 phi = 2.5, xi = 0.2
    copy이기 때문이다.

    auto l_inc = [phi](double x) {phi += 0.5; return phi;}; // error phi is const
    
    만약 캡처된 값을 수정하려면 람다를 mutable로 한정해야한다.
    auto l_mut = [phi](double x) mutable { phi += 6.0; return phi;}; // mutablization
    이 경우 펑터에서 phi와 xi가 const 가 아닌 것과 같다.
*/

/*
    레퍼런스에 의한 캡처
    변수를 레퍼런스로 캡처할 수도 있다.
    double phi = 2.5, xi = 0.2;
    auto pxr = [&phi, &xi](double x) {return sin(phi*x) + cos(x) * xi};
    phi = 3.5; xi = 0.5;
    a = fin_diff(pxr, 1., 0.001);       // 이제 phi = 3.5와 xi = 1.2를 사용한다.
    이는 다음과 같다.
    struct lambda_ref_f{
        lambda_ref_f(double& phi, double& xi) : phi(phi), xi(xi) {}
        double operator()(double x) const{
            return sin(phi * x) + cos(x) * xi;
        }
        double& phi;
        double& xi;
    };

    레퍼런스 람다의 또 다른 기능은 참조된 값을 수정할 수 있는 기능이다. 이 기능은 부작용의 원인일 수 있지만, 생산적으로 쓰일 수 있다.

    만약 람다 안의 return이 없다면 void를 의미한다.
    모든 변수를 캡처할 수 있는 지름길
    [=] : 복사를 통해 모든 변수를 캡처한다.
    [&] : 레퍼런스를 통해 모든 변수를 캡처한다.
    [=, &a, &b, &c] : 복사를 통해 모든 변수를 캡처하되, a, b, c는 레퍼런스를 통해 캡처한다.
    [&, a, b, c] : 레퍼런스를 통해 모든 변수를 캡처하되, a, b, c는 복사를 통해 캡처한다.

    물론 모든 변수를 캡처하는 기능은 사용하지 않는 것이 좋다.
    부실 레퍼런스가 발생할 위험이 있고, 정적 변수나 멤버 변수를 무실하기 때문이다.
*/

/*
    일반화된 캡처 Init Capture
    일반화된 캡처는 변수를 클로저로 옮기고 컨텍스트 변수나 표현식에 새로운 이름을 부여할 수 있다.
    Hilbert 행렬을 unique_ptr로 반환하는 함수가 있다고 가정하자.
    auto F = make_unique<Mat>(Mat{ {1., 0.5}, {0.5, 1./3.} });
    closure에 대한 참고
    http://blog.naver.com/PostView.nhn?blogId=jun0683&logNo=30090931687&viewDate=&currentPage=1&listtype=0
    우리는 포인터로 가리키는 레퍼런스를 캡처할 수 있지만, 클로저가 포인터보다 더 오래 살면 스테일 레퍼런스(부실 레퍼런스)가 될 수 있다.
    반면에 unique_ptr는 복사할 수 없다. 우리의 행렬이 클로저만큼 살아있는지 확인하려면 데이터를 클로저가 소유한 unique_ptr로 옮겨야 한다.
    auto apply_hilbert = [F = move(F)](const Vec& x) {return Vec(*F*x)};    //move를 통해 unique_ptr을 옮김
    일반화된 캡처를 사용하면 기존 변수에 새로운 이름을 추가하고, 표현식을 계산하고 계산 결과를 이름과 연결한다.
    int x = 4;
    auto y = [&r = x, x = x+1](){
        r += 2;             // 외부에 있는 x를 가리키는 r레퍼런스를 증가시킨다.
        return x + 2;       // x + 2를  반환한다. 여기서 x는 외부에 있는 x + 1 이다.
    }

    표준 문서에 있는 이 예제는 int를 반환하는 nullary closure(인자없는 클로저)를 정의한다.
    클로저는 두 개의 지역변수를 도입한는데, r은 컨텍스트의 x를 가리키는 레퍼런스이며, 지역 값 x는 외부에 있는 x+1로 초기화 한다. 
    위를 보면 일반화된 캡처가 var = expr(표현식) 임을 알 수 있다. 신기한 점은 var과 expr가 다른 스코프에서 정의된다는 점이다.
    따라서 = 의 양쪽에 같은 이름이 나타날 수 있다. (같은 이름이지만 다른 변수이다.)
    다음 캡처 리스트는 r이 클로저에 존재하기 때문에 캡처의 오른쪽에서 사용할 수 없다.
    int x = 4;
    auto y = [&r = x, x = r + 1]() {...}; => Error ! r doesn't exist in context!
    

*/

/*
    제네릭 람다 (cpp14)
    cpp11에서는 람다 표현식은 리턴 타입을 결정했으나 명시적으로 선언해야하는 인수가 있었다.
    이러한 제한은 cpp14에서 해제되었는데, 인수는 함수 템플릿과 달리 다소 장황한 template-typename 표기법이 아닌 auto 키워드로 선언한다.
    예를 들어 (임의접근) 컨테이너의 요소를 내림차순으로 정렬하는 함수는 다음과 같이 간단하게 구현할 수 있다.
    template<typename T>
    void reverse_sort(C& c){
        sort(begin(c), end(c), [](auto x, auto y) { return x > y; });
    }
    위의 방식을 통해 우리는 
    using value_type = typename Matrix::value_type;으로 선언했던것을
    auto로 대체할 수 있다.
*/