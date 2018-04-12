coord_t segment_point3D_distance(const Point3D& A, const Point3D& B, const Point3D& C, bool is_segment) {
	if (A == B) return (A-C).length();
	Point3D BA = A - B;
	Point3D BC = C - B;
	Point3D AB = B - A;
	Point3D AC = C - A;
	coord_t d = (AB ^ AC).length() / (A - B).length();
	if (is_segment) {
		coord_t dot1 = AB * BC;
		if (dot1 > 0) return BC.length();
		coord_t dot2 = BA * AC;
		if (dot2 > 0) return AC.length();
	}
	return abs(d);
}
