#include "base.h"
#include "expand01.h"
#include<iostream>
using namespace std;

int main()
{
	auto x = Placeholder();
	auto y = Placeholder();
	auto z = Placeholder();
	auto t = Print(x + y,"Print: t=");
	auto res = t + z;
	cout<<eval(res,{{x,1}, {y,3}, {z,2}})<<'\n';
	cout<<eval(res,{{x,1}, {y,2}, {z,3}})<<'\n';
	return 0;
}
