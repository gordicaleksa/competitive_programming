// minimum enclosing circle theory:
// http://www.cs.mcgill.ca/~cs507/projects/1998/jacob/problem.html
// http://www.cs.uu.nl/docs/vakken/ga/slides4b.pdf

// naive implementation, O(n^4) | there exists O(n) algorithm

void update_mec_radius(vector<Point2D>& points, Point2D& m, double& mec_radius) {
	double max = 0;
	for (Point2D& c : points) {
		double tmp = (m - c).length();
		if (tmp > max) {
			max = tmp;
		}
	}
	mec_radius = min(mec_radius, max);
}
	
coord_t mec_radius(vector<Point2D>& points) {

	coord_t mec_radius = 10e9;
	for (int i = 0; i < points.size(); i++) {
		for (int j = i + 1; j < points.size(); j++) {
			Point2D m = (points[i] + points[j]) / 2;
			update_mec_radius(points, m, mec_radius);
			for (int k = j + 1; k < points.size(); k++) {
				bool collinear = false;
				Point2D c = circle_center(points[i], points[j], points[k], collinear);
				if (!collinear)
					update_mec_radius(points, c, mec_radius);
			}
		}
	}
	return mec_radius;
}