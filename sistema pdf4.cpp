#include <iostream>
#include <math.h>
using namespace std;

class Point{
		int x,y;
	public:
		Point(int xx=0,int yy=0): x(xx), y(yy){}
		int getX()const{
			return x;
		}
		int getY()const{
			return y;
		}
		void setX(int xx){
			xx=x;
		}
		void setY(int yy){
			yy=y;
		}
};

class PointArray{
	    int size;
	    Point *points;

	    void resize(int size);
	}
	public:
		PointArray();
		PointArray(const Point pts[], const int size);
	        PointArray( const PointArray &pv);
		~PointArray();
	        void clear();
	        int getSize() const { return size;}
	        void push_back( const Point &p);
                void insert( const int pos, const Point &p);
                void remove( const int pos);
                Point *get( const int pos);
                const Point *get( const int pos) const ;
};

 PointArray::PointArray() 
 {
     size = 0;
     points = new Point[0]; // Allows deleting later
 }

 PointArray::PointArray( const Point ptsToCopy[], const int toCopySize
){
  size = toCopySize;
  points = new Point[toCopySize];
  for(int i = 0; i < toCopySize; ++i) 
  {
      points[i] = ptsToCopy[i];
  }
 }

 PointArray::PointArray( const PointArray &other) 
 {
   // Any code in the PointArray class has access to
   // private variables like size and points
   size = other.size;
   points = new Point[size];
   for (int i=0; i<size; i++) 
   {
   points[i] = other.points[i];
   }
 }

 PointArray::~PointArray() 
 {
   delete [] points;
 }

 void PointArray::resize( int newSize) 
 {
    Point *pts = new Point[newSize];
    int minSize = (newSize > size ? size : newSize);
    for (int i = 0; i < minSize; i++)
    pts[i] = points[i];
    delete [] points;
    size = newSize;
    points = pts;
 }

 void PointArray::clear() {
    resize(0);
 }


 void PointArray::push_back( const Point &p) 
 {
    resize(size + 1);
    points[size -1] = p;
    // Could also just use insert(size, p);
 }

 void PointArray::insert( const int pos, const Point &p) 
 {
    resize(size + 1);

    for (int i= size -1; i>pos; i--) 
    {
        points[i] = points[i -1];
    }

    points[pos] = p;
 }

 void PointArray::remove( const int pos) 
 {
    if(pos >= 0 && pos < size) 
    { // pos < size implies size > 0
    // Shift everything over to the left
        for(int i = pos; i < size -2; i++) 
        {
            points[i] = points[i + 1];
        }
        resize(size -1);
    }
 }

 Point *PointArray::get( const int pos) 
 {
     return pos >= 0 && pos < size ? points + pos : NULL;
 }

 const Point *PointArray::get( const int pos) const 
 {
    return pos >= 0 && pos < size ? points + pos : NULL;
 }

class Polygon{
	protected :
		static int numPolygons ;
		PointArray points ;
	public :
		Polygon ( const PointArray &pa) : points(pa){
			numPolygons++;
		}
		Polygon ( const Point pointArr [], const int numPoints ) : points(pointArr, numPoints){
			numPolygons++;
		}
		virtual double area () const = 0;
		static int getNumPolygons (){ 
			return	numPolygons ;
		}
		int getNumSides ()const{ 
			return points . getSize ();
		}
		const PointArray * getPoints () const{ 
			return	&points ;
		}
		~ Polygon (){
			--numPolygons;
		}
};
int Polygon::numPolygons = 0;
Point constructorPoints[4];
Point *updateConstructorPoints( const Point &p1, const Point &p2,const Point &p3, const Point &p4 = Point(0,0)) {
	constructorPoints[0] = p1;
	constructorPoints[1] = p2;
	constructorPoints[2] = p3;
	constructorPoints[3] = p4;
	return constructorPoints;
}
class Rectangle : public Polygon {
	public :
		Rectangle( const Point &ll, const Point &ur): Polygon(updateConstructorPoints(ll, Point(ll.getX(), ur.getY()),ur, Point(ur.getX(), ll.getY())), 4) {}
		double area() const {
			int length = points.get(1) ->getY() -points.get(0) ->getY();
    		int width = points.get(2) ->getX() -points.get(1) ->getX();
    		return abs(( double )length * width);
    	}
};
class Triangle : public Polygon {
	public :
		Triangle( const Point &a, const Point &b, const Point &c): Polygon(updateConstructorPoints(a, b, c), 3) {}
	 	virtual double area() const {
			int 	dx01 = points.get(0) ->getX() -points.get(1) ->getX(),
					dx12 = points.get(1) ->getX() -points.get(2) ->getX(),
					dx20 = points.get(2) ->getX() -points.get(0) ->getX();
			int 	dy01 = points.get(0) ->getY() -points.get(1) ->getY(),
					dy12 = points.get(1) ->getY() -points.get(2) ->getY(),
					dy20 = points.get(2) ->getY() -points.get(0) ->getY();
			double 	a = sqrt(dx01*dx01 + dy01*dy01),
					b = sqrt(dx12*dx12 + dy12*dy12),
					c = sqrt(dx20*dx20 + dy20*dy20);
			double s=(a +b+c) /2;
			return sqrt( s * (s-a) * (s-b) * (s-c) );
		}
};
void printAttributes(Polygon *p) {
	cout << "pâ€™s area is " << p->area() << ".\n";
	cout << "pâ€™s points are:\n";
	const PointArray *pa = p->getPoints();
	for(int i = 0; i < pa ->getSize(); ++i) {
		cout << "(" << pa ->get(i) ->getX() << ", " << pa ->get(i) -> getY() << ")\n";
	}
}
int main(){
	cout << "Enter lower left and upper right coords of rectangle as four space separated integers: ";
	int llx, lly, urx, ury;
	cin >> llx >> lly >> urx >> ury;
	Point ll(llx, lly), ur(urx, ury);
	Rectangle r(ll, ur);
	printAttributes(&r);
	
	cout << "Enter three coords of triangle as six space separated integers: ";
	int x1, y1, x2, y2, x3, y3;
 	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	Point a(x1, y1), b(x2, y2), c(x3, y3);
	Triangle t(a, b, c);
 	printAttributes(&t);
	return 0;
}
