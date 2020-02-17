/*
    20-02-17 Enoch Kim
    cpp 교재 <모던 C++입문> 2강
    2.8 연습문제
    db관련 코드는 https://github.com/gilbutITbook/006828/blob/master/c%2B%2B03/occi_old_style.cpp 참고 
    
*/
#include <iostream>
#include <initializer_list>


class polynomial {
    public :
        polynomial() : degree(0), coefficient(new double[1]) {}

        polynomial(int d) : degree(d){}

        polynomial(int d, double* coeff) : degree(d), coefficient(new double[d + 1]) {
            for(unsigned i = 0; i <= d; ++i){
                coefficient[i] = coeff[i];
            }
        }

        polynomial(polynomial& p) = default;

        polynomial(polynomial&& p) : degree(p.degree), coefficient(p.coefficient) {
            p.coefficient = nullptr;
            p.degree = 0;
        }

        polynomial(std::initializer_list<double> values) : degree(values.size() - 1), coefficient(new double[values.size()]) {
            std::copy(std::begin(values), std::end(values),coefficient);
        }

        polynomial& operator=(polynomial& p) {
            std::cout << "assign operator action!" << std::endl;
            delete[] coefficient;
            coefficient = new double[degree+1];
            degree = p.degree;
            for(int i=0; i <= degree; ++i) 
                coefficient[i] = p.coefficient[i];
            return *this;
        }

        polynomial& operator=(polynomial&& p) {
            std::cout << "move assign operator action!" << std::endl;
            degree = p.degree;
            std::swap(coefficient, p.coefficient);
            p.coefficient = nullptr;
            p.degree = 0;
            return *this;
        }

        polynomial& operator=(std::initializer_list <double> values){
            delete[] coefficient;
            coefficient = new double[values.size()];
            degree = values.size() - 1;
            std::copy(std::begin(values), std::end(values), coefficient);
            return *this;
        }
            
        ~polynomial() {
            delete[] coefficient;
        }

        int getSize() {
            return degree + 1;
        }
        int getDegree() {
            return degree;
        }
        double& getCoefficient() {
            return *coefficient;
        }

    private :
        int degree;
        double* coefficient;
};



std::ostream& operator<< (std::ostream &os, polynomial &p) {         // ostream 연산자 오버로딩
    const double& coeff = p.getCoefficient();
    int size = p.getSize();
    std::cout<< "size is " << size << std::endl;
    for(int i = 0; i < size; ++i){
        if(i == (size - 1)){
            os << (&coeff)[0] << std::endl;
            return os;
        }
        os << (&coeff)[size - i - 1] << " * " << "x ^ " << (size - i - 1) << " + ";
    }
    return os << "Something going Wrong!!";
}

polynomial createPolynomial(double d1, double d2, double d3){
    polynomial p;
    p = {d1,d2,d3};
    return p;
}

int main() {
    int size = 5;
    int degree = 4;
    double* coeff = new double[size];
    coeff[0] = 3.0; coeff[1] = 3.4; coeff[2] = 4.2; coeff[3] = 0.0; coeff[4] = 2.2;
    polynomial p{degree, coeff}, p2{degree, coeff};
    std::cout << "p is " << p << std::endl;
    p = createPolynomial(1.3, 4.2, 5.3);
    std::cout << "p is " << p << std::endl;
    p = p2;
    std::cout << "p is " << p << std::endl;
    return 0;
}