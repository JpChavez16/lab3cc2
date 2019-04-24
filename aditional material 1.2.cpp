#include <iostream>

using namespace std;

class CDummy
{
	public:
	    static int n;
	    CDummy(){ ++n; }
	    ~CDummy(){ --n; }
};

int CDummy ::n=0;

int main()
{
	CDummy a;
	CDummy b[5];
	CDummy* c=new CDummy;
	cout<<a.n<<"\n";//prints out 7
	delete c;
	cout<<CDummy::n<<"\n";//prints out 6
	return 0;
}