#include <cmath>

typedef double coord_t;         // coordinate type

struct Point {
	coord_t x, y;

	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

// this can be extended to matrices

// rotates point A 'angle' degrees/radians (depending on is_degree flag) around point O and returns that new point
Point rotate(const Point& O, const Point& A, double angle, bool is_degree) {
	if (is_degree) angle *= PI / 180.0; // convert to radians
	// shift coordinate system
	coord_t x = A.x - O.x;
	coord_t y = A.y - O.y;
	// rotate
	coord_t x_r = x*cos(angle) - y*sin(angle);
	coord_t y_r = x*sin(angle) + y*cos(angle);
	// shift again
	x_r += O.x;
	y_r += O.y;
	Point r;
	r.x = x_r;
	r.y = y_r;
	return r;
}
