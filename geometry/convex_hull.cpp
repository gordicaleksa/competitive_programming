// Implementation of Andrew's monotone chain 2D convex hull algorithm.
// Asymptotic complexity: O(n log n).
// Practical performance: 0.5-1.0 seconds for n=1000000 on a 1GHz machine.


// 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
// Returns a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
coord_t cross(const Point2D &O, const Point2D &A, const Point2D &B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Returns a list of points on the convex hull in counter-clockwise order.
vector<Point2D> convex_hull(vector<Point2D>& points) // changed to pass as reference
{
	size_t n = points.size(), k = 0;
	if (n <= 3) return points;
	vector<Point2D> H(2 * n);

	// Sort points lexicographically
	sort(points.begin(), points.end());

	// Build lower hull
	for (size_t i = 0; i < n; ++i) {
		while (k >= 2 && cross(H[k - 2], H[k - 1], points[i]) <= 0) k--;
		H[k++] = points[i];
	}

	// Build upper hull
	for (int i = n - 2, t = k + 1; i >= 0; --i) {
		while (k >= t && cross(H[k - 2], H[k - 1], points[i]) <= 0) k--;
		H[k++] = points[i];
	}

	H.resize(k - 1);
	return H;
}