#ifndef BASE_H
#define BASE_H
#include<iostream>
#include<string>
#include<sstream>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<map>
#include<memory>
using namespace std;
class Placeholder;
class PH_Hash
{
public:
	Placeholder *val;
	PH_Hash(Placeholder &ph):val(&ph){};
	int operator ==(const PH_Hash &b)const{return val==b.val;}
};//把引用转成指针，这样在传InputList的时候就不用手动加&
class Hash
{
	hash<Placeholder*> ph_hash;
public:
	long long operator ()(const PH_Hash &phh)const
	{
		return ph_hash(phh.val);
	}
};
typedef unordered_map<PH_Hash,float,Hash> InputList;

class Node
{
	
protected:
	static int time_stamp;//当前时间戳，用于表示当前是哪一次计算
	static int node_count;//对节点进行计数，调试用
	int evtime=0;//求值的时间，和当前时间进行比较可以得知计算出的值是否过期
	float val;//保存计算出的值以便多次使用
public:
	virtual float _eval(const InputList &il)=0;//内部的求值函数，应避免主程序中直接调用
	friend float eval(Node &node,const InputList &il);//用来在主程序中调用的求值函数
	Node(){/*node_count++;cerr<<"Node created at "<<this<<'\n';*/}
	Node(const Node &){/*node_count++;cerr<<"Node created at "<<this<<'\n';*/}
	Node(Node &&){/*node_count++;cerr<<"Node created at "<<this<<'\n';*/}
	virtual ~Node(){/*node_count--;cerr<<"Node destroyed at "<<this<<" node_count="<<node_count<<'\n';*/}//构造函数和析构函数，不设成默认的只是为了调试
};
int Node::time_stamp=0;
int Node::node_count=0;

class Constant:public Node//看名字就知道是干什么的
{
	const float cval;
	float _eval(const InputList &il)override
	{
		return cval;
	}
public:
	Constant(float c):cval(c){};
};

unordered_map<Node*,int> ref_count;//鬼畜的仅限内部使用的手写引用计数，不要在主程序中调用它，
void check_free(Node *p)
{
	auto it=ref_count.find(p);
	if(it!=ref_count.end())
	{
		it->second--;
		if(it->second==0){ref_count.erase(it);delete p;}
	}
}
void check_add(Node *p)
{
	auto it=ref_count.find(p);
	if(it!=ref_count.end())it->second++;
}
//鬼畜的仅限内部使用的手写引用计数到此为止
class Nodeptr
{
public:
	Node *p;
	template<class T>Nodeptr(T &t):p(&t){}
	template<class T>Nodeptr(T &&t):p(new T(t)){ref_count[p]=1;}//这里手动分配了空间，所以需要上面写的引用计数来管理什么时候释放
	~Nodeptr(){check_free(p);}
	
};//为了auto x=a+b+c;这样的鬼畜玩意能正常运行而搞的鬼畜东西，作用就是把右值放到一个手动分配的空间，左值保持不变
template<> Nodeptr::Nodeptr<float>(float &&t):p(new Constant(t)){ref_count[p]=1;}//为了不显式定义Constant，直接使用float常量而搞的东西
template<> Nodeptr::Nodeptr<float>(float &t):p(new Constant(t)){ref_count[p]=1;}//为了不显式定义Constant，直接使用float变量中的值而搞的东西


class Placeholder:public Node//看名字就知道是什么东西
{
	string name;
	float _eval(const InputList &il)override
	{
		auto it=il.find(*this);
		if(it!=il.end()){ return it->second;} else
		{
			cerr<<"Error: Placeholder "<<name<<" was used unassigned.\n";
			exit(1);
		}
	}
public:
	Placeholder(const string &nm=""):name(nm){/*cerr<<"Placeholder created at "<<this<<'\n';*/};
	Placeholder(const Placeholder &)=delete;//因为Placeholder之间的区分是用地址，所以如果把一个Placeholder复制了一份就可能会出现别的结点引用的是这个而灌入的数值给了另一个的现象
	Placeholder(Placeholder &&)=default;//居然要显式声明使用默认的移动构造函数，否则就不生成移动构造函数
};
float eval(Node &node,const InputList &il={})//用来给主程序调用的eval函数
{
	Node::time_stamp++;
	return node._eval(il);
}
class Node_Uni:public Node//一元运算符
{
protected:
	Node *op1;
	int evtime=0;
	float tval;
	float _eval(const InputList &il)=0;
public:
	Node_Uni(const Nodeptr &_op1):op1(_op1.p){check_add(op1);}
	~Node_Uni(){check_free(op1);}
	
};

class Node_Bin:public Node//二元运算符
{
protected:
	Node *op1,*op2;
	int evtime=0;
	float tval;
	float _eval(const InputList &il)=0;
public:
	Node_Bin(const Nodeptr &_op1,const Nodeptr &_op2):op1(_op1.p),op2(_op2.p){check_add(op1);check_add(op2);}
	~Node_Bin(){check_free(op1);check_free(op2);}
	
};

class Add:public Node_Bin//看名字就知道是啥了
{
	float _eval(const InputList &il)override
	{
		if(evtime==Node::time_stamp)return tval;else
		{
			float t1=op1->_eval(il),t2=op2->_eval(il);
			evtime=Node::time_stamp;
			tval=t1+t2;
			return tval;
		}
	}
public:
	Add(const Nodeptr &_op1,const Nodeptr &_op2):Node_Bin(_op1,_op2){}
};
Add operator + (const Nodeptr &op1,const Nodeptr &op2){return Add(op1,op2);}
#endif
	
