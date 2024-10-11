#pragma once

#include "SEL/Maths/Matrices/Mat4x4.hpp"
#include "SEL/Maths/Vectors/Vec3.hpp"

#include <cmath>


namespace sel {

	class Transform : public Mat4x4f
	{
	public:

		/// @brief Default constructor. Sets the matrix to identity.
		///
		Transform() : Mat4x4f(1.0f) {}

		/// @brief Constructor allowing to specify values for the matrix.
		/// @param mat is the matrix to copy.
		/// 
		Transform(const Mat4x4f& mat) : Mat4x4f(mat) {}

		/// @brief Translates the transformation matrix by a translation vector.
		/// 
		/// @param vec is the translation vector to apply to the matrix.
		/// 
		void translate(const Vec3f& vec)
		{
			// Translation matrix:
			// 1  0  0  dx
			// 0  1  0  dy
			// 0  0  1  dz
			// 0  0  0  1

			auto& matrix = *this;

			// 4th column
			matrix[0][3] += vec.x;
			matrix[1][3] += vec.y;
			matrix[2][3] += vec.z;
		}

		/// @return the position vector of the transformation matrix.
		Vec3f getPosition() const { return { (*this)[0][3], (*this)[1][3], (*this)[2][3] }; }
	};


	/// @brief Transforms a matrix by a translation.
	/// 
	/// @param mat is the matrix that will be transformed.
	/// @param vec is the translation vector to apply to the matrix.
	/// 
	/// @return The transformed matrix.
	/// 
	inline Mat4x4f translate(const Mat4x4f& mat, const Vec3f& vec)
	{
		// Translation matrix:
		// 1  0  0  dx
		// 0  1  0  dy
		// 0  0  1  dz
		// 0  0  0  1
		
		// result = Translation * mat
		Transform result(mat);
		result.translate(vec);
		
		return result;
	}

	/// @brief Transforms a matrix by a rotation.
	///
	/// @param mat is the matrix that will be transformed.
	/// @param axis is the axis of the rotation.
	/// @param radians is the angle of the rotation in radians.
	/// 
	/// @return The transformed matrix.
	/// 
	inline Mat4x4f rotate(const Mat4x4f& mat, const Vec3f& axis, float radians)
	{
		// Rotation matrix on X-axis:
		//  1    0    0    0
		//  0   cos  -sin  0
		//  0   sin  cos   0
		//  0    0    0    1
		// 
		// Rotation matrix on Y-axis:
		// cos   0   sin   0
		//  0    1    0    0
		// -sin  0   cos   0
		//  0    0    0    1
		// 
		// Rotation matrix on Z-axis:
		// cos -sin   0    0
		// sin  cos   0    0
		//  0    0    1    0
		//  0    0    0    1
		
		float c = std::cos(radians);
		float s = std::sin(radians);

		float temp = 1 - c;

		// Normalize axis
		Vec3f normalizedAxis = normalize(axis);

		// Calculate cross products
		Vec3f axisSquare(normalizedAxis.x * normalizedAxis.x, normalizedAxis.y * normalizedAxis.y, normalizedAxis.z * normalizedAxis.z);
		Vec3f crossProd(normalizedAxis.x * normalizedAxis.y, normalizedAxis.y * normalizedAxis.z, normalizedAxis.z * normalizedAxis.x);

		// Calculate matrix values
		Mat4x4f rotMatrix;
		rotMatrix[0][0] = c + axisSquare.x * temp;
		rotMatrix[0][1] = crossProd.z * s + normalizedAxis.x * normalizedAxis.y * temp;
		rotMatrix[0][2] = -crossProd.y * s + normalizedAxis.x * normalizedAxis.z * temp;
		rotMatrix[0][3] = 0;

		rotMatrix[1][0] = -crossProd.z * s + normalizedAxis.x * normalizedAxis.y * temp;
		rotMatrix[1][1] = c + axisSquare.y * temp;
		rotMatrix[1][2] = crossProd.x * s + normalizedAxis.y * normalizedAxis.z * temp;
		rotMatrix[1][3] = 0;

		rotMatrix[2][0] = crossProd.y * s + normalizedAxis.x * normalizedAxis.z * temp;
		rotMatrix[2][1] = -crossProd.x * s + normalizedAxis.y * normalizedAxis.z * temp;
		rotMatrix[2][2] = c + axisSquare.z * temp;
		rotMatrix[2][3] = 0;

		rotMatrix[3][0] = 0;
		rotMatrix[3][1] = 0;
		rotMatrix[3][2] = 0;
		rotMatrix[3][3] = 1;

		return rotMatrix * mat;
	}

	/// @brief Transforms a matrix by a scale.
	///
	/// @param mat is the matrix that will be transformed.
	/// @param vec is the scale vector to apply to the matrix.
	/// 
	/// @return The transformed matrix.
	/// 
	inline Mat4x4f scale(const Mat4x4f& mat, const Vec3f& vec)
	{
		// Scaling matrix:
		// sx 0  0  0
		// 0  sy 0  0
		// 0  0  sz 0
		// 0  0  0  1

		// result = Scaling * mat
		Mat4x4f result;

		// 1st row
		result[0][0] = mat[0][0] * vec.x;
		result[0][1] = mat[0][1] * vec.x;
		result[0][2] = mat[0][2] * vec.x;
		result[0][3] = mat[0][3] * vec.x;

		// 2nd row
		result[1][0] = mat[1][0] * vec.y;
		result[1][1] = mat[1][1] * vec.y;
		result[1][2] = mat[1][2] * vec.y;
		result[1][3] = mat[1][3] * vec.y;

		// 3rd row
		result[2][0] = mat[2][0] * vec.z;
		result[2][1] = mat[2][1] * vec.z;
		result[2][2] = mat[2][2] * vec.z;
		result[2][3] = mat[2][3] * vec.z;

		// 4th row
		result[3][0] = mat[3][0];
		result[3][1] = mat[3][1];
		result[3][2] = mat[3][2];
		result[3][3] = mat[3][3];

		return result;
	}

}
