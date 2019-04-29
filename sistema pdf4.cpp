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
		void setX(int x){
			this->x=x;
		}
		void setY(int y){
			this->y=y;
		}
};

class PointArray{
	Point *ptr;
	int size;
	void resize(int newsize){
		Point *temp=new Point[newsize];
		int minsize=(newsize>size)?size:newsize;
		for(int i=0;i<minsize;i++)
			temp[i]=ptr[i];
		delete[] ptr;
		ptr=temp;
		size=newsize;
	}
	public:
		PointArray(){
			size=0;
			ptr=new Point[size];
		}
		PointArray(const Point arr[],const int size){
			ptr=new Point[size];
			for(int i=0;i<size;i++)
				ptr[i]=arr[i];
			this->size=size;
		}
		PointArray(const PointArray &o){
			this->size=o.size;
			ptr=new Point[size];
			for(int i=0;i<size;i++)
				ptr[i]=o.ptr[i];
		}
		~PointArray(){
			delete[] ptr;
		}
		void push_back(Point x){
			resize(size+1);
			ptr[size-1]=x;
		}
		void insert(const int position, const Point &p){
			resize(size+1);
			for(int i=size-1;i>position;i--)
				ptr[i]=ptr[i-1];
			ptr[position]=p;
		}
		void remove(const int position){
			for(int i=position;i<size-1;i++)
				ptr[position]=ptr[position+1];
			resize(size-1);
		}
		int getSize()const{
			return size;
		}
		void clear(){
			resize(0);
		}
		
		Point *get( const int pos) {
 			return pos >= 0 && pos < size ? ptr + pos : NULL;
 		}

 		const Point *get( const int pos) const {
  			return pos >= 0 && pos < size ? ptr + pos : NULL;
  		}
};

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