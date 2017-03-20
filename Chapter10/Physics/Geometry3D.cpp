#include "Geometry3D.h"
#include <cmath>
#include <cfloat>

float Length(const Line& line) {
	return Magnitude(line.start - line.end);
}

float LengthSq(const Line& line) {
	return MagnitudeSq(line.start - line.end);
}

Ray FromPoints(const Point& from, const Point& to) {
	return Ray(
		from,
		Normalized(to - from)
	);
}

vec3 GetMin(const AABB& aabb) {
	vec3 p1 = aabb.position + aabb.size;
	vec3 p2 = aabb.position - aabb.size;

	return vec3(fminf(p1.x, p2.x), fminf(p1.y, p2.y), fminf(p1.z, p2.z));
}
vec3 GetMax(const AABB& aabb) {
	vec3 p1 = aabb.position + aabb.size;
	vec3 p2 = aabb.position - aabb.size;

	return vec3(fmaxf(p1.x, p2.x), fmaxf(p1.y, p2.y), fmaxf(p1.z, p2.z));
}

AABB FromMinMax(const vec3& min, const vec3& max) {
	return AABB((min + max) * 0.5f, (max - min) * 0.5f);
}

float PlaneEquation(const Point& point, const Plane& plane) {
	return Dot(point, plane.normal) - plane.distance;
}

#ifndef NO_EXTRAS
float PlaneEquation(const Plane& plane, const Point& point) {
	return Dot(point, plane.normal) - plane.distance;
}
#endif

#ifndef NO_EXTRAS
std::ostream& operator<<(std::ostream& os, const Line& shape) {
	os << "start: (" << shape.start.x << ", " << shape.start.y << ", " << shape.start.z << "), end: (";
	os << shape.end.x << ", " << shape.end.y << ", " << shape.end.z << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, const Ray& shape) {
	os << "origin: (" << shape.origin.x << ", " << shape.origin.y << ", " << shape.origin.z << "), ";
	os << "direction: (" << shape.direction.x << ", " << shape.direction.y << ", " << shape.direction.z << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, const Sphere& shape) {
	os << "position:" << shape.position.x << ", " << shape.position.y << ", " << shape.position.z << "), ";
	os << "radius: " << shape.radius;
	return os;
}

std::ostream& operator<<(std::ostream& os, const AABB& shape) {
	vec3 min = GetMin(shape);
	vec3 max = GetMax(shape);
	os << "min: (" << min.x << ", " << min.y << ", " << min.z << "), ";
	os << "max: (" << max.x << ", " << max.y << ", " << max.z << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, const Plane& shape) {
	os << "normal: (" << shape.normal.x << ", " << shape.normal.y << ", " << shape.normal.z << "), ";
	os << "distance: " << shape.distance;
	return os;
}

std::ostream& operator<<(std::ostream& os, const Triangle& shape) {
	os << "a: (" << shape.a.x << ", " << shape.a.y << ", " << shape.a.z << "), ";
	os << "b: (" << shape.b.x << ", " << shape.b.y << ", " << shape.b.z << "), ";
	os << "c: (" << shape.c.x << ", " << shape.c.y << ", " << shape.c.z << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, const OBB& shape) {
	os << "position:" << shape.position.x << ", " << shape.position.y << ", " << shape.position.z << "), ";
	os << "size:" << shape.size.x << ", " << shape.size.y << ", " << shape.size.z << "), ";
	os << "x basis:" << shape.orientation._11 << ", " << shape.orientation._21 << ", " << shape.orientation._31 << "), ";
	os << "y basis:" << shape.orientation._12 << ", " << shape.orientation._22 << ", " << shape.orientation._32 << "), ";
	os << "z basis:" << shape.orientation._13 << ", " << shape.orientation._23 << ", " << shape.orientation._33 << ")";
	return os;
}
#endif 