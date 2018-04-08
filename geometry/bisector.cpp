typedef double coord_t;         // coordinate type

struct Point {
	coord_t x, y;

	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

// This function finds a line perpendicular to segment XY that cuts the segment XY in half.
// line form: Ax + By = C a line perpendicular to it has form: -Bx + Ay = D, we find D using middle point of XY
void bisector(const Point& X, const Point& Y, coord_t& A, coord_t& B, coord_t& C) {
	// line XY A and B parameters
	coord_t A1 = Y.y - X.y;
	coord_t B1 = X.x - Y.x;
	// segment XY middle point
	coord_t x_m = (X.x + Y.x)/(coord_t)2;
	coord_t y_m = (X.y + Y.y)/(coord_t)2;
	// find D
	coord_t D = -B1*x_m + A1*y_m;
	// finally return bisector
	A = -B1;
	B = A;
	C = D;
	return;
}

// This function finds a line perpendicular to segment XY that cuts the segment XY in half.
// line form: Ax + By = C a line perpendicular to it has form: -Bx + Ay = D, we find D using middle point of XY
// we return 2 points that uniquely define bisector
void bisector(const Point& X, const Point& Y, Point& A, Point& B) {
	// line XY A and B parameters
	coord_t A1 = Y.y - X.y;
	coord_t B1 = X.x - Y.x;
	// segment XY middle point
	coord_t x_m = (X.x + Y.x)/(coord_t)2;
	coord_t y_m = (X.y + Y.y)/(coord_t)2;	
	// find D
	coord_t D = -B1*x_m + A1*y_m;
	// find second point
	coord_t x2 = x_m+1; // randomely choosed WHAT IF BISECTOR IS VERTICAL?
	coord_t y2 = (D + B1*x2)/A1;
	// finally return 2 points of bisector 
	A.x = x_m; A.y = y_m;
	B.x = x2; B.y = y2;
	
	return;
}