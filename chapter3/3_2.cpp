/*
    20-02-21 Enoch Kim
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

int main() {
    statistics::window win();
    GUI::window windo();


    return 0;
}