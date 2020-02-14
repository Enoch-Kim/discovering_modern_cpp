/*  
    20-02-12 Enoch Kim
    cpp 교재 <모던 C++입문> 2강
    2.1 ~ 2.2
*/


#include <iostream>
#include <fstream>
#include <typeinfo>
#include <memory>
#include <vector>


// 이 둘은 같은 의미이다. 
// 즉, struct는 기본적으로 모두 public이고, class는 기본적으로 모두 private인데,
// class의 모든 부분이 public이면 struct와 다를바 없다.
class complex {
    public :
        double i, r;
};

struct complex1 {
    double i, r;
};
/*
*/

class complex3 {
    public :
        double get_r(){
            // ... 이 안에 다른 제한 범위 설정가능
            return r;
        }
        void set_r(double new_r){
            // ... 이 안에 다른 제한 범위 설정가능
            r = new_r;
        }
        double get_i(){
            // ... 이 안에 다른 제한 범위 설정가능
            return i;
        }
        void set_i(double new_i){
            // ... 이 안에 다른 제한 범위 설정가능
            i = new_i;
        }

        double get_sum(){
            // ... 이 안에 다른 제한 범위 설정가능
            double sum = i + r;
            return sum;
        }

    private :
        double r, i;
};


int main () {

    /*
        도메인에서 중요한 수학적 추상화 식별
        소프트웨어에서 이러한 추상화를 포괄적으로, 그리고 효울적으로 표현하자.
        L(v) 와 L * v 같은 간단한 선형 연산자 표현법을 놔두고 매우 어렵고 긴 표현법을 사용하는 경우가 있다.
        이는 C언어나 Fortran같은 극한의 raw레벨 플랫폼과 연동했기 때문인데, 
        만약 이런 플랫폼과 연동할 때는 캡슐화해 플랫폼의 개발자들에게 노출시키지 않고,
        간결하고 직관적인 인터페이스로 소프트웨어를 작성하라.

        C++에서 클래스의 가장 중요한 장점은 상속 메커니즘이 아니라 새로운 추상화를 확립하고 대체 실현을 제공하는 기능이다.
    */

    /*
        접근성

        public : 어디에서나 접근 가능
        protected : 클래스 내부와 파생 클래스에서 접근 가능
        private : 클래스 내부에서만 접근 가능

        public멤버가 있는 간단한 클래스와 private데이터가 포함된 완전한 클래스를 어떻게 구별할 것인가.
        => 새로운 추상화를 설정하면 내부를 모두 private
        => 기존 추상화를 단순히 수집하는 데 사용한다면 데이터 멤버는 public이 될 수 있다.
            z.set_real(z.get_real() * 2);  =>  z.real *= 2;
                  
        가능하면 class를 사용하되 불변하지 않는 헬퍼타입(?)에서만 struct를 사용하라

        friend 키워드로 private과 protected로의 접근을 허용할 수 있다.
            friend std::ostream& operator << (std::ostream&, const complex&);
            friend class complex_algebra
        모든 friend가 내부 데이터의 무결성유지를 보장해야하므로 가능한 사용 x

    */

    // 접근 연산자

    complex z, z1, z2;
    complex *z1_ptr = &z1;
    z.i = 1.0; z.r = 2.0;
        // *z1_ptr.r = 3.0 => *(z1_ptr.r)을 의미하여 오류
    (*z1_ptr).r = 3.5;
    z1_ptr -> r = 4.0;
        // z1_ptr -> r -> d -> o 이런식
    
    /*
        static

        static으로 선언된 멤버 변수는 클래스마다 하나만 존재 => 개체간 리소스 공유가능
        이와 비슷한 경우는 디자인 패턴 싱글턴이다. 싱글턴은 특정 클래스의 인스턴스가 하나만 존재하게한다.

        메서드를 static으로 하는 경우 static 데이터만 접근할 수 있고, static 함수만 호출할 수 있다. 
            => 메서드가 개체 데이터에 접근할 필요가 없는 경우에는 최적화할 수 있다.
    */

    // 멤버 함수
    complex3 c1, c2;
    c1.set_r(3.0);
    c1.set_i(2.0);
        // 얕은 복사
    c2.set_r(c1.get_r());
    c2.set_i(c1.get_i());




    return 0;
}