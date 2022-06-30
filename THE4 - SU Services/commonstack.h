#ifndef COMMONSTACK_H
#define COMMONSTACK_H
#include <string>
using namespace std;

struct stackInfo{ /*Struct for the stack info. */
	string funcname;
	string command;
	stackInfo::stackInfo(string f,string c){ /*constructor with parameter. */
		funcname = f;
		command = c;
	}
	stackInfo::stackInfo(){ /*default constructor. */
		funcname = "NULL";
	}
};
struct StackNode /*Struct for the nodes of the dynamic stack. */
{
	stackInfo stackinfo;
	StackNode *next;
	StackNode::StackNode(){
		next = NULL;

	}
};

class CommonStack
{
private:
	StackNode *top;

public:
	CommonStack(void); /*constructor for the class. */
	~CommonStack(); /*destructor. */
	void push(stackInfo stackinfo); /*adds element. */
	void pop(stackInfo & stack); /*deletes element. */
	bool isEmpty(void);
};
#endif