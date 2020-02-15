/*
    20-02-14 Enoch Kim
    cpp 교재 <모던 C++입문> 2강
    2.4
    
*/

/*
    소멸자
    소멸자는 개체를 파괴할 때마다 호출되는 함수
    소멸자 앞에는 ~을 붙이는데 이것은 생성자의 보수 연산을 행하기 때문이다.
    오직 하나의 오버로드만 있고 인수가 없다.

    소멸자 구현규칙
    1. 소멸자에서는 절대로 예외를 던지면 안된다. 프로그램 크래시가 발생하고 예외도 발견할 수 없을 확률이 높다.
    2. 클래스에 virtual함수가 포함되어 있으면 소멸자도 virtual이어야 한다.

    리소스 처리
    소멸자에서는 개체의 리소스(메모리, 파일 핸들, 소켓, 락...)를 해제하고 더 이상 필요하지 않은 개체와 관련된 모든 것들을 정리하는 일을 한다.
    다른 것들도 할 수 있지만. 프로그램의 안정성을 위해 리소스 해제만을 다루는 것이 좋다.

*/

class vector {
    public :
        // ...
        ~vector() {
            delete[] data;
        }
        // ...
    private :
        unsigned my_size;
        double *data;
}


int main() {
    
}