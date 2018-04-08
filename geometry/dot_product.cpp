typedef double coord_t;         // coordinate type
typedef double coord2_t;  // must be big enough to hold 2*max(|coordinate|)^2

struct Point {
	coord_t x, y;

	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

// calculates dot product between vectors OA and OB
coord2_t dot_product(const Point &O, const Point &A, const Point &B) {
	return (A.x - O.x)*(B.x - O.x) + (A.y - O.y)*(B.y - O.y);
}