#include "base.h"
#include "expand01.h"
#include<iostream>
using namespace std;

int main()
{
	auto para=Parameter();
	para.set(1);
	cout<<eval(para)<<'\n';
	para.add(2);
	cout<<eval(para)<<'\n';
	para.sub(4);
	cout<<eval(para)<<'\n';
	para.mul(8);
	cout<<eval(para)<<'\n';
	para.div(16);
	cout<<eval(para)<<'\n';
	auto ans=para*5.f;
	cout<<eval(ans)<<'\n';
	return 0;
}
