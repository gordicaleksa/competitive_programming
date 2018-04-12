// this can be extended to matrices

// rotates point A 'angle' degrees/radians (depending on is_degree flag) around point O and returns that new point
Point2D rotate(const Point2D& O, const Point2D& A, double angle, bool is_degree) {
	if (is_degree) angle *= PI / 180.0; // convert to radians
										// shift coordinate system
	coord_t x = A.x - O.x;
	coord_t y = A.y - O.y;
	// rotate
	coord_t x_r = x * cos(angle) - y * sin(angle);
	coord_t y_r = x * sin(angle) + y * cos(angle);
	// shift again
	x_r += O.x;
	y_r += O.y;
	return Point2D(x_r, y_r);
}
