/*
    20-03-04 Enoch Kim
    cpp 교재 <모던 C++입문> 3강
    3.7 타입이 아닌 템플릿 매개변수
    https://github.com/gilbutITbook/006828/blob/master/c%2B%2B11/fsize_vector.cpp 참고

*/

#include <cassert>
#include <iostream>
#include <cmath>
#include <algorithm>

/*
    우리는 템플릿 매개변수로 타입만 사용했지만
    정수와 bool값도 사용이 가능하다. (포인터도 사용 가능하지만 생략한다.)
*/
template <typename T, int Size>         // size를 매개변수로 받았다.
class fsize_vector 
{
    using self= fsize_vector;
    void check_index(int i) const { assert(i >= 0 && i < my_size); }
  public:  
    using value_type= T;
    const static int     my_size= Size;

    fsize_vector(int s= Size) { assert(s == Size); }

    fsize_vector(const self& that)
    {
	std::copy(that.data, that.data + Size, data);
    }

    self& operator=(const self& that) 
    {
	std::copy(that.data, that.data + Size, data);
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

    self operator+(const self& that) const 
    {
	self sum;
	for (int i= 0; i < my_size; ++i) 
	    sum[i]= data[i] + that[i];
	return sum;
    }
  private:
    T     data[my_size];
};
/*
    위와 같이 size를 매개변수로 받으면, 컴파일 타임에 크기를 알 수 있기 때문에 컴파일러에 따라 최적화를 실행한다.
    다음과 같은 루프 풀기(loop unrolling)가 예이다.
    self operator+(const self& that) const{
        self sum;
        sum[0] = data[0] + that[0];
        sum[1] = data[1] + that[1];
        sum[2] = data[2] + that[2];
        return sum;
    }
    카운트를 증가시키는 부분과 끝을 검사하는 부분을 생략할 수 있다.
    
    크기가 타입의 일부가 되기 때문에 벡터의 크기가 같은지 판단하는 검사를 생략할 수 있다.
    즉 인수의 타입이 같다면 암시적으로 같은 크기를 갖는다.
    fsize_vector<float, 3> v;
    fsize_vector<float, 4> w;
    vector<float> x(3), y(4);
    v = w;
    x = y;
    
    우리는 보통 벡터를 3차원으로 사용하기 때문에 3차원을 디폴트 값으로 설정할 수 있다.
    template<typename T, int Size = 3>
    class fsize_vector{
        // ...
    }
    int main() {
        fsize_vector<float> v, w, x, y;
        fsize_vector<float, 4> space_time;
        fsize_vector<float, 11> string;
    }
    
*/