#include <iostream>
#include <cstdio>
#include "vectors.h"
#include "matrices.h"
#include <stdlib.h>

// http://realtimecollisiondetection.net/pubs/Tolerances/
#define CMP(x, y) \
	(fabsf(x - y) <= FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))


void DebugPrintMatrixArray(mat4& m) {
	std::cout << "[0] :"  << m.asArray[0]  << ", [1] :" << m.asArray[1]  << ", [2] :"  << m.asArray[2]  << ", [3] :" << m.asArray[3]  << ",\n";
	std::cout << "[4] :"  << m.asArray[4] <<  ", [5] :" << m.asArray[5]  << ", [6] :"  << m.asArray[6]  << ", [7] :" << m.asArray[7]  << ",\n";
	std::cout << "[8] :"  << m.asArray[8]  << ", [9] :" << m.asArray[9]  << ", [10]:" << m.asArray[10]  << ", [11]:" << m.asArray[11] << ",\n";
	std::cout << "[12]: " << m.asArray[12] << ", [13]:" << m.asArray[13] << ", [14]:" << m.asArray[14] << ", [15]: " << m.asArray[15] << "\n";
}

void DebugPrintColMatrix(float* col) {
	std::cout << "[0]: " << col[0] << ", [1]" << col[1] << "\n";
	std::cout << "[2]: " << col[2] << ", [3]" << col[3] << "\n";
	std::cout << "[4]: " << col[4] << ", [5]" << col[5] << "\n";
	std::cout << "[6]: " << col[6] << ", [7]" << col[7] << "\n";
}

void DebugPrintRowMatrix(float* row) {
	std::cout << "[0] :" << row[0] << ", [1] :" << row[1] << ", [2] :" << row[2] << ", [3] :" << row[3] << ",\n";
	std::cout << "[4] :" << row[4] << ", [5] :" << row[5] << ", [6] :" << row[6] << ", [7] :" << row[7] << ",\n";
}

void PrintMat2(mat2& m) {
	std::cout << "[0] :" << m.asArray[0] << ", [1] :" << m.asArray[1] << ",\n";
	std::cout << "[2] :" << m.asArray[2] << ", [3] :" << m.asArray[3] << "\n";

}

bool ArrCompare(float* a, float* b, int s) {
	for (int i = 0; i < s; ++i) {
		if (!CMP(a[i], b[i])) {
			std::cout << "bad index: " << i << "\n";
			return false;
		}
	}
	return true;
}



int main(int argc, char** argv) {
	mat4 M1(-4, 0, 0, 0,
		-1, 2, 0, 0,
		-4.0f, 4.0f, 4.0f, 0.0f,
		- 1.0f, -9.0f, -1.0f, 1.0f);
	float det = Determinant(M1);
	//mat4 x = Minor(M1);
	std::cout << "det: " << det << " / -32\n";
	mat4 A1(8, 0, 0, 0,
		4, -16, 0, 0,
		4, 16, -8, 0,
		48, -128, -8, -32);
	mat4 E1(-8.0f / 32.0f, 0.0f, 0.0f, 0.0f,
		-4.0f / 32.0f, 16.0f / 32.0f, 0.0f, 0.0f,
		-4.0f / 32.0f, -16.0f / 32.0f, 8.0f / 32.0f, 0.0f,
		-48.0f / 32.0f, 128.0f / 32.0f, 8.0f / 32.0f, 32.0f / 32.0f);
	if (Adjugate(M1) != A1) {
		std::cout << "ERROR adjugate 1\n";
	}
	if (Inverse(M1) != E1) {
		std::cout << "ERROR inverse 1\n";
	}
	mat3 M2(1, 2, 3,
		2, 5, 3,
		1, 0, 8);
	mat3 E2(-40, 16, 9,
		13, -5, -3,
		5, -2, -1);
	if (Inverse(M2) != E2) {
		std::cout << "ERROR inverse 2\n";
	}
	mat3 M3(4, 2, 1,
		6, 3, 4,
		2, 1, 0);
	mat3 E3(-4, -8, 0, -1, -2, 0, 5, 10, 0);
	if (Minor(M3) != E3) {
		std::cout << "ERROR minor 1\n";
	}
	mat4 M4(1, 0, 0, 1,
		0, 2, 1, 2,
		2, 1, 0, 1,
		2, 0, 1, 4);
	mat4 E4(
		-2, -0.5f, 1, 0.5f, 
		1, 0.5f, 0, -0.5f,
		-8, -1, 2, 2,
		3, 0.5f, -1, -0.5f
	);
	if (Inverse(M4) != E4) {
		std::cout << "ERROR inverse 3\n";
	}

	std::cout << "Press return to exit...";

	getchar();

	return 0;
}