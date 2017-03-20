#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <limits>

#include "vectors.h"
#include "matrices.h"
#include "Geometry2D.h"
#include "QuadTree.h"
#include "Geometry3D.h"
#include "ObjLoader.h"

int main(int argc, char** argv) {
	Mesh mesh;

	Model m1, m2;

	m1.position = vec3(1, 1, 1);
	m2.position = vec3(3, 2, 1);
	m1.parent = &m2;

	mat4 world = GetWorldMatrix(m1);
	vec3 debug = MultiplyPoint(vec3(), world);
	std::cout << debug.x << ", " << debug.y << ", " << debug.z << "\n";

	std::cout << "Press return to exit...";

	getchar();

	return 0;
}