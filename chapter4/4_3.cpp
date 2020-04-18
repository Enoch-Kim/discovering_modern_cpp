/*
    20-04-16 Enoch Kim
    cpp 교재 <모던 C++입문> 4강
    4.3 메타 프로그래밍 입문
    
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <numeric>
#include <iterator>
#include <limits>
#include <type_traits>
#include <unordered_map>
#include <functional>
#include <chrono>

template <typename T>
inline void test(const T& x){
    using std::cout;
    cout << "x = " << " (";
    int oldp = cout.precision(std::numeric_limits<T>::digits10 + 1);
    cout << x << ")" << '\n';
    cout.precision(oldp);
}

template<typename Container>
typename Container::value_type
inline minimum(const Container& c){
    using vt = typename Container::value_type;
    vt min_value = std::numeric_limits<vt>::max();
    for(const vt& x:c){
        if(x < min_value)
            min_value = x;
    }
    return min_value;
}

struct simple_point{
    #ifdef __cplusplus
        simple_point(double x, double y):x(x), y(y){

        }
        simple_point() = default;
        simple_point(std::initializer_list<double> il){
            auto it = begin(il);
            x = *it;
            it++;
            y = *it;
        }
    #endif
        double x,y;
};

int main() {
    using namespace std;
    test(1.f/3.f);
    test(2. / 3.);
    test(1. / 3.l);

    cout << "simple_point is pod = " << boolalpha
        << is_pod<simple_point>::value << endl;
    unordered_map<int, int> m;
    m[23] = 1;
    m[12] = 3;
    m[14] = 23;
    for(auto&i : m){
        cout << i.first << '\n';
    }
    vector<vector<int>*> vv;
    vector<int> v{0, 2, 3,4};
    vv.push_back(&v);
    vv[0]->push_back(1);
    cout << v[4] << '\n';
    cout << vv[0] -> at(4) << '\n';
    vector<reference_wrapper<vector<int>>> vv2;
    vv2.push_back(v);
    vv2[0].get().push_back(5);
    cout << vv2[0].get()[5] << '\n';
    using namespace chrono;
    time_point<system_clock> now = system_clock::now(), then = now + hours(2);
    time_t then_time = system_clock::to_time_t(then);
    cout << "Darling, I'll be with you at " << ctime(&then_time);
}