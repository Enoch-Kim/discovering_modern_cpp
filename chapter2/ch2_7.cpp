/*
    20-02-17 Enoch Kim
    cpp 교재 <모던 C++입문> 2강
    2.7 연산자 오버로딩 디자인
    
*/

/*
    cpp11에서는 연산자를 몇가지를 제외하고 대부분의 연산자를 오버로딩할 수 있다. 그러나 일부 연산자는 특정 목적을 위해서만 오버로드하는것이 좋다.
    예를들어 p -> m 은 새로운 스마트 포인터를 구현하는데 좋다. 그러나 과학적 또는 공학적 맥락에서 이 연산자를 직관적으로 사용하는 방법은 명확하지 않아 좋지 않다.
    주소연산자 &o를 사용자 정의 연산자로 만든 의미가 있으려면 마땅한 이유가 필요
*/

/*
    일관성있게 디자인하라
    cpp연산자를 구현하는 데 있어 높은 자유도를 갖기 때문에 사용자가 사용하기에 표준 타입의 행동에 가깝게 디자인하는 것이 중요하다.
    물론 오버로딩이 특정 애플리케이션 도메인에서의 동작을 간결하게 표현하기위해, 즉 도메인 특정 임베디드언어 (domain specific embedded language, DSEL)를 확립하는데 사용가능하다.
    이경우 표준 타입의 행동을 벗어나는게 더 생산적일 수 있다. 그럼에도 불구하고 DSEL은 그 자체로 일관성을 가져야한다. 
    =, +, += 연산자의 결과가 같아야한다. 즉 a = a + b와 a += b는 같은 효과여야 한다.

    우리는 각 연산자의 리턴 타입을 자유롭게 마음대로 선택할 수 있다. 예를들어 x==y는 문자열이나 파일 핸들을 반환할 수 있다. 그러나 일반적인 리턴타입과 가까울수록 모든 사람이 더 쉽게 사용할 수 있다.

    유일하게 미리 정의된 연산자의 측면은 항(Arity)이다. 일부 연산자의 경우 가변적인 항을 취하기도 한다. 예를 들면 첨자 연산자가 첨자를 사용한 개체 이외에 두개의 인수를 허용한다면
    A[i,j]와 같이. 행렬 요소에 접근할 수 있다. 임의의 항을 허용하는 유일한 연산자는 응용 연산자인 operator()이다.
*/

/*
    우선순위를 고려하자
    LATEX표기법을 이용해 행렬의 지수를 나타내고자 할 때,
    A = B^2 의 ^는 비트연산에 사용되지만 불필요하므로 괜찮다.
    그러나 A = B^2 + C;의 경우 동작하지 않는다. 왜냐하면 +가 ^보다 우선순위가 높기 때문이다. 
    그러므로 A = (B^2) + C;와 같이 해야한다.
    => 오버로드한 연산자의 의미/의도한 우선순위가 cpp연산자의 우선순위와 일치해야한다.
*/ 
#include <iostream>

class complex{
    public :
        explicit complex(double rn = 0.0, double in = 0.0) : r(rn), i(in){}
        complex operator+(const complex& c2) const{
            return complex(r + c2.r, i + c2.i);
        }

        complex operator+(double r2) const{
            return complex(r + r2, i);
        }
        friend std::ostream& operator<< (std::ostream& os, const complex &c);   // 접근가능하도록 설정
        friend complex operator+ (double d, complex& c);

    private : 
        double r, i;
};

std::ostream& operator<< (std::ostream &os, const complex &c) {         // ostream 연산자 오버로딩
    os << "( " << c.r << ", " << c.i << " )" << std::endl;
    return os;
}

inline complex operator+ (double d, complex& c){
    return complex(d + c.r, c.i);
}

/*
    멤버 함수는 두번째 인수에 대한 암시적 변환만 허용하지만 자유함수의 경우 두 인수 모두 암시적 변환을 허용한다.\
    이진 연산자를 자유함수로 구현하라.
*/

int main () {
    complex cc(7.0, 8.0), c4(cc);
    std::cout << "cc + 4.2 is " << (cc + 4.2) << std::endl;   //explicit 을 제거하거나 추가해줘야한다.
    std::cout << "4.2 + cc is " << (4.2 + cc) << std::endl;
    return 0;
}