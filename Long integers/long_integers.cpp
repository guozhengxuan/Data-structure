#include "long_integers.h"
#include <sstream>
#include <vector>


Longint::Longint() {}

Longint::Longint(string value) 
/* Post: The integer is initialized to value.*/
{
  int begin;
  char x;
  if (value[0] == '-') {
    sign = '-';
	begin = 1;
  }
  else if (value[0] == '+') {
	sign = '+';
	begin = 1;
  }
  else {
	sign = '+';
	begin = 0;
  }
  for (int i = begin; i < value.size(); i++) {
	x = value[i];
    longint.insert(0, atoi(&x));
  }
}

string Longint::show()
/* Post: print and return integer in string.*/
{
  string integer = "";
  string number;
  int x;
  if (sign == '-')
	integer += '-';
  for (int i = longint.size() - 1; i >= 0 ; i--) {
	longint.retrieve(i, x);
	number = to_string(x);
	integer += number;
  }
  cout << integer;
  return integer;
}

void Longint::add(const Longint& Q) 
/* Post: A complete method of addition based on abs_add
		 and abs_subtract.*/
{
  if (sign == Q.sign)
	abs_add(Q);
  else {
	if (longint.size() > Q.longint.size())
	  abs_subtract(Q);
	else if (longint.size() < Q.longint.size()) {
	  Longint P;
	  P.longint = longint;
	  P.sign = sign;
	  longint = Q.longint;
	  sign = Q.sign;
	  abs_subtract(P);
	}
	else {
	  int p, q, i = longint.size() - 1;
	  do {
		longint.retrieve(i, p);
		Q.longint.retrieve(i, q);
		i--;
	  } while (p == q);
	  if (p > q) 
		abs_subtract(Q);
	  else {
		Longint P;
		P.longint = longint;
		P.sign = sign;
		longint = Q.longint;
		sign = Q.sign;
		abs_subtract(P);
	  }
	}
  }
}

void Longint::subtract(const Longint& Q) 
/* Post: A complete method of subtraction based on abs_add
		 and abs_subtract.*/
{
  Longint result;
  if (sign != Q.sign)
	abs_add(Q);
  else {
	if (longint.size() > Q.longint.size())
	  abs_subtract(Q);
	else if (longint.size() < Q.longint.size()) {
	  Longint P;
	  P.longint = longint;
	  P.sign = sign;
	  longint = Q.longint;
	  sign = Q.sign;
	  abs_subtract(P);
	  if (sign == '+') sign = '-';
	  else sign = '+';
	}
	else {
	  int p, q, i = longint.size() - 1;
	  do {
		longint.retrieve(i, p);
		Q.longint.retrieve(i, q);
		i--;
	  } while (p == q);
	  if (p > q) 
		abs_subtract(Q);
	  else {
		Longint P;
		P.longint = longint;
		P.sign = sign;
		longint = Q.longint;
		sign = Q.sign;
		abs_subtract(P);
		if (sign == '+') sign = '-';
		else sign = '+';
	  }
	}
  }
}

void Longint::multiply(const Longint& Q) 
/* Post: Multiply self by Q.*/
{
  if (sign == Q.sign) 
	sign = '+';
  else sign = '-';
  Longint X, Y, Z("0");
  X.longint = longint;
  X.sign = sign;
  for (int i = 0; i < Q.longint.size(); i++) {
	int q;
	Y.sign = X.sign;
	Y.longint = X.longint;
	Q.longint.retrieve(i, q);
	Y.single_multiply(q);
	for (int j = 0; j < i; j++)
	  Y.longint.insert(0, 0);
	Z.add(Y);
  }
  longint = Z.longint;
}

void Longint::operator=(const Longint& P)
/* Post: overload the equal operator.*/
{
  longint = P.longint;
  sign = P.sign;
}

Longint Longint::operator+(const Longint& P) 
/* Post: overload the plus operator.*/
{
  Longint result;
  result.longint = longint;
  result.sign = sign;
  result.add(P);
  return result;
}

Longint Longint::operator-(const Longint& P)
/* Post: overload the minus operator.*/
{
  Longint result;
  result.longint = longint;
  result.sign = sign;
  result.subtract(P);
  return result;
}

Longint Longint::operator*(const Longint& P) 
/* Post: overload the multiply operator.*/
{
  Longint result;
  result.longint = longint;
  result.sign = sign;
  result.multiply(P);
  return result;
}

void Longint::operator+=(const Longint& P)
/* Post: overload the self plus operator.*/
{
  add(P);
}

void Longint::operator-=(const Longint& P)
/* Post: overload the self minus operator.*/
{
  subtract(P);
}

void Longint::operator*=(const Longint& P)
/* Post: overload the self multiply operator.*/
{
  multiply(P);
}

void Longint::abs_add(const Longint& Q)
/* Post: Add Q to self, ignoring their signs.*/
{
  int max_size, nump, numq, num_result, carry = 0;
  List <int> p = longint, q = Q.longint;
  max_size = p.size() > q.size() ? p.size() : q.size();
  for (int i = 0; i < max_size; i++) {
	if (i >= p.size()) nump = 0;
	else p.retrieve(i, nump);
	if (i >= q.size()) numq = 0;
	else q.retrieve(i, numq);
	num_result = nump + numq + carry >= 10 ? nump + numq + carry - 10 : nump + numq + carry;
	if (i < p.size()) longint.replace(i, num_result);
	else longint.insert(longint.size(), num_result);
	carry = nump + numq + carry >= 10;
  }
  if (carry != 0)
	longint.insert(longint.size(), carry);
}

void Longint::abs_subtract(const Longint& Q)
/* Post: Assuming that absolute of self is greater than that of Q,
         ignore signs of two integers and subtract Q from self.*/
{
  int nump, numq, num_result, borrow = 0;
  List <int> p = longint, q = Q.longint;
  for (int i = 0; i < p.size(); i++) {
	if (i >= q.size()) numq = 0;
	else q.retrieve(i, numq);
	p.retrieve(i, nump);
	num_result = nump - borrow < numq ? 10 + nump - borrow - numq : nump - borrow - numq;
	longint.replace(i, num_result);
	borrow = nump - borrow < numq;
  }
}

void Longint::single_multiply(int x)
/* Post: Multiply self by a single int x, designed for reducing 
         the whole multiplication of two long ints.*/
{
  int nump, num_result, carry = 0;
  for (int i = 0; i < longint.size(); i++) {
	longint.retrieve(i, nump);
	num_result =  (nump * x + carry) % 10;
	longint.replace(i, num_result);
	carry = (nump * x + carry) / 10;
  }
  if (carry != 0) 
	longint.insert(longint.size(), carry);
}