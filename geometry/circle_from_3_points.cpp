// pass different A,B and C points
Point2D circle_center(const Point2D& A, const Point2D& B, const Point2D& C, bool& collinear) {
	collinear = false;
	Point2D B1, B2, B3, B4;
	bisector(A, B, B1, B2);
	bisector(B, C, B3, B4);
	bool are_parallel = false;
	bool do_intersect = false;
	// problem if A,B and C are collinear
	Point2D center = segment_intersection(B1, B2, false, B3, B4, false, are_parallel, do_intersect);
	if (are_parallel) collinear = true;
	return center;
}