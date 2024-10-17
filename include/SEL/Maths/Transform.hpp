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
			// NOTE: Assumes that matrix[3][3] = 1.0f
			matrix[0][3] += vec.x;
			matrix[1][3] += vec.y;
			matrix[2][3] += vec.z;
		}

		/// @brief Rotates the transformation matrix.
		///
		/// @param axis is the axis of the rotation.
		/// @param radians is the angle of the rotation in radians.
		/// 
		void rotate(const Vec3f& axis, float radians)
		{
			// https://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle

			float c = std::cos(radians);
			float s = std::sin(radians);

			float negC = 1 - c;

			// Normalize axis
			Vec3f n = normalize(axis);

			float xx = n.x * n.x;
			float yy = n.y * n.y;
			float zz = n.z * n.z;
			float xy = n.x * n.y;
			float yz = n.y * n.z;
			float xz = n.x * n.z;

			// Calculate matrix values
			Mat4x4f rotMatrix;

			// 1st row
			rotMatrix[0][0] = xx * negC + c;
			rotMatrix[0][1] = xy * negC - n.z * s;
			rotMatrix[0][2] = xz * negC + n.y * s;
			rotMatrix[0][3] = 0.0f;

			// 2nd row
			rotMatrix[1][0] = xy * negC + n.z * s;
			rotMatrix[1][1] = yy * negC + c;
			rotMatrix[1][2] = yz * negC - n.x * s;
			rotMatrix[1][3] = 0.0f;

			// 3rd row
			rotMatrix[2][0] = xz * negC - n.y * s;
			rotMatrix[2][1] = yz * negC + n.x * s;
			rotMatrix[2][2] = zz * negC + c;
			rotMatrix[2][3] = 0.0f;

			// 4th row
			rotMatrix[3][0] = 0.0f;
			rotMatrix[3][1] = 0.0f;
			rotMatrix[3][2] = 0.0f;
			rotMatrix[3][3] = 1.0f;

			// Multiply the rotation matrix with the current matrix
			*this = rotMatrix * *this;
		}

		/// @brief Scales the transformation matrix.
		///
		/// @param vec is the scaling vector.
		/// 
		void scale(const Vec3f& vec)
		{
			// Scaling matrix:
			// sx 0  0  0
			// 0  sy 0  0
			// 0  0  sz 0
			// 0  0  0  1

			auto& matrix = *this;

			// 1st row
			matrix[0][0] *= vec.x;
			matrix[0][1] *= vec.x;
			matrix[0][2] *= vec.x;
			matrix[0][3] *= vec.x;

			// 2nd row
			matrix[1][0] *= vec.y;
			matrix[1][1] *= vec.y;
			matrix[1][2] *= vec.y;
			matrix[1][3] *= vec.y;

			// 3rd row
			matrix[2][0] *= vec.z;
			matrix[2][1] *= vec.z;
			matrix[2][2] *= vec.z;
			matrix[2][3] *= vec.z;

			// Nothing to do on 4th row
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
		Transform result(mat);
		result.rotate(axis, radians);
		
		return result;
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
		Transform result(mat);
		result.scale(vec);
		
		return result;
	}

}
