#include <string >
#include <iostream>

using namespace std;

int main()
{
string s = "Hello ";
s += " world!";
if(s == "Hello world!") 
{
 cout << "Success!" << endl;
 }
 cout << s.substr(6, 6) << endl; // 
 cout << s.find("world ")<<endl; //  
 cout << s.find('l', 5); // 
 }