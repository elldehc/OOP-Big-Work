#include "base.h"
#include "expand01.h"
#include<iostream>
using namespace std;

int main()
{
	auto x=Placeholder("x");
	auto y=Placeholder();
	auto z=Constant(3);
	auto t=y+z;
	auto res=t+(y*x);
	cout<<eval(res,{{x,1},{y,2}})<<'\n';
	cout<<eval(res,{{x,1},{y,0}})<<'\n';
	cout<<eval(t,{{y,0}})<<'\n';
	cout<<eval(res,{{y,0}})<<'\n';
	return 0;
}
