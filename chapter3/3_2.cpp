/*
    20-02-21, 20-02-24 Enoch Kim
    cpp 교재 <모던 C++입문> 3강
    3.2
    마소의 Docs 참고 https://docs.microsoft.com/ko-kr/cpp/cpp/namespaces-cpp?view=vs-2019

*/

#include <iostream>
#include <memory>

/*
    네임스페이스
    이름 충돌을 해결하는 방법 중 하나로 사용자 정의 클래스와 함수 템플릿을 사용할 때 매우 중요하다.
*/
namespace GUI {
    class window;
}

namespace statistics {
    class window;
}
// 위와 같이 네임스페이스를 지정하여 같은 이름을 가진 window 클래스를 구분한다.
namespace ContosoData
{
    class ObjectManager
    {
    public:
        void DoSomething() {}
    };
    void Func(ObjectManager) {}
}
/*
    https://docs.microsoft.com/ko-kr/cpp/cpp/namespaces-cpp?view=vs-2019 참고

    위와 같이 선언한 ObjectManager를 사용하는 방법은 크게 3가지이다.
    1. 정규화된 이름 사용
        ContosoData::ObjectManager mgr;
        mgr.DoSomething();
        ContosoData::Func(mgr);

        꽤나 코드가 길어진다.

    2. using을 사용하여 하나의 식별자를 범위로 가져오기
        using ContosoData::ObjectManager;
        ObjectManager mgr;
        mgr.DoSomething();

        특정 부분을 가져오기에 코드가 간결해지나 Func는 사용하려면 정규화된 이름을 사용해야한다.

    3. using 지시문을 사용하여 네임스페이스의 모든 식별자를 범위로 가져오기:
        using namespace ContosoData;
            
        ObjectManager mgr;
        mgr.DoSomething();
        Func(mgr);

        ObjectManager와 Func 둘 다 간결하게 사용하나 다른 이름과 충돌이 발생할 우려가 있다.

    using 지시문을 사용하는 경우는 위의 두가지이다.
    2번의 하나 혹은 두개의 식별자를 가져오는 경우와 3번의 네임스페이스 전체를 가져오는 경우.
    지역변수의 이름이 네임스페이스 변수의 이름과 동일하면 지역변수를 호출한다.(네임스페이스 변수가 숨겨진다.)
    전역변수와 동일한 이름을 가진 네임스페이스 변수를 사용하면 오류가 발생한다!!
    using 지시문은 .cpp 파일 맨 위나(파일 범위) 클래스 또는 함수 정의 내에 배치할 수 있다.

    헤더파일에 using지시문을 넣지 말라. 만약 넣으면 그 헤더파일을 부른 모든곳에서 using이 적용되기 때문에 많은 버그가 발생한다.

    일반적으로 헤더파일에 네임스페이스를 선언한다.
    //contosoData.h
    #pragma once
    namespace ContosoDataServer
    {
        void Foo();
        int Bar();
    }

    using 지시문을 사용하더라도 함수를 구현하거나 할 때는 정규화된 이름을 사용해야한다.
    #include "contosodata.h"
    using namespace ContosoDataServer;

    void ContosoDataServer::Foo() // use fully-qualified name here
    {
    // no qualification needed for Bar()
    Bar();
    }

    int ContosoDataServer::Bar(){return 0;} // use fully-qualified name here

    단일 파일의 여러 블록과 여러 파일에서 네임스페이스를 선언할 수 있다.

    아직 선언되지 않은 변수를 선언하는 것은 불가능하다.
    
    namespace V {
        void f();
    }

    void V::f() { }        // ok
    void V::g() { }        // C2039, g() is not yet a member of V

    main함수를 제외하고는 전역 네임스페이스를 만들지 말라
    기본적으로 네임스페이스를 한정하지 않으면 암시적 전역 네임스페이스에 포함된다. 
    만약 명시적으로 전역 네임스페이스를 호출하고 싶을 시 다음과 같이 사용한다.
    ::SomethingToDo();

    네임스페이스를 중첩할 수 있다. 
    자식은 부모의 멤버에 무한적 엑세스가 가능하지만 
    부모는 인라인 네임스페이스로 선언되지 않은 자식을 무한정 엑세스할 수 없다.
    namespace ContosoDataServer
    {
        void Foo();

        namespace Details
        {
            int CountImpl;
            void Ban() { return Foo(); }
        }

        int Bar(){...};
        int Baz(int i) { return Details::CountImpl; } // 정규화된 이름을 사용한다.
    }

    인라인 네임스페이스를 사용하면 가능 (cpp11)
    일반적인 중첩된 네임스페이스와 달리, 인라인 네임스페이스의 멤버는 부모 네임스페이스의 멤버로 처리된다. 
    이러한 특징 때문에 오버로드된 함수의 인수 종속 조회가 부모 및 중첩된 인라인 네임스페이스에 오버로드가 있는 함수에서 작동할 수 있다. 
    //Header.h
    #include <string>

    namespace Test
    {
        namespace old_ns
        {
            std::string Func() { return std::string("Hello from old"); }
        }

        inline namespace new_ns // 이 부분은 부모의 멤버로 속하게 된다.
        {
            std::string Func() { return std::string("Hello from new"); }
        }
    }

    #include "header.h"
    #include <string>
    #include <iostream>

    int main()
    {
        using namespace Test;
        using namespace std;

        string s = Func();
        std::cout << s << std::endl; // "Hello from new"
        return 0;
    }

    인라인 네임스페이스에서 선언된 템플릿의 부모 네임스페이스에서 특수화를 선언할 수 있습니다. => 이게 뭔소리일까.
    => 부모가 자식이 가진 템플릿의 형을 특수화 할 수 있다는 것 같음. 오버로드를 이용한 방식인 것 같다.
    namespace Parent
    {
        inline namespace new_ns
        {
            template <typename T>
            struct C
            {
                T member;
            };
        }
        template<>
        class C<int> {};
    }

    인라인 네임스페이스를 사용하면 버전관리도 쉽다. 예를들어 버전별 지정해두고 최신을 인라인 설정하면
    기본적으로 최신 버전을 쓰돼, 다른 버전을 사용하고 싶은사람은 정규화된 접근 방식을 사용하면 된다.

    namespace Contoso
    {
        namespace v_10
        {
            template <typename T>
            class Funcs
            {
            public:
                Funcs(void);
                T Add(T a, T b);
                T Subtract(T a, T b);
                T Multiply(T a, T b);
                T Divide(T a, T b);
            };
        }

        inline namespace v_20
        {
            template <typename T>
            class Funcs
            {
            public:
                Funcs(void);
                T Add(T a, T b);
                T Subtract(T a, T b);
                T Multiply(T a, T b);
                std::vector<double> Log(double);
                T Accumulate(std::vector<T> nums);
        };
        }
    }

    네임스페이스 이름은 고유해야 하며, 이는 대체로 이름이 너무 짧지 않는게 좋다.
    너무 길어서 코드를 읽기 어렵거나 using 지시문을 사용할 수 없는 헤더 파일의 경우(겹칠 우려가 있는경우) 약어(별칭)를 만들 수 있다.
    
    namespace a_very_long_namespace_name { class Foo {}; }
    namespace AVLNN = a_very_long_namespace_name;
    void Bar(AVLNN::Foo foo){ }

    익명 네임스페이스
    명명 하지 않은 네임스페이스는 그 파일 내부에서만 접근 가능하다. (캡슐화(?)가 가능하다는 말인 것 같다.)

    namespace
    {
        int MyFunc(){}
    }


*/

/*
    네임스페이스가 블록과 다른 점은 네임스페이스_한정(Namespace Qualification)으로 이름을 계속 참조할 수 있다는 것이다.
    struct same{};
    namespace c1{
        struct same{};
        namespace c2{
            struct same{};
            sturct csame{
                ::same x;      //same of global
                c1::same y;    //same of c1
                same z;        //same of c2
            }
        }
    }

    만약 c2안에 c1을 다시 선언하면 바깥쪽 c1네임스페이스는 숨겨지고, y의 타입을 정의할 수 없다.
    처음의 c1의 same을 참조하기 위해서는 전역 네임스페이스 부분을 명시하거나 using으로 명시한다.
    struct same{};
    namespace c1{
        struct same{};
        namespace c2{
            struct same{};
            namespace c1{};
            sturct csame{
                ::same x;      //same of global
                c1::same y;    //   error occure => c1::c2::c1::same is not defined
                same z;        //same of c2
                ::c1::same y;  //same of c1(specify)
            }
        }
    }

    using에 관하여는 MicroSoft의 설명이 더 좋다
    using의 경우 네임스페이스와 함수에서 동작하지만 클래스에서는 선언을 사용하는 다른 클래스와 충돌하므로 동작하지 않는다(클래스 스코프에서는 동작하지 않는다)
    
*/

/*
    Argument-Dependent Lookup, ADL 인수 종속 룩업
    함수이름의 검색을 인수 네임스페이스로 확장하는 것을 인수 종속 룩업이라고 한다.
    주의할 점은 부모의 네임스페이스로 확장하지는 않는다는 것이다.
    ...
    namespace rocketscience{
        struct matrix{};
        void initialize(matrix& A) {...}
        matrix operator+(const matrix& A, const matrix& B){
            matrix C;
            initialize(C);
            add(A, B, C);
            return C;
        }
    }

    int main () {
        rocketscience::matrix A, B, C, D;
        rocketscience::initialize(B); //한정함
        initialize(C);                //ADL 의존
        chez_herbert::matrix E, F, G;
        rocketscience::initialize(E); // 한정 필요
        initialize(C);                // Error : can not find initialize
    }

    ADL이 없으면 다음의 식도 복잡해진다.
    A = B + C + D;
    => A = rocketscience::operator+(rocketscience::operator+(B,C),D);

    I/O stream을 처리하는 문장은 훨씬 추악하고 성가시게 된다.
    사용자 코드가 네임스페이스 std::에 없어야 하므로 operator<<는 클래스의 네임스코프에서 정의하는게 좋다. 그럼으로써 ADL은 각 타입별로 적절한 오버로드를 찾을 수 있다.

    ADL메커니즘은 여러 네임스페이스에 분산되어 있는 경우 올바른 함수 템플릿 오버로드를 선택하는 데 사용할 수도 있다. 
    선형 대수의 L1법선은 행렬과 벡터에 모두 정의되므로 두 타입 모두 사용할 수 있는 템플릿 구현을 제공하려고 한다.
    template<typename Matrix>
    double one_norm(const Matrix& A){...}
    template<typename Vector>
    double one_norm(const Vector& x){...}
    문제는 컴파일러가 우리가 원하는 오버로드를 알 수 없다는 것이다.
    컴파일러가 알기 위해서는 행렬 네임스페이스와 벡터 네임스페이스를 도입해 ADL로 올바른 오버로드를 사용하게 해야한다.
    namespace rocketscience{
        namespace mat{
            struct sparse_matrix{};
            struct dense_matrix{};
            struct uber_matirx{};
            template<typename matrix>
            double one_norm(const Matrix& A){...}
        }
        namespace vec{
            struct sparse_vector{};
            struct dense_vector{};
            struct uber_vector{};
            template<typename Vector>
            double one_norm(const Vector& A){...}
        }
    }

    ADL 메커니즘은 인수의 타입 선언의 네임스페이스에서만 함수를 검색하고 각각의 상위 네임스페이스에서는 검색하지 않는다.
    namespace rocketscience{
        namespace mat{
            struct sparse_matrix{};
            struct dense_matrix{};
            struct uber_matirx{};
            template<typename matrix>
            double one_norm(const Matrix& A){...}
        }
        namespace vec{
            struct sparse_vector{};
            struct dense_vector{};
            struct uber_vector{};
            
        }
        template<typename Vector>
        double one_norm(const Vector& A){...}
    }

    int main() {
        rocketscience::vec::uber_vector x;
        double norm_x = one_norm(x); // 오류 : ADL을 통해 찾을 수 없다.
    }

    또한 다른 네임스페이스 안에 있는 이름을 가져올 때, 해당 네임스페이스의 함수는 ADL에 종속하지 않는다.
    namespace rocketscience{
        namespace mat{
            struct sparse_matrix{};
            struct dense_matrix{};
            struct uber_matirx{};
            template<typename matrix>
            double one_norm(const Matrix& A){...}
        }
        namespace vec{
            struct sparse_vector{};
            struct dense_vector{};
            struct uber_vector{};
            
        }
        using vec::uber_vector; // 의미없다.
        template<typename Vector>
        double one_norm(const Vector& A){...}
    }

    int main() {
        rocketscience::vec::uber_vector x;
        double norm_x = one_norm(x); // 오류 : ADL을 통해 찾을 수 없다.
    }
    오버로드를 적절하게 선택하려고 ADL에 의존하는 것은 한계가 있고, 단일함수만 사용해 줄일 수 있으나 이도 완전하진 않다.
    
    인자가 여러 개인 함수를 사용할 때, 특히 매개변수 타입이 서로 다른 네임스페이스에서 비록된 경우 모호할 가능성이 더 높아진다.
    namespace rocketscience{
        namespace mat{
            ...
            template<typename Scalar, typename Matrix>
            Matrix operator*(const Scalar& a, const Matrix& A){...}
        }
        namespace vec{
            ...
            template<typename Scalar, typename Vector>
            Matrix operator*(const Scalar& a, const Vector& x){...}
            template<typename Matrix, typename Vector>
            Matrix operator*(const Matrix& A, const Vector& x){...}
            
        }
        
    }

    int main() {
        rocketscience::mat::uber_matrix A;
        rocketscience::vec::uber_vector x, y;
        y = A * x; // 어떤 오버로드를 선택해야 하는가 모호하다. 
    }
    컴파일러는 두 네임스페이스 모두 탐색하며, 세가지의 오버로드 모두 사용 가능하다... 그리고 우선순위도 없어서 망한다.

    아쉽게도 명시적 템플릿 인스턴스화는 ADL에서 동작하지 않는다. 
    함수 호출에서 템플릿 인수를 명시적으로 선언할 때마다 함수 이름은 인수의 네임스페이스에서 찾지 않는다.

    요약하면 이렇다.
    1. 네임스페이스 중첩 및 한정
    2. 이름 숨김
    3. ADL
    4. 오버로드 판별
*/

/*
    swap함수 템플릿의 구현 방식을 보자
    template<typename T>
    inline void swap(T& x, T& y){
        T tmp(x); x = y; y = tmp;
    }
    이 방식은 1기가의 데이터를 옮기는데 3기가의 메모리를 필요로한다.
    이런 비효율을 지우기 위해 class안에 inline-friend 자유함수를 선언한다. (클래스 안에 선언함으로 코드 길이를 훨씬 줄일 수 있다.)
    template<typename Value>
    class vector{
        ...
        friend inline void swap(vector& x, vector& y){
            std::swap(x.my_size, y.my_size); std::swap(x.data, y.data);
        }
        private :
            unsigned my_size;
            Value *data;
    }
    만약 다음과 같이 제네릭 함수에서 매개변수 타입의 데이터를 교환해야한다고 가정하면 3기가의 데이터를 복사해야한다.
    template<typename T, typename U>
    inline void some_function(T& x, T& y, const U& z, int i){
        ...
        std::swap(x, y);    // 비용이 비쌀 수 있다.
        ...
    }
    이 상황에서 using을 사용하면
    template<typename T, typename U>
    inline void some_function(T& x, T& y, const U& z, int i){
        using std::swap;
        ...
        ::swap(x, y);    // ADL을 포함한다. => 클래스 내의 함수와 기본 함수 둘다 고려하나, 인수타입이 표준 구현보다 구체적이어서 클래스의 함수가 쓰인다.
        ...
    }
    이를 통해 클래스 내에 구현한 포인터 교환을 사용할 수 있다.

    물론 기본 swap구현은 C++11부터는 move를 통해 두 인수와 임시 변수 사이의 값을 이동하도록 구현한다.
    template<typename T>
    inline void swap(T& x, T& y){
        T tmp(move(x));
        x = move(y);
        y - move(tmp);
    }
    사용자 정의로 구현한 swap이 없는 타입의 경우 빠른 이동 생성자 및 이동 할당 연산자를 제공하면 두 데이터를 효과적으로 바꿀 수 있다.
    결과적으로 사용자 정의로 구현하지 않고, 이동 연산을 지원하지도 않는 타입만 복사된다.
*/


int main() {
    statistics::window win();
    GUI::window windo();


    return 0;
}