#include "expand01.h"
#include<fstream>
#include<ctime>
#include<cstdlib>
using namespace std;
Node *a[1000001];
int main()
{
	int i,j,k;
	srand(time(0));
	a[1]=new Constant(1);
	a[2]=new Constant(2);
	for(i=3;i<=1000000;i++)a[i]=new Add(*a[i-2],*a[i-1]);
	cout<<eval(*a[100])<<'\n';
	for(i=1000000;i>=1;i--)delete a[i];
	return 0;
}
			
