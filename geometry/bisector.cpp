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

// pass different X and Y points
// This function finds a line perpendicular to segment XY that cuts the segment XY in half.
// line form: Ax + By = C a line perpendicular to it has form: -Bx + Ay = D, we find D using middle point of XY
// we return 2 points that uniquely define a bisector
void bisector(const Point2D& X, const Point2D& Y, Point2D& A, Point2D& B) {
	// line XY A and B parameters
	coord_t A1 = Y.y - X.y;
	coord_t B1 = X.x - Y.x;
	// segment XY middle point
	coord_t x_m = (X.x + Y.x) / (coord_t)2;
	coord_t y_m = (X.y + Y.y) / (coord_t)2;
	// find D
	coord_t D = -B1 * x_m + A1 * y_m;
	// find second point
	coord_t x2;
	coord_t y2;
	if (A1 == 0) { // bisector is vertical
		x2 = x_m;
		y2 = y_m + 1;
	}
	else {
		x2 = x_m + 1; 
		y2 = (D + B1 * x2) / A1;
	}
	
	// finally return 2 points of bisector 
	A.x = x_m; A.y = y_m;
	B.x = x2; B.y = y2;

	return;
}
