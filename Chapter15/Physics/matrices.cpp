#include "matrices.h"
#include <cmath>
#include <cfloat>
#define SANITY_TEST_MAT4_INVERSE

#ifdef SANITY_TEST_MAT4_INVERSE
#include <iostream>
#endif 


// http://realtimecollisiondetection.net/pubs/Tolerances/
#define CMP(x, y) \
	(fabsf(x - y) <= FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))

#ifndef NO_EXTRAS
bool operator==(const mat2& l, const mat2& r) {
	for (int i = 0; i < /* 2 * 2 = */4; ++i) {
		if (!CMP(l.asArray[i], r.asArray[i])) {
			return false;
		}
	}
	return true;
}

bool operator==(const mat3& l, const mat3& r) {
	for (int i = 0; i < /* 3 * 3 = */ 9; ++i) {
		if (!CMP(l.asArray[i], r.asArray[i])) {
			return false;
		}
	}
	return true;
}
bool operator==(const mat4& l, const mat4& r) {
	for (int i = 0; i < /* 4 * 4 = */ 16; ++i) {
		if (!CMP(l.asArray[i], r.asArray[i])) {
			return false;
		}
	}
	return true;
}

bool operator!=(const mat2& l, const mat2& r) {
	return !(l == r);
}

bool operator!=(const mat3& l, const mat3& r) {
	return !(l == r);
}

bool operator!=(const mat4& l, const mat4& r) {
	return !(l == r);
}
#endif 

void Transpose(const float *srcMat, float *dstMat, int srcRows, int srcCols) {
	for (int i = 0; i < srcRows * srcCols; i++) {
		int row = i / srcRows;
		int col = i % srcRows;
		dstMat[i] = srcMat[srcCols * col + row];
	}
}

mat2 Transpose(const mat2& matrix) {
	mat2 result;
	Transpose(matrix.asArray, result.asArray, 2, 2);
	return result;
}

mat3 Transpose(const mat3& matrix) {
	mat3 result;
	Transpose(matrix.asArray, result.asArray, 3, 3);
	return result;
}

mat4 Transpose(const mat4& matrix) {
	mat4 result;
	Transpose(matrix.asArray, result.asArray, 4, 4);
	return result;
}

mat2 operator*(const mat2& matrix, float scalar) {
	mat2 result;
	for (int i = 0; i < 4; ++i) {
		result.asArray[i] = matrix.asArray[i] * scalar;
	}
	return result;
}

mat3 operator*(const mat3& matrix, float scalar) {
	mat3 result;
	for (int i = 0; i < 9; ++i) {
		result.asArray[i] = matrix.asArray[i] * scalar;
	}
	return result;
}

mat4 operator*(const mat4& matrix, float scalar) {
	mat4 result;
	for (int i = 0; i < 16; ++i) {
		result.asArray[i] = matrix.asArray[i] * scalar;
	}
	return result;
}

bool Multiply(float* out, const float* matA, int aRows, int aCols, const float* matB, int bRows, int bCols) {
	if (aCols != bRows) {
		return false;
	}

	for (int i = 0; i < aRows; ++i) {
		for (int j = 0; j < bCols; ++j) {
			out[bCols * i + j] = 0.0f;
			for (int k = 0; k < bRows; ++k) {
				out[bCols * i + j] += matA[aCols * i + k] * matB[bCols * k + j];
			}
		}
	}

	return true;
}

mat2 operator*(const mat2& matrixA, const mat2& matrixB) {
	mat2 result;
	Multiply(result.asArray, matrixA.asArray, 2, 2, matrixB.asArray, 2, 2);
	return result;
}

mat3 operator*(const mat3& matrixA, const mat3& matrixB) {
	mat3 result;
	Multiply(result.asArray, matrixA.asArray, 3, 3, matrixB.asArray, 3, 3);
	return result;
}

mat4 operator*(const mat4& matrixA, const mat4& matrixB) {
	mat4 result;
	Multiply(result.asArray, matrixA.asArray, 4, 4, matrixB.asArray, 4, 4);
	return result;
}

float Determinant(const mat2& matrix) {
	return matrix._11 * matrix._22 - matrix._12 * matrix._21;
}

mat2 Cut(const mat3& mat, int row, int col) {
	mat2 result;
	int index = 0;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (i == row || j == col) {
				continue;
			}
			result.asArray[index++] = mat.asArray[3 * i + j];
		}
	}

	return result;
}

mat3 Cut(const mat4& mat, int row, int col) {
	mat3 result;
	int index = 0;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == row || j == col) {
				continue;
			}
			result.asArray[index++] = mat.asArray[4 * i + j];
		}
	}

	return result;
}

mat3 Minor(const mat3& mat) {
	mat3 result;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			result[i][j] = Determinant(Cut(mat, i, j));
		}
	}
	
	return result;
}

mat2 Minor(const mat2& mat) {
	return mat2(
		mat._22, mat._21,
		mat._12, mat._11
	);
}

void Cofactor(float* out, const float* minor, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			out[cols * j + i] = minor[cols * j + i] * powf(-1.0f, i + j);
		}
	}
}

mat2 Cofactor(const mat2& mat) {
	mat2 result;
	Cofactor(result.asArray, Minor(mat).asArray, 2, 2);
	return result;
}

mat3 Cofactor(const mat3& mat) {
	mat3 result;
	Cofactor(result.asArray, Minor(mat).asArray, 3, 3);
	return result;
}

float Determinant(const mat3& mat) {
	float result = 0.0f;

	/*float A = mat.asArray[3 * 0 + 0] * Determinant(Cut(mat, 0, 0));
	float B = mat.asArray[3 * 0 + 1] * Determinant(Cut(mat, 0, 1));
	float C = mat.asArray[3 * 0 + 2] * Determinant(Cut(mat, 0, 2));
	result = A - B + C;*/

	/*for (int j = 0; j < 3; ++j) {
		result += mat.asArray[3 * 0 + j] * Determinant(Cut(mat, 0, j)) * powf(-1, 0 + j);
	}*/

	mat3 cofactor = Cofactor(mat);
	for (int j = 0; j < 3; ++j) {
		result += mat.asArray[3 * 0 + j] * cofactor[0][j];
	}

	return result;
}

mat4 Minor(const mat4& mat) {
	mat4 result;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result[i][j] = Determinant(Cut(mat, i, j));
		}
	}

	return result;
}

mat4 Cofactor(const mat4& mat) {
	mat4 result;
	Cofactor(result.asArray, Minor(mat).asArray, 4, 4);
	return result;
}

float Determinant(const mat4& mat) {
	float result = 0.0f;

	mat4 cofactor = Cofactor(mat);
	for (int j = 0; j < 4; ++j) {
		result += mat.asArray[4 * 0 + j] * cofactor[0][j];
	}

	return result;
}

mat2 Adjugate(const mat2& mat) {
	return Transpose(Cofactor(mat));
}

mat3 Adjugate(const mat3& mat) {
	return Transpose(Cofactor(mat));
}

mat4 Adjugate(const mat4& mat) {
	return Transpose(Cofactor(mat));
}

mat2 Inverse(const mat2& mat) {
	float det = Determinant(mat);
	if (CMP(det, 0.0f)) { return mat2(); }
	return Adjugate(mat) * (1.0f / det);

	/*float det = mat._11 * mat._22 - mat._12 * mat._21;
	if (CMP(det, 0.0f)) { 
		return mat2(); 
	}
	float i_det = 1.0f / det;
	mat2 result;
	result._11 =  mat._22 * i_det;
	result._12 = -mat._12 * i_det;
	result._21 = -mat._21 * i_det;
	result._22 =  mat._11 * i_det;
	return result;*/
}

mat3 Inverse(const mat3& mat) {
	float det = Determinant(mat);
	if (CMP(det, 0.0f)) { return mat3(); }
	return Adjugate(mat) * (1.0f / det);
}

mat4 Inverse(const mat4& m) {
	/*float det = Determinant(m);
	if (CMP(det, 0.0f)) { return mat4(); }
	return Adjugate(m) * (1.0f / det);*/

	// The code below is the expanded form of the above equation.
	// This optimization avoids loops and function calls

	float det 
		= m._11 * m._22 * m._33 * m._44 + m._11 * m._23 * m._34 * m._42 + m._11 * m._24 * m._32 * m._43
		+ m._12 * m._21 * m._34 * m._43 + m._12 * m._23 * m._31 * m._44 + m._12 * m._24 * m._33 * m._41
		+ m._13 * m._21 * m._32 * m._44 + m._13 * m._22 * m._34 * m._41 + m._13 * m._24 * m._31 * m._42
		+ m._14 * m._21 * m._33 * m._42 + m._14 * m._22 * m._31 * m._43 + m._14 * m._23 * m._32 * m._41
		- m._11 * m._22 * m._34 * m._43 - m._11 * m._23 * m._32 * m._44 - m._11 * m._24 * m._33 * m._42
		- m._12 * m._21 * m._33 * m._44 - m._12 * m._23 * m._34 * m._41 - m._12 * m._24 * m._31 * m._43
		- m._13 * m._21 * m._34 * m._42 - m._13 * m._22 * m._31 * m._44 - m._13 * m._24 * m._32 * m._41
		- m._14 * m._21 * m._32 * m._43 - m._14 * m._22 * m._33 * m._41 - m._14 * m._23 * m._31 * m._42;

	if (CMP(det, 0.0f)) { 
		return mat4(); 
	}
	float i_det = 1.0f / det;

	mat4 result;
	result._11 = (m._22 * m._33 * m._44 + m._23 * m._34 * m._42 + m._24 * m._32 * m._43 - m._22 * m._34 * m._43 - m._23 * m._32 * m._44 - m._24 * m._33 * m._42) * i_det;
	result._12 = (m._12 * m._34 * m._43 + m._13 * m._32 * m._44 + m._14 * m._33 * m._42 - m._12 * m._33 * m._44 - m._13 * m._34 * m._42 - m._14 * m._32 * m._43) * i_det;
	result._13 = (m._12 * m._23 * m._44 + m._13 * m._24 * m._42 + m._14 * m._22 * m._43 - m._12 * m._24 * m._43 - m._13 * m._22 * m._44 - m._14 * m._23 * m._42) * i_det;
	result._14 = (m._12 * m._24 * m._33 + m._13 * m._22 * m._34 + m._14 * m._23 * m._32 - m._12 * m._23 * m._34 - m._13 * m._24 * m._32 - m._14 * m._22 * m._33) * i_det;
	result._21 = (m._21 * m._34 * m._43 + m._23 * m._31 * m._44 + m._24 * m._33 * m._41 - m._21 * m._33 * m._44 - m._23 * m._34 * m._41 - m._24 * m._31 * m._43) * i_det;
	result._22 = (m._11 * m._33 * m._44 + m._13 * m._34 * m._41 + m._14 * m._31 * m._43 - m._11 * m._34 * m._43 - m._13 * m._31 * m._44 - m._14 * m._33 * m._41) * i_det;
	result._23 = (m._11 * m._24 * m._43 + m._13 * m._21 * m._44 + m._14 * m._23 * m._41 - m._11 * m._23 * m._44 - m._13 * m._24 * m._41 - m._14 * m._21 * m._43) * i_det;
	result._24 = (m._11 * m._23 * m._34 + m._13 * m._24 * m._31 + m._14 * m._21 * m._33 - m._11 * m._24 * m._33 - m._13 * m._21 * m._34 - m._14 * m._23 * m._31) * i_det;
	result._31 = (m._21 * m._32 * m._44 + m._22 * m._34 * m._41 + m._24 * m._31 * m._42 - m._21 * m._34 * m._42 - m._22 * m._31 * m._44 - m._24 * m._32 * m._41) * i_det;
	result._32 = (m._11 * m._34 * m._42 + m._12 * m._31 * m._44 + m._14 * m._32 * m._41 - m._11 * m._32 * m._44 - m._12 * m._34 * m._41 - m._14 * m._31 * m._42) * i_det;
	result._33 = (m._11 * m._22 * m._44 + m._12 * m._24 * m._41 + m._14 * m._21 * m._42 - m._11 * m._24 * m._42 - m._12 * m._21 * m._44 - m._14 * m._22 * m._41) * i_det;
	result._34 = (m._11 * m._24 * m._32 + m._12 * m._21 * m._34 + m._14 * m._22 * m._31 - m._11 * m._22 * m._34 - m._12 * m._24 * m._31 - m._14 * m._21 * m._32) * i_det;
	result._41 = (m._21 * m._33 * m._42 + m._22 * m._31 * m._43 + m._23 * m._32 * m._41 - m._21 * m._32 * m._43 - m._22 * m._33 * m._41 - m._23 * m._31 * m._42) * i_det;
	result._42 = (m._11 * m._32 * m._43 + m._12 * m._33 * m._41 + m._13 * m._31 * m._42 - m._11 * m._33 * m._42 - m._12 * m._31 * m._43 - m._13 * m._32 * m._41) * i_det;
	result._43 = (m._11 * m._23 * m._42 + m._12 * m._21 * m._43 + m._13 * m._22 * m._41 - m._11 * m._22 * m._43 - m._12 * m._23 * m._41 - m._13 * m._21 * m._42) * i_det;
	result._44 = (m._11 * m._22 * m._33 + m._12 * m._23 * m._31 + m._13 * m._21 * m._32 - m._11 * m._23 * m._32 - m._12 * m._21 * m._33 - m._13 * m._22 * m._31) * i_det;

#ifdef  SANITY_TEST_MAT4_INVERSE
	if (result * m != mat4()) {
		std::cout << "ERROR! Expecting matrix x inverse to equal identity!\n";
	}
#endif


	return result;
}