//
//long_integers.h
//Implementaiton of long int operations containing addition, subtraction and multiplication.

#pragma once
#include "simply_linked_list.h"
#include <string>


class Longint {
public:
  // Initializers.
  Longint();
  Longint(string value);
  // method of visualization.
  string show();
  // Operations'specifications.
  void add(const Longint& Q);
  void subtract(const Longint& Q);
  void multiply(const Longint& Q);
  // overload operators.
  void operator=(const Longint& P);
  Longint operator+(const Longint& P);
  Longint operator-(const Longint& P);
  Longint operator*(const Longint& P);
  void operator+=(const Longint& P);
  void operator-=(const Longint& P);
  void operator*=(const Longint& P);
private:
  // absolute addition and subtraction.
  void abs_add(const Longint& Q);
  void abs_subtract(const Longint& Q);
  // multiplication of a long int and a single int.
  void single_multiply(int x);
  // long int storage prototype and its sign.
  List <int> longint;
  char sign;
};