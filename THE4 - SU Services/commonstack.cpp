#include <iostream>
#include "commonstack.h"
using namespace std;

//************************************************
// Constructor to generate an empty stack.       *
//************************************************
CommonStack::CommonStack()
{
	top = NULL; 
}
//************************************************
// Destructor. Deletes the queue.       *
//************************************************
CommonStack::~CommonStack(){ 
	StackNode*temp = top;
	while(top != NULL){
		temp = top->next;
		delete top;
		top = temp;
	}

}

//************************************************
// Member function push pushes the argument onto *
// the stack.                                    *
//************************************************
void CommonStack::push(stackInfo sinfo)
{
	StackNode *newNode;

	// Allocate a new node & store info.
	newNode = new StackNode;
	newNode->stackinfo = sinfo;

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}
}

//****************************************************
// Member function pop pops the value at the top     *
// of the stack off, and copies it into the variable *
// passed as an argument.                            *
//****************************************************
void CommonStack::pop(stackInfo &sinfo)
{
	StackNode *temp;

	if (isEmpty())
	{
		cout << "The stack is empty.\n";
	}
	else	// pop value off top of stack
	{
		sinfo = top->stackinfo;
		temp = top->next;
		delete top;
		top = temp;
	}
}

//****************************************************
// Member funciton isEmpty returns true if the stack *
// is empty, or false otherwise.                     *
//****************************************************
bool CommonStack::isEmpty(void)
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}

