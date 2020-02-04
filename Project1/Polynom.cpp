#include <cmath>
#include <cstring>

#include "Polynom.h"

using namespace std;

istream& operator>>(istream& in, Poly& p)
{
	int k = -1;

	cout << "please, enter the poly power: ";

	while (k < 0)
		in >> k;



	cout << "please, enter the poly coefficients: " << endl;

	try {
		double* mas = new double[k + 1];

		for (int i = k; i >= 0; i--)
		{
			cout << "x^" << i << ": ";
			in >> mas[i];
		}
		if (cin.good())
			p.Init(k, mas);
		else { throw std::runtime_error("Input error"); };
	}
	catch (std::exception const& e) {
		cout << "There was an error: " << e.what() << endl;
	}
	return in;
}

ostream& operator<<(ostream& out, const Poly& p)
{

	if (p.k < 0)
	{
		out << "Not exists";
		return out;
	}

	out << "P(x) = " << p.mas[p.k] << "*x^" << p.k << " + ";

	for (int i = p.k - 1; i >= 0; i--)
	{
		out << p.mas[i];
		if (i != 0) out << "*x^" << i << " + ";
	}

	out << endl;

	return out;
}


Poly operator+(const Poly& p1, const Poly& p2)
{
	const Poly& max = (p1.k > p2.k) ? p1
		: p2;

	const Poly& min = (p1.k > p2.k) ? p2
		: p1;

	Poly res;

	res.k = max.k;
	res.mas = new double[max.k + 1];

	for (int i = 0; i < max.k + 1; i++)
	{
		res.mas[i] = max.mas[i];

		if (i < min.k + 1)
			res.mas[i] += min.mas[i];
	}

	return res;
}

//Construstors
Poly::Poly() : k(-1), mas(nullptr) {}

Poly::Poly(double c) : k(0)
{
	mas = new double(c);
}

Poly::Poly(int s, double* koef)
{
	if (k < 0) k = 0;
	k = s; mas = koef;
}

Poly::Poly(const Poly& p) {
	try {
		
		k = p.k;
		mas = new double[k + 1];
		void* t = memcpy(mas, p.mas, (k + 1) * sizeof(double));
		if (t == nullptr) throw std::runtime_error("error");
	}
	catch (std::exception const& e) {
		cout << "There was an error: " << e.what() << endl;
	}
}
/*
Poly::Poly(const Poly& p)
{
	this = new Poly();
	cout << "1";
	k=(&p)->k;
	cout << "1";
	if (mas!=nullptr){delete(mas);}
	mas=(&p)->mas;
	cout << "1";
	//Init(p.k,p.mas);
}
*/
Poly::~Poly()
{
	delete[] mas;
}

//Funcs
double Poly::Calc(const double x)
{
	double temp = 1.0;
	double f = 0.0;

	for (int i = 0; i < k + 1; ++i)
	{
		f += (temp * mas[i]);
		temp *= x;
	}
	return f;
}

void Poly::Div(const double n, Poly& res, double& R) {

	res.~Poly();
	res.k = k - 1;
	res.mas = new double[k];

	double t = 0;
	for (int i = k - 1; i >= 0; i--) {
		res.mas[i] = mas[i + 1] + n * t;
		t = res.mas[i];
	}
	R = mas[0] + (n * res.mas[0]);

}

void Poly::Init(const int k_, double* mas_) {
	k = k_;
	try {
		delete[] mas;
		mas = new double[k + 1];
		void* t = memcpy(mas, mas_, (k + 1) * sizeof(double));
		if (t == nullptr) throw std::runtime_error("error");
	}
	catch (std::exception const& e) {
		cout << "There was an error: " << e.what() << endl;
	}
}



bool Poly::Root(double& root, double x1, double x2)
{
	Poly f1 = (*this)();
	Poly f2 = f1();

	if (f1.Calc(x1) * f2.Calc(x1) < 0)
		return false;

	double t = (x1 + x2) / 2.0;
	double left = x1, rgt = x2;
	double z = Calc(t);

	while (abs(z) > 0.0001)
	{
		if (z * Calc(left) < 0)
			rgt = t;
		else
			left = t;

		t = (left + rgt) / 2.0;
		z = Calc(t);
	}

	root = t;

	return true;
}


Poly Poly::operator()() {
	Poly res;

	res.k = k - 1;


	res.mas = new double[k];

	for (int i = 1; i < k + 1; i++)
		res.mas[i - 1] = mas[i] * i;



	return res;
}


Poly& Poly::operator=(const Poly& right) {
	
	if (this == &right) {
		return *this;
	}
	 
	k = right.k;
	try {
		mas = new double[k + 1];
		void* t = memcpy(mas, right.mas, (k + 1) * sizeof(double));
		if (t == nullptr) throw std::runtime_error("error");
	}
	catch (std::exception const& e) {
		cout << "There was an error: " << e.what() << endl;

	}
	return *this;
}

Poly::Poly(Poly&& p) :k(p.k), mas(p.mas)
{
	p.k = 0;
	p.mas = nullptr;
}

Poly& Poly::operator=(Poly&& p) {
	;
	int tmp = k;
	k = p.k;
	p.k = tmp;
	double* tmpp = mas;
	mas = p.mas;
	p.mas = tmpp;
	return *this;
}