/*
    20-02-21 Enoch Kim
    cpp 교재 <모던 C++입문> 3강
    3.3
    https://github.com/gilbutITbook/006828/blob/master/c%2B%2B11/vector_template.cpp 참고
    https://github.com/gilbutITbook/006828/blob/master/c%2B%2B03/accumulate_example.cpp 참고
*/

#include <cassert>
#include <iostream>
#include <memory>
#include <algorithm>


/*
    클래스 템플릿
    함수 템플릿처럼 클래스도 템플릿화 할 수 있다.
    일상에서는 템플릿 클래스로 많이 불린다.
    템플릿 클래스는 데이터의 타입을 매개변수화 함으로써 벡터, 행렬 및 리스트와 같은 범용 컨테이너 클래스에 많이 쓰인다.

*/

template <typename T>
class vector 
{
        void check_size(int that_size) const { assert(my_size == that_size); }
        void check_index(int i) const { assert(i >= 0 && i < my_size); }
    public:
        explicit vector(int size)
        : my_size(size), data( new T[my_size] )
        {}

        vector()
        : my_size(0), data(0)
        {}

        vector(const vector& that)
        : my_size(that.my_size), data(new T[my_size])
        {
        std::copy(&that.data[0], &that.data[that.my_size], &data[0]);
        }

        vector& operator=(const vector& that) 
        {
        check_size(that.my_size);
        std::copy(&that.data[0], &that.data[that.my_size], &data[0]);
        return *this;
        }

        int size() const { return my_size; }

        const T& operator[](int i) const 
        {
        check_index(i);
        return data[i];
        }
                
        T& operator[](int i) 
        {
        check_index(i);
        return data[i];
        }

        vector operator+(const vector& that) const 
        {
        check_size(that.my_size);
        vector sum(my_size);
        for (int i= 0; i < my_size; ++i) 
            sum[i] = data[i] + that[i];
        return sum;
        }
    private:
        int                   my_size;
        std::unique_ptr<T[]>  data;
};
/*
    data 타입을 T로 매개변수화 하여 사용했다.
    특히 [] operator가 적절히 사용됐을을 보라

    템플릿 매개변수를 기본값으로 설정할 수 있다.
    struct row_major {};
    struct col_major {};
    struct heap {};
    struct stack{};

    template<typename T = double, typename Orientation = col_major, typename Where = heap>
    class vector;

    이 때, 벡터의 인수를 다음과 같이 선언할 수 있다.
    vector<float, row_major, heap> v;   
    vector<float, row_major> v;         // 위의 선언과 같다.
    vector<float, col_major, stack> v;  // 중간것이 생략가능할 때도 뒤에거가 안되면 생략해선 안된다.
    vector x; //  error => class로 간주된다.
    vector<> x; // 3개의 매개변수 모두 기본값과 동일하게 간주.

    템플릿의 기본 값은 함수 인수의 기본값 이외에 앞의 매개변수를 참조할 수 있다.
    template<typename T, typename U = T>
    class pair;
    이 때, 서로 다른 타입을 선언하지 않으면 하나만 선언해도 된다.
    pair<int, int> p1;
    pair<int> p1;   // 위와 같다.
*/

/*
    함수 템플릿을 작성한 후 클래스의 메서드 구현하냐와 클래스의 인터페이스를 개발한 뒤 이 인터페이스에 대한 제네릭 함수를 구현하냐는 상관없지만,
    제네릭 함수가 표준 라이브러리에서 내장 타입이나 클래스를 처리할 수 있어야 할 때에는 클래스를 변경할 수 없기에 인터페이스에 함수를 적용해야한다.
    그 대표적인 예가 다음의 사이트의 코드다.
    https://github.com/gilbutITbook/006828/blob/master/c%2B%2B03/accumulate_example.cpp
*/

/*
    배열에 있는 각 요소의 합을 구하기 위해서는 배열의 주소와 크기를 가져오는 제네릭 함수일 것이다.
    template<typename T>
    T sum(const T* array, int n){
        T sum(0);
        for(int i = 0; i < n; ++i){
            sum += array[i];
        }
        return sum;
    }

    배열의 크기를 컴파일러가 추론하게 할 수는 없을까?
    template<typename T, unsigned N>
    T sum(const T (&array)[N]){
        T sum(0);
        for (int i = 0; i < N; ++i)
            sum += array[i];
        return sum;
    }
    위와 같이 사용시 컴파일러가 배열의 크기를 추론한다.
    레퍼런스의 배열과는 달리 배열의 레퍼런스를 선언하려면 괄호가 필요하다.
    동일한 타입이면서 서로 다른 크기를 갖는 두 개의 배열을 더하면 함수가 두 번 인스턴스화된다.
    그럼에도 불구하고 이 작은 함수는 일반적으로 인라인되어 있기 때문에 실행 파일의 크기에는 영향을 미치지 않는다.
*/

/*
    리스트를 요소에 값과 다음 (혹은 이전 요소)의 레퍼런스를 포함하는 단순한 자료 구조다.
    cpp11은 이전 요소의 레퍼런스가 없는 리스트인 std::forward_list가 도입되었으나, 
    우리는 다음 요소의 레퍼런스만을 고려한 리스트를 만든다.
*/

template <typename T>
struct list_entry
{
    list_entry(const T& value) : value(value), next(0) {}

    T              value;
    list_entry<T>* next;
};

template <typename T>
struct list_iterator
{
    list_iterator(list_entry<T>* entry) : entry(entry) {}
    bool operator!=(const list_iterator<T>& that) const 
    { return entry != that.entry; }

    list_iterator<T> operator++() 
    { entry= entry->next; return *this; }

    list_iterator<T> operator++(int) 
    {
	list_iterator<T> tmp(*this);
	entry= entry->next;
	return tmp;
    }
    T& operator*() { return entry->value; }
    T operator*() const { return entry->value; }

  private:
    list_entry<T>* entry;
};

template <typename T>
struct list
{
    list() : first(0), last(0) {}
    ~list() { while (first) { list_entry<T> *tmp= first->next; delete first; first= tmp; } }
    void append(const T& x) { 
        last= (first ? last->next : first)= new list_entry<T>(x); // 매우 간결한 코드..ㅎㅎ..
    }

    // iterator을 사용하기 위한 부분
    list_iterator<T> begin() { return list_iterator<T>(first); }
    list_iterator<T> end() { return list_iterator<T>(0); }


    list_entry<T> *first, *last;
};

/*
    위의 리스트의 합도 간결하게 작성이 가능하다.
*/
template <typename T>
T sum(const list<T>& l)
{
    T sum= 0;
    for (list_entry<T>* entry= l.first; entry != 0; entry= entry->next)
	sum+= entry->value; // (*entry).value;
    return sum;
}

/*
    공통으로 사용할 수 있는 인터페이스 구현을 목표로 할 때, 우선 sum함수의 두 구현이 얼마나 비슷한가를 질문 해야 한다.
    차이점 :
        1. 서로 다른 방법으로 값에 접근한다.
        2. 서로 다른 방법으로 요소를 순회한다.
        3. 서로 다른 종료 기준을 갖는다.
    공통점 :
        1. 데이터 접근
        2. 다음 요소로 진행
        3. 끝을 확인
    결국 두 구현의 차이점은 타입에 따라 인터페이스를 사용해 이러한 작업들을 구현한다는 것이다.
    따라서 두 타입 모두에 대해 하나의 제네릭 함수를 제공하려면 공통의 인터페이스를 구축해야한다.
*/

/*
    앞의 인덱스를 활용한 배열의 합을 구하는 방법은 중간에 값이 비어있을 시 사용할 수 없다.
    이를 고치기 위해 포인터연산을 통해 구현하도록 하자.
*/
template <typename T>
inline T accumulate_array(T* a, T* a_end)
{
    T sum(0);
    for (; a != a_end; ++a)
	sum+= *a;
    return sum;
}

/*
    위의 함수는 다음과 같이 사용할 수 있다.
    int main (int argc, char* argv[]) {
        int    ai[]= {2, 4, 7};
        double ad[]= {2., 4.5, 7.};
        std::cout << "sum ai is " << accumulate_array(ai, &ai[3]) << '\n';  // &ai[3]을 통해 마지막 주소를 전해준다.
        std::cout << "sum ad is " << accumulate_array(ad, ad+3) << '\n';    // 포인터 연산을 통해 마지막 주소를 전달한다.
    }
    이와 같이 오른쪽의 개구간을 나타내는 한 쌍의 포인터(ex ai && &ai[3])를 범위(Range)라고 한다.
*/

/*
    위의 배열 시퀀스를 점진적으로 순회하는 보다 추상적인 개념의 인터페이스를 개선하면
    모든 컨테이너 타입과 기존 배열을 위한 공통 인터페이스를 사용할 수 있다.
    즉 반복자라는 일반화된 포인터를 구성함으로써 모든 알고리즘에 적용될 수 있게 한다. (코드는 위에 있다.)
*/
template <typename Iter, typename T>
inline T accumulate(Iter it, Iter end, T init)
{
    for (; it != end; ++it){
        std::cout << "it is " << *it << std::endl;
        init+= *it;
    }
	    
    return init;
}
/*
    이것은 다음과 같이 사용한다.
    std::cout << "sum l is " << accumulate(l.begin(), l.end(), 0.0) << '\n'; 

    위의 반복문에서는 사전 증가를 수행해야 entry멤버를 갱신하고 반복자를 가리키는 레버런스를 반환할 수 있다.
    만약 사후 증가를 사용하면 이전 값을 반환하고 다음번 반복자를 사용할 때 다음 리스트 요소를 참조하도록 내부 상태를 증가시킨다.
    이는 멤버 데이터를 변경하기 전에 반복자 전체를 복사하고 이 복사본을 반환할 때만 달성할 수 있다.
*/



int main() {

    list<float>  l;
    l.append(2.0f); l.append(4.0f); l.append(7.0f);// l.append(NULL); l.append(6.0f);
    std::cout << "sum l is " << accumulate(l.begin(), l.end(), 0.0) << '\n';
    return 0;
}