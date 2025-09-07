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

		// adds v.e to the current instance's e
		// returns the current instance
		vec3& operator+=(const vec3& v);

		// multiplies e[0] by v.e[0], e[1] by v.e[1] and so on. Then returns current instance
		// variable *= expression is the SAME as variable = variable * expression;
		vec3& operator*=(double t);

		// divides current instance by t and returns current instance
		// calls overloaded operator*= function	
		vec3& operator/=(double t);

		// Squares each element of the array e
		// then adds the squared results together
		// returns a copy; doesn't modify this instance
		// The length ||v|| of a vector v is the square root of v·v
		double length_squared() const;

		// returns a copy of the square root of length_squared
		double length() const;
	};

	// point3 is just an alias for vec3, but useful for geometric clarity in the code.
	using point3 = vec3;

	// Vector Utility Functions
	// Prints the vector components
	inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
		return out << v.e[0] << ',' << ' ' << v.e[1] << ',' << ' ' << v.e[2];
	}
	// does vector addition v+u, and returns a new vector representing the sum
	inline vec3 operator+(const vec3& u, const vec3& v) {
		return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
	}

	// does vector subtraction u-v, and returns a new vector representing the difference
	inline vec3 operator-(const vec3& u, const vec3& v) {
		return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
	}

	// does vector multiplication u*v, and returns a new vector representing the product
	inline vec3 operator*(const vec3& u, const vec3& v) {
		return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
	}

	// Returns the vector scaled by a scalar t (c(v1,...,vn))
	inline vec3 operator*(double t, const vec3& v) {
		return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
	}

	// calls function above, if vector is param1, scalar param2
	inline vec3 operator*(const vec3& v, double t) {
		return t * v;
	}

	// scales vector by 1/t (vector divided by t)
	inline vec3 operator/(const vec3& v, double t) {
		return (1 / t) * v;
	}

	// returns dot product of u·v
	inline double dot(const vec3& u, const vec3& v) {
		return u.e[0] * v.e[0]
			+ u.e[1] * v.e[1]
			+ u.e[2] * v.e[2];
	}

	// returns a copy of the cross product of u and v
	inline vec3 cross(const vec3& u, const vec3& v) {
		return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
			u.e[2] * v.e[0] - u.e[0] * v.e[2],
			u.e[0] * v.e[1] - u.e[1] * v.e[0]);
	}

	// scales vector to be unit vector
	// returns a vector going in the same direction as v but with a length of 1
	inline vec3 unit_vector(const vec3& v) {
		return v / v.length();
	}

}
#endif