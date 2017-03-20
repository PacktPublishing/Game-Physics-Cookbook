#ifndef _H_MATH_MATRICES_
#define _H_MATH_MATRICES_

#include "vectors.h"

typedef struct mat2 {
	union {
		struct {
			float	_11, _12,
					_21, _22;
		};
		float asArray[4];
	};

	inline mat2() { 
		_11 = _22 = 1.0f;
		_12 = _21 = 0.0f;
	}

	inline mat2(float f11, float f12,
				float f21, float f22) {
		_11 = f11; _12 = f12;
		_21 = f21; _22 = f22;
	}

	inline float* operator[](int i) {
		return &(asArray[i * 2]);
	}
} mat2;

typedef struct mat3 {
	union {
		struct {
			float	_11, _12, _13,
					_21, _22, _23,
					_31, _32, _33;
		};
		float asArray[9];
	};

	inline mat3() {
		_11 = _22 = _33 = 1.0f;
		_12 = _13 = _21 = 0.0f;
		_23 = _32 = _32 = 0.0f;
	}

	inline mat3(float f11, float f12, float f13,
				float f21, float f22, float f23,
				float f31, float f32, float f33) {
		_11 = f11; _12 = f12; _13 = f13;
		_21 = f21; _22 = f22; _23 = f23;
		_31 = f31; _32 = f32; _33 = f33;
	}

	inline float* operator[](int i) {
		return &(asArray[i * 3]);
	}
} mat3;

typedef struct mat4 {
	union {
		struct {
			float	_11, _12, _13, _14,
					_21, _22, _23, _24,
					_31, _32, _33, _34,
					_41, _42, _43, _44;
		};
		float asArray[16];
	};

	inline mat4() {
		_11 = _22 = _33 = _44 = 1.0f;
		_12 = _13 = _14 = _21 = 0.0f;
		_23 = _24 = _31 = _32 = 0.0f;
		_34 = _41 = _42 = _43 = 0.0f;
	}

	inline mat4(float f11, float f12, float f13, float f14,
				float f21, float f22, float f23, float f24,
				float f31, float f32, float f33, float f34,
				float f41, float f42, float f43, float f44) {
		_11 = f11; _12 = f12; _13 = f13; _14 = f14;
		_21 = f21; _22 = f22; _23 = f23; _24 = f24;
		_31 = f31; _32 = f32; _33 = f33; _34 = f34;
		_41 = f41; _42 = f42; _43 = f43; _44 = f44;
	}

	inline float* operator[](int i) {
		return &(asArray[i * 4]);
	}
} mat4;

#ifndef NO_EXTRAS
	bool operator==(const mat2& l, const mat2& r);
	bool operator==(const mat3& l, const mat3& r);
	bool operator==(const mat4& l, const mat4& r);

	bool operator!=(const mat2& l, const mat2& r);
	bool operator!=(const mat3& l, const mat3& r);
	bool operator!=(const mat4& l, const mat4& r);
#endif 

void Transpose(const float *srcMat, float *dstMat,  int srcRows,  int srcCols);
mat2 Transpose(const mat2& matrix);
mat3 Transpose(const mat3& matrix);
mat4 Transpose(const mat4& matrix);

mat2 operator*(const mat2& matrix, float scalar);
mat3 operator*(const mat3& matrix, float scalar);
mat4 operator*(const mat4& matrix, float scalar);

bool Multiply(float* out, const float* matA, int aRows, int aCols, const float* matB, int bRows, int bCols);
mat2 operator*(const mat2& matrixA, const mat2& matrixB);
mat3 operator*(const mat3& matrixA, const mat3& matrixB);
mat4 operator*(const mat4& matrixA, const mat4& matrixB);

mat3 Cut(const mat4& mat, int row, int col);
mat2 Cut(const mat3& mat, int row, int col);
void Cofactor(float* out, const float* minor, int rows, int cols);

mat2 Minor(const mat2& mat);
mat2 Cofactor(const mat2& mat);
float Determinant(const mat2& matrix);
mat2 Adjugate(const mat2& mat);
mat2 Inverse(const mat2& mat);

mat3 Minor(const mat3& mat);
mat3 Cofactor(const mat3& mat);
float Determinant(const mat3& mat);
mat3 Adjugate(const mat3& mat);
mat3 Inverse(const mat3& mat);

mat4 Minor(const mat4& mat);
mat4 Cofactor(const mat4& mat);
float Determinant(const mat4& mat);
mat4 Adjugate(const mat4& mat);
mat4 Inverse(const mat4& mat);

#endif