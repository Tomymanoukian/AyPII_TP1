#ifndef _COMPLEJO_H_INCLUDED_
#define _COMPLEJO_H_INCLUDED_

#include <iostream>

class complejo {
    double re_, im_;
public:
    complejo();
    complejo(double);
    complejo(double, double);
    complejo(const complejo &);
    complejo const &operator=(complejo const &);
    complejo const &operator*=(complejo const &);
    complejo const &operator+=(complejo const &);
    complejo const &operator-=(complejo const &);
    ~complejo();

    void set_re(double x);
    void set_im(double x);
    
    double re() const;
    double im() const;
    double abs() const;
    double abs2() const;
    complejo const &conjugar();
    complejo const conjugado() const;
    bool zero() const;

    friend complejo const operator+(complejo const &, complejo const &);
    friend complejo const operator-(complejo const &, complejo const &);
    friend complejo const operator*(complejo const &, complejo const &);
    friend complejo const operator*(complejo const &, double);
    friend complejo const operator/(complejo const &, complejo const &);
    friend complejo const operator/(complejo const &, double);

    friend bool operator==(complejo const &, double);
    friend bool operator==(complejo const &, complejo const &);

    friend std::ostream &operator<<(std::ostream &, const complejo &);
    friend std::istream &operator>>(std::istream &, complejo &);
};

#endif
