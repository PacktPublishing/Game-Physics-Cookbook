#include "Geometry3D.h"
#include <cmath>
#include <cfloat>

#define CMP(x, y) \
	(fabsf(x - y) <= FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))

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

bool PointInSphere(const Point& point, const Sphere& sphere) {
	return MagnitudeSq(point - sphere.position) < sphere.radius * sphere.radius;
}

bool PointOnPlane(const Point& point, const Plane& plane) {
	// This should probably use an epsilon!
	//return Dot(point, plane.normal) - plane.distance == 0.0f;

	return CMP(Dot(point, plane.normal) - plane.distance, 0.0f);
}

bool PointInAABB(const Point& point, const AABB& aabb) {
	Point min = GetMin(aabb);
	Point max = GetMax(aabb);

	if (point.x < min.x || point.x < min.y || point.z < min.z) {
		return false;
	}
	if (point.x > max.x || point.y > max.y || point.z > max.z) {
		return false;
	}

	return true;
}

bool PointInOBB(const Point& point, const OBB& obb) {
	vec3 dir = point - obb.position;

	for (int i = 0; i < 3; ++i) {
		const float* orientation = &obb.orientation.asArray[i * 3];
		vec3 axis(orientation[0], orientation[1], orientation[2]);

		float distance = Dot(dir, axis);

		if (distance > obb.size.asArray[i]) {
			return false;
		}
		if (distance < -obb.size.asArray[i]) {
			return false;
		}
	}

	return true;
}

Point ClosestPoint(const Sphere& sphere, const Point& point) {
	vec3 sphereToPoint = point - sphere.position;
	Normalize(sphereToPoint);
	sphereToPoint = sphereToPoint * sphere.radius;
	return sphereToPoint + sphere.position;
}

Point ClosestPoint(const AABB& aabb, const Point& point) {
	Point result = point;
	Point min = GetMin(aabb);
	Point max = GetMax(aabb);

	result.x = (result.x < min.x) ? min.x : result.x;
	result.y = (result.y < min.x) ? min.y : result.y;
	result.z = (result.z < min.x) ? min.z : result.z;

	result.x = (result.x > max.x) ? max.x : result.x;
	result.y = (result.y > max.x) ? max.y : result.y;
	result.z = (result.z > max.x) ? max.z : result.z;

	return result;
}

Point ClosestPoint(const OBB& obb, const Point& point) {
	Point result = obb.position;
	vec3 dir = point - obb.position;

	for (int i = 0; i < 3; ++i) {
		const float* orientation = &obb.orientation.asArray[i * 3];
		vec3 axis(orientation[0], orientation[1], orientation[2]);

		float distance = Dot(dir, axis);

		if (distance > obb.size.asArray[i]) {
			distance = obb.size.asArray[i];
		}
		if (distance < -obb.size.asArray[i]) {
			distance = -obb.size.asArray[i];
		}

		result = result + (axis * distance);
	}

	return result;
}

Point ClosestPoint(const Plane& plane, const Point& point) {
	// This works assuming plane.Normal is normalized, which it should be
	float distance = Dot(plane.normal, point) - plane.distance;
	// If the plane normal wasn't normalized, we'd need this:
	// distance = distance / DOT(plane.Normal, plane.Normal);

	return point - plane.normal * distance;
}

bool PointOnLine(const Point& point, const Line& line) {
	Point closest = ClosestPoint(line, point);
	float distanceSq = MagnitudeSq(closest - point);
	return CMP(distanceSq, 0.0f);
}

Point ClosestPoint(const Line& line, const Point& point) {
	vec3 lVec = line.end - line.start; // Line Vector
	// Project "point" onto the "Line Vector", computing:
	// closest(t) = start + t * (end - start)
	// T is how far along the line the projected point is
	float t = Dot(point - line.start, lVec) / Dot(lVec, lVec);
	// Clamp t to the 0 to 1 range
	t = fmaxf(t, 0.0f);
	t = fminf(t, 1.0f);
	// Return projected position of t
	return line.start + lVec * t;
}

bool PointOnRay(const Point& point, const Ray& ray) {
	if (point == ray.origin) {
		return true;
	}

	vec3 norm = point - ray.origin;
	Normalize(norm);
	float diff = Dot(norm, ray.direction); // Direction is normalized
	// If BOTH vectors point in the same direction, diff should be 1
	return CMP(diff, 1.0f);
}

Point ClosestPoint(const Ray& ray, const Point& point) {
	// Project point onto ray, 
	float t = Dot(point - ray.origin, ray.direction);
	// Not needed if direction is normalized!
	// t /= Dot(ray.direction, ray.direction);

	// We only want to clamp t in the positive direction.
	// The ray extends infinatley in this direction!
	t = fmaxf(t, 0.0f);

	// Compute the projected position from the clamped t
	// Notice we multiply r.Normal by t, not AB.
	// This is becuase we want the ray in the direction 
	// of the normal, which technically the line segment is
	// but this is much more explicit and easy to read.
	return Point(ray.origin + ray.direction * t);
}