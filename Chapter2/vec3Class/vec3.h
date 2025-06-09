#ifndef VEC3_H
#define VEC3_H
#include <cmath>
#include <iostream>

namespace vec {
	class vec3 {	

	public:
		// instance variable
		double e[3];

		// constructor that initializes e to [0,0,0]
		vec3();

		// parameterized constructor
		vec3(double e0, double e1, double e2);

		// Getters to return each element in e
		double x() const;
		double y() const;
		double z() const;

		// calls the vec3 constructor with the negative values of the array e
		vec3 operator-() const;

		// simple subscripting operator returns a COPY of e[i].
		double operator[](int i) const;

		// subscripting operator returns a REFERENCE to e[i].
		double& operator[](int i);

		// adds v.e[0] to e[0], v.e[1] to e[1] and so on. Then returns current instance
		vec3& operator+=(const vec3& v);

		// multiplies e[0] by v.e[0], e[1] by v.e[1] and so on. Then returns current instance
		// variable *= expression is the SAME as variable = variable * expression;
		vec3& operator*=(double t);

		// multiplies current instance by 1/t and returns current instance
		// calls overloaded operator*= function
		// division is reciprocal multiplication
		vec3& operator/=(double t);

		// Squares each element of the array e
		// then adds the squared results together
		// returns a copy
		double length_squared() const;

		// returns a copy of the square root of length_squared
		double length() const;
	};

	// point3 is just an alias for vec3, but useful for geometric clarity in the code.
	using point3 = vec3;

	// Vector Utility Functions

	inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
		return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
	}

	inline vec3 operator+(const vec3& u, const vec3& v) {
		return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
	}

	inline vec3 operator-(const vec3& u, const vec3& v) {
		return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
	}

	inline vec3 operator*(const vec3& u, const vec3& v) {
		return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
	}

	inline vec3 operator*(double t, const vec3& v) {
		return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
	}

	inline vec3 operator*(const vec3& v, double t) {
		return t * v;
	}

	inline vec3 operator/(const vec3& v, double t) {
		return (1 / t) * v;
	}

	inline double dot(const vec3& u, const vec3& v) {
		return u.e[0] * v.e[0]
			+ u.e[1] * v.e[1]
			+ u.e[2] * v.e[2];
	}

	inline vec3 cross(const vec3& u, const vec3& v) {
		return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
			u.e[2] * v.e[0] - u.e[0] * v.e[2],
			u.e[0] * v.e[1] - u.e[1] * v.e[0]);
	}

	inline vec3 unit_vector(const vec3& v) {
		return v / v.length();
	}

}
#endif