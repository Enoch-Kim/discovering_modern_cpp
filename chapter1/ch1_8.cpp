/*
    20-02-09 ~ 20-02-11 Enoch Kim
    cpp 교재 <모던 C++입문> 1강
    + https://boycoding.tistory.com/199 의 포인터 개념 참조
    1.8
*/

#include <iostream>
#include <fstream>
#include <typeinfo>
#include <memory>
#include <vector>


// 선형대수연산 => 별루임
void vector_add(unsigned size, const double v1[], const double v2[], double s[]){
    for(unsigned i = 0; i < size; ++i){
        s[i] = v1[i] + v2[i];
        std::cout << "s[i] is " << s[i] << std::endl;
    }
}

// unique_ptr 
std::unique_ptr<double> f(){
    return std::unique_ptr<double> (new double);
}

// shared_ptr
std::shared_ptr<double> ff(){
    std::shared_ptr<double> p1(new double);
    std::shared_ptr<double> p2(new double), p3 = p2;
    std::cout << "p3.use_cout() = " << p3.use_count() << std::endl;
    return p3;
}

// reference
double* square_ref (double d) {
    double s = d * d;
    return &s;
}
    // 이 경우 square_ref가 더이상 존재하지 않는 s를 참조하기 때문에 안된다.
 
double& square_ref2(double d) {
    double s = d*d;
    return s;
}
    // 이 포인터는 스코프를 벗어난 지역 주소를 갖는다. 이를 댕글링 포인터라 한다.

// vector
void vector_add2(const std::vector<float>& v1, const std::vector<float>& v2, std::vector<float>& s){
    assert(v1.size() == v2.size()); // 크기를 알고있어 일치여부 확인하기 쉽다.
    assert(v1.size() == s.size());
    for (unsigned i = 0; i < v1.size(); ++i)
        s[i] = v1[i] + v2[i];
}

std::vector<float> vector_add3(const std::vector<float>& v1, const std::vector<float>& v2){
    assert(v1.size() == v2.size());
    std::vector<float> s(v1.size());
    for(unsigned i = 0; i < v1.size(); ++i)
        s[i] = v1[i] + v2[i];
        return s;
}   // 벡터는 복사 가능 => 함수에 반환 가능

       

int main() {

    // https://boycoding.tistory.com/199 [소년코딩] 참고
    {    
        int x = 5; std::cout << x << '\n'; // print the value of variable x 
        std::cout << &x << '\n'; // print the memory address of variable x 
        std::cout << *&x << '\n'; /// print the value at the memory address of variable x 

        int* iPtr; // int형 포인터 
        double* dPtr; // double형 포인터 
        int* iPtr2, *iPtr3; // int형 두 개의 포인터 선언 => 보이는 대로 오른쪽의 변수를 포인터로 만들기위해서는 변수앞에 *을 추가해야한다.
        int *iPtr4, *iPtr5; // 그래서 이렇게 각 변수에 포인터를 붙이는게 더 보기에 좋다.
    }
    {
        int value = 5; int *ptr = &value; // 변수 값의 주소로 ptr 초기화 
        std::cout << &value << '\n'; // value 변수의 주소 출력 
        std::cout << ptr << '\n'; // ptr 변수 값 출력 return 0;

        //이 블럭의 ptr값과 위 블럭의 x값이 같은것을 보아 이 컴에서는 첫 주소값이 0x7ffeec4cc268 인것같다.
    }
    {
        int iValue = 5; 
        double dValue = 7.0; 
        int *iPtr = &iValue; // ok => int *iPtr = &dValue; 는 오류 왜냐하면 자료형이 다르다.
        double *dPtr = &dValue; // ok
            //int *ptr = 5; => 주소값이 정수 리터럴일 수 없다.
            // int *ptr = 0x7ffeec4cc268; => 이것도 정수 리터럴로 취급하기 때문에 주소값으로 볼 수 없다.
        int x = 4; 
        std::cout << typeid(&x).name() << std::endl; // typeid는 인수의 자료형을 반환한다.
        // 주소연산자 &는 주소값을 반환하지 않고 주소를 가르키는 포인터를 반환한다.
        // 역참조연산자 *는 주소값에 해당하는 value를 반환한다.
        // 결국 포인터는 자료형을 가져야한다. 그래야 그 주소에 해당하는 값을 어떻게 해석할지 알 수 있다.
        // 또한 위의 포인터에 할당하는 주소값도 포인터와 동일한 자료형을 가져야한다.
    }
    {
        int value = 5; int *ptr = &value; // ptr points to value 
        std::cout << "ptr is " << ptr << "\n"
                  << "*ptr is " << *ptr << std::endl;
        *ptr = 7; // *ptr is the same as value, which is assigned 7 
        std::cout << value << std::endl; // prints 7
        // 포인터 주소의 값을 변경하면 해당하는 변수의 값도 변경 

    }
    {
        char *chPtr; // chars are 1 byte 
        int *iPtr; // ints are usually 4 bytes 
        struct Something { int nX, nY, nZ; }; Something *somethingPtr; // Something is probably 12 bytes 
        std::cout << sizeof(chPtr) << '\n'; // prints 8 
        std::cout << sizeof(iPtr) << '\n'; // prints 8
        std::cout << sizeof(somethingPtr) << '\n'; // prints 8
        // pointer's size is always 32bit => 4byte or 64bit => 8byte
    }

    // <모던 C++입문>

    {       
        float v[] = {1.0, 2.0, 3.0};
        float w[] = {7.0, 8.0, 4.0};
        int y[] = {1.0, 2.0};           // not allowed in cpp 11

        float x[3];
        for (int i = 0; i < 3; ++i){
            x[i] = v[i] - 3.0 * w[i];
        }
        float a[3][4];
        int b[3][1][3];
    }

    {
        double x[] = {2, 3, 4}, y[] = {4, 2, 0}, sum[3];
        vector_add(3, x, y, sum);
        vector_add(sizeof x / sizeof x[0], x, y, sum);      // 배열의 크기 계산 방식 but 배열의 크기 일치여부 알 수 없다.
        std::cout << "sizeof x is " << sizeof x << "\n"
                << "sizeof x[0] is " << sizeof x[0] << std::endl;

        std::ifstream ifs("some_array.dat");
        int size;
        ifs >> size;
        std::cout << "size is " << size << std::endl;
        float v[size];          // 컴파일 타임에 크기를 알지 못한다.
        for(int i = 0; i < size; i++)
        ifs >> v[i];
    }
    /*
        위의 배열 선언 형태는 두가지의 문제가 있음
        1. 배열 접근시 인덱스 검사를 하지 않아 크러쉬 발생 가능성 있음. => 새로운 배열 타입
        2. 배열의 크기는 컴파일 타임을 알고있어야 한다.              => 동적할당으로 해결
    */

    {
        std::ifstream ifs("some_array.dat");
        int size;
        ifs >> size;
        std::cout << "size is " << size << std::endl;
        float* v = new float[size];
        for(int i = 0; i < size; i++)
            ifs >> v[i];
    /* 
        배열의 동적할당도 범위를 벗어날 시 충돌이 일어난다. 
        그러니 배열의 크기를 저장하고, 불필요시 메모리에서 삭제해야한다.
    */
        delete[] v;
        
        double *x = new double[3], *y = new double[3], *sum = new double[3];
        std::cout << "x is " << x << "\n"
                  << "*x is " << *x << std::endl;
        for(unsigned i = 0; i < 3; ++i){
            x[i] = i + 2, y[i] = 4.2 * i;
            std::cout << x[i] << "  " << y[i] << std::endl;
            std::cout << "x is " << x << "\n"
                      << "*x is " << *x << std::endl;       // 이건 항상 x 주소에 있는 값을 가져오므로 x[0]을 가져온다.
        }
        vector_add(3, x, y, sum);                           // 포인터를 사용하면 sizeof 사용불가 오직 포인터 크기만 반환한다.

        std::cout << "*(x+1) is " << *(x + 1) << std::endl;  // 이건 x 주소 다음 값을 가져오므로 x[1]을 가져온다.
        /* 
            대부분의 상황에서 배열과 포인터를 바꿔쓸 수 있다. 
            배열의 인수로 포인터를 전달할 수 있고, 포인터의 인수로 배열을 전달할 수 있다.
            배열의 인수와 포인터의 인수가 다른점은 정의다. 
            크기가 n인 배열을 정의하면 n개의 항목에 대한 공간을 예약하고,
            포인터를 정의하면 주소를 보유할 공간만 예약한다.
        */

        int* ip = new int;
        std::cout << "*ip is " << *ip << std::endl;
        std::cout << "ip is " << ip << std::endl;
        *ip = 3;
        delete ip;
        ip = new int;
        std::cout << "   *ip is " << *ip << std::endl; // 이게 대체 왜 3이 나오는거지 delete를 때렸는데 ;;;
        std::cout << "*&*ip is " << *&*ip << std::endl;
        std::cout << "&*ip is " << &*ip << std::endl;
        std::cout << "ip is " << ip << std::endl;   
        std::cout << "&ip is " << &ip << std::endl; // 포인터의 주소값 => delete를 때려도 ip 포인터 자체가 사라지지 않는 이유다.
        // 모르겠다.. 언젠가 알겠지...
        ip = nullptr;
            // std::cout << "*ip is " << *ip << std::endl; => null화 된 포인터를 참조하면 그다음부터 종료는 안되지만 작동 x
            // ip = NULL;    nullptr만 쓰자

        int *ip1 = new int[3];
            // delete ip1; => 이건 [0]의 메모리만 삭제하기 때문에 잘못된 방식
        delete[] ip1;

        int i = 7;
        int *ip2 = &i;
        int j = *ip2;
        std::cout << "i is " << i << '\n'
                  << "ip is " << ip2 << '\n'
                  << "*ip is " << *ip2 << '\n'
                  << "j is " << j << std::endl;
    }

    /*
        포인터의 위험한 점은 메모리 누수! 그에 대한 해결책은???
        1. 표준 컨테이너를 사용하라 => 표준 라이브러리나 유효성이 검증된 라이브러리를 사용하라!
        2. 캡슐화를 해라! => 클래스에서 동적 메모리 관리는 클래스당 한번만! RAII원칙?? 
        3. 스마트 포인터를 활용하라.
    */

    // 스마트 포인터 
    // if there is not allowed to use C++11, Useing Boost's smart pointer.
    {
        // unique_ptr
        std::unique_ptr<double> dp (new double);
        *dp = 7;
            // double d;
            // std::unique_ptr<double> dd {&d}; => 정적 주소를 할당하면 오류, dd의 소멸자가 d를 삭제하려 하기 때문이다.
            // std::unique_ptr<double> d {dp}; => 다른 포인터 타입에 할당될 수 없음
            // std::unique_ptr<double> d;
            // d = dp;                        => 같음
        double *d = dp.get(); // get을 통해 데이터를 얻음
        *d = *dp.get();
        std::cout << "dp's value is " << *dp.get() << std::endl;
        
        std::unique_ptr<double> dp2(move(dp)), dp3;
        dp3 = move(dp2);
        
        std::unique_ptr<double> d2;
        d2 = f(); // 여기서는 move()필요없다. 왜냐면 함수 결과가 이동될 임시 값이기 때문이다.

        std::unique_ptr<double[]> dArray (new double[3]);
        for(unsigned i = 0; i < 3; ++i)
            dArray[i] = i + 2;
        /*
            이 방식으로 delete[]가 적절히 이루어진다.
            그러나, * 배열에서 사용 못함
        */
        
    }

    // shared_ptr
    {   
        // 여러 파티에서 각각의 포인터로 공통된 메모리를 관리한다. 
        // 하나도 남지않으면 메모리 해제.
        std::shared_ptr<double> p = ff();
        std::cout << "p.use_count() is " << p.use_count() << std::endl;
        
        // 가능하다면 make_shared를 통해 shared_ptr을 만들어야함 => 이러면 단순화를 위해 자동 타입추론을 사용할 수 있다??? 이건 아직 모르겠다.
        std::shared_ptr<double> p1 = std::make_shared<double>();
        /* 
            https://stackoverflow.com/questions/20895648/difference-in-make-shared-and-normal-shared-ptr-in-c 을 참고한 결과
            F(std::shared_ptr<Lhs>(new Lhs("foo")), std::shared_ptr<Rhs>(new Rhs("bar")));
            이것은 new Lhs()와 std::shared_ptr을 같이 사용하고 싶지만 new Lhs()에서 예외를 발생시키기에 
            F(std::make_shared<Lhs>("foo"), std::make_shared<Rhs>("bar")); 이처럼 make_shared를 사용하는것이 선호된다고 한다.
        */

    }
    
    // weak_ptr 
    {
        //http://egloos.zum.com/sweeper/v/3059940를 참고
        // strong refCount = 1
        std::shared_ptr<int> sp1(new int(5));
    
        // shared_ptr sp1으로부터 복사 생성
        // weak_ptr이 참조하여, strong refCount = 1, weak refCount = 1
        std::weak_ptr<int> wp1 = sp1;
        {
            // wp1이 참조하고 있던 sp1을 weak_ptr::lock 메써드를 이용해 sp2가 참조
            // string refCount = 2, weak refCount = 1
            std::shared_ptr<int> sp2 = wp1.lock();
            if (sp2)
            {
                // weak_ptr<_Ty>의 _Ty 포인터에 엑세스 하려면
                // 이렇게 shared_ptr로 convert하는 방법 밖에 없다
            }
            // sp2가 여기에서 소멸, strong RefCount = 1, weak refCount = 1
        }
    
        // sp1.reset으로 인해 strong refCount = 0, 즉 sp1 소멸
        // wp1이 참조하고 있던 sp1이 소멸되었으므로, wp1은 expired
        sp1.reset();
    
        // expired된 wp1은 참조하고 있는 shared_ptr이 없다.
        // 따라서, sp3도 empty
        std::shared_ptr<int> sp3 = wp1.lock();
        if (sp3)
        {
            // 여기 문장은 실행되지 않는다
        }
        /*
            weak_ptr은 다음과 같은 경우에 사용하면 유용하다.
            어떠한 객체를 참조하되, 객체의 수명에 영향을 주고 싶지 않은 경우
            그리고 매번 특정 객체의 ID로 컬렉션에서 검색하고 싶지 않을 경우
            그러면서 dangling pointer의 잠재 위험성을 없애고 싶을 때
        */

    }

    // reference
    {
        int i = 5;
        int& j = i; // 무조건 변수를 같이 할당해야한다. const와 비슷
        j = 4;
        std::cout << "i = " << i << std::endl;
        /*
            함수 인수로 사용
            다른 개체의 부분참조 (벡터의 7번째 요소??)
            뷰 구축에 매우 유용

            정적인 메모리를 다룰때는 레퍼런스를 사용하자
            포인터는 동적 메모리만 다룰때 사용해야한다.
        */
        
       
    }

    // vector
    {
        std::vector<float> v(3), w(3), s(3), s1(3);
        v[0] = 1; v[1] = 2; v[3] = 3;
        w[0] = 7; w[1] = 8; v[2] = 9;
        // equal to     std::vector<float> v = {1, 2, 3}, w = {7, 8, 9};
        vector_add2(v, w, s);
        std::cout << "s[0] is " << s[0] << '\n';
        s1 = vector_add3(v, w);
        std::cout << "s1[0] is " << s1[0] << std::endl;
        /*
            vector는 수학적의미의 벡터가 아니나(산술연산이 없다) 과학적 애플리케이션에 매우 유용하다.
        */
    }


    return 0;
}


