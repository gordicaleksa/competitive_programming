// coordinate type
typedef double coord_t;        

class Point2D {	
public:
	// This is against OOP but it's great for TopCoder-like problems
	coord_t x, y;
	
	// Constructors
	Point2D() {
		this->x = 0;
		this->y = 0;
	}
	Point2D(coord_t x, coord_t y) {
		this->x = x;
		this->y = y;
	}
	
	// euclidian distance from origin
	double length() {
		return sqrt(x*x + y * y); 
	}

	// vector addition
	Point2D operator +(const Point2D& p) const {
		return Point2D(x + p.x, y + p.y);
	}
	// vector subtraction
	Point2D operator -(const Point2D& p) const {
		return Point2D(x - p.x, y - p.y);
	}
	// vector scaling
	Point2D& operator /(double s) {
		if (s != 0) {
			x /= s;
			y /= s;
		}
		return *this;
	}
	// dot product
	coord_t operator *(const Point2D& p) const {
		return x * p.x + y * p.y;
	}
	// cross product signed intensity
	coord_t operator ^(const Point2D& p) const {
		return x * p.y - y * p.x;
	}
	// compare 2 points
	bool operator <(const Point2D& p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
	// compare equality
	bool operator ==(const Point2D& p) const {
		return x == p.x && y == p.y;
	}
	// compare inequality
	bool operator !=(const Point2D& p) const {
		return x != p.x || y != p.y;
	}
	// prints out this point/vector in format (x,y)
	friend ostream& operator<<(ostream& strm, const Point2D& p) {
		return strm << "(" << p.x << "," << p.y << ")";
	}
};