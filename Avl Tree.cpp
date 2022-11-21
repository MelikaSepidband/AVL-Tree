#include <iostream>
using namespace std;
class node{
	public:
	double data;
	int height;
	node* leftchild;
	node* rightchild;
};
class AVL{
public:
	AVL();
	~AVL();
	node* r;    // root node
	bool add(double d);
	node* addnode(node* n,double d);
	bool remove(double d);
	node* removenode(node* n,double d);
	node* leftleft(node *n);
	node* rightright(node *n);
	node* balancing(node *n);
	int height(node *n);
	int balance(node *n);
	bool find(double d);
	node *findnode(node* n,double d);
	node *maxleft(node* n);
	void printdouble(double d);
};
AVL::AVL() {
	r=NULL;
}
AVL::~AVL() {}

int AVL::height(node *n)
{
    if (n == NULL)
        return 0;
    return n->height;
}
int AVL::balance(node *n)
{
	if (n==NULL)
		return 0;
	return (height(n->leftchild) - height(n->rightchild));
}
node *AVL::rightright(node* n)
{
	node *n1=n->leftchild;
	n->leftchild=n1->rightchild;
	n1->rightchild=n;
	n->height=max(height(n->rightchild),height(n->leftchild))+1;
	n1->height=max(height(n1->rightchild),height(n1->leftchild))+1;
	return n1;
}
node *AVL::leftleft(node *n)
{
	node *n1=n->rightchild;
	n->rightchild=n1->leftchild;
	n1->leftchild=n;
	n->height=max(height(n->rightchild),height(n->leftchild))+1;
	n1->height=max(height(n1->rightchild),height(n1->leftchild))+1;
	return n1;
}
node *AVL::balancing(node *n)
{
	n->height=max(height(n->leftchild),height(n->rightchild))+1;
	if(balance(n)>1)
	{
		cout<<"balancing ";
		printdouble(n->data);
		if(balance(n->leftchild)<0) //leftright
		{
			n->leftchild=leftleft(n->leftchild);
			n=rightright(n);
		}
		else //right
		n=rightright(n);
	}
	else if(balance(n)<-1)
	{
		cout<<"balancing ";
		printdouble(n->data);
		if(balance(n->rightchild)>0) //rightleft
		{
			n->rightchild=rightright(n->rightchild);
			n=leftleft(n);
		}
		else //left
		n=leftleft(n);
	}
	return n;
}
node *AVL::maxleft(node *n)
{
	node *m=n->leftchild;
	while((m->rightchild)!=NULL)
	m=m->rightchild;
	return m;
}
node* AVL::addnode(node* n, double d) {
	if(n==NULL)
	{
		n= new node();
		n->data = d;
		n->height =1;
		n->leftchild = NULL;
		n->rightchild = NULL;
		cout<<"added"<<endl;
	}
	else
	{
		if((n->data)>d)
		{
			n->leftchild = addnode(n->leftchild, d);
		}
		else if((n->data)<d)
		{
			n->rightchild= addnode(n->rightchild, d);
		}
		else if((n->data)==d)
		{
			cout<<"already in there"<<endl;
		}
	}
	n=balancing(n);
	return n;
}
bool AVL::add(double d) {
	r=addnode(r,d);
	return true;
}
node* AVL::removenode(node *n,double d)
{
	if(n==NULL)
	{
		cout <<"does not exist"<< endl;
		return n;
	}
	if((n->data)>d)
	{
		n->leftchild=removenode(n->leftchild,d);
	}
	else if((n->data)<d)
	{
		n->rightchild=removenode(n->rightchild,d);
	}
	else if((n->data)==d)
	{
		if(n->leftchild==NULL)
		{
			if(n->rightchild==NULL)
			{
				delete n;
				n=NULL;
				cout<<"removed"<<endl;
			}
			else
			{
				*n=*n->rightchild;
				delete n->rightchild;
				cout<<"removed"<<endl;
			}
		}
		else
		{
			if(n->rightchild==NULL)
			{
				*n=*n->leftchild;
				delete n->leftchild;
				cout<<"removed"<<endl;
			}
			else
			{
				node *t1=maxleft(n);
				n->data=t1->data;
				n->leftchild=removenode(n->leftchild,t1->data);
			}
		}
	}
	if(n==NULL)
	return n;
	n=balancing(n);
	return n;
}
bool AVL::remove(double d) {
	r=removenode(r,d);
	return true;
}
node *k=NULL;
node* AVL::findnode(node *n,double d)
{
	if(n==NULL)
	{
		if(k==NULL)
		cout<<"not found"<<endl;
		else
		{
			printdouble(k->data);
			k=NULL;
		}
	}
	else
	{
	if((n->data)==d)
	printdouble(d);
	else if((n->data)>d)
	{
		k=n;
		n->leftchild=findnode(n->leftchild,d);
	}
	else if((n->data)<d)
	{
		n->rightchild=findnode(n->rightchild,d);
	}
	}
return n;
}
bool AVL::find(double d)
{
	r=findnode(r,d);
	return true;
}
void AVL::printdouble(double d)
{
    if ((int)d == d) 
    cout<<d<<".0"<<endl;
    else
    cout<<d<<endl;
}
int main()
{
	int queries;
	cin>>queries;
	string command;
	node* n=NULL;
	AVL tree;
	double value;
	for(int i=0;i<queries;i++)
	{
		cin>>command;
		cin>>value;
		if(command=="add")
		{
			tree.add(value);
		}
		else if(command=="remove")
		{
			tree.remove(value);
		}
		else if(command=="find")
		{
			tree.find(value);
		}
	}
}
