/*
*  vec3.cpp
*/

#include <assert.h>
#include "vec3.h"
#include <math.h>
#include <iostream>
#define EPSILON 0.000000001
	///----------------------------------------------------------------------
	/// Constructors
	///----------------------------------------------------------------------
using namespace std;
	vec3::vec3()
	{
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
	}
	vec3::vec3(float x, float y, float z)
	{
		data[0] = x;
		data[1] = y;
		data[2] = z;
	}

	///----------------------------------------------------------------------
	/// Getters/Setters
	///----------------------------------------------------------------------		
	/// Returns the value at index
	float vec3::operator[](unsigned int index) const
	{
		assert(index < 3);
			return data[index];
	}

	/// Returns a reference to the value at index
	float& vec3::operator[](unsigned int index)
	{
		assert(index < 3);
			float& elRef = data[index];
			return elRef;
	}

	/// Prints the vector to standard output in a nice format
	void vec3::print()
	{
		cout << "< " << data[0] <<", " << data[1]<< ", " << data[2]<< " >" << endl; // print <x, y, z>
	}

	///----------------------------------------------------------------------
	/// Vector Operations
	///----------------------------------------------------------------------
	/// Returns the geometric length of the vector
	float vec3::length() const
	{
		return sqrt(pow(data[0], 2) + pow(data[1], 2) + pow(data[2], 2)); //return sqrt(x^2+y^2+z^2), the inner product of the vector.
	}

	///----------------------------------------------------------------------
	/// Friend Functions
	///----------------------------------------------------------------------		
	/// Checks if v1 == v2
	bool operator==(const vec3& v1, const vec3& v2)
	{
		//Checks every entry in the two vectors if they are within the epsilon

		if (abs(v1[0] - v2[0]) < EPSILON)
		{
			if (abs(v1[1] - v2[1]) < EPSILON)
			{
				if (abs(v1[2] - v2[2]) < EPSILON)
				{
					//if so return 1
					return 1;
				}
			}
		}
		//return 0 by default unless we return 1 if everything is equal
		return 0;
	}

	/// Checks if v1 != v2
	 bool operator!=(const vec3& v1, const vec3& v2)
	{
		//Same logic as the == operator, but flipped the return values.
		if (abs(v1[0] - v2[0]) < EPSILON)
		{
			if (abs(v1[1] - v2[1]) < EPSILON)
			{
				if (abs(v1[2] - v2[2]) < EPSILON)
				{
					return 0;
				}
			}
		}
		return 1;
	}

	/// Vector Addition (v1 + v2)
	 vec3 operator+ (const vec3& v1, const vec3& v2)
	{
		return  vec3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]); 
		//return a new vector that is <x1+x2, y1+y2, z1+z2>
	}

	/// Vector Subtraction (v1 - v2)
	 vec3 operator- (const vec3& v1, const vec3& v2)
	 {
		 return  vec3(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
		 //return a new vector that is <x1-x2, y1-y2, z1-z2>
	 }

	/// Scalar Multiplication (v * c)
	 vec3 operator* (const vec3& v, float c)
	 {
		 float newX = v[0] * c;
		 float newY = v[1] * c;
		 float newZ = v[2] * c;
		 return vec3(newX, newY, newZ);
	 }


	/// Scalar Multiplication (c * v)
	 vec3 operator* (float c, const vec3& v)
	 {
		 //Scalar multiplication is commutative
		 /*
			proof: c<x, y, z> = <cx, cy, cz>. Since integer multiplication is commutative,
			<cx, cy, cz> = <xc, yc, zc> = <x, y, z>c.
		 */
		 //Hence this is the same function as before.
		 float newX = v[0] * c;
		 float newY = v[1] * c;
		 float newZ = v[2] * c;
		 return vec3(newX, newY, newZ);
	 }

	/// Scalar Division (v/c)
	 vec3 operator/ (const vec3& v, float c)
	 {
		 assert(c != 0);
		 float newX = v[0] / c;
		 float newY = v[1] / c;
		 float newZ = v[2] / c;
		 return vec3(newX, newY, newZ);
	 }

	/// Dot Product (v1 * v2)
	 float operator* (const vec3& v1, const vec3& v2)
	 {
		 //return x1*x2 + y1*y2 + z1*z2
		 return ((v1[0] * v2[0]) + (v1[1] * v2[1]) + (v1[2] * v2[2]));
	 }

	/// Cross Product (v1 % v2)
	 vec3 operator% (const vec3& v1, const vec3& v2)
	 {
			//a = b x c
			 float newX = (v1[1] * v2[2]) - (v1[2]*v2[1]); //a_x = b_yc_z - b_zc_y
			 float newY = (v1[2] * v2[0]) - (v1[0] * v2[2]); //a_y = b_zc_x - b_xc_z
			 float newZ = (v1[0] * v2[1]) - (v1[1] * v2[0]); //a_z = b_xc_y - b_yc_x
			 return vec3(newX, newY, newZ);
	 }