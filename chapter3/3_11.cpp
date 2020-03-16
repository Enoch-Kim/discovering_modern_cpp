/*
    20-03-07 Enoch Kim
    cpp 교재 <모던 C++입문> 3강
    3.11 연습문제 1 ~ 3
*/

#include <cassert>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <sstream>
#include <memory>
#include <initializer_list>


// Q1
class testClass {
    public :
        testClass (char c) : c(c) {}
        friend std::stringstream& operator<<(std::stringstream& ss, testClass &TestClass); // getC하기 싫어서 함
    private :
        char c;
};

std::stringstream& operator<<(std::stringstream& ss, testClass &TestClass)
{
    ss << TestClass.c;
    return ss;
}


std::string to_string(std::string s){
    return s;                  
}

template <typename T>\
std::string to_string( T& t){
    std::stringstream ss;
    ss << t;
    std::string s = ss.str();
    return s;
}

// Q2
template <typename Last>
void to_tuple_string_aux(std::stringstream& ss, Last p){
    ss << p << ')';
}

template <typename First, typename ...Parameters>
void to_tuple_string_aux(std::stringstream& ss, First f, Parameters ...p){
    ss << f << ',' << ' ';
    to_tuple_string_aux(ss, p...);
};

template <typename ...P>
std::string to_tuple_string(P ...p) {
    std::stringstream ss;
    std::string s;
    ss << '(';
    to_tuple_string_aux(ss, p...);
    s = ss.str();
    return s;
};

// Q3
template <typename StackType>
class GenericStack {    // top pop push, clear, size, full, empty
    public :
        
        GenericStack() : capacity(10), stackSize(0), stack() {}
        
        GenericStack(int capacity) : capacity(capacity) ,stack(), stackSize(0) {}

        GenericStack(std::initializer_list<StackType> values) : capacity(values.size()), stackSize(capacity), stack(new StackType[capacity]){
            std::copy(std::begin(values), std::end(values), stack);
        }

        GenericStack& operator=(std::initializer_list<StackType> values){
            assert(capacity >= values.size());
            std::copy(std::begin(values), std::end(values), stack);
            return *this;
        }

        ~GenericStack(){
            delete[] stack;
        }

        void resize(int size) {
            capacity = size;
        }

        int size () {
            return stackSize;
        }

        bool full () {
            return capacity == stackSize;
        }

        bool empty() {
            return stackSize;
        }


        StackType top() {
            assert(stackSize);
            return stack[stackSize - 1];
        }

        void pop() {
            if(stackSize == 0) return;
            stack[stackSize - 1] = 0;
            --stackSize;
        }

        void push(StackType data) {
            assert(!full());
            stack[stackSize] = data;
            ++stackSize;
        }

        void clear() {
            for(int i=0; i < stackSize; ++i)
                stack = NULL;
            stackSize = 0;
        }        

    private :
        int                             capacity;
        int                             stackSize;
        StackType                       *stack;    // unique_ptr 쓰고싶지만... copy가 안돼서 못쓴다.
};

template <typename T>
class Stack{
    public :
        Stack(T data) : data(data){}

        ~Stack() {
            delete data;
        }

        Stack operator=(T newData){
            data = newData;
            return *this;
        }

        T get() {
            return data;
        }

    private :
        T data;
};


// class GenericStack1 {    // top pop push, clear, size, full, empty
//     public :
        
//         GenericStack1() : capacity(10), stackSize(0), stack() {}
        
//         GenericStack1(int capacity) : capacity(capacity) ,stack(), stackSize(0) {}

//         template <typename ...StackType>
//         GenericStack1(StackType ...values) : capacity(sizeof...(StackType)), stackSize(capacity), stack(new Stack<StackType...>[capacity]){
//             push(values...);
//         }

//         ~GenericStack1(){
//             for(int i=0; i < stackSize; ++i)
//                 delete stack[i];
//         }

//         void resize(int size) {
//             capacity = size;
//         }

//         int size () {
//             return stackSize;
//         }

//         bool full () {
//             return capacity == stackSize;
//         }

//         bool empty() {
//             return stackSize == 0;
//         }


//         auto top() {
//             assert(stackSize);
//             return stack[stackSize - 1] -> get();
//         }

//         void pop() {
//             if(stackSize == 0) return;
//             delete stack[stackSize-1];
//             stack[stackSize - 1] = NULL;
//             --stackSize;
//         }
//         template<typename D>
//         void push( D data) {
//             assert(!full());
//             stack[stackSize] = new Stack<D>(data);
//             ++stackSize;
            
//         }

//         void clear() {
//             for(int i=0; i < stackSize; ++i){
//                 delete stack[i];
//                 stack[i] = NULL;
//             }
//             stackSize = 0;
//         }        

//     private :
//         int                              capacity;
//         int                             stackSize;
//         std::unique_ptr<Stack<StackType>>  *stack;    // unique_ptr 쓰고싶지만... copy가 안돼서 못쓴다.
        
// };

// 파이썬처럼 여러 타입을 받는 템플릿은 실패 ex {3.0 , 5, false, "fine"}



int main() {
    using namespace std;
    int testInt = 45234;
    double testDouble = 3.24324;
    char testChar = 'd';
    string testString = "test String";
    testClass TestClass{'j'};

    cout << "testChar to string is " << to_string(testChar) << '\n';
    cout << "testInt to string is " << to_string(testInt) << '\n';
    cout << "testDouble to string is " << to_string(testDouble) << '\n';
    cout << "testString to string is " << to_string(testString) << '\n';
    cout << "TestClass to string is " << to_string(TestClass) << '\n';
    
    cout << "tuple_string is " << to_tuple_string(1, 'd', TestClass, "hall", testInt, testDouble, testString) << '\n';
   
    GenericStack myStack{3.0, 4.0, 5.0};
    GenericStack myStack2{false, true, false};
    myStack.resize(10);
    myStack2.resize(10);
    cout << "myStack's size is " << myStack.size() << '\n';
    cout << "myStack2's size is " << myStack2.size() << '\n';
    cout << "myStack's top is " << myStack.top() << '\n';
    cout << "myStack2's top is " << myStack2.top() << '\n';
    myStack.pop();
    myStack2.pop();
    cout << "after myStack's pop is " << myStack.top() << '\n';
    cout << "after myStack2's pop is " << myStack2.top() << '\n';
    myStack.push(8.44);
    myStack2.push(true);
    myStack.push(10.3);
    // myStack2.push(7.7); -> type conversion occur
    cout << "after myStack's push is " << myStack.top() << '\n';
    cout << "after myStack2's push is " << myStack2.top() << '\n';
    cout << "myStack's size is " << myStack.size() << '\n';
    cout << "myStack2's size is " << myStack2.size() << '\n';
    myStack.clear();
    myStack2.clear();
    cout << "after myStack's clear size is " << myStack.size() << '\n';
    cout << "after myStack2's clear size is " << myStack2.size() << '\n';
    // cout << "after myStack2's clear top is" << myStack2.top(); assertion fail good


    GenericStack1 myStack3{3.0, true, 5};
    
    myStack3.resize(10);
    
    cout << "myStack's size is " << myStack3.size() << '\n';
    cout << "myStack's top is " << myStack3.top() << '\n';
    myStack3.pop();
    cout << "after myStack's pop is " << myStack3.top() << '\n';
    myStack3.push('c');
    cout << "after myStack3's push is " << myStack3.top() << '\n';
    myStack2.push("dcj");
    cout << "after myStack3's push is " << myStack3.top() << '\n';
    myStack.push(10.3);
    cout << "after myStack3's push is " << myStack3.top() << '\n';
    cout << "myStack3's size is " << myStack.size() << '\n';
    myStack3.clear();
    cout << "after myStack3's clear size is " << myStack3.size() << '\n';
    // cout << "after myStack2's clear top is" << myStack2.top(); assertion fail good
    
    

    return 0;
}