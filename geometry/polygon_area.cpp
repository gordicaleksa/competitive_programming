#include <cmath>

typedef double coord_t;         // coordinate type

struct Point {
	coord_t x, y;

	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

// just pass the points without replicating the first one
// it is important that points are ordered either cw or ccw
// shoelace formula, time complexity: O(n)
coord_t polygon_area(vector<Point>& vertices) {
	
	int n = vertices.size();
	coord_t area = 0;

	// Calculate value of shoelace formula
	int j = n - 1;
	for (int i = 0; i < n; i++)
	{
		area += (vertices[j].x + vertices[i].x) * (vertices[j].y - vertices[i].y);
		j = i;  // j is previous vertex to i
	}

	// Return absolute value
	return abs(area / (coord_t)2);
}

// it is important that points are ordered either cw or ccw
// triangulation, time complexity: O(n) it's less efficient than the upper definition
coord_t polygon_area(vector<Point>& vertices) {

	int n = vertices.size();
	coord_t area = 0;

	for (int i = 1; i < n - 1; i++) {
		// first vector
		coord_t x1 = vertices[i].x - vertices[0].x;
		coord_t y1 = vertices[i].y - vertices[0].y;
		// second vector
		coord_t x2 = vertices[i + 1].x - vertices[0].x;
		coord_t y2 = vertices[i + 1].y - vertices[0].y;
		coord_t cross = x1 * y2 - x2 * y1;
		area += cross; // signed cross product
	}
	// divide by two because we were taking areas of paralelograms
	// abs because points may come in cw or ccw order
	return abs(area / (coord_t)2);
}