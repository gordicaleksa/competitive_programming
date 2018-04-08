#include <cmath>

typedef double coord_t;   // coordinate type
typedef double coord2_t;  // must be big enough to hold 2*max(|coordinate|)^2

struct Point {
	coord_t x, y;

	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

coord_t distance(const Point& A,const Point& B) {
	coord_t x = (A.x-B.x);
	coord_t y = (A.y-B.y);
	return sqrt(x*x + y*y);
}