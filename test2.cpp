#include "base.h"
#include "expand01.h"
#include<iostream>
using namespace std;

int main()
{
	auto x=Placeholder("x");
	auto y=Placeholder();
	auto z=Constant(3);
	float a=3;
	auto t=y+3.f;
	auto p1=Print(t,"t=");
	auto res=p1*(y+x);
	auto p2=Print(res,"res=");
	cout<<eval(res,{{x,1},{y,2}})<<'\n';
	cout<<eval(p2,{{x,1},{y,0}})<<'\n';
	cout<<eval(p1,{{y,0}})<<'\n';
	auto para=Parameter();
	para=1;
	para+=2;
	para-=4;
	para*=8;
	para/=16;
	auto ans=para*res;
	auto ans2=para*5.f;
	cout<<eval(ans,{{x,1},{y,2}})<<'\n';
	//cout<<eval(res,{{x,0}})<<'\n';
	return 0;
}
