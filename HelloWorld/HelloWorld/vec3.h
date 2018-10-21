#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3
{
public:
	float e[3];

	vec3() {
	}
		
	vec3(float e0, float e1, float e2) {
		e[0] = e0;
		e[1] = e1;
		e[2] = e2;
	}
	
	/* C++ inline function is powerful concept that is commonly used with classes.
	If a function is inline, the compiler places a copy of the code of that function 
	at each point where the function is called at compile time. ... 
	The compiler can ignore the inline qualifier in case defined function is more than a line. */

	/*
	A "const function", denoted with the keyword const after a function declaration, 
	makes it a compiler error for this class function to change a member variable of the class. 
	However, reading of a class variables is ok inside of the function, 
	but writing inside of this function will generate a compiler error.

	Another way of thinking about such "const function" is by viewing an class function as a 
	normal function taking an implicit this pointer. So a method 
	int Foo::Bar(int random_arg) 
	(without the const at the end) results in a function like 
	int Foo_Bar(Foo* this, int random_arg), 
	and a call such as 
	Foo f; f.Bar(4)
	will internally correspond to something like
	Foo f; Foo_Bar(&f, 4).
	Now adding the const at the end 
	(int Foo::Bar(int random_arg) const) 
	can then be understood as a declaration with a const this pointer: 
	int Foo_Bar(const Foo* this, int random_arg). 
	Since the type of this in such case is const, 
	no modifications of member variables are possible.
	*/
	inline float x() const {
		return e[0];
	}
	inline float y() const {
		return e[1];
	}
	inline float z() const {
		return e[2];
	}
	inline float r() const {
		return e[0];
	}
	inline float g() const {
		return e[1];
	}
	inline float b() const {
		return e[2];
	}

	inline const vec3& operator+()const {
		return *this;
	}

	inline vec3 operator-() const {
		return vec3(-e[0],-e[1],-e[2]);
	}
	inline float operator[](int i) const {
		return e[i];
	}

	inline float& operator[](int i) {
		return e[i];
	}

	inline vec3& operator+=(const vec3 &v2);
	inline vec3& operator-=(const vec3 &v2);
	inline vec3& operator*=(const vec3 &v2);
	inline vec3& operator/=(const vec3 &v2);

	inline vec3& operator*=(const float t);
	inline vec3& operator/=(const float t);

	inline float length() const {
		return sqrt(e[0]*e[0] + e[1] * e[1] + e[2] * e[2]);
	}

	inline float squared_length()const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	inline void make_unit_vector();

	~vec3() {
	}
};

