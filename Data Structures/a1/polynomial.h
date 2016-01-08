#ifndef polynomial_h
#define polynomial_h

#include <typeinfo>
#include <iostream>
#include <math.h>

using namespace std;

const double eps = 1e-15;

template <typename T>
class Polynomial
{
private:
	int Max_degree;
	T *Coefs;

public:
	// Default constructor p(x) = 0
	Polynomial(){
		this->Max_degree = 0;
		this->Coefs = new T[Max_degree+1];
		this->Coefs[0] = 0;
	}

	// Copy constructor
	Polynomial(const Polynomial& source);

	// Destructor
	~Polynomial();

	// Assignment operator
	Polynomial& operator = (const Polynomial& source);

	// Sum of *this and source polynomials
	Polynomial operator+(const Polynomial& source);
	
	// Subtract of source polynomials from *this
	Polynomial operator-(const Polynomial& source);

	// Product of *this and source polynomials
	Polynomial operator*(const Polynomial& source);

	// Evaluate polynomial *this at x and return the result
	T Eval(T x);

	// Print polynomial
	void Print();

	// Create a new term. If the term exists, overwrite its coefficient.
	void CreateTerm(const T coef, const int exp);
};

//
// Implementation
//

// Copy constructor
template <typename T>
Polynomial<T>::Polynomial(const Polynomial& source)
{
	this->Max_degree = source.Max_degree;
	this->Coefs = new T[this->Max_degree+1];
	for(int i=0; i<=this->Max_degree; i++) this->Coefs[i] = source.Coefs[i];
}	

template <typename T>
Polynomial<T>& Polynomial<T>::operator = (const Polynomial& source)
{
	if (this == &source) return *this;
	delete [] Coefs;
	this->Max_degree = source.Max_degree;
	this-> Coefs = new T[this->Max_degree+1];
	for(int i=0; i<=this->Max_degree; i++) this->Coefs[i] = source.Coefs[i];
	return *this;
}

template <typename T>
Polynomial<T>::~Polynomial()
{
	delete [] Coefs;
}

template <typename T>
void Polynomial<T>::Print()
{	
	for(int i = this->Max_degree; i>=0; i--) {
		T x = this->Coefs[i];
		if (x<eps && (-1*x)<eps) continue;
		if (i<this->Max_degree && this->Coefs[i]>0) cout<<"+";
		if (i>0) cout<<this->Coefs[i]<<"x^"<<i;
			else cout<<this->Coefs[i];
	}
	cout<<endl;
}

// Sum of *this and source polynomials
template <typename T>
Polynomial<T> 
Polynomial<T>::operator+(const Polynomial& source)
{
	Polynomial<T> sum;
	int n1 = this->Max_degree, n2 = source.Max_degree;
	sum.Max_degree = max(n1,n2);
	sum.Coefs = new T[max(n1,n2)+1];
	for(int i=0; i<=max(n1,n2); i++) {
		sum.Coefs[i] = 0;
		if (i<=n1) sum.Coefs[i] += this->Coefs[i];
		if (i<=n2) sum.Coefs[i] += source.Coefs[i];
	}
	return sum;
}

template <typename T>
Polynomial<T> 
Polynomial<T>::operator-(const Polynomial& source)
{
	Polynomial<T> sub;
	int n1 = this->Max_degree, n2 = source.Max_degree;
	sub.Max_degree = max(n1,n2);
	sub.Coefs = new T[max(n1,n2)+1];
	for(int i=0; i<=max(n1,n2); i++) {
		sub.Coefs[i] = 0;
		if (i<=n1) sub.Coefs[i] += this->Coefs[i];
		if (i<=n2) sub.Coefs[i] -= source.Coefs[i]; 
	}
	while (sub.Coefs[sub.Max_degree]<eps && (-1*sub.Coefs[sub.Max_degree])<eps) sub.Max_degree--;
	return sub;
}

template <typename T>
Polynomial<T> 
Polynomial<T>::operator*(const Polynomial& source)
{
	Polynomial<T> mul;
	mul.Max_degree = this->Max_degree + source.Max_degree;
	mul.Coefs = new T[mul.Max_degree+1];
	for(int i=0; i<=mul.Max_degree; i++) mul.Coefs[i] = 0;
	for(int i=this->Max_degree; i>=0; i--)
	 	for(int j=source.Max_degree; j>=0; j--)
			mul.Coefs[i+j] += this->Coefs[i] * source.Coefs[j];
	return mul;
}

template <typename T>
T Polynomial<T>::Eval(T x)
{
	T res = 0;
	for(int i=0; i<=this->Max_degree; i++){ 
		res += this->Coefs[i] * pow(x, i);
		//cout<<res<<endl;
		}
	return res;
}

template <typename T>
void Polynomial<T>::CreateTerm(const T coef, const int exp)
{
	if(exp>this->Max_degree) {
		Polynomial<T> temp;
		temp.Max_degree = exp;
		temp.Coefs = new T[exp+1];
		for(int i=0; i<=exp; i++) temp.Coefs[i] = 0;
		for(int i=0; i<=this->Max_degree; i++) temp.Coefs[i] = this->Coefs[i];
		temp.Coefs[exp] = coef;
		delete [] this->Coefs;
		this->Max_degree = exp;
		this->Coefs = new T[exp+1];
		for(int i=0; i<=exp; i++) this->Coefs[i] = temp.Coefs[i];
	} else this->Coefs[exp] = coef;
}


#endif
