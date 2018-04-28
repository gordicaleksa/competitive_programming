// coordinate type
typedef double coord_t;  
double M_PI = 3.14159265358979323846; 

// convert int to string
string itos(int i) {
	stringstream s;
	s << i;
	return s.str();
}

// custom hashing function so I can use Point2D in unordered_set/map
namespace std {
	template<>
	struct hash<Point2D> {
		size_t operator()(const Point2D & p) const {
			string id = "x" + itos(p.x) + "y" + itos(p.y);
			return hash<std::string>()(id);
		}
	};
}     

class Point2D {	
public:
	// 0. members
	
	// This is against OOP but it's great for TopCoder-like problems
	coord_t x, y;
	
	// 1. constructors

	// default constructor
	Point2D() {
		this->x = 0;
		this->y = 0;
	}
	// cartesian coordinates constructor
	Point2D(coord_t x, coord_t y) {
		this->x = x;
		this->y = y;
	}
	
	// 2. public functions
	
	// calculate angle between 2 points/vectors using linear algebra (v1)dot(v2)=|v1|*|v2|*cos(angle)
	double angle(const Point2D& p) const {
		coord_t dot = ((*this)*p);
		coord_t v1 = (*this).length();
		coord_t v2 = p.length();
		return acos(dot / (v1*v2));
	}
	// rotate this vector by theta in ccw direction
	Point2D& rotate(double angle, bool is_degree) {
		if (is_degree) angle *= M_PI / 180.0; // convert to radians

		coord_t x_r = x * cos(angle) - y * sin(angle);
		coord_t y_r = x * sin(angle) + y * cos(angle);

		// modify this vector
		x = x_r;
		y = y_r;

		// return reference to it
		return *this;
	}
	// euclidian distance from origin
	double length() {
		return sqrt(x*x + y * y); 
	}
	// make this vector unit vector
	Point2D& normalize() {
		return (*this) / (*this).length();
	}
	
	// 3. operator overloading

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