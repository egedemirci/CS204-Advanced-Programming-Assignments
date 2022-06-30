#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream> 
using namespace std;

struct busStop { 
	string busStopName;
	busStop *left;
	busStop *right;
};

struct busLine {
	string busLineName;
	busLine *next;
	busStop *busStops;
};

busLine* head = nullptr;

/*This function takes head of the buStop linked list as a parameter and it prints the stop names until temp became null. */
void printBusStop(busStop*busHead){
	busStop*temp = busHead; /*dummy variable for head of the busHead list.*/
	while ( temp != NULL){
		cout << temp->busStopName;
		if ( temp->right != NULL){
			cout << " <-> ";
		}
		temp = temp->right; /*moves to the next pointer. */
	}
}
/*This function prints the main menu. */
void printMainMenu() {
	cout << endl;
	cout <<"I***********************************************I"<<endl
	<<"I 0 - EXIT PROGRAM I"<<endl
	<<"I 1 - PRINT LINES I"<<endl
	<<"I 2 - ADD BUS LINE I"<<endl
	<<"I 3 - ADD BUS STOP I"<<endl
	<<"I 4 - DELETE BUS LINE I"<<endl
	<<"I 5 - DELETE BUS STOP I"<<endl
	<<"I 6 - PATH FINDER I"<<endl
	<<"I***********************************************I"<<endl
	<<">>";
	cout << endl;
}
bool consistencyCheck() {
	busLine* currBL = head; //a global variable
	while(currBL) {
		busStop* currBS = currBL->busStops;
		while(currBS) {
			busStop* rightBS = currBS->right;
			if(rightBS && rightBS->left != currBS) {
				cout << "Inconsistency for " << currBL->busLineName
					<< " " << currBS->busStopName << endl;
				return false;
			}
			currBS = currBS->right;
		}
		currBL = currBL->next;
	}
	return true;
}
/*Delete all the stops of the busLine which is given by the user. */
void deleteAlltheStops(busLine*ptr){ 
	busStop*busStopDeleted = ptr->busStops;
	while ( ptr->busStops != NULL){
		ptr->busStops = ptr->busStops->right;
		delete busStopDeleted;
		busStopDeleted = NULL;
		busStopDeleted = ptr->busStops;
	}
}

/*This function takes head of the busLines and prints necessary information for menu 1 and other menus. It uses printBusStop function for busStops. */
void printBusLines(busLine*head){
	busLine*temp = head; /*dummy pointer to head of busLine. */
	while (temp != NULL){ /*It will print the information until no element left. */
		cout << temp->busLineName << ": ";
		printBusStop(temp->busStops);
		cout << endl;
		temp = temp->next; /*moves to the next pointer. */
	}
}
/*This function is prepared for the main menu, it uses the printBusLines function which has parameters. */
void printBusLines(){
	printBusLines(head);
}

/*This function adds new nodes to busStop linked list, return head of the list. */
busStop*addBusStop(busStop*newNode, busStop*busStophead){
	busStop*temp = busStophead; /*dummy pointer to head. */
	busStop*prev = NULL; /*pointer to previous value. */
	if (busStophead == NULL){ /*Special case if head is null, new element will be head. */
		busStophead = newNode; /*new element became head. */
		newNode->left = NULL; /*Since head is the first element, left and right values will be the null. */
		newNode-> right = NULL;
		return busStophead; /*return head.*/
	}
	else{
		while ( temp != NULL){ /*If head is not null, the new element will be placed at the end. */ 
			prev = temp; /*pointer to previous value to make arrangements easier.*/
			temp = temp->right;  /*When temp became null, it means pointer reached to end of the list. */
		}
	}
	prev->right = newNode; /*The next of the last element before null became new node. */
	newNode->right = NULL; /*Since new node is at the end, the next element of newNode is NULL. */
	newNode->left = prev; /*Since it's a doubly linked list, new node points to the prev with left. */
	return busStophead; /*return head. */
}
/*This function adds new nodes to end of the busLines linked list, return head of the list.*/
busLine* addBusLine(busLine*newNode, busLine*head){
	busLine*temp = head; /*dummy pointer to head. */
	busLine*prev = NULL; /*pointer to previous value. */
	if (head == NULL){ /*If head is NULL, the new element will be the new head. */
		head = newNode;
		newNode->next = NULL; /*It will point to NULL. */
		return head; /*return new head. */
	}
	else{
		while ( temp != NULL){
			prev = temp; /*pointer to previous value to make arrangements easier.*/
			temp = temp->next; /*When temp became null, it means pointer reached to end of the list which will be the place of the new element. */
		}
	}
	prev->next = newNode; /*The next of the last element before null became new node.*/
	newNode->next = temp; /*Since temp is null, newNode's next is temp. */
	return head; /*return head. */
}
/*This function controls the busLine. It takes name and head as a parameters, if it found the name in busLineNames, it returns true. */
bool busLineControl(busLine*head, string bname){
	busLine*temp = head; /*dummy pointer to head. */
	while (temp != NULL){
		if (bname == temp->busLineName){ /*If search value equals to temp's busLineName, it means the bname is one of the elements of the list. */
			return true; /*there is a match so return true. */
		}
		temp = temp->next; /*moves to the next pointer. */
	}
	return false; /*no match, return false. */

}
/*This function controls the busStop. It takes stopname and head of busStop list as a parameters, if it found the stopname in busStops, it returns true. */
bool busStopControl(busStop*bushead,string stopname){
	busStop*temp = bushead; /*dummy pointer to head. */
	while (temp != NULL){
		if (temp->busStopName == stopname){  /*If search value equals to temp's busStopName, it means the stopname is one of the elements of the list. */
			return true; /*match, return true. */
		}
		temp = temp->right; /*moves to the next pointer. */
	}
	return false; /* no match, return false. */
}

/*This function is different from previous print functions because it only prints the info of single node. */
void printInfo(busLine*ptr){
	cout << "The bus line information is shown below" << endl;
	cout << ptr->busLineName << ": "; /*Prints the name of the busLine. */
	printBusStop(ptr->busStops); /*Prints the stopnames with the help of printbusStops function. */
}
/*This function adds busLine to busLine linked list. It is prepared for the main menu. */
void addBusLine(){
	string buslinename,busstopname,menu; /*The names which will be taken by the user. */
	busStop*bushead =  NULL; /*The head of the busStop linked list which will be added to a busLines linked list. */
	busStop*ptr = new busStop(); /*The new node of busStop linked list. /*/
	busLine* newBusLine = new busLine(); /*The new node which will be added to busLines. */
	cout << "Enter the name of the new bus line (0 for exit to main menu)." << endl;
	cin >> buslinename; /*takes input from the user. */
	/*If it's already a element of the linked list, it asks new input from the user until the user enters a new busLineName. */
	while (busLineControl(head,buslinename) == true){ 
		cout << "Bus line already exists: enter a new one (0 for exit)" << endl;

		cin >> buslinename;
	}
	/*If busLineName is equals to 0, program exits to main menu. If it's not, it continues. */
	if (buslinename != "0"){
		cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
		cin >> busstopname; /*takes stopName from the user. */
		while (busstopname != "0"){ /*It will take stopNames and add to the busStops linked list until the user enters 0. */
			if (busStopControl(bushead,busstopname) == true){ /*same purpose as busLineControl.*/
				cout << "Bus stop already exists in the line" << endl;
				cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
				cin >> busstopname;
			}
			else if (busStopControl(bushead,busstopname) == false){
				ptr->busStopName = busstopname; /*ptr node is filled with busStopName. */
				bushead = addBusStop(ptr,bushead); /*add to linked list, keep head of the list. */
				ptr = new busStop();
				cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
				cin >> busstopname;
			}

		}
		if (bushead == NULL){ /*If user enters 0 and bushead is still NULL, he/she can't allowed to add an empty busLine. */
			cout << "You are not allowed to add an empty bus line" << endl;
			delete ptr;
			delete newBusLine;
		}
		else{
			newBusLine->busLineName = buslinename; /*If busHead is notNull, busLine node will be filled with info. */
			newBusLine->busStops = bushead; /*It keeps the head of busStops, in the node. */
			printInfo(newBusLine); /*Print the info of single node. */
			cout << endl << "Are you sure? Enter (y/Y) for yes (n/N) for no? " << endl;
			cin >> menu;
			if (menu == "y" || menu == "Y"){ /*If user enters "Y", new node will be added to beginning. */
				newBusLine->next = head; 
				head = newBusLine; /*New haed is busLine. */
				cout << endl << endl;
				printBusLines(newBusLine); /*Prints the current situation of the busLines. */
			}
			if (menu == "N" || menu == "n"){
				deleteAlltheStops(newBusLine); /*Free the memory which is allocated. */
				delete newBusLine;
				newBusLine = NULL;
			}
		}
	}
}
/*This function search busLine but if it founds a match, it returns busLine instead of bool. */
busLine*searchBusLine(busLine*head, string busline){
	busLine*temp = head; /*dummy pointer to head. */
	while (temp != NULL){
		if (temp->busLineName == busline){ /*if there is a match, return temp. */
			return temp;
		}
		temp = temp->next; /*moves to the next pointer. */
	}
	return NULL; /*there is no match, return null. */
}
/*This function search busLine but if it founds a match, it returns busLine instead of bool. */
busStop*searchBusStop(busStop*bushead, string stopname){
	busStop*temp = bushead;  /*dummy pointer to head. */
	while (temp != NULL){
		if (temp->busStopName == stopname){ /*if there is a match, return temp. */
			return temp;
		}
		temp = temp->right; /*moves to the next pointer. */
	}
	return NULL; /*there is no match, return null. */
}

/*This function adds new BusStops to the busLines.*/
void addBusStop(){
	bool exittomenu = false;
	string busline,busstop, prevstop; /*inputs.*/
	busLine*updatedBusLine = NULL; /*BusLine which will be updated. */
	busStop*newBusStop = new busStop(); /*BusStop which will be added to route. */
	busStop*prev = NULL; 
	busStop*next = NULL;
	cout << "Enter the name of the bus line to insert a new bus stop (0 for main menu)"<< endl;
	cin >> busline;
	if (busline != "0"){ /*If user enters 0, it exist to main menu. */
		if (busLineControl(head,busline) == true){ /*This checks if the given name is in the busLine list, if it is correct, it does the update. */
			updatedBusLine = searchBusLine(head,busline); /*BusLine which will be updated.*/
			printInfo(updatedBusLine); /*Print the current situation of busLine. */
			cout << endl;
			cout << "Enter the name of the new bus stop" << endl;
			cin >> busstop;
			/*This searches busStop name in busLine's bus stops, if it's true this means busStop already exists in a line so it's going back to prev menu. */
			if (busStopControl(updatedBusLine->busStops, busstop) == true){
				cout << "Bus stop already exists. Going back to previous menu." << endl;
				delete newBusStop;
			}
			else{ /*If busStop name does not exists in busLine. */
				cout << "Enter the name of the previous bus stop to put the new one after it (0 to put " << endl
				<< "the new one as the first bus stop)" << endl;
				cin >> prevstop;
				if (prevstop == "0"){ /*If user enters 0, the new busStop will be added to beginning. */
					newBusStop->busStopName = busstop;
					next = updatedBusLine->busStops;
					newBusStop -> right = next;
					next->left = newBusStop;
					newBusStop -> left = NULL;
					updatedBusLine->busStops = newBusStop;
				}
				else{
					/*If the given prevstop is not a part of the linkedlist, it will ask again until it found a one or user enters 0. */
					while (busStopControl(updatedBusLine->busStops,prevstop) == false){ 
						cout << "Bus stop does not exist. Typo? Enter again (0 for main menu)" << endl;
						cin >> prevstop;
						if (prevstop == "0"){ /*If user enters 0, it will free the memory and go back to main menu. */
							exittomenu = true;
							delete newBusStop;
							break;
						}
					}
					if (exittomenu != true){ /*If prevStop is not equals to 0, program will continue and add busStop. */
						newBusStop->busStopName = busstop; /*newBusStop is filled with info. */
						prev = searchBusStop(updatedBusLine->busStops,prevstop); /*Place of the prevPointer will come from busLine's busStops. */
						next = prev->right; /*this element will be the next of the node which will be added. */
						prev->right = newBusStop; /*connections.*/
						newBusStop->right = next;/*connections.*/
						newBusStop -> left = prev;/*connections.*/
						if(next != NULL){
							next->left = newBusStop;/*connections.*/
						}
					}
				}
				if (exittomenu == false){
					cout << endl;
					printBusLines(head);
				}
			}

		}
		else{
			cout << "Bus line cannot be found. Going back to previous menu." << endl;
		}
	}
}

/*This function will delete the busLine which is given by the user, it returns the head */
busLine*deleteBL (busLine*head, string busline){
	busLine*ptr = searchBusLine(head,busline); /*The node which will be deleted. */
	busLine*temp = head; /*dummy pointer to head. */
	if (ptr == head){ /*If element which will be deleted is a head of the list, this is a speacial case. */
		ptr = ptr->next; /*Head's next will be the new head. */
		deleteAlltheStops(head);
		delete head; /*delete head.*/
		head = NULL; /*to prevent confusion. */
		return ptr; /*return new head. */
	}
	else{
		while (temp != NULL){
			if ( temp->next == ptr){ /*when temp->next equals to pointer which will be deleted, it should exit the loop.*/ 
				break;
			}
			temp = temp->next;
		}
		temp->next = ptr->next; /*connect the rest. */
		deleteAlltheStops(ptr); /*deletes all the busstops. */
		delete ptr; /*delete ptr. */
		ptr = NULL; /*to prevent confusion. */
		return head; /*return head. */
	}
}

/*This function for the process of main menu, it will use deleteBL function. */
void deleteBusLine(){
	string busline;
	cout << "Enter the name of the bus line to delete"<< endl;
	cin >> busline;
	if(busLineControl(head,busline) == false){
		cout << "Bus line cannot be found. Going back to the previous (main) menu.";
	}
	else{
		head = deleteBL(head,busline); /*If the given busLine is a element of the given list, it will delete the busLine. */
		printBusLines(head); /*Print current situation. */
	}

}
/*This function will delete the busLine which is given by the user, it returns the head of busStops.*/
busStop*deleteBS(busStop*bushead, string stopname){
	busStop*ptr = searchBusStop(bushead,stopname); /*The node which will be deleted. */
	busStop*temp = bushead; /*dummy pointer to bushead.*/
	if (ptr == bushead){ /*Special case, delete head of the busStops. */
		ptr = ptr->right; /*Moves next pointer.*/
		ptr -> left = NULL; /*the ptr->left will be NULL since it will be the new head. */
		delete bushead; /*delete busHead. */
		bushead = NULL; /*to prevent confusion. */
		return ptr; /*return new head. */
	}
	else{
		while (temp != NULL){
			if ( temp == ptr){ /*when the element which will be deleted found, exit the while loop. */
				break;
			}
			temp = temp->right;
		}
		busStop*prev = temp->left; /*connections.*/
		busStop*next = temp->right; /*connections.*/
		prev->right = next;/*connections.*/
		if (next != NULL){
			next->left = prev;/*connections.*/
		}
		delete temp; /*delete*/
		temp = NULL;
		return bushead; /*return the head. */
	}

}
/*This function deletes busStop, this function will use deleteBS. */
void deleteBusStop(){
	string busline,busstop;
	cout << "Enter the name of the bus line to delete a new bus stop (0 for main menu)"<< endl;
	cin >> busline;
	if (busline == "0"){
	}
	else if(busLineControl(head,busline) == false){ /*If the name of the BusLine cannot be found, going back to the previous menu. */
		cout << "Bus line cannot be found. Going back to previous (main) menu.";
	}
	else{
		busLine*ptr = searchBusLine(head,busline); /*Bus stop will be deleted from this busLine. */
		printInfo(ptr);
		cout << endl << "Enter the name of the bus stop to delete (0 for main menu)" << endl;
		cin >> busstop;
		/*If the given busstop is not a part of the linkedlist, it will ask again until it found a one or user enters 0. */
		while (busStopControl(ptr->busStops,busstop) == false && busstop != "0"){
			cout << "Bus stop cannot be found. Enter the name of the bus stop to delete (0 for main menu)" << endl;
			cin >> busstop;
			if (busstop == "0"){
				break;
			}
		}
		if (busstop != "0"){ /*When it found a one and busStop is not equal to 0, it will delete the given element. */
			if (ptr->busStops->right == NULL){
				deleteAlltheStops(ptr);
				head = deleteBL(head,ptr->busLineName);
			}
			else{
				ptr->busStops = deleteBS(ptr->busStops, busstop);
			}
			printBusLines();
		}
	}
}

/*This function prints the route for 6th menu, there are special cases so it's a different from previous print functions. */
void printBusStopMenu6(busStop*bushead,string firststop, string secondstop){
	busStop*temp = bushead;
	bool firststopfirst = false, secstopfirst = false; /*This booleans check which stop is a first in the route. */
	while (temp != NULL){
		if (temp->busStopName == firststop){ /*If there is a match, boolean became true, and break the loop. */
			firststopfirst = true;
			break;
		}
		else if (temp->busStopName == secondstop){
			secstopfirst = true;
			break;
		}
		temp = temp->right;
	}
	temp = NULL; /*default.*/
	if (secstopfirst == true){ /*If second stop is a first in the route, it will be printed to the left. */
		temp = searchBusStop(bushead,firststop);
		while(temp->busStopName !=secondstop){
			cout << temp->busStopName << "->";
			temp = temp -> left;
		}
		cout << secondstop;
	}
	else if (firststopfirst == true){  /*If first stop is a first in the route, it will be printed to the right. */
		temp = searchBusStop(bushead,firststop);
		while(temp->busStopName !=secondstop){
			cout << temp->busStopName << "->";
			temp = temp -> right;
		}
		cout << secondstop;
	}
}
/*This function checks if there is a direct route between two given stops, if it founds a match it returns the busLine. */
busLine*directroad(string firststop, string secondstop){
	busLine*temp = head;
	while (temp != NULL){
		/*If both of the elements are the part of the busLine's busstops, there is a direct road. */
		if(searchBusStop(temp->busStops,firststop) != NULL && searchBusStop(temp->busStops,secondstop) != NULL){
			return temp; 
		}
		temp = temp->next;
	}
	return NULL; /* no match. */
}
/*This function controls busStop in all busLines, if there is no match bus stop does not exist in the table. */
bool busStopControlAllBusLines(string busStop){
	busLine*temp = head; /*dummy pointer to head. */
	while (temp != NULL){
		if(busStopControl(temp->busStops,busStop) == true){ /*If busStop is a part of the busLine, there is a match so return true. */
			return true;
		}
		temp = temp->next;
	}
	return false;
}
/*This function find all the paths, it takes firststop and secondstop as a parameters.*/
void pathfinder(string firststop,string secondstop){
	busLine*temp = head; /*Dummy pointer to head. */
	bool thereIsRoad=false; /*functions of them are same but thereIsRoad2 provides all the interchanges which includes 2 busLine. */
	/*This while loop will control all the buslines and if it founds a busline which includes that busStop it will print the direct road.*/
	while (temp != NULL){ 
		/*If searchBusStop is not equal to NULL for both of them, that means there is a direct road. */
		if(searchBusStop(temp->busStops,firststop) != NULL && searchBusStop(temp->busStops,secondstop) != NULL){
			cout << "You can go there by " << temp->busLineName << ": " ;
			printBusStopMenu6(temp->busStops,firststop,secondstop);	
			thereIsRoad = true; /*There is a road so boolean converted to true */
			break;
		}
		temp = temp->next;
	}
	temp = head; /*Temp converted to head for the next iteration. */
	/*There is no direct road, so we should control interchanges. */
	while ( temp != NULL && thereIsRoad == false){
		if(searchBusStop(temp->busStops,firststop) != NULL){ /*Firstly, the first stop will be searched. */
			/*If the given stop is an element of a route, it will be checked whether
			there is a direct route to the second stop from all other stops on that route.*/
			busStop*ptr = temp->busStops;
			while (ptr != NULL){ /*It will loop through all the stops in busLine. */
				if (directroad(ptr->busStopName,secondstop) != NULL){ /*If there is a direct road, we found a interchange. */
					busLine* interchangeLine =  directroad(ptr->busStopName,secondstop); /*ptr->busStopName is the interchange stop. */
					cout << endl << "You can go there by " << temp->busLineName << ": "; /*BusLine between first stop and interchange stop. */
					printBusStopMenu6(temp->busStops, firststop ,ptr->busStopName); /*It will print the road between first stop and interchange stop first.*/
					cout << endl <<  "                    " << interchangeLine->busLineName << ": " ; /*BusLine between interchange stop and second stop. */
					printBusStopMenu6(interchangeLine->busStops,ptr->busStopName,secondstop);	/*It will print the road between interchange and second stop.*/ 
					thereIsRoad= true; /*found a road. */
					break;
				}
				ptr = ptr->right;
			}
		}
		temp = temp->next;
	}
	if (thereIsRoad == false){
		cout << "Sorry no path from "<< firststop << " to " << secondstop << " could be found." << endl;
	}
}
/*This function is for the process of the main menu. */
void pathfinder(){
	string startplace, endplace;
	cout << "Where are you now?" << endl;
	cin >> startplace;
	if (busStopControlAllBusLines(startplace) == true){ /*If busStop doesn't exist in all the busLines, it will go back to previous menu. */
		cout << "Where do you want to go?" << endl;
		cin >> endplace;
		if (startplace == endplace){
			cout << "Same stops! Going back to previous menu." << endl;
		}
		else{
			if (busStopControlAllBusLines(endplace) == true){ /*If busStop doesn't exist in all the busLines, it will go back to previous menu. */
				pathfinder(startplace,endplace); /*If both of them exist, it will try to find a path. */
			}
			else{
				cout << "Bus stop does not exist in the table. Going back to previous menu." << endl;
			}
		}
	}
	else{
		cout << "Bus stop does not exist in the table. Going back to previous menu." << endl;
	}
}

void deleteAll(busLine*head){
	busLine*ptr = head;
	while(ptr != NULL){
		head = head->next;
		deleteAlltheStops(ptr);
		delete ptr;
		ptr = NULL;
		ptr = head;
	}
}

/*Process of main menu. */
void processMainMenu() {
	char input;
	do
	{
		if(!consistencyCheck()) {
			cout << "There are inconsistencies. Exit." << endl;
			return;
		}
	printMainMenu();
	cout << "Please enter your option " << endl;
	cin >> input;
	switch (input) {
		case '0':
			cout << "Thanks for using our program" << endl;
			return;
		case '1':
			printBusLines();
			break;
		case '2':
			addBusLine();
			break;
		case '3':
			addBusStop();
			break;
		case '4':
			deleteBusLine();
			break;
		case '5':
			deleteBusStop();
			break;
		case '6':
			pathfinder();
			break;
		default:
			cout << "Invalid option: please enter again" << endl;
		} //switch
	} while(true);
}//processMainMenu


int main(){
	ifstream input;
	string filename = "busLines.txt",s,buslinename, bus_stop;
	input.open(filename.c_str()); /*open the file.*/
	busLine*ptr = nullptr;
	busStop*bushead = nullptr;
	busStop* newBusStop = new busStop();
	busLine*newBusLine = new busLine();
	while (getline(input,s)){ /*process file. */
		istringstream linestream(s);
		linestream >> buslinename;
		newBusLine->busLineName = buslinename.substr(0,buslinename.size()-1); /*to delete : character */
		while (linestream >> bus_stop){

			newBusStop->busStopName = bus_stop;
			bushead = addBusStop(newBusStop,bushead); /*creates busStops double linked list. */
			newBusStop = new busStop();
		}
		newBusLine->busStops = bushead; /*adds busStops to busLine. */
		head = addBusLine(newBusLine,head);
		bushead = NULL;
		newBusLine = new busLine();
	}
	processMainMenu();
	deleteAll(head); /*free the memory. */
	system("pause");
}