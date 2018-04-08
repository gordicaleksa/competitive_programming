typedef double coord_t;         // coordinate type

struct Point {
	coord_t x, y;

	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

// intersection between lines defined by points AB and CD
// line definition we use: A1*x + B1*y = C1, A2*x + B2*y = C2
Point line_intersection(const Point& A, const Point& B, const Point& C, const Point& D) {
	// line AB equation
	coord_t A1 = B.y - A.y;
	coord_t B1 = A.x - B.x;
	coord_t C1 = A1*A.x + B1*A.y;
	// line CD equation
	coord_t A2 = D.y - C.y;
	coord_t B2 = C.x - D.x;
	coord_t C2 = A2*C.x + B2*C.y;
	
	coord_t det = A1*B2 - A2*B1;
	if (det == 0) {
		// this is like this only temporary...We can change some flag and notify user that lines are parallel
		Point p;
		p.x = 0;
		p.y = 0;
		return p;
	} else {
		coord_t x = (B2*C1 - B1*C2)/det;
		coord_t y = (A1*C2 - A2*C1)/det;
		Point p;
		p.x = x;
		p.y = y;
		return p;
	}
}