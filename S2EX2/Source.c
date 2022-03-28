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
void FastPrinterForChecks(WorkerList* head);
Worker* FastCreatWorkerForChecks(char name[10], int id, int salary, int birthyear);

void main() {
	WorkerList* head = (WorkerList*)calloc(1, sizeof(WorkerList)); // head will be the worker with the highest salary
	int dataType;
	printf("\nPlease enter 1 to enter english dates or 0 to enter hebrew dates for all workers: ");
	scanf("%d", &dataType);
	Worker* firstWorker = FastCreatWorkerForChecks("eliraz", 206478, 100000, 1998);
	Worker* secondWorker = FastCreatWorkerForChecks("kali", 123, 20000, 2010);
	Worker* thirdWorker = FastCreatWorkerForChecks("elisheva", 5, 10000, 2020);
	head = addWorker(head, firstWorker);
	//head = addWorker(head, secondWorker);
	//head = addWorker(head, thirdWorker);
	FastPrinterForChecks(head);
	int num;
	num = Index(head, 5);
	//num = IndexRec(head, 5);
	printf("\n%d", num);
	//FastPrinterForChecks(head);
}
void FastPrinterForChecks(WorkerList* head) {
	WorkerList* ptr = head;
	while (ptr) {
		printf("\n%s", ptr->data->Name);
		printf("\n%d", ptr->data->Salary);
		ptr = ptr->next;
	}
}

Worker* FastCreatWorkerForChecks(char name[10], long unsigned id, long unsigned salary, long unsigned birthyear) {
	Worker* newEmploye;
	newEmploye = (Worker*)calloc(1, sizeof(Worker));
	newEmploye->Name = (char*)malloc(9 * sizeof(char) + 1);
	strcpy(newEmploye->Name, name);
	newEmploye->Id = id;
	newEmploye->Salary = salary;
	newEmploye->Byear.EByear = birthyear;
}

Worker* CreateWorker(int signByear) {
	Worker* newEmploye;
	newEmploye = (Worker*)calloc(1, sizeof(Worker));
	char name[50];
	printf("\nPlease enter worker name: ");
	fseek(stdin, 0, SEEK_END);
	gets(name);
	int len = strlen(name);
	newEmploye->Name = (char*)malloc(len * sizeof(char) + 1);
	if (!newEmploye->Name) {
		printf("allocation failed");
		return 0;
	}
	strcpy(newEmploye->Name, name);
	printf("\nPlease enter worker ID: ");
	scanf("%lu", &(newEmploye->Id));
	printf("\nPlease enter worker salary: ");
	scanf("%lu", &(newEmploye->Salary));
	printf("\nPlease enter birth year: ");
	if (signByear == 1) scanf("%lu", &(newEmploye->Byear.EByear));
	if (signByear == 0) scanf("%s", newEmploye->Byear.HByear);
	return newEmploye;
}

void PrintWorker(Worker* employe, int signByear) {
	printf("\nWorker name: %s\nID: %lu\nSalary: %lu", employe->Name, employe->Id, employe->Salary);
	if (signByear == 1) printf("\nBirth year: %lu", employe->Byear.EByear);
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
	newPtr->next = ptr->next;
	ptr->next = newPtr;
	return head;
}

WorkerList* deleteWorstWorker(WorkerList* head) {
	if (!(head->data)) {
		printf("there are no workers in this list");
		return head;
	}
	WorkerList* ptr = head;
	if (!(ptr->next)) {
		free(ptr->data->Name);
		free(ptr);
		printf("\nAll employes deleted");
		return;
	}
	while (ptr->next->next) {
		ptr = ptr->next;
	}
	free(ptr->next->data->Name);
	free(ptr->next);
	ptr->next = NULL;
	return head;
}

void update_worker(WorkerList* head, float percent) {
	WorkerList* ptr = head;
	float oldSalary;
	while (ptr) {
		ptr->data->Salary = (1 + percent / 100)* ptr->data->Salary;
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

	//list is empty
	if (head->data == NULL) return -1;

	//id number has been located
	if (head->data->Id == id) return 1;

	//return minus one recursively backwards if the id was not located
	if (IndexRec(head->next, id) == -1) return -1;

	//if id was found, add one for every recursive call to calculate place in list
	return 1 + IndexRec(head->next, id);

}

int Index(WorkerList* head, long unsigned id) {

	int counter = 1;

	WorkerList* ptr = head;

	//list is empty
	if (ptr == NULL) return -1;


	//counts upwards from one until it finds the place of the id number
	while (ptr->data->Id != id) {
		counter++;
		if (!ptr->next) {
			printf("\nno such ID found");
			return -1;
		}
		ptr = ptr->next;
	}

	//returns number in list of the worker with searched id number
	return counter;
}