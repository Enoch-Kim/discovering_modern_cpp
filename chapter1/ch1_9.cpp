/*
    20-02-11 Enoch Kim
    cpp 교재 <모던 C++입문> 1강
    1.9
*/

#include <iostream>
#include <fstream>
#include <typeinfo>
#include <memory>
#include <vector>

int main () {

    // 주석은 pseudo-code이다. 의사코드, 즉 코드를 명확히 해준다.

    // 매크로는 매우_긴_다른것으로_대체_할_수_있는_것을_사용하고_왠만하면_쓰지_마라.

    /*
        iostream과 같은 기본 라이브러리는 전처리기를 통해 구현되어있다.
        이는 컴파일러를 통해 추가가 가능하며, 리눅스에선 -l을 윈도우에선 /l을 사용한다.
        #include "herberts_math_functions.hpp"
        이렇게하면 현재 디렉터리 검색 후 표준경로 검색한다.
        종종 구분을 위해 상위 디렉터리를 포함한다.
        #include "herberts_includes/math_functions.hpp"
        #include <another_project/more_functions.h>
    */

    /*
        포함방지는 간접적인 포함으로 인해 자주 사용하는 헤더파일이 하나의 번역 단위에 여러 번 포함 될 수 있다. 
        금지된 반복을 피하고 텍스트 확장을 제한하기 위해 소위 Include Guard는 첫번째로 포함할 때만 수행한다.
        특정파일을 포함하는 매크로임

        #ifndef HERBERTS_MATH_FUNCTIONS_INCLUDE
        #define HERBERTS_MATH_FUNCTIONS_INCLUDE
        #include <cmath>

        ...

        #endif // HERBERTS_MATH_FUNCTIONS_INCLUDE
        모든 매크로와 마찬가지로 프로젝트의 이름뿐만 아니라 직접 간접적으로 포함하는 다른 모든 헤더의 이름도 고유해야한다.
        이상적으로 이름은 프로젝트와 파일 이름을 나타내야하며, _INCLUDE OR _HEADER를 붙인다.

        대안은 
        #pragma once
        이다. 이러면 이중포함이 컴파일러의 책임이 된다.
    */

    /*
        조건부 컴파일
        나중에 다시 보자
    */

    /*
        #if를 통해 주석처리가 가능하지만 권장하지 않는다.
    */

    return 0;
}