#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream> 
#include "strutils.h"
using namespace std;

struct courseNode
{
	string courseCode, courseName;
	vector<int> studentsAttendingIDs;
	courseNode * next;
	courseNode::courseNode (){ /* default constructor.*/
		next = NULL;
	}
};
/*This function takes head node and course_name. It searches course_name in linked list and when course_name matches it returns true.*/
bool linkedlistsearch(courseNode*head,string course_code){
	courseNode*ptr = head; /*dummy pointer to head*/
	while (ptr != NULL){
		if (ptr->courseCode == course_code){ 
			return true; /*If there is a match, it returns true.*/
		}
		ptr = ptr->next;
	}
	return false; /*When there is no return, it returns false.*/
}
/*This function takes integer vector and returns the size of it, it will compute number of student in courseNode.*/
int numberofStudents(vector<int> classes){
	return classes.size(); 
}
/*This function sorts the vector which is given.*/
void SortVector(vector<int> & studentIDs){
	int size = studentIDs.size();
	for(int i=0; i < studentIDs.size();i++){
		for (int k=i+1; k<studentIDs.size() ;k++){
			if(studentIDs[i] > studentIDs[k]){ /*If first element is bigger than second, it swaps the elements with the help of temp.*/
				int temp = studentIDs[i];
				studentIDs[i] = studentIDs[k];
				studentIDs[k] = temp; /*swap*/
			}
		}
	}
}
/*This function prints the vector which is given.*/
void printVector(vector<int> studentIDs){
	for (int i=0; i < studentIDs.size();i++){
		cout << studentIDs[i] << " "; /*print elements.*/
	}
}
/*This function displays the list, it uses printVector function for printing the vector, it takes head and shows all the elements.*/
void PrintList(courseNode * head)
{
	courseNode*ptr = head; /*dummy variable for head.*/
	while (ptr != NULL)
	{
		cout << ptr->courseCode << " " << ptr->courseName << ": ";
		printVector(ptr->studentsAttendingIDs);
		cout << endl;
		ptr = ptr->next; /*move to the next pointer until null*/
	}
}

/*This function is similar to first PrintList function but it displays courses which will be closed as an addition.*/
void PrintListForOption4(courseNode * head)
{
	courseNode*ptr = head; 
	while ( ptr != NULL)
	{
		cout << ptr->courseCode;
		int studentnumber = numberofStudents(ptr->studentsAttendingIDs);
		if ( studentnumber < 3){
			cout << " " << ptr->courseName << " ";
			printVector(ptr->studentsAttendingIDs);
			cout << "-> This course will be closed";
		}
		else{
			cout << " " << ptr->courseName << ": ";
			printVector(ptr->studentsAttendingIDs);
		}
		cout << endl;
		ptr = ptr->next;
	}
}

/*This function deletes ID, which is given by the user, from studentAttendingIDs vector, it is important for menu option 2.*/
void deleteInVector(courseNode*head, string course_code,int id){
	courseNode*temp = head;
	int pos;
	while (temp != NULL){
		if (temp->courseCode== course_code){
			for (int i=0; i<temp->studentsAttendingIDs.size(); i++){ /*It will be still sorted when it deleted with the help of this part.*/
				if (temp->studentsAttendingIDs[i] == id){
					pos = i; /*find the index now it will be shifted*/
				}
			}
			for (int k=pos; k < temp->studentsAttendingIDs.size()-1; k++){
				temp->studentsAttendingIDs[k] = temp->studentsAttendingIDs[k+1]; /*shift*/
			}
			temp->studentsAttendingIDs.pop_back();  
			break; /* function doesn't need to continue after this process. */
		}
		temp = temp->next;
	}
}

/*This function searches id in studentAttendingIDs vector. If it finds studentID which is given by the user, it returns true.*/
bool searchInVector(courseNode*head, string courseCode, int id){
	courseNode*temp = head;
	while ( temp != NULL){
		if (temp->courseCode == courseCode){
			for (int i=0; i<temp->studentsAttendingIDs.size(); i++){
				if (temp->studentsAttendingIDs[i] == id){ 
					return true; /*when there is a match, it returns true.*/
				}
			}
		}
		temp = temp->next; /*moves to the next node.*/
	}
	return false;
}

/*This function updates vector. Firstly, it takes head and finds node of course_code which is given by user. After that it adds id to studentAttendingIDs.*/
void updateVector(courseNode*head, string course_code,int id){
	courseNode*temp = head;
	while (temp != NULL){
		if (temp->courseCode== course_code){ /*found a match*/
			if ( searchInVector(head,course_code,id) == false){ /*this line prevents repetitions of id's in classes. */ 
				temp->studentsAttendingIDs.push_back(id);
				SortVector(temp->studentsAttendingIDs); /*sort vector with function. */
			}
		}
		temp = temp->next; /*moves to the next node.*/
	}
}

/*This function adds new node to linked list in a sorted way, it takes head and node which will be added as a parameter. It returns head in the end.*/
courseNode*addSorted(courseNode*newNode, courseNode*head){ 
	courseNode*prev=NULL; /*pointer to previous node*/
	/*if list is empty or newNode's coursename is smaller than first node's coursename, newNode should be new head (taken from lecture slides.)*/
	if (head == NULL || newNode->courseName < head->courseName ){ 
		newNode -> next = head; /*connect the rest.*/
		head = newNode; /*newNode is new head. */
		return head;
	}
	else{
		courseNode*temp = head; /*dummy variable for head.*/
		/*it should check all the nodes to find right place for new node.*/
		while(temp != NULL && newNode->courseName > temp->courseName){
			prev = temp; /*pointer to previous value to make arrangements easier.*/
			temp = temp->next; 
		}
		newNode->next = temp; /*connect the rest*/
		prev->next = newNode; /*connect the previous*/
		return head;
	}

}

/*The purpose of this function is to pull the required node from the linkedlist. It takes head as a parameter and when there is a match it returns
the node. If there is no match, it returns null. */
courseNode*menuCourseControl(courseNode*head, string info){
	courseNode*temp = head;
	while (temp != NULL){
		if ( info == temp->courseCode){
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

/*This function taken from labcodes, it frees the memory which allocated with new.*/
void clearList(courseNode*head)
{
	courseNode * ptr = head;
	while (head!=NULL)
	{
		head = head->next;
		delete ptr;
		ptr = NULL; 
		ptr = head;
	}
}
int main(){
	ifstream input;
	string filename, linestr,course_code, course_name;
	int student_id;
	cout << "Please enter file name: "; 
	cin >> filename;
	input.open(filename.c_str()); /*opens the file*/
	cout << "Successfully opened file " << filename <<endl;
	courseNode *head = NULL, *ptr = new courseNode(); /*initialize nodes for linkedlist*/
	while (getline(input,linestr)){ /*reads file line by line*/
		istringstream linestream(linestr); /*stringstream is used for take info from lines. */
		linestream >> course_code >> course_name >> student_id ;
		if (linkedlistsearch(head,course_code) == true){ /*If course is already in list,  update node's vector with student id.*/
			updateVector(head,course_code,student_id);
		}
		else{
			ptr->courseCode = course_code; /*If course is not in list, update node which will be added.*/
			ptr-> courseName = course_name;
			ptr->studentsAttendingIDs.push_back(student_id);
			head = addSorted(ptr,head); /*add new node to linkedlist but keep the head's information. */
			ptr = new courseNode();
		}
	}
	cout << "The linked list is created." << endl;
	cout << "The initial list is:" << endl;
	PrintList(head); /*Displays list for the first time.*/
	int menu,counter=0,counter2=0; /*Counter will count number of iterations in linestream, menu is an input from the user. */
	cout << endl << "Please select one of the choices:\n1. Add to List\n2. Drop from List\n3. Display List\n4. Finish Add/Drop and Exit" << endl;
	cin >> menu;
	string firstinput,secondinput,info; /*First input will be used for first menu, secondinput will be used for second menu, info is a dummy variable for linestream */
	bool newcoursecode = false, option4=false; /*The newcoursecode is important for linestream, it
	determines which category the next information belongs to depending on the condition, option4 for exit.*/
	while((menu == 1 || menu == 2 || menu == 3 || menu==4)&&option4 == false){ /*While loop will continue until option4 became false. */
		if (menu == 1){
			cin.ignore(); 
			cout << "Give the student ID and the course names and course codes that he/she wants to add:" << endl;
			getline(cin,firstinput); /*Take input as a line*/
			istringstream linestr(firstinput); /*Convert it into linestream*/
			while ( linestr >> info){
				counter++; /*It will count the number of iterations in linestr, it's purpose is determine special cases like first cases. */
				if (newcoursecode==false){ /*If condition is false, that means the course_code will be the first info of stream*/
					course_code = info;
				}
				if (menuCourseControl(head,course_code)==NULL && counter == 1){ /*If course_code is not in list and it's first info in stream, newcoursecode
																				is converted to true. */
					newcoursecode=true;
				}
				if (menuCourseControl(head,course_code)!=NULL){
					if (newcoursecode == false){ /*Because the newcoursecode became false in 194th line, course_code is already filled so the next info from
											 linestream will be course_name */
						linestr >> course_name;
					}
					else{
						course_name = info; /*If newcoursecode true, course_name will be info. This means doesn't need to take new info from linestream for course_name.*/
					}
					while (linestr >> info){ /*Linestream will take info until the new course_code.*/
						if (info[0] >= 48 && info[0] <= 57 ){ /*If the first element of info is a number, the info is a studentID. This will be checked with ASCII*/
							student_id = atoi(info);  /*info is a string so it will be converted into integer with the help of atoi from strutils*/
							if (searchInVector(head,course_code,student_id)== true){ /*ID will be searched and if there is a match no need to action. */
								cout<<"Student with id " << student_id << " already is enrolled to " << course_code <<". No action taken."<< endl;
							}
							else{
								updateVector(head,course_code,student_id); /*If there is no match, ID will added to related course
																		   node's vector which contain studentID's */
								cout << "Student with id " << student_id << " is enrolled to " << course_code << "." << endl;
							}
						}
						else{ /*If the first two elements of info are not a number, next info should be course_code*/
							course_code = info;
							newcoursecode = true; /*newcoursecode converted to true since there is a new course_code. */
							break; /*Break the while loop because there is a new course_code. */
						}
					}
				}
				else if (menuCourseControl(head,course_code)==NULL && newcoursecode == true){ /*If course_code is valid but it is not part of the list*/
					courseNode*newelement = new courseNode(); /*New node to be added */
					cout << course_code << " does not exist in the list of Courses. It is added up." << endl;
					newelement->courseCode = course_code; /*Fill the node*/
					course_name = info; /*Since course_code is already taken, the info which was read by the linestream will be course_name. */
					newelement->courseName = course_name;
					head = addSorted(newelement,head); /*Add to list*/
					while (linestr >> info){ /*Since course_name is the last info, next ones from linestream will be student_ID's for related course */
						if (info[0] >= 48 && info[0] <= 57){ /*same ascii check for the first index. */
							student_id = atoi(info); /*convert info to integer if it's student_id*/
							if (searchInVector(head,course_code,student_id)== true){ /*If student id is an already part of the vector, no action. */
								cout<<"Student with id " << student_id << " already is enrolled to " << course_code <<". No action taken."<< endl;
							}
							else{
								updateVector(head,course_code,student_id); /*Update vector if it's not part of the vector. */
								cout << "Student with id " << student_id << " is enrolled to " << course_code << "." << endl;
							}
						}
						else{
							course_code = info; /*If the first two elements of info are not a number, info should be course_code*/
							newcoursecode = true;
							break; /*Break the loop since there is new coursecode. */
						}
					}
				}
			}
			counter=0;/* The counter value has been changed to 0 in case the user enters menu 1 again. */
			newcoursecode = false; /*The newcoursecode value has been changed to false in case the user enters menu 1 again. */
			cout << "\nPlease select one of the choices:\n1. Add to List\n2. Drop from List\n3. Display List\n4. Finish Add/Drop and Exit" << endl;
			cin >> menu; 
		}
		else if (menu == 2){
			cout << "Give the student ID and the course names and course codes that he/she wants to drop:" << endl;
			cin.ignore();
			getline(cin,secondinput);
			istringstream linestr_2(secondinput); /*Second linestream for secondinput.*/
			while ( linestr_2 >> info){
				counter2++; /*It will count the number of iterations in linestr2, it's purpose is determine special cases like first cases. */
				if (newcoursecode==false){ /*Same purpose as the first condition, default value is false. If it's false, it means the first info is course_code.*/
					course_code = info;
				}
				if (menuCourseControl(head,course_code)==NULL && counter2 == 1){ /*If course_code is not in list and it's first info in stream, newcoursecode
																				is converted to true. */
					newcoursecode=true;
				}
				if (menuCourseControl(head,course_code)!=NULL){ /*If there is a match, element will be deleted.*/
					if (newcoursecode == false){ /*Same purpose as menu 1. */
						linestr_2 >> course_name; 
					}
					else{
						course_name = info;
					}
					while (linestr_2 >> info){ /*Since course_name is already passed, the next infos will be studentID's. */
						if (info[0] >= 48 && info[0] <= 57){ /*same ASCII check for first index of info. */
							student_id = atoi(info); /*if it's a studentID, convert string into integer with atoi. */
							if (searchInVector(head,course_code,student_id)== false){ /*If student is not a part of the course, he/she can't drop. */
								cout<<"Student with id " << student_id <<" is not enrolled to " << course_code <<", thus he can't drop that course." << endl;
							}
							else{ /*If student is a part of the course, he/she can drop. */
								deleteInVector(head,course_code,student_id);
								cout << "Student with id " << student_id << " has dropped " << course_code << "." << endl;
							}
						}
						else{
							course_code = info; /*If the first two elements of info are not a number, next info should be course_code*/
							newcoursecode = true; /*newcoursecode became true since we have new course_code. */
							break; /*Break the while loop since we have new course_code. */
						}
					}
				}
				else if (menuCourseControl(head,course_code)==NULL && newcoursecode == true){ /*If course_code is valid but not the part of the list.*/
					course_name = info; /*Since course_code is already taken, the info which was read by the linestream will be course_name. */
					while (linestr_2 >> info){
						if (info[0] >= 48 && info[0] <= 57){ /*same ascii check for the first index.*/
							student_id = atoi(info);
							cout << "The " << course_code <<" course is not in the list, thus student with id " << student_id <<" can't be dropped" << endl;
						}
						else{
							course_code = info; /*Same purpose as above.*/
							break; /*Break the while loop since we have a new node. */
						}
					}
				}
			}
			counter2=0; /*Counter value has changed to 0 in case user enters menu 2 again. */
			newcoursecode = false; /*newcoursecode value has been changed to false in case user enters menu 2 again. */
			cout << "\nPlease select one of the choices:\n1. Add to List\n2. Drop from List\n3. Display List\n4. Finish Add/Drop and Exit" << endl;
			cin >> menu;
		}
		/*Menu 3 shows current situation of the list. */
		else if (menu == 3){
			cout << "The current list of course and the students attending them: " << endl;
			PrintList(head); 
			cout << "\nPlease select one of the choices:\n1. Add to List\n2. Drop from List\n3. Display List\n4. Finish Add/Drop and Exit" << endl;
			cin >> menu;
		}
		else if (menu == 4){ /*Menu 4 means exit, it will display the menu one last time and free the memory. */
			cout << "\nThe add/drop period is finished. Printing the final list of courses and students attending them." << endl;
			cout << "NOTE: Courses with less than 3 students will be closed this semester." << endl;
			PrintListForOption4(head); /*Print list with additional info. */
			option4 = true; /*Option4 converted to true, so while loop won't continue. */
			clearList(head); /*Free the memory*/
		}
	}
	delete ptr;
	return 0;
}
