#include <iostream>
#include "StudentsQueue.h"
using namespace std;

//************************************************
// Constructor. Generates an empty queue         *
//************************************************
StudentsQueue::StudentsQueue()
{
	front = NULL;
	rear = NULL;   

}
//************************************************
// Destructor. Deletes the queue.         *
//************************************************
StudentsQueue::~StudentsQueue(){ 
	QueueNode*temp = front;
	while(front != NULL){
		temp = front->next;
		delete front;
		front = temp;
	}

}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void StudentsQueue::enqueue(studentInfo info)
{       
	if (isEmpty())   //if the queue is empty
	{	//make it the first element
		front = new QueueNode(info);
		rear = front;
	}
	else  //if the queue is not empty
	{	//add it after rear
		rear->next = new QueueNode(info);
		rear = rear->next;
	} 
}


//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into studentInfo. *
//**********************************************
void StudentsQueue::dequeue(studentInfo &info)
{
	QueueNode *temp;
	if (isEmpty())
	{
		cout << "Attempting to dequeue on empty queue, exiting program...\n";
		exit(1);
	}
	else //if the queue is not empty
	{	//return front's value, advance front and delete old front
		info = front->info;
		temp = front;
		front = front->next;
		delete temp;      
	}
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool StudentsQueue::isEmpty() const
{
	if (front == NULL)
		return true;
	else 
		return false;
}

//********************************************
// Function clear dequeues all the elements  *
// in the queue.                             *
//********************************************
void StudentsQueue::clear()
{
	studentInfo info;   // Dummy variable for dequeue

	while(!isEmpty())
		dequeue(info); //delete all elements
	#ifdef _DEBUG
		cout << "queue cleared\n";
	#endif
}