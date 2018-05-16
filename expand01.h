#ifndef EXPAND01_H
#define EXPAND01_H
#include "base.h"
class Multiply:public Node
{
	Node *op1,*op2;
	int evtime;
	float tval;
	float _eval(const InputList &il)override
	{
		if(evtime==Node::time_stamp)return tval;else
		{
			float t1=op1->_eval(il),t2=op2->_eval(il);
			evtime=Node::time_stamp;
			tval=t1*t2;
			return tval;
		}
	}
public:
	Multiply(const Nodeptr &_op1,const Nodeptr &_op2):op1(_op1.p),op2(_op2.p){check_add(op1);check_add(op2);}
	~Multiply(){check_free(op1);check_free(op2);}
	
};
Multiply operator * (const Nodeptr &op1,const Nodeptr &op2){return Multiply(op1,op2);}
class Print:public Node
{
	Node *op1;
	string message_pre,message_post;
	int evtime;
	float tval;
	float _eval(const InputList &il)override
	{
		if(evtime==Node::time_stamp)return tval;else
		{
			float t=op1->_eval(il);
			evtime=Node::time_stamp;
			tval=t;
			cout<<message_pre<<t<<message_post<<'\n';
			return tval;
		}
	}
public:
	Print(const Nodeptr &_op1,const string &_m1="Print:",const string &_m2=""):
		op1(_op1.p),message_pre(_m1),message_post(_m2){check_add(op1);}
	~Print(){check_free(op1);}
};
class Parameter:public Node
{
	float pval;
	float _eval(const InputList &il)override
	{
		return pval;
	}
public:
	Parameter(float c=0):pval(c){};
	Parameter operator = (float c){this->pval=c;return *this;}
	Parameter operator += (float c){this->pval+=c;return *this;}
	Parameter operator -= (float c){this->pval-=c;return *this;}
	Parameter operator *= (float c){this->pval*=c;return *this;}
	Parameter operator /= (float c){this->pval/=c;return *this;}
};
#endif
