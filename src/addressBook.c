#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "addressBook.h"

Person *top; // Person pointer to point to the top of the linked list
int numPeople = 0; // integer to keep track of the number of people in the address book

Person *createPerson(char *last, char *first, char *email, char *phone) { // passes through strings to create a new Person pointer
	Person *newPerson = (Person*) malloc(sizeof(Person));
	strcpy(newPerson->last_name , last);
	strcpy(newPerson->first_name , first);
	strcpy(newPerson->email , email);
	strcpy(newPerson->phone_number , phone);
	newPerson->next = NULL;
	newPerson->prev = NULL;
	return newPerson;
}

void addContact(int index, char *contact) { // takes the index of desired add location and the string of the contact
	char last[256];
	char first[256];
	char email[256];
	char phone[256];
	char *separator = ",";
	char *token;
	char* element[] = {last, first, email, phone};
	token = strtok(contact, separator); // creates pointer of each string separated by a ","
	for (int i = 0; i < 4; i++) {
		strcpy(element[i], token); // copies the string of the token to the specified string
		token = strtok(NULL, separator);
	}

	Person* newPerson = createPerson(last, first, email, phone); // creates a new person with the given values
	Person* cur; // creates a new Person pointer called cur to be the cursor

	if (numPeople == 0) { // if there are no people in the address book
		top = newPerson; // set the top equal to the new person
		numPeople++; // increment the number of people by one
	} else if (index == 0) { // if the index is the beginning of the address book
		top->prev = newPerson;
		newPerson->next = top;
		top = newPerson;
		numPeople++;
	} else if (index == numPeople) { // the index is at the end of the address book
		cur = top;
		while(cur->next != NULL) { // while the end of the address book has not been reached
			cur = cur->next;
		}
		cur->next = newPerson;
		newPerson->prev = cur;
		numPeople++;
	} else if (index < numPeople) { // the index is somewhere in the middle of the address book
		cur = top;
		for (int i = 0; i < index; i++) { // increments the cursor until the index is reached
			cur = cur->next;
		}
		Person* prev = cur->prev;
		prev->next = newPerson;
		newPerson->prev = prev;
		newPerson->next = cur;
		cur->prev = newPerson;
		numPeople++;
	} else { // the index is out of range
		// do nothing
	}
}

void deleteContact(int index) { // deletes a contact at a given index
	Person* cur = top; // creates a new person pointer called cur
	if (index > numPeople - 1) { // if the index is out of range
		return;
	}
	for (int i = 0; i < index; i++) { // increments the cursor until the index is reached
		cur = cur->next;
	}
	if (cur->prev != NULL) { // if the cursor is not at the beginning of the address book
		cur->prev->next = cur->next;
	} else { // the cursor is at the beginning of the address book
		top = cur->next;
	}
	if (cur->next != NULL) { // if the cursor is not at the end of the address book
		cur->next->prev = cur->prev;
	}
	numPeople--; // decrements the number of people by one
	free(cur); // frees the cursor
}

void getContact(int index) { // gets the contact information at a given index
	Person* cur = top; // creates a new Person pointer called cur to be the cursor
	if (index > numPeople - 1) { // if index is out of range
		return;
	}
	for (int i = 0; i < index; i++) { // move the cursor to the index
		cur = cur->next;
	}
	printf("%s,%s,%s,%s\n", cur->last_name, cur->first_name, cur->email, cur->phone_number); // prints the data at the index
}

void getField(int index, char *field) { // gets the data at a given field of a given index
	Person* cur = top; // creates a new Person pointer called cur to be the cursor
	if (index > numPeople - 1) { // if index is out of range
		return;
	}
	for (int i = 0; i < index; i++) { // moves the cursor to the index
		cur = cur->next;
	}
	if (strcmp("lastName", field) == 0) { // if the desired field is the last name
		printf("%s\n", cur->last_name);
	} else if (strcmp("firstName", field) == 0) { // if the desired field is the first name
		printf("%s\n", cur->first_name);
	} else if (strcmp("email", field) == 0) { // if the desired field is the email
		printf("%s\n", cur->email);
	} else if (strcmp("phoneNumber", field) == 0) { // if the desired field is the phone number
		printf("%s\n", cur->phone_number);
	} else {
		// do nothing
	}
}

void getNumber() { // gets the number of people in the address book
	printf("%d\n", numPeople);
}

void loadFromFile(char *path) { // loads people from a file with a given name into the address book
	FILE *loadFile = fopen(path, "r"); // opens a file called loadFile for reading
	char line[BUFSIZ];
	fgets(line, BUFSIZ, loadFile);
	while (fgets(line, BUFSIZ, loadFile) != NULL) { // while the end of the document has not been reached
		line[strlen(line) - 1] = '\0';
		addContact(numPeople, line); // add the contact to the end of the address book
	}
	fclose(loadFile);
}

void saveToFile(char *path) { // saves the address book to a file with a given name
	FILE *saveFile = fopen(path, "w"); // opens a file called saveFile for writing
	fprintf(saveFile, "lastName,firstName,email,phoneNumber\n"); // prints the header
	Person* cur = top;
	while (cur != NULL) { // while the cursor is not at the end of the address book
		fprintf(saveFile, "%s,%s,%s,%s\n", cur->last_name, cur->first_name, cur->email, cur->phone_number); // writes the data to the file
		cur = cur->next;
	}
	fclose(saveFile);
}

void editContact(int index, char *field, char *newVal) { // edits the value of the specific field of a specific contact
	Person* cur = top; // creates a new Person pointer called cur to be the cursor
	if (index > numPeople - 1) { // if the index is out of range
		return;
	}
	for (int i = 0; i < index; i++) { // moves the cursor to the index
		cur = cur->next;
	}
	if (strcmp("lastName", field) == 0) { // if the desired field is the last name
		strcpy(cur->last_name, newVal); // copies the new value to the field
	} else if (strcmp("firstName", field) == 0) { // if the desired field is the first name
		strcpy(cur->first_name, newVal); // copies the new value to the field
	} else if (strcmp("email", field) == 0) { // if the desired field is the email
		strcpy(cur->email, newVal); // copies the new value to the field
	} else if (strcmp("phoneNumber", field) == 0) { // if the desired field is the phone number
		strcpy(cur->phone_number, newVal); // copies the new value to the field
	} else {
		// do nothing
	}
}

void sortContacts() { // sorts contacts in ascending order
	Person* people[numPeople]; // creates an array of Person pointers
	Person* cur = top; // creates a new Person pointer called cur to be the cursor
	for (int i = 0; i < numPeople; i++) { // adds each Person pointer from the address book to the array
		people[i] = cur;
		cur = cur->next;
	}
	qsort(people, numPeople, sizeof(Person*), compareFunc); // sorts the array using the compareFunc
	int prevNumPeople = numPeople; // creates a new integer equal to the number of people in the address book
	for (int i = 0; i < prevNumPeople; i++) { // for every person in the address book
		char contact[BUFSIZ];
		sprintf(contact, "%s,%s,%s,%s", people[i]->last_name, people[i]->first_name, people[i]->email, people[i]->phone_number);
		addContact(numPeople, contact); // add the contact of the first Person pointer in the sorted array
	}
	for (int i = 0; i < prevNumPeople; i++) { // for every person in the address book before adding the sorted ones
		deleteContact(0); // delete the top contact
	}
}

int compareFunc(const void *a, const void *b) { // compares values from two Person pointers
	int returnVal;
	const Person* aPerson = *((const Person**)a);
	const Person* bPerson = *((const Person**)b);
	returnVal = strcmp(aPerson->last_name, bPerson->last_name); // returnVal is the value from comparing the two pointers last names
	if (returnVal == 0) { // if the last names are the same
		returnVal = strcmp(aPerson->first_name, bPerson->first_name); // compare the first names
	}
	if (returnVal == 0) { // if the first names are the same
		returnVal = strcmp(aPerson->email, bPerson->email); // compare the emails
	}
	if (returnVal == 0) { // if the emails are the same
		returnVal = strcmp(aPerson->phone_number, bPerson->phone_number); // compare the phone numbers
	}
	return returnVal; // return the value of the first comparison that is not 0
}
