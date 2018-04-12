// Compute the distance from line formed by A and B to C
// if is_segment is true AB is segment otherwise it's a line
coord_t segment_point_distance(const Point2D& A, const Point2D& B, const Point2D& C, bool is_segment) {
	if (A == B) return (A - C).length();
	Point2D BA = A - B;
	Point2D BC = C - B;
	Point2D AB = B - A;
	Point2D AC = C - A;
	coord_t d = (AB ^ AC) / BA.length();
	if (is_segment) {
		coord_t dot1 = AB * BC;
		if (dot1 > 0) return BC.length();
		coord_t dot2 = BA * AC;
		if (dot2 > 0) return AC.length();
	}
	return abs(d);
}












