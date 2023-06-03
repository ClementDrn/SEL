#pragma once

#include <SEL/Maths/Matrices/Mat4x4.hpp>
#include <SEL/Maths/Vectors/Vec3.hpp>

#include <cmath>


namespace sel {

	/// @brief Transforms a matrix by a translation.
	/// 
	/// @tparam T is the data type of the transformation.
	/// 
	/// @param mat is the matrix that will be transformed.
	/// @param vec is the translation vector to apply to the matrix.
	/// 
	/// @return The transformed matrix.
	/// 
	template <typename T>
	Mat4x4<T> translate(Mat4x4<T> mat, Vec3<T> vec)
	{
		// Translation matrix:
		// 1  0  0  dx
		// 0  1  0  dy
		// 0  0  1  dz
		// 0  0  0  1

		// result = Translation * mat
		Mat4x4<T> result = mat;

		// 4th column
		result[0][3] += vec.x * mat[3][3];
		result[1][3] += vec.y * mat[3][3];
		result[2][3] += vec.z * mat[3][3];

		return result;
	}

	/// @brief Transforms a matrix by a rotation.
	///
	/// @tparam T is the data type of the transformation.
	/// 
	/// @param mat is the matrix that will be transformed.
	/// @param axis is the axis of the rotation.
	/// @param radians is the angle of the rotation in radians.
	/// 
	/// @return The transformed matrix.
	/// 
	template <typename T>
	Mat4x4<T> rotate(Mat4x4<T> mat, Vec3<T> axis, T radians)
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
		
		T c = std::cos(radians);
		T s = std::sin(radians);

		Vec3<T> temp(1 - c);

		// Normalize axis
		Vec3<T> normalizedAxis = normalize(axis);

		// Calculate cross products
		Vec3<T> axisSquare(normalizedAxis.x * normalizedAxis.x, normalizedAxis.y * normalizedAxis.y, normalizedAxis.z * normalizedAxis.z);
		Vec3<T> crossProd(normalizedAxis.x * normalizedAxis.y, normalizedAxis.y * normalizedAxis.z, normalizedAxis.z * normalizedAxis.x);

		// Calculate matrix values
		Mat4x4<T> rotMatrix;
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
	/// @tparam T is the data type of the transformation.
	/// 
	/// @param mat is the matrix that will be transformed.
	/// @param vec is the scale vector to apply to the matrix.
	/// 
	/// @return The transformed matrix.
	/// 
	template <typename T>
	Mat4x4<T> scale(Mat4x4<T> mat, Vec3<T> vec)
	{
		// Scaling matrix:
		// sx 0  0  0
		// 0  sy 0  0
		// 0  0  sz 0
		// 0  0  0  1

		// result = Scaling * mat
		Mat4x4<T> result;

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
	}

}
