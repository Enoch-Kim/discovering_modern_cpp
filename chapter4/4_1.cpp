/*
    20-04-16 Enoch Kim
    cpp 교재 <모던 C++입문> 4강
    4.1 ~
    뭔가 적으면서 하니 효율성이 떨어진다 (차라리 여러번 반복 숙달해야겠다)
*/
#include <iostream>
#include <vector>
// #include <algorithm>
#include <utility>
#include <numeric>
#include <iterator>
/*
    utility의 begin cbegin end cend 등등 함수가 좋은 이유는
    만약 그냥 배열을 넣더라도 동작하기 때문인 것 같다. (포인터는 컴파일러가 크기를 알 수 없다 그러니 무조건 동적 배열은 벡터를 쓰자)

*/
template <typename T>
double calcSum(T& arr) {
    double ans = std::accumulate(std::begin(arr), std::end(arr), 0.0);
    return ans;
}

/*
    만약 반복자를 상수로 만들고 싶다면
    cbegin, cend 등을 사용하자. 매번 const로 캐스팅하는것은 가독성에 안좋다.
*/

/*
    벡터 vector
    벡터의 경우 기본 배열과는 다르게 항상 힙에 할당 되어있어서 (동적할당) 효율적이다.
    
    for(auto& i : v) 와 같이 각 요소를 가져올 때 &를 사용하면 생성하는 오버헤드가 없다.
    push_back의 경우 만약 capacity의 여유공간이 없다면 새로운 곳에 재할당하지만 여유공간이 있다면 빠른 추가를 한다.

    벡터의 capacity의 증가는 exponential하게 증가한다.

    resize()의 경우 증가시키는데는 문제없으나 감소시키면 그 자리에 있던 메모리를 해제하지 않는다
    그러니 cpp11의 shrink_to_fit을 사용하여 용량을 실제 벡터 크기로 줄일 수 있다.
*/

int main () {
    using namespace std;
    vector<int> v;
    int i = 0;
    v.emplace_back(i);
    v.emplace_back(v[i]);
    cout << "vector's capacity is " << v.capacity() << '\n';
    cout << "vector's max size is " << v.size() << '\n';
    v.emplace_back(2);
    cout << "vector's capacity is " << v.capacity() << '\n';
    cout << "vector's max size is " << v.size() << '\n';
    v.emplace_back(3);
    cout << "vector's capacity is " << v.capacity() << '\n';
    cout << "vector's max size is " << v.size() << '\n';
    v[30] = 30;
    cout << v[30] << '\n';      // why this allowed? though capacity is 4?
    cout << "vector's capacity is " << v.capacity() << '\n';
    cout << "vector's max size is " << v.size() << '\n';
    double vSum = calcSum(v);
    cout << "vector's Sum is " << vSum << '\n';
    v.resize(100);
    cout << "vector's capacity is " << v.capacity() << '\n';
    cout << "vector's max size is " << v.size() << '\n';
    v[99] =132;
    v.resize(10);
    cout << "vector's capacity is " << v.capacity() << '\n';
    cout << "vector's max size is " << v.size() << '\n';
    cout << "resize not free memory " << v[99] << '\n';
    v.shrink_to_fit();
    cout << "vector's capacity is " << v.capacity() << '\n';
    cout << "vector's max size is " << v.size() << '\n';
    cout << "resize not free memory " << v[99] << '\n';
    cout << v[30] << '\n';
    cout << "vector's max size is " << v.size() << '\n';
    copy(begin(v), end(v), ostream_iterator<int>(cout, ", "));
    sort(begin(v), end(v));
    auto it = unique(begin(v), end(v));
    v.resize(distance(begin(v), it));
    cout << '\n';
    copy(begin(v), end(v), ostream_iterator<int>(cout, ", "));
    
    double arr[10]{1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9,11.};
    double test = std::accumulate(std::begin(arr), std::end(arr), 0.0); // 동작한다 그러나 포인터라면 동작하지 않는다 왜냐하면 컴파일러가 크기를 알 도리가 없기 때문이다
    double arrSum = calcSum(arr);
    cout << "arr's Sum is " << arrSum << '\n';
    
    
}