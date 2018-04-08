#include <cmath>

typedef double coord_t;         // coordinate type

struct Point {
	coord_t x, y;

	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

// 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
// Returns a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
coord_t cross(const Point &O, const Point &A, const Point &B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

coord_t distance(const Point& A,const Point& B) {
	coord_t x = (A.x-B.x);
	coord_t y = (A.y-B.y);
	return sqrt(x*x + y*y);
}

//Compute the distance from line formed by A and B to C
coord_t line_point_distance(const Point& A, const Point& B, const Point& C) {
	return abs(cross(A,B,C) / distance(A,B));
}












