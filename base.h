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
};
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
	static int time_stamp;
	static int node_count;
	int vtime;
	float val;
public:
	virtual float _eval(const InputList &il)=0;
	friend float eval(Node &node,const InputList &il);
	Node(){node_count++;cerr<<"Node created at "<<this<<'\n';}
	Node(const Node &){node_count++;cerr<<"Node created at "<<this<<'\n';}
	Node(Node &&){node_count++;cerr<<"Node created at "<<this<<'\n';}
	virtual ~Node(){node_count--;cerr<<"Node destroyed at "<<this<<" node_count="<<node_count<<'\n';}
};
int Node::time_stamp=0;
int Node::node_count=0;

class Constant:public Node
{
	const float cval;
	float _eval(const InputList &il)override
	{
		return cval;
	}
public:
	Constant(float c):cval(c){};
};

unordered_map<Node*,int> ref_count;
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
class Nodeptr
{
public:
	Node *p;
	template<class T>Nodeptr(T &t):p(&t){}
	template<class T>Nodeptr(T &&t):p(new T(t)){ref_count[p]=1;}
	~Nodeptr(){check_free(p);}
	
};
template<> Nodeptr::Nodeptr<float>(float &&t):p(new Constant(t)){ref_count[p]=1;}
template<> Nodeptr::Nodeptr<float>(float &t):p(new Constant(t)){ref_count[p]=1;}


class Placeholder:public Node
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
	Placeholder(const Placeholder &)=delete;
	Placeholder(Placeholder &&)=default;
};
float eval(Node &node,const InputList &il)
{
	Node::time_stamp++;
	return node._eval(il);
}
class Node_Uni:public Node
{
protected:
	Node *op1;
	int evtime;
	float tval;
	float _eval(const InputList &il)=0;
public:
	Node_Uni(const Nodeptr &_op1):op1(_op1.p){check_add(op1);}
	~Node_Uni(){check_free(op1);}
	
};

class Node_Bin:public Node
{
protected:
	Node *op1,*op2;
	int evtime;
	float tval;
	float _eval(const InputList &il)=0;
public:
	Node_Bin(const Nodeptr &_op1,const Nodeptr &_op2):op1(_op1.p),op2(_op2.p){check_add(op1);check_add(op2);}
	~Node_Bin(){check_free(op1);check_free(op2);}
	
};

class Add:public Node_Bin
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
	
