#include <iostream>
using namespace std;

class PointArray
{
	    int size;
	    Point *points;

	    void reslize(int size);

	public:
		PointArray();
		PointArray(const Point pts[], const int size);
		~PointArray();
}