// coordinate type
typedef double coord_t;  

class Point3D {
private:
	const double PI = 3.141592653589793;
	
	void convert_to_rad(double& x) {
		x = x * (PI / 180.0);
	}
public:
	// Cartesian coordinates
	coord_t x, y, z;

	// Constructors
	Point3D(coord_t x, coord_t y, coord_t z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Point3D(coord_t radius, coord_t latitude, coord_t longitude, bool is_degree) {
		if (is_degree) {
			convert_to_rad(latitude); convert_to_rad(longitude);
		}
		// angle increases from +z axis where it is 0 degrees to 90 degrees when the point is in z = 0 plane to 180 degrees on the -z axis
		double zenith = PI / 2.0 - latitude; 
		x = radius * sin(zenith)*cos(longitude);
		y = radius * sin(zenith)*sin(longitude);
		z = radius * cos(zenith);
	}
	
	// euclidian distance from the origin
	double length() const{
		return sqrt(x * x + y * y + z * z);
	}
	// calculate angle between 2 points using linear algebra (v1)dot(v2)=|v1|*|v2|*cos(angle)
	double angle(const Point3D& p) const {
		coord_t dot = ((*this)*p);
		coord_t v1 = (*this).length();
		coord_t v2 = p.length();		
		return acos(dot / (v1*v2));
	}
	// vector addition
	Point3D operator +(const Point3D& p) const {
		return Point3D(x + p.x, y + p.y, z + p.z);
	}
	// vector subtraction
	Point3D operator -(const Point3D& p) const {
		return Point3D(x - p.x, y - p.y, z - p.z);
	}
	// vector scaling
	Point3D& operator /(double s) {
		if (s != 0) {
			x /= s;
			y /= s;
			z /= s;
		}
		return *this;
	}
	// dot product
	coord_t operator *(const Point3D& p) const {
		return x * p.x + y * p.y + z * p.z;
	}
	// cross product
	Point3D operator ^(const Point3D& p) const {
		return Point3D(y*p.z - p.y*z, p.x*z - x * p.z, x*p.y - p.x*y);
	}
	// compare equality
	bool operator ==(const Point3D& p) const {
		return x == p.x && y == p.y && z == p.z;
	}
	// prints out this point/vector in format (x,y)
	friend ostream& operator<<(ostream& strm, const Point3D& p) {
		return strm << "(" << p.x << "," << p.y << "," << p.z << ")";
	}
};
