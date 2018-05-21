#include "expand01.h"
#include<iostream>
using namespace std;
int main()
{
	auto x = Placeholder();
	auto t = Print(x);
	auto y = Constant(1);
	auto a0 = t + y;
	auto a1 = t + a0;
	auto a2 = t + a1;
	cout<<eval(a2,{{x,1}})<<'\n';
	return 0;
}

