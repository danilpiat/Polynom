//
// Created by Олег on 12.11.2019.
//

#ifndef DAN_POLYNOM_H
#define DAN_POLYNOM_H

#include <iostream>

using namespace std;


class Poly
{
    friend istream& operator>>(istream& in, Poly& p);
    friend ostream& operator<<(ostream& out, const Poly& p);

    friend Poly operator+(const Poly& p1, const Poly& p2);

public:
    Poly();

    Poly(double c);
    Poly(int s, double* koef);
    Poly(Poly &&p);
    Poly(const Poly& p);

    ~Poly();

    double Calc(const double x);
    void Div(const double n, Poly& res, double& R);
    void Init(const int k_, double* mas_);
    bool Root(double& root, double x1, double x2);
    Poly operator()();
    Poly& operator=(const Poly& right);

    Poly& operator=(Poly&& right);


    int k;
    double* mas;
};




#endif //DAN_POLYNOM_H
