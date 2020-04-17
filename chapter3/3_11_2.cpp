/*
    20-03-17 Enoch Kim
    cpp 교재 <모던 C++입문> 3강
    3.11 연습문제 4 ~
*/

#include <bits/stdc++.h>

// Q4
template <typename T>
struct const_vector_iterator{
    typedef T value_type;
    const_vector_iterator(T* data) : data(data) {}

    const T& operator*() { return *data; }
    const T& operator*() const { return *data; }
    const_vector_iterator<T> operator++() { data += 1; return *this; }
    bool operator!=(const const_vector_iterator<T>& other) const { return data != other.data; }
    
    const T* data;
};

template <typename T>
struct vector_iterator{
    typedef T value_type;
    vector_iterator(T* data) : data(data) {}

    T& operator*() { return *data; }
    const T& operator*() const { return *data; }
    vector_iterator<T> operator++() { data += 1; return *this; }
    vector_iterator<T> operator--() { data -= 1; return *this; }
    bool operator!=(const vector_iterator<T>& other) const { return data != other.data; }
    
    T* data;
};

template<typename T>
class vector {
    public :
        vector(){}
        explicit vector(int size) : my_size(0), my_capacity(size), data(new T[my_capacity]) {}

        vector(const vector& that)
            : my_size(that.my_size), my_capacity(that.my_capacity), data(new T[my_capacity]){
            std::copy(&that.data[0], &that.data[that.my_size], &data[0]);
        }


        vector(const vector&& v) : my_size(v.my_size), my_capacity(v.my_capacity), data(std::move(v.data)){
            v.size = 0;
            v.capacity = 0;
            // v.data는 move를 통해 빈값이됌
        }

        vector& operator=(vector& v) {
            my_size = v.my_size;
            my_capacity = v.my_capacity;
            data.reset(new T[v.my_capacity]);
            std::copy(v.begin(), v.end(), begin());
            return *this;
        }
        
        vector& operator=(vector&& v) {
            my_size = v.my_size;
            my_capacity = v.my_capacity;
            data.swap(v.data);
            return *this;
        }

        T operator[](int i){
            assert(i < my_size);
            return data[i];
        }

        vector_iterator<T> begin(){
            return vector_iterator<T>(&data[0]);
        }

        vector_iterator<T> end(){
            return vector_iterator<T>(&data[my_size]);
        }

        const_vector_iterator<T>  cbegin(){
            return const_vector_iterator<T>(&data[0]);
        }
        const_vector_iterator<T>  cend(){
            return const_vector_iterator<T>(&data[my_size]);
        }

        void push_back(T t) {
            assert(my_capacity > my_size);
            data[my_size++] = t;
        }

        int size (){
            return my_size;
        }

        int capacity(){
            return my_capacity;
        }

        void resize(int newSize) {
            assert(my_capacity <= newSize);
            std::unique_ptr<T[]> newData = new T[newSize];
            std::copy(begin(), end(), &newData[0]);
            data.swap(newData);
            my_capacity = newSize;
        }


    private :
        int my_size;
        int my_capacity;
        std::unique_ptr<T[]> data;
};



template <typename T>
std::ostream& operator<<(std::ostream& os, vector<T>& v)
{
  os << '[';
  for (int i= 0; i < v.size(); ++i) os << v[i] << ',';
  os << ']';
  return os;
}


int main () {

    vector<float> v( 4 );
    v.push_back(1.0); 
    v.push_back(1.0);
    v.push_back(2.0);
    v.push_back(-3.0);
    sort(v.begin(), v.end());
    vector<float> v1(v);
    vector<float> v3(3);
    v3 = v1;
    v = vector<float>();
    std::cout << "v is " << v << '\n';
    std::cout << "v1 is " << v1 << '\n';
    std::cout << "v3 is " << v3 << '\n';
    std::cout << "v3 is " << v3 << '\n';
    return 0;
}
