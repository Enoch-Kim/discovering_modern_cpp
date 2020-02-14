/*
    20-02-12 Enoch Kim
    cpp 교재 <모던 C++입문> 2강
    2.3 ~ 2.3.3
    https://github.com/gilbutITbook/006828/blob/master/c%2B%2B03/vector_test.cpp 참고

    initializer_list에 관해서는 사용법이 달라진듯하다. 책과는 다름 나중으로 미룸
    
*/


#include <iostream>
#include <fstream>
#include <typeinfo>
#include <memory>
#include <vector>
#include <initializer_list>



class matrix_type {
    public :
        matrix_type(int r, int i) {

        }

};

class solver {
    public :
        solver (int nrows, int ncols) : A(nrows, ncols) {    // 이걸 설정하지 않을 시 컴파일러가 알아서 생성한다.
            // A(new_r, new_i); 생성자 안에서 멤버의 생성자를 호출할 수 없다.
        }

    private :
        matrix_type A;
};

/*
    이미 matrix가 존재하는 경우 복사본을 만들지 않고 기존의 것을 참조한다. (메모리 세이프)

    class solver {
        public :
            solver(matrix_type& A) : A(A){
                rows = A -> rows;
            }
        private :
            const matrix_type& A;

    };
*/
class complex {
    public :

        // 디폴트 생성자
        complex() : r(0), i(0) {

        }

        // 복사 생성자
        complex(const complex& c) : i(c.i), r(c.r) {

        }

        complex(double r, double i) : r(r), i(i) {

        }

        complex(double r) : r(r), i(0) {

        }

        // complex(std::initializer_list<complex> value): r(value.begin.get_r), i(value.begin.get_i){
            
        // }

        // complex& operator=(std::initializer_list<complex> value){
        //     r = value.begin.get_r;
        //     i = value.begin.get_i;
        // }

        double get_r (){
            return r;
        }

        double get_i () {
            return i;
        }

    private :
        double r, i;
};

class vector {
    public:
        

    private:
        unsigned my_size;
        double *data;
};

struct sloppy_complex
    {
        double r, i;
    };

int main() {

    /*
        생성자
        동일한 이름을 가지는 메소드

        디폴트 생성자
        인수가 없는 생성자 또는 모든 인수가 기본값을 갖는 생성자.
            필요한 이유
            1. 외부 스코프의 불필요한 변수 유지를 없애기위해
            2. 디폴트 생성자가 없을 시 리스트, 트리, 벡터, 행렬과 같이 디폴트 생성자가 없는 타입의 컨테이너를 구현하기에 매우 번거롭기 때문에
        => 가능한 디폴트 생성자를 정의하라
        예외 : 멤버 중 일부가 레퍼런스일때... 조심하자...

        복사 생성자
        제대로 복사를 하고자 할 때, 복사 생성자를 정의하자
        만약 정의하지 않으면 컴파일러가 표준 생성방법에따라 복사를 진행한다.
        만약 표준 생성방법처럼 모든 값을 그저 복사하고 싶다 하더라도 기본값을 사용해야하는 이유가있다.
            1. 덜 장황하다.
            2. 오류가 덜 발생한다.
            3. 다른사람들은 코드를 읽지 않고도 복사 생성자가 하는일을 바로 알고 있다.
            4. 컴파일러가 더 많은 최적화를 할 수 있다.

        complex(complex& c) => 이처럼 변경 가능한 레퍼런스로 사용하는 건 부적절하다. 왜냐하면 변경 가능한 개체만 복사할 수 있기 때문이다.

        complex(complex c) => 왜 값을 전달하면 안될까??? => 값을 전달하려면 정의할 복사 생성자가 필요하지만...없잖아..이거잖아.
    */


    complex z1,
            // z2(),// => 이건 complex를 반환하는 함수로 취급해서 노답이다. Most Vexing Parse!!
        z3(4),
        z4(3.0,2.0),
        z5 = 4,
        z6(z4); // 복사
        // z7{z6}; // 복사 + 축소하지 않음 C++11 => 왜 오류로 뜨지... 삭제되었나... => initializer_list로 구현해야함

    sloppy_complex zz{3.66, 2.33};


    return 0;
}

/*

    https://github.com/gilbutITbook/006828/blob/master/c%2B%2B03/vector_test.cpp

    #include <cassert>
    #include <iostream>

    class vector 
    {
    public:
        vector(int size) : my_size(size), data(new double[size]) {}

        vector() : my_size(0), data(0) {}

        ~vector() { delete[] data; }

        // vector(const vector& that)                                       => 포인터를 새로 생성하지 않아 동일 주소 즉, 같은 데이터를 가르킴
        //   : my_size(that.my_size), data(new double[my_size])                 + 하나를 삭제할때 동일 주소기 때문에 다른 하나의 소멸자 호출이 실패한다.
        // {
        // for (int i=0; i<my_size; ++i) { data[i] = that.data[i]; }
        // }

        // void operator=(const vector& that) 
        // {
        // assert(that.my_size == my_size);
        // for (int i=0; i<my_size; ++i) 
        //     data[i] = that.data[i];
        // }

        int size() const { return my_size; }
        int size() { return my_size; }

        double& operator[](int i) const {
        assert(i>=0 && i<my_size);
        return data[i];
        }

        double& operator[](int i) {
        assert(i>=0 && i<my_size);
        return data[i];

        }

        // vector operator+(const vector& that) const {
        // assert(that.my_size == my_size);
        // vector sum(my_size);
        // for (int i= 0; i < my_size; ++i)
        //     sum[i] = (*this)[i] + that[i]; 
        // return sum;
        // }

    private:
        int     my_size;
            //double* data;
        std::unique_ptr<double[]> data; => 메모리를 자동 해제하고, 컴파일러의 복사 생성자의 호출을 막는다
    };

    std::ostream& operator<<(std::ostream& os, const vector& v)
    {
    os << '[';
    for (int i= 0; i < v.size(); ++i) os << v[i] << ',';
    os << ']';
    return os;
    }

    double dot(const vector& v, const vector& w) 
    {
        double s;
        for (int i= 0; i < v.size(); i++)
        s+= v[i] * w[i];
        return s;
    }

    int main() {
    vector v(4);
    v[0] = v[1] = 1.0; v[2] = 2.0; v[3] = -3.0;
    std::cout << v << std::endl;

    vector w(v.size());
    w = v;

    const vector z(w);
    std::cout << "z[3] is " << z[3] << '\n';

    std::cout << "w is " << w << '\n';
    v[1]= 9.;
    std::cout << "w is " << w << '\n';
    std::cout << v << std::endl;
    std::cout << z << std::endl;


    return 0;
    }

*/

/*
    암시적 생성자
    생성자 표기법은
    1. complex c1{3.0} // cpp11
    2. complex c1(3.0)
    3. complex c1 = 3.0
    4. complex c1 = pi * pi * 4;
    
    만약 vector class가 사이즈를 생성자로 받고
    class vector{
        public :
            vector(int n) : my_size(n), data(new double[my_size]){}
    };
     스칼라 곱을 계산하는 함수는 인수로 두 벡터를 받는다 할때,
    double dot (const vector& v1, const vector& v2){...}

    dot(8, 8)을 실행 시 생성자에서 8을 넣어 사이즈가 8인 벡터 두개를 생성하는 상황이 벌어진다
    이러한 오류를 방지하기 위해서 explicit속성을 추가하는데, 다음과 같다.
    class vector {
        public :
            explicit vector(int n) : my_size(n), data(new double[my_size]){}
    }
    이러한 명시적 생성자는 단일 인자 생성자 뿐만 아니라 cpp11의 유니폼 초기화에서도 중요하다.
*/

/*
    생성자 위임
    중복된 생성자 코드를 줄이는 cpp11의 기능
    class complex {
        public :
            complex(double r, double i) : r{r}, i{i} {}
            complex(double r) : complex{r, 0.0} {}
            complex() : complex{0.0, 0.0} {}
    }
    => 개꿀일거다.

    멤버 기본값
    생성자에서 기본값 설정을 해야하는 귀찮음을 해결해준 cpp11기능
    class complex {
        public :
            complex(double r, double i) : r{r}, i{i} {}
            complex(double r) : r{r} {}
            complex(double i) : i{i} {}
            complex() {}
        
        private :
            double r = 0.0, i = 0.0;
    }

    => 멤버 기본값과 생성자 위임을 활용하면 복잡한 클래스에서 초기화가 더 쉬워진다.


*/

/* 
    할당
    x = y;
    u = v = w = x; 이와 같은 식으로 기존 개체를 복사하고자할 때
    클래스는 할당 연산자를 제공해야한다.
    class complex {
        public :
            ...
            complex& operator=(const complex& src){
                r = src.r; i = src.i;
                return *this;
            }
    };
    개체 타입의 값을 할당하는 연산자를 복사 할당 연산자라고 하며 컴파일러에서 사용자 정의로 구현할 수 있다.

    만약 double타입의 값을 complex에 할당한다면?
    c = 7.5; => 암시적 변환을 통해 double로 생성자를 통해 complex를 생성, 그 후 할당
    그러므로 성능관련 문제가 있을 시 double타입의 할당 연산자를 추가하자
    class complex {
        public :
            ...
            complex& operator=(const complex& src){
                r = src.r; i = src.i;
                return *this;
            }

            complex& operator=(const double& nr) {
                r = nr; i = 0;
                return *this;
            }
    };

    vector의 경우 데이터 자체가 아닌 데이터의 주소만 할당하므로 꼭 복사생성자와 동일한 방식을 취해주자
    vector& operator=(const vector& v){
        if(this == &src)
            return *this;
        assert(my_size == src.my_size);
        for(int i = 0; i < my_size; ++i)
            data[i] = src.data[i];
        return *this;
    }
*/

/*
    초기화 리스트 (!= 멤버초기화리스트)
    float v[] = {1.0, 2.0, 3.0}; 과 같이 클래스도 값들로 초기화 가능
    vector v = {1.0, 2.0, 3.0}; or
    vector v{1.0, 2.0, 3.0};으로 선언 
    v = {2.0, 3.0, 4.0};과 같이 할당도 가능
    vector x = lu_solve(A, vector {1.0, 2.0, 3.0}); 과 같이 함수 인수로 바로 호출 가능
    이를 위해서는 클래스에서 인수로 initializer_list<double>을 받는 생성자와 복사할당연산자가 필요하다.
    두가지 방식이 있는데
    1. 생성자와 복사할당연산자 각각 구현하는 방식
    class vector {
        //...
        vector(std::initializer_list<double> values) : my_size(values.size(), data(new double[my_size]){
            std::copy(std::begin(values), std::end(values), std::begin(data));
        }

        vector& operator=(std::initializer_list<double> values){
            assert(my_size == values.size());
            std::copy(std::begin(values), std::end(values), std::begin(data)); // begin && end functions are cpp11
            return *this;
        }
    }
    2. 생성자를 구현하고 복사할당연산자에서 이를 사용하는 방식
        (생략)
*/

/*
    유니폼 초기화
    

*/
