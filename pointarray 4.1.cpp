#include <iostream>
using namespace std;

class PointArray
{
	    int size;
	    Point *points;

	    void resize(int size);

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
}
