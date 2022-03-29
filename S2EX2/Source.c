#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 7

typedef struct  Worker {
	long unsigned Id;
	char* Name;
	long unsigned Salary;
	union {
		char HByear[7];
		long unsigned EByear;
	} Byear;

} Worker;

typedef struct WorkerList {
	Worker* data;
	struct WorkerList* next;
}WorkerList;

Worker* CreateWorker(int signByear);
void PrintWorker(Worker* employe, int signByear);
WorkerList* addWorker(WorkerList* head, Worker* w);
void update_worker(WorkerList* head, float percent);
WorkerList* deleteWorstWorker(WorkerList* head);
void freeWorkers(WorkerList* head);
WorkerList* reverse(WorkerList* head);
int Index(WorkerList* head, long unsigned id);
int IndexRec(WorkerList* head, long unsigned id);

void main() {
	WorkerList* head = (WorkerList*)calloc(1, sizeof(WorkerList)); // head will be the worker with the highest salary
	int dataType;
	printf("\nPlease enter 1 to enter english dates or 0 to enter hebrew dates for all workers: ");
	scanf("%d", &dataType);
	Worker* firstWorker = CreateWorker(dataType);
	Worker* secondWorker = CreateWorker(dataType);
	Worker* thirdWorker = CreateWorker(dataType);
	PrintWorker(firstWorker, firstWorker);
	head = addWorker(head, firstWorker);
	head = addWorker(head, secondWorker);
	head = addWorker(head, thirdWorker);
	WorkerList* ptr = head;
	while (ptr) {
		printf("\n%s", ptr->data->Name);
		ptr = ptr->next;
	}
	head = deleteWorstWorker(head);
	update_worker(head, 30);
	int num;
	num = Index(head, 2064);
	printf("\nlocation in list of employe with this id: %d", num);
	num = IndexRec(head, 5); // there is no employee with 5 as id
	head = reverse(head);
	if (num == -1) printf("no employe with this id found");
	else printf("\nlocation in list of employe with this id: %d", num);
	ptr = head;
	while (ptr) {
		printf("\n%s", ptr->data->Name);
		ptr = ptr->next;
	}
	freeWorkers(head);
}

Worker* CreateWorker(int signByear) {
	Worker* newEmploye;  //create new employe
	newEmploye = (Worker*)calloc(1, sizeof(Worker)); //initalize all variables of newemploye to NULL
	char name[50];
	printf("\nPlease enter worker name: "); // ask user for worker name
	fseek(stdin, 0, SEEK_END);
	gets(name);
	int len = strlen(name);
	newEmploye->Name = (char*)malloc(len * sizeof(char) + 1);
	if (!newEmploye->Name) {
		printf("allocation failed");
		return 0;
	}
	strcpy(newEmploye->Name, name); // enter name to newEmplye structre
	printf("\nPlease enter worker ID: "); // ask user for worker id and then enter it to newEmplye structre
	scanf("%lu", &(newEmploye->Id));
	printf("\nPlease enter worker salary: "); // ask user for worker salary and then enter it to newEmplye structre
	scanf("%lu", &(newEmploye->Salary));
	printf("\nPlease enter birth year: "); // ask user for worker birth year according to choice made in main and then enter it to newEmplye structre
	if (signByear == 1) scanf("%lu", &(newEmploye->Byear.EByear));
	if (signByear == 0) scanf("%s", newEmploye->Byear.HByear);
	return newEmploye;
}

void PrintWorker(Worker* employe, int signByear) {
	printf("\nWorker name: %s\nID: %lu\nSalary: %lu", employe->Name, employe->Id, employe->Salary); //print name, id, salary
	if (signByear == 1) printf("\nBirth year: %lu", employe->Byear.EByear); //print birth year according to choce made in main
	if (signByear == 0) printf("\nBirth year: %s", employe->Byear.HByear);
}

WorkerList* addWorker(WorkerList* head, Worker* w) {
	if (head->data == NULL) { // case list is empty
		head->data = w;
		return head;
	}
	WorkerList* newPtr = (WorkerList*)calloc(1, sizeof(WorkerList));
	newPtr->data = w;
	if (head->data->Salary < w->Salary) { // case new emplyee has the highest salary
		newPtr->next = head;
		return newPtr;
	}
	if (!head->next) { // case new employee is second employee
		head->next = newPtr;
		return head;
	}
	WorkerList* ptr = head;
	while (ptr->next->data->Salary > w->Salary) {
		if (ptr->next->next == NULL) { // case new employee has smallest salary
			ptr->next->next = newPtr;
			return head;
		}
		ptr = ptr->next;
	}
	newPtr->next = ptr->next; // general case - in between
	ptr->next = newPtr;
	return head;
}

WorkerList* deleteWorstWorker(WorkerList* head) {
	if (!(head->data)) { // case list is empty
		printf("there are no workers in this list");
		return head;
	}
	WorkerList* ptr = head;
	if (!(ptr->next)) { // case list is one worker
		free(ptr->data->Name);
		free(ptr);
		printf("\nAll employes deleted");
		return;
	}
	while (ptr->next->next) { //general case - last worker
		ptr = ptr->next;
	}
	free(ptr->next->data->Name);
	free(ptr->next);
	ptr->next = NULL;
	return head;
}

void update_worker(WorkerList* head, float percent) {
	WorkerList* ptr = head; //create temp ptr to not change head
	while (ptr) { //change salary to all employes
		ptr->data->Salary = (1 + percent / 100) * ptr->data->Salary;
		ptr = ptr->next;
	}
}

void freeWorkers(WorkerList* head) {

	WorkerList* ptr = head;
	WorkerList* temp;

	//empty list
	if (head == NULL) return;

	//free all allocated data inward out by incrementing pointer forward and freeing what's behind
	while (ptr != NULL) {
		temp = ptr;
		ptr = temp->next;

		// free(temp->data->Name);
		free(temp->data);

		free(temp);
	}

}

WorkerList* reverse(WorkerList* head) {

	WorkerList* prev = NULL;
	WorkerList* current = head;
	WorkerList* next = NULL;

	if (head == NULL) printf("list empty");

	//go through entire list, reverse next points with previous pointers

	while (current != NULL) {
		next = current->next; //next updated to point to what head points to
		current->next = prev; //head's next points to previous
		prev = current; //previous points to head
		current = next; // head points to next

	}

	//update head to point to other end of list
	head = prev;

	return head;
}

int IndexRec(WorkerList* head, long unsigned id) {

	//end of list, no id found
	if (head == NULL) {
		return -1;
	}
	//id number has been located
	if (head->data->Id == id) return 1;

	//return minus one recursively backwards if the id was not located
	if (IndexRec(head->next, id) == -1) return -1;

	//if id was found, add one for every recursive call to calculate place in list
	return 1 + IndexRec(head->next, id);

}

int Index(WorkerList* head, long unsigned id) {

	int counter = 1;

	WorkerList* ptr;
	ptr = head;

	//list is empty
	if (ptr == NULL) {
		printf("\nlist empty");
		return -1;
	}
	//counts upwards from one until it finds the place of the id number
	while (ptr->data->Id != id) {

		if (ptr->next == NULL) {
			printf("\nno such id found");
			return -1;
		}

		counter++;
		ptr = ptr->next;
	}



	//returns number in list of the worker with searched id number
	return counter;
}
