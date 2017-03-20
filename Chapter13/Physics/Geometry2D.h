#ifndef _H_GEOMETRY_2D
#define _H_GEOMETRY_2D

#include "vectors.h"

#ifndef NO_EXTRAS
#include <ostream>
#endif 

typedef vec2 Point2D;

typedef struct Line2D {
	Point2D start;
	Point2D end;

	inline Line2D() {}
	inline Line2D(const Point2D& s, const Point2D& e) :
		start(s), end(e) {}
} Line2D;

typedef struct Circle {
	Point2D position;
	float radius;

	inline Circle() : radius(1.0f) {}
	inline Circle(const Point2D& p, float r):
		position(p), radius(r) {}
} Circle;

typedef struct Rectangle2D {
	Point2D origin;
	vec2 size;

	inline Rectangle2D() : size(1, 1) { }
	inline Rectangle2D(const Point2D& o, const vec2& s) :
		origin(o), size(s) { }
} Rectangle2D;

typedef struct OrientedRectangle {
	Point2D position;
	vec2 halfExtents;
	float rotation;

	inline OrientedRectangle() :
		halfExtents(1.0f, 1.0f), rotation(0.0f) { }
	inline OrientedRectangle(const Point2D& pos, const vec2& ext) :
		position(pos), halfExtents(ext), rotation(0.0f) { }
	inline OrientedRectangle(const Point2D& pos, const vec2& ext, float rot) :
		position(pos), halfExtents(ext), rotation(rot) { }
} OrientedRectangle;

float Length(const Line2D& line);
float LengthSq(const Line2D& line);
vec2 GetMin(const Rectangle2D& rect);
vec2 GetMax(const Rectangle2D& rect);
Rectangle2D FromMinMax(const vec2& min, const vec2& max);

bool PointOnLine(const Point2D& point, const Line2D& line);
bool PointInCircle(const Point2D& point, const Circle& circle);
bool PointInRectangle(const Point2D& point, const Rectangle2D& rectangle);
bool PointInOrientedRectangle(const Point2D& point, const OrientedRectangle& rectangle);

bool LineCircle(const Line2D& line, const Circle& circle);
bool LineRectangle(const Line2D& line, const Rectangle2D& rectangle);
bool LineOrientedRectangle(const Line2D& line, const OrientedRectangle& rectangle);

#define PointLine(point, line) PointOnLine(point, line)
#define LinePoint(line, point) PointOnLine(point, line)
#define CircleLine(circle, line) LineCircle(line, circle)
#define RectangleLine(rectangle, line) \
	LineRectangle(line, rectangle);
#define OrientedRectangleLine(rectangle, line) \
	LineOrientedRectangle(line, rectangle);

#ifndef NO_EXTRAS
std::ostream& operator<<(std::ostream& os, const Line2D& shape);
std::ostream& operator<<(std::ostream& os, const Circle& shape);
std::ostream& operator<<(std::ostream& os, const Rectangle2D& shape);
std::ostream& operator<<(std::ostream& os, const OrientedRectangle& shape);
#endif 


#endif