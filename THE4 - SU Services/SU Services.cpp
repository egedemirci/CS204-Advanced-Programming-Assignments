#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "StudentsQueue.h"
#include "TeachersQueue.h"
#include "commonstack.h"
using namespace std;

struct commands { /*Node structure for the commands linked list. */
	string commandName;
	commands *next;
};


struct services {  /*Node structure for the services linked list, it keeps serviceName, next node and head of the commands. */
	string serviceName;
	services *next;
	commands* commandHead;
};

services*servicehead = NULL; /*Global head variable. */

TeachersQueue instructorsQueue(10); /*10 instructors queue. */
StudentsQueue studentsQueue; /*Queue for student's operations. */
CommonStack sharedstack; /*Shared stack for operations. */
CommonStack copystack; /*to keep the stack the same.*/

/*This function search service, it took serviceName and if it founds the serviceName it returns the node. */
services* searchService(services*head,string servicename){
	services*ptr = head; /*dummy pointer to head. */
	while (ptr!=NULL){ 
		if (ptr->serviceName == servicename){
			return ptr; /*if there is a match return the node. */
		}
		ptr = ptr->next; /*go next until null. */
	}
	return NULL; /*there is no match so return null. */
}

/*This function adds new service to services linked list. */
services* addServices(services*newNode, services*head){
	services*temp = head; /*dummy pointer to head. */
	if (head == NULL){ /*If head is NULL, the new element will be the new head. */
		head = newNode; 
		newNode->next = NULL; /*Next element of it will be NULL. */
		return head; /*return new head. */
	}
	else{
		while ( temp->next != NULL){
			temp = temp->next; /*When temp->next became null, it means pointer reached to last element before the end of the list which will be the place of the new element. */
		}
	}
	temp->next = newNode; /*The next of the last element before null became new node.*/
	newNode->next = NULL; /* newNode's next is NULL. */
	return head; /*return head. */
}

/*This function adds new commands to command linked list. */

commands*addCommands(commands*newNode, commands*commandHead){
	commands*temp = commandHead; /*dummy pointer to head. */
	if (commandHead == NULL){ /*Special case if head is null, new element will be head. */
		commandHead = newNode; /*new element became head. */
		newNode-> next = NULL;
		return newNode; /*return head.*/
	}
	else{
		while ( temp->next != NULL){ /*If head is not null, the new element will be placed at the end. */ 
			temp = temp->next;  /*Same as above. */
		}
	}
	temp->next = newNode; /*The next of the last element before null became new node.*/
	newNode->next = NULL; /*Since temp is null, newNode's next is temp. */
	return commandHead; /*return head. */
}

/*This function takes the input file and services, and processes it. It returns the head of the services. */
services*fileProcess(ifstream &input, services*servicehead){
	string info,command,functionname; /*info is the dummy variable for file process. */
	bool foundcommand = false, foundfunc = false; /*bool condtions for commands and functions. */
	while(getline(input,info)){
		if (info.at(0) == 'f'){ /*if the first element is f it means we have function. */
			functionname = info.substr(0,info.length()-1); /*functionname will be the line we are working on but we won't take the last element since it is ;. */
			foundfunc = true; /*New function name so found func true. */
		}
		else{ /*If the first element of string is not f, it means we have command. */
			command = info.substr(0,info.length()-1); /*command will be the line we are working on but we won't take the last element. */
			foundcommand = true; /*New command so foundcommand true. */
		} 
		if(foundfunc == true && searchService(servicehead,functionname) == NULL){ /*If we have a function but it's not a part of the services linked list, we will add it. */
			services*newService = new services; 
			newService->serviceName = functionname;
			newService->commandHead = NULL;
			servicehead = addServices(newService,servicehead); /*add with addServices function but keep head. */
		}
		if(foundcommand == true){ /*If we have a command and function, we will add a command to function we are working on. */
			commands*newCommand = new commands;
			newCommand->commandName = command;
			services*ptr = searchService(servicehead,functionname); /*The command must be added to the node of the corresponding function.*/
			ptr->commandHead = addCommands(newCommand,ptr->commandHead); /*keep the head. */
		}
		foundcommand = false; /*for the next iterations.*/
		foundfunc = false;
	}
	return servicehead; /*return head.*/
}


/*This functions prints the info of linked list structure. */
void printInfo(services*servicehead){
	cout << "-------------------------------------------------------------------" << endl;
	cout << "PRINTING AVAILABLE SERVICES <FUNCTIONS> TO BE CHOSEN FROM THE USERS" << endl;
	cout << "-------------------------------------------------------------------" << endl << endl << endl;
	services*temp = servicehead; /*dummy pointer to head.*/
	while ( temp != NULL){
		cout << temp->serviceName << ":" << endl;
		commands*head = temp->commandHead;
		while(head->next != NULL){ /*print the info until null. */
			cout << head->commandName << ", ";
			head = head->next;
		}
		cout << head->commandName << ".";
		cout << endl << endl;
		temp = temp->next;
	}

}
/*This function adds insturctor request to the queue*/
void addInstructorRequest(){
	string func_name,instructor_name;
	int id; 
	cout << "Add a service <function> that the instructor wants to use:" << endl;
	cin >> func_name;
	if( searchService(servicehead,func_name) == NULL){ /*If searchService is NULL, function does not exist. */
		cout << "The requested service <function> does not exist." << endl;
		cout << "GOING BACK TO MAIN MENU!" << endl;
	}
	else{
		cout << "Given the instructor's name: ";
		cin >> instructor_name;
		cout << "Give instructor's id <an int>: ";
		cin >> id;
		teacherInfo addToQueue(func_name,instructor_name,id); /*This element will be added to queue. */
		instructorsQueue.enqueue(addToQueue); /*enqueue the element. */
		cout << "Prof. " << instructor_name << " service request of " << func_name;
		cout << " has been put in the instructor's queue. " << endl;
		cout << "Waiting to be served..." ;
	}
}


/*Same function as above but for the students. */
void addStudentRequest(){
	string func_name,student_name;
	int id;
	cout << "Add a service <function> that the student wants to use:" << endl;
	cin >> func_name;
	if( searchService(servicehead,func_name) == NULL){
		cout << "The requested service <function> does not exist." << endl;
		cout << "GOING BACK TO MAIN MENU!" << endl;
	}
	else{
		cout << "Given the student's name: ";
		cin >> student_name;
		cout << "Give student's id <an int>: ";
		cin >> id;
		studentInfo addToQueue(func_name,student_name,id);
		studentsQueue.enqueue(addToQueue);
		cout << student_name << "'s service request of " << func_name;
		cout << " has been put in the student's queue. " << endl;
		cout << "Waiting to be served..." ;
	}
}

/*This function is for the main menu, it processes the request. */
void processARequest(string functionName)
{
	services* ptr = searchService(servicehead,functionName); /*Take the corresponding node of the function. */
	commands *  temp = ptr->commandHead; /*dummy pointer to head of the commands of the function in services linked list. */
	while(temp != NULL){ 
		if((temp->commandName).substr(0,6) =="define") /*If the command is define, command should be pushed to sharedstack. */
		{
			stackInfo stackInfo(functionName, temp->commandName); /*constructor used. */
			sharedstack.push(stackInfo); 
		}
		else if ((temp->commandName).substr(0,4)=="call") /*If the command is call, function should be called recursively*/
		{
			string funcname = temp->commandName.substr(5,temp->commandName.length()-5); /*substring operation to take function name. */
			cout << "Calling a " << funcname << " from " << functionName << endl;
			processARequest(funcname); /*recursion. */
		}
		else{
			cout << "PRINTING THE STACK TRACE: " << endl;
			if (sharedstack.isEmpty()){
				cout << "The stack is empty. " << endl;
			}
			else{
				stackInfo popped; /*dummy variable for pop. */
				while(sharedstack.isEmpty() == false){ 
					sharedstack.pop(popped); /*to keep the stack same, the elements will be added to copystack after print. */
					copystack.push(popped);
				}
				while(copystack.isEmpty()==false){
					copystack.pop(popped); /*pop from copystack, add to shared stack again structure will be same as beginning. */
					cout << popped.funcname << ": " << popped.command << endl;
					sharedstack.push(popped);
				}
			}
			
		}
		temp = temp->next;
	}
	while(sharedstack.isEmpty() == false){ /*Clean the related function's commands from stack. */
		stackInfo deleted;
		sharedstack.pop(deleted); /*delete all the commands until function changes. */
		if(deleted.funcname != functionName){
			sharedstack.push(deleted);  /*if you delete from the next function, push again. */
			break; /*new function so break the loop. */
		}
	}
	cout<<functionName<<" is finished. Clearing the stack from it's data... "
	<<endl;
	system("pause");
	if(sharedstack.isEmpty()){
		cout << "The stack is empty. " << endl;
	}
}
/*This function is taken from HW file, it controls the process. */
void processARequest(){
	string functionName;
	if (!instructorsQueue.isEmpty()) /*instructors have priority. */
	{
		teacherInfo info;
		instructorsQueue.dequeue(info); /*dequeue the info. */
		functionName = info.function; /*take related function. */
		cout << "Processing instructors queue..." << endl;
		cout << "Processing prof. " << info.name << "'s request <with ID "<< info.id << "> of service <function>:" << endl;
		cout << functionName << endl;
		 //if instructors queue is not empty, process the next request
		processARequest(functionName); /*process a instructor's function. */
		cout<<"GOING BACK TO MAIN MENU"<<endl;
	}
	else if (!studentsQueue.isEmpty()) /*if instructor is empty, students can make operations. */
	{
		studentInfo sinfo;
		studentsQueue.dequeue(sinfo); /*dequeue the info. */
		functionName = sinfo.function;
		cout << "Instructor queue is empty. Processing students queue..." << endl;
		cout << "Processing " << sinfo.name << "'s request <with ID "<< sinfo.id << "> of service <function>:" << endl;
		cout << functionName << endl;
		//if instructors queue is empty and student’s not,
		 //then process the next student request
		processARequest(functionName); /*process a student's function. */
		cout<<"GOING BACK TO MAIN MENU"<<endl;
	}
	else{
		// otherwise…
		cout<<"Both instructor's and student's queue is empty.\nNo request is processed."<<endl<<"GOING BACK TO MAIN MENU"<<endl;
	}
}

/*This function deletes the commands. */
void deleteAlltheCommands(services*ptr){ 
	commands*commandsDeleted = ptr->commandHead;
	while ( ptr->commandHead != NULL){
		ptr->commandHead = ptr->commandHead->next;
		delete commandsDeleted;
		commandsDeleted = NULL;
		commandsDeleted = ptr->commandHead;
	}
}

/*This function deletes the linkedList structure, it uses deleteAlltheCommands for delete process of commands.*/
void deleteAll(services*servicehead){
	services*ptr = servicehead;
	while(ptr != NULL){
		servicehead = servicehead->next;
		deleteAlltheCommands(ptr);
		delete ptr;
		ptr = NULL;
		ptr = servicehead;
	}
}


int main(){
	string option,filename;
	cout << "If you want to open a service <function> defining file " << endl;
	cout << "then press <Y/y> for 'yes', otherwise press any single key." << endl;
	cin>> option; /*option for the first question. */
	if (option != "y" && option != "Y"){
		exit(0);
	}
	while (option == "y" || option == "Y"){ /*take input while option is yes. */
		cout  << "Enter the input file name: ";
		cin >> filename;
		ifstream input;
		input.open(filename.c_str());
		if(input.fail() == true){
			cout << "File cannot be opened!"; /*if file cannot be opened, terminate the program. */
			exit(0);
		}
		else{
			servicehead = fileProcess(input,servicehead); /*If file is opened, process it and keep the head. */
			cout << "Do you want to open another service defining file?: " << endl;
			cout << "Press <Y/y> for 'yes', otherwise press any key." << endl;
			cin >>option; /*ask for another file. */
		}
	}
	printInfo(servicehead); /*print the information. */
	while (true){
		cout << endl;
		cout<<"**********************************************************************"<<endl
		<<"**************** 0 - EXIT PROGRAM *************"<<endl
		<<"**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST *************"<<endl
		<<"**************** 2 - ADD A STUDENT SERVICE REQUEST *************"<<endl
		<<"**************** 3 - SERVE (PROCESS) A REQUEST *************"<<endl
		<<"**********************************************************************"<<endl;
		cout << endl;
		int option;
		cout << "Pick an option from above (int number from 0 to 3): ";
		cin>>option;
		switch (option)
		{
		case 0:
		
			cout<<"PROGRAM EXITING ... "<<endl;
			deleteAll(servicehead); /*free the memory*/
			system("pause");
			exit(0);
		case 1:
			addInstructorRequest();
			break;
		case 2:
			addStudentRequest();
			break;
		case 3:
			processARequest();
			break;
		default:
			cout<<"INVALID OPTION!!! Try again"<<endl;
		}//switch
	}//while (true)
}