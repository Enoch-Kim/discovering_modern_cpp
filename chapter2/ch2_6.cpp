/*
    20-02-17 Enoch Kim
    cpp 교재 <모던 C++입문> 2강
    2.6 멤버 변수에 접근
    
*/

/*
    접근 함수
    complex 클래스로의 접근을 위해 게터와 세터를 도입하면 코드가 안이쁘다.
    c.set_r(c.get_r() + 5.0);
    이런 코드는 가독성이 안좋다 누가봐도 연산같지 않다.
    이를 해결하기 위해서 우리는 레퍼런스를 반환하는 멤버함수를 작성한다.
    class complex{
        public :
            double& real() {return r;}
        // ...
    };
    이렇게 하면 다음과 같이 코드가 변한다.
    c.real() += 5.0;
    이전보다 낫지만 보기에 이상한건 마찬가지다.
    이를 개선하기위해 자유함수를 작성하자
    inline double& real(complex& c) {return c.real();};
    그렇다면 이렇게 작성할 수 있다.
    real(c) += 5.0;
    우리는 private 멤버 r에 접근기위해 멤버 함수를 호출하도록 했다.
    또다른 방법은 friend로 선언하는것이다.
    
    class complex{
        //...
        friend double& real(complex& c);
    };
    inline double& real(complex&c) {return c.r;};
    
    위의 방법들의 문제는 complex가 상수일때도 동작해야한다는 것이다. 따라서 인수와 결과에 관련해 함수의 const버전도 필요하다.
    inline const double& real(const complex& c) {return c.r;}; => c.r로 했기에 friend 선언이 필요하다.

    위의 함수들은 레퍼런스를 반환하기 때문에 반환한 레퍼런스가 쓸모없어지지 않기위해 변수에 담아야한다.
    double &rr = real(c);
    같은 스코프에서 선언됐다 하더라도 나중에 선언된 rr이 먼저 파괴된다(선언의 역순으로 파괴)

    임시 개체의 멤버 참조는 동일한 표현식 내에서 안전하게 사용할 수 있다.
    double r2 = real(compex(3, 7)) * 2.0;
    complex  레퍼런스가 real의 실수부 레퍼런스보다 오래 살아서 옳은 문장이다.
    그러나 실수부를 유지하는 레퍼런스를 유지하면 더 이상 쓸모없어지게 된다.
    const double &rr = real(complex(3.7)); => 개 쓰레기 문장
    => **임시 표현식의 레퍼런스를 유지하지마라! 처음 사용하기 전부터 이미 유효하지 않은 값을 갖는다.
*/

/*
    첨자 연산자
    class vector{
        public :
            double at(int i){
                assert(i >= 0 && i < my_size);
                return data[i];
            }
    }
    위의 at함수는 벡터를 반복하기위해 작성되었다.
    double sum = 0.0;
    for (int i = 0; i < v.size(); ++i)
        sum += v.at(i);
    
    연산자 오버로딩은 대입 연산자 및 "at" 의 구현부와 동일한 구문을 사용한다.
    class vector {
        public :
            double operator[](int i){
                assert(i >= 0 && i < my_size);
                return data[i];
            }
    }
    이 연산자를 사용할경우 벡터의 요소에 접근할 수 있지만 벡터의 값을 변경할 수 있는 경우에만 접근 가능하다. => 이게 뭔소리지? 
*/

// v[i]; 와 v.operator[](i);는 동일하다.

/*
    상수 멤버 함수
    우리가 상수 개체를 받는 멤버 함수와 연산자를 작성하려면 const 표기법을 사용해야한다.
    class vector{
        public :
            const double& operator[](int i) const{
                assert(i >= 0 && i < my_size);
                return data[i];
            }
    };
    위와 같은 const표기를 할 시 단순한 상수개체로 이 함수를 표현한다는 것이 아닌,
    컴파일러가 이 불변성을 매우 심각하게 받아들여 함수가 개체를 수정하지 않고 개체를 다른 함수에 const 인수로만 전달하는지 확인한다.
    따라서 다른 메서드를 호출할 때는 const여야한다.
    또한, 이 불변성 보증은 데이터 멤버를 가리키는 상수가 아닌 포인터나 레퍼런스를 반환하는 경우를 방해한다.
    반환한 값은 현재 개체, 멤버 변수 (또는 상수) 중 하나 또는 임시 변수 중 하나의 복사본이므로 상수일 필요는 없다.(상수일수도 있다)
    이러한 복사본 중 현재 개체를 수정할 위험이 있는 복사본은 없다.
    상수 멤버 함수는 상수가 아닌 개체를 인수로 호출할 수 있다. 왜냐하면 cpp는 필요하지 않을 떄 상수가 아닌 레퍼런스를 암시적으로 상수 레퍼런스로 변환하기 때문이다.
    따라서 상수 멤버 함수만 제공하면 된다.
    class vector{
        public :
            int size() const {return my_size};
            // int size() {return my_size}; => 필요없다 위에꺼가 둘다 된다.
        
    }
    첨자 연산자의 경우는 const버전과 아닌 버전 둘다 필요하다. 우리가 상수 멤버함수를 갖고 있다면 const버전과 아닌 요소를 읽을 수 있지만,
    후자는 벡터의 요소를 수정할 수 없다. 그러므로 const버전이 아닌 연산자를 두어 요소를 수정할 수 있도록 세워야한다.

    데이터 멤버는 mutable로 선언할 수 있다. 이렇게 하면 const 메서드에서도 값을 변경할 수 있다. 그러나 사용을 최소화 하는것을 추천한다.

*/

/*
    레퍼런스로 한정된 멤버 C++11
    cpp11에서는 개체의 불변성(즉 *this)이외에도 개체가 Lvalue 또는 Rvalue레퍼런스 이어야 한다고 요구할 수 있다. 
    벡터의 합을 구하는 함수가 있다고 가정하자 그결과는 상수가 아닌 임시 개체가 된다. 따라서 항목에 값을 할당할 수 있다.
    (v + w)[i] = 7.3;   // 개소리..
    할당문의 왼쪽에는 변경 가능한 Lvalue만을 사용해야한다. 그렇다면 왜 위의 (v+w)[i]가 왜 변경가능한 Lvalue인가?
    벡터의 첨자 연산자에는 두가지 오버로드가 있다. 바로 변경 가능한 개체와 상수 개체이다. v + w는 상수가 아니므로
    변경가능한 벡터를 받는 오버로드를 선호한다.
    문제는 (v+w)[i]는 변경 가능한 Lvalue이지만 v+w는 아니라는 것이다. 우리는 첨자 연산자를 Lvalue에만 적용될 수 있다는 요구사항을 넣는다
    class vector {
        public :
            double&    operator[](int i) & {...} // #1
            const double& operator[](int i) const& {...} // #2
    };
    멤버의 오버로드 중 하나를 &로 한정하면 다른 오버로드도 한정해야한다. 여기서 #1은 임시 벡터에 사용할 수 없으며,
    #2는 값을 할당할 수 없는 상수 레퍼런스를 반환한다. 결과적으로 위의 무의미한 할당은 컴파일 오류를 발생시킨다.

    마찬가지로 임시 개체를 비활성화하기 위해 벡터의 할당 연산자를 레퍼런스로 한정할 수 있다.
    v + w = u; //방지해야한다.
    class my_class{
        something_good donate_my_data() && {...}    // 두개의 &연산자로 멤버함수를 Rvalue로 제한할 수 있다. 메서드는 임시 개체에서만 호출 가능해야한다.
    }
    => 거대한 복사본을 피해야하는 변환이 대표적인 용례이다 (ex 행렬)

    

*/

int main () {
    return 0;
}