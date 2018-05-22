#ifndef EXPAND01_H
#define EXPAND01_H
#include "base.h"
//都是看了名字就知道是什么的东西，也没有什么鬼畜的定义或者实现，就不给注释了
class Sub:public Node_Bin
{
	float _eval(const InputList &il)override
	{
		if(evtime==Node::time_stamp)return tval;else
		{
			float t1=op1->_eval(il),t2=op2->_eval(il);
			evtime=Node::time_stamp;
			tval=t1-t2;
			return tval;
		}
	}
public:
	Sub(const Nodeptr &_op1,const Nodeptr &_op2):Node_Bin(_op1,_op2){}	
};
Sub operator - (const Nodeptr &op1,const Nodeptr &op2){return Sub(op1,op2);}

class Mul:public Node_Bin
{
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
	Mul(const Nodeptr &_op1,const Nodeptr &_op2):Node_Bin(_op1,_op2){}	
};
Mul operator * (const Nodeptr &op1,const Nodeptr &op2){return Mul(op1,op2);}

class Div:public Node_Bin
{
	float _eval(const InputList &il)override
	{
		if(evtime==Node::time_stamp)return tval;else
		{
			float t1=op1->_eval(il),t2=op2->_eval(il);
			evtime=Node::time_stamp;
			if (t2 == 0) cerr<<"Warning: Calculation Div was meaningless.\n";
			tval=t1/t2;
			return tval;
		}
	}
public:
	Div(const Nodeptr &_op1,const Nodeptr &_op2):Node_Bin(_op1,_op2){}	
};
Div operator / (const Nodeptr &op1,const Nodeptr &op2){return Div(op1,op2);}


class Print:public Node_Uni
{
	string message_pre,message_post;
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
		Node_Uni(_op1),message_pre(_m1),message_post(_m2){}
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
	void set(float c){this->pval=c;}
	void add(float c){this->pval+=c;}
	void sub(float c){this->pval-=c;}
	void mul(float c){this->pval*=c;}
	void div(float c){this->pval/=c;}
};
#endif
