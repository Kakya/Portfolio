///----------------------------------------------------------------------
/// Constructors
///----------------------------------------------------------------------
/// Default Constructor.  Initialize to matrix of all 0s.
#include <assert.h>
#include "mat3.h"
#include <math.h>
#include <iostream>
#include "vec3.h"
using namespace std;
/// Initializes matrix with each vector representing a row in the matrix
mat3::mat3(const vec3& row1, const vec3& row2, const vec3& row3)
{
	data[0] = row1;
	data[1] = row2;
	data[2] = row3;
}
mat3::mat3()
{
	data[0] = vec3();
	data[1] = vec3();
	data[2] = vec3();
}
//function to convert degrees to radians
float deg2Rad(float angle)
{
	//Returns (ang*pi)/180. Value of pi copied from WolframAlpha
	return ((angle*3.141592653589793238462643383279502884197169399375) / 180);
}
///----------------------------------------------------------------------
/// Getters
///----------------------------------------------------------------------	
/// Returns the values of the row at the index
vec3 mat3::operator[](unsigned int index) const
{
	assert(index < 3);
	return data[index];
}

/// Returns a reference to the row at the index
vec3& mat3::operator[](unsigned int index)
{
	assert( index < 3);
	return data[index];
}

/// Returns a column of the matrix
vec3 mat3::getColumn(unsigned int index) const
{
	//Initialize an empty array that will hold the column entries
	float colEnt[3];
	//check index
	assert(index < 3);
	//Loop through all the vectors and append the element
	//In the correct column to the column entry array
	for (int i = 0; i < 3; i++)
	{
		colEnt[i] = data[i][index];
	}
	//return a new vector with the column entries
	return vec3(colEnt[0], colEnt[1], colEnt[2]);
}

/// Prints the matrix to standard output in a nice format
void mat3::print()
{
	//Let the vec3 print to the heavy working
	for (int i = 0; i < 3; i++)
	{
		data[i].print();
	}
}

///----------------------------------------------------------------------
/// Matrix Operations
///----------------------------------------------------------------------	
/// Returns the transpose of the matrix (v_ij == v_ji)
mat3 mat3::transpose() const
{
	//Get the columns in the current matrix
	vec3 c0 = getColumn(0);
	vec3 c1 = getColumn(1);
	vec3 c2 = getColumn(2);
	//Since the inputs to mat3 assume they are rows
	//If we pass in the columns, they'll appear as rows
	//Giving us the transpose.
	return mat3(c0, c1, c2);
}

///----------------------------------------------------------------------
/// Static Initializers
///----------------------------------------------------------------------	
/// Creates a 3-D rotation matrix.
/// Takes an angle in degrees and outputs a 3x3 rotation matrix
 mat3 mat3::rotation2D(float angle)
{
	//convert the angle to radians.
	float radAngle = deg2Rad(angle);
	//implement the rotation homogenous matrix as a series of vectors
	vec3 rot1 = vec3(cos(radAngle), -sin(radAngle), 0);
	vec3 rot2 = vec3(sin(radAngle), cos(radAngle), 0);
	vec3 hom = vec3(0, 0, 1);
	return mat3(rot1, rot2, hom);
}

/// Takes an x and y displacement and outputs a 3x3 translation matrix
 mat3 mat3::translation2D(float x, float y)
{
	vec3 tr0 = vec3(1, 0, x);
	vec3 tr1 = vec3(0, 1, y);
	vec3 hom = vec3(0, 0, 1);
	return mat3(tr0, tr1, hom);
}

/// Takes an x and y scale and outputs a 3x3 scale matrix
 mat3 mat3::scale2D(float x, float y)
{
	vec3 sc0 = vec3(x, 0, 0);
	vec3 sc1 = vec3(0, y, 0);
	vec3 hom = vec3(0, 0, 1);
	return mat3(sc0, sc1, hom);
}

/// Generates a 3x3 identity matrix
 mat3 mat3::identity()
{
	vec3 r0 = vec3(1, 0, 0);
	vec3 r1 = vec3(0, 1, 0);
	vec3 r2 = vec3(0, 0, 1);
	return mat3(r0, r1, r2);
}


///----------------------------------------------------------------------
/// Friend Functions
///----------------------------------------------------------------------
/// Checks if m1 == m2
bool operator==(const mat3& m1, const mat3& m2)
{
	//Uses the vec3 == operator, with the Epsilon definition
	if (m1[0] == m2[0])
	{
		if (m1[1] == m2[1])
		{
			if (m1[2] == m2[2])
			{
				return 1;
			}
		}
	}
	return 0;
}

/// Checks if m1 != m2
bool operator!=(const mat3& m1, const mat3& m2)
{
	if (m1[0] == m2[0])
	{
		if (m1[1] == m2[1])
		{
			if (m1[2] == m2[2])
			{
				return 0;
			}
		}
	}
	return 1;

}
//Use the vec3 operator definitions to perform the following mathematical operations
/// Matrix addition (m1 + m2)
mat3 operator+ (const mat3& m1, const mat3& m2)
{
	return mat3(m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2]);
}

/// Matrix subtraction (m1 - m2)
mat3 operator- (const mat3& m1, const mat3& m2)
{
	return mat3(m1[0] - m2[0], m1[1] - m2[1], m1[2] - m2[2]);
}

/// Scalar multiplication (m * c)
mat3 operator* (const mat3& m, float c)
{
	vec3 new0 = m[0] * c;
	vec3 new1 = m[1] * c;
	vec3 new2 = m[2] * c;
	return mat3(new0, new1, new2);
}

/// Scalar multiplication (c * m)
mat3 operator* (float c, const mat3& m)
{
	vec3 new0 = m[0] * c;
	vec3 new1 = m[1] * c;
	vec3 new2 = m[2] * c;
	return mat3(new0, new1, new2);
}

/// Scalar division (m / c)
mat3 operator/ (const mat3& m, float c)
{
	assert(c!=0);
	vec3 new0 = m[0] / c;
	vec3 new1 = m[1] / c;
	vec3 new2 = m[2] / c;
	return mat3(new0, new1, new2);
}

/// Matrix multiplication (m1 * m2)
mat3 operator* (const mat3& m1, const mat3& m2)
{
	vec3 row0 = vec3(m1[0] * m2.getColumn(0), m1[0] * m2.getColumn(1), m1[0] * m2.getColumn(2));
	vec3 row1 = vec3(m1[1] * m2.getColumn(0), m1[1] * m2.getColumn(1), m1[1] * m2.getColumn(2));
	vec3 row2 = vec3(m1[2] * m2.getColumn(0), m1[2] * m2.getColumn(1), m1[2] * m2.getColumn(2));
	return mat3(row0, row1, row2);
}

/// Matrix/vector multiplication (m * v)
/// Assume v is a column vector (ie. a 3x1 matrix)
vec3 operator* (const mat3& m, const vec3& v)
{
	return vec3(m[0]*v, m[1]*v, m[2]*v);
}

/// Vector/matrix multiplication (v * m)
/// Assume v is a row vector (ie. a 1x3 matrix)
vec3 operator* (const vec3& v, const mat3& m)
{
	return vec3(v*m.getColumn(0), v*m.getColumn(1), v*m.getColumn(2));
}

