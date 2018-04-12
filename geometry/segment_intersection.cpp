// make sure A and B as well as C and D are different points!
// intersection between lines/segments defined by points AB and CD
// line definition we use: A1*x + B1*y = C1, A2*x + B2*y = C2
Point2D segment_intersection(const Point2D& A, const Point2D& B, bool is_segment_AB, const Point2D& C, const Point2D& D, bool is_segment_CD, bool& are_parallel, bool& do_intersect) {
	if (A == B || C == D) {
		do_intersect = false;
		return Point2D();
	}
	coord_t e = 1e-6; // epsilon error
	are_parallel = false;
	do_intersect = true;
	// line AB equation
	coord_t A1 = B.y - A.y;
	coord_t B1 = A.x - B.x;
	coord_t C1 = A1 * A.x + B1 * A.y;
	// line CD equation
	coord_t A2 = D.y - C.y;
	coord_t B2 = C.x - D.x;
	coord_t C2 = A2 * C.x + B2 * C.y;

	coord_t det = A1 * B2 - A2 * B1;
	if (abs(det) < e) { // lines AB and CD are parallel
		are_parallel = true;
		
		double s; // this will not work if we have 2 equal points because A=B=C=0
		if (A2 != 0) s = A1 / A2;
		else if (B2 != 0) s = B1 / B2;
		else s = C1 / C2;
		A2 = s * A2; B2 = s * B2; C2 = s * C2;
		if (abs(C1 - C2)<e) { // exactly the same lines
			if (is_segment_AB && is_segment_CD) {
				Point2D s_AB = A < B ? A : B;
				Point2D b_AB = A < B ? B : A;
				Point2D s_CD = C < D ? C : D;
				Point2D b_CD = C < D ? D : C;
				if ((s_AB < s_CD && s_CD < b_AB) || (s_AB == s_CD) || (b_AB == s_CD)) {
					return s_CD;
				}
				else if ((s_AB < b_CD && b_CD < b_AB) || (s_AB == b_CD) || (b_AB == b_CD)) {
					return b_CD;
				}
				else {
					do_intersect = false;
					return Point2D();
				}
			}
			else {
				// they do intersect
				return is_segment_AB ? A : C;
			}
		}
		else { // parallel but different lines
			do_intersect = false;
			return Point2D();
		}
	}
	else { // lines AB and CD do intersect, but we need to check if segments actually intersect
		coord_t x = (B2*C1 - B1 * C2) / det;
		coord_t y = (A1*C2 - A2 * C1) / det;
		Point2D ip(x, y);
		if (is_segment_AB) {
			if (segment_point_distance(A, B, ip, true) > e) do_intersect = false;
		}
		if (is_segment_CD) {
			if (segment_point_distance(C, D, ip, true) > e) do_intersect = false;
		}
		return ip;
	}
}