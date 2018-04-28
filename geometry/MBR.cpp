// rotating calipers: O(n)
// main resource: http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.155.5671&rep=rep1&type=pdf
coord_t mbr_rc(vector<Point2D>& boundary) {
	int n = boundary.size();

	// step 1: scale all of the points
	int scale_factor = 200.0; // experimentally found it
	for (int i = 0; i < n; i++)
		boundary[i] = boundary[i] / scale_factor;

	// step 2: find correct points/indices where to attach calipers
	int p1 = 0, p2 = 0, p3 = 0, p4 = 0; // starting indices of calipers
	Point2D fst = boundary[0];
	coord_t min_x = fst.x, max_x = fst.x, min_y = fst.y, max_y = fst.y;
	for (int i = 1; i < n; i++) {
		Point2D c = boundary[i];
		if (c.y <= min_y) p1 = i, min_y = c.y;
		if (c.y >= max_y) p3 = i, max_y = c.y;
		if (c.x <= min_x) p4 = i, min_x = c.x;
		if (c.x >= max_x) p2 = i, max_x = c.x;
	}
	
	// step 3: prepare calipers and other init variables
	// unit vectors representing rotating calipers
	Point2D vp1(1, 0);
	Point2D vp2(0, 1);
	Point2D vp3(-1, 0);
	Point2D vp4(0, -1);
	// this is where area of OMBB (oriented minimum bounding box) will be stored
	coord_t min_area = numeric_limits<double>::infinity();
	coord_t e = 0.0000001; // degrees 

	// step 4: start moving the calipers
	for (int i = 0; i < n; i++) {
		coord_t f1 = vp1.angle((boundary[(p1 + 1) % n] - boundary[p1]).normalize());
		coord_t f2 = vp2.angle((boundary[(p2 + 1) % n] - boundary[p2]).normalize());
		coord_t f3 = vp3.angle((boundary[(p3 + 1) % n] - boundary[p3]).normalize());
		coord_t f4 = vp4.angle((boundary[(p4 + 1) % n] - boundary[p4]).normalize());

		// step 5: find the minmum angle
		coord_t min_f = min(min(min(f1, f2), f3), f4);
	
		// step 6: rotate all of the calipers by that minimum angle
		vp1.rotate(min_f, false);
		vp2.rotate(min_f, false);
		vp3.rotate(min_f, false);
		vp4.rotate(min_f, false);

		// step 7: update minimum bounding box area
		update_area(boundary, p1, p2, p3, p4, vp1, vp2, vp3, vp4, min_area);

		// step 8: advance calipers
		if (deg(abs(f1 - min_f)) <= e) p1 = (p1 + 1) % n;
		if (deg(abs(f2 - min_f)) <= e) p2 = (p2 + 1) % n;
		if (deg(abs(f3 - min_f)) <= e) p3 = (p3 + 1) % n;
		if (deg(abs(f4 - min_f)) <= e) p4 = (p4 + 1) % n;
	}

	return min_area * scale_factor*scale_factor; // area of OMBB
}

void utility(const Point2D& A, const Point2D& B, const Point2D& C, coord_t& h_tmp, coord_t& len) {
	Point2D BA = A - B;
	Point2D BC = C - B;
	Point2D AB = B - A;
	Point2D AC = C - A;
	coord_t d = (AB ^ AC) / BA.length();
	h_tmp = abs(d);

	len = 0;
	coord_t dot1 = AB * BC;
	if (dot1 > 0) {
		len = dot1 / AB.length();
		return;
	}
	coord_t dot2 = BA * AC;
	if (dot2 > 0) {
		len = -(dot2 / AB.length());
		return;
	}
}


// brute force: O(n^2)
coord_t mbr(vector<Point2D>& boundary) {
	int n = boundary.size();
	coord_t area_opt = numeric_limits<double>::infinity();
	for (int i = 0; i < n; i++) {
		Point2D a = boundary[i];
		Point2D b = boundary[(i + 1) % n];
		coord_t h = 0, l = 0, r = 0;
		for (int j = 0; j < n; j++) {
			Point2D put = boundary[j];
			coord_t len, h_tmp;
			utility(a, b, put, h_tmp, len);
			if (h_tmp > h) h = h_tmp;
			if (len > r) r = len;
			if (len < l) l = len;
		}
		coord_t area = ((a - b).length() + r - l) * h;
		if (area < area_opt) area_opt = area;
	}
	return area_opt;
}
