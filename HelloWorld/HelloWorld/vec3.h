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


inline std::istream& operator>>(std::istream &is, vec3 &t) {
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}

inline std::ostream& operator<<(std::ostream &os, vec3 &t) {
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];
	return os;
}

inline void vec3::make_unit_vector() {
	float k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}


inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline vec3 operator*(const float t, const vec3 &v) {
	return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, const float t) {
	return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator/(float t, const vec3 &v) {
	return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline vec3 operator/(const vec3 &v, float t) {
	return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline float dot(const vec3 &v1, const vec3 &v2) {
	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline vec3 cross(const vec3 &v1, const vec3 &v2) {
	return vec3(
		(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
		(-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])),
		(v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0])
	);
}

inline vec3& vec3::operator+=(const vec3 &v) {
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
}

inline vec3& vec3::operator*=(const vec3 &v) {
	e[0] *= v.e[0];
	e[1] *= v.e[1];
	e[2] *= v.e[2];
	return *this;
}

inline vec3& vec3::operator/=(const vec3 &v) {
	e[0] /= v.e[0];
	e[1] /= v.e[1];
	e[2] /= v.e[2];
	return *this;
}

inline vec3& vec3::operator-=(const vec3 &v) {
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	e[2] -= v.e[2];
	return *this;
}

inline vec3& vec3::operator*=(const float t) {
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

inline vec3& vec3::operator/=(const float t) {
	float k = 1.0 / t;
	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
	return *this;
}

inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}

