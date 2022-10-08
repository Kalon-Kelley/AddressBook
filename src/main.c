/*
 ============================================================================
 Name        : LKelleyAddressBook
 Author      : Lucas Kelley
 Version     :
 Copyright   : Your copyright notice
 Description : Address Book assignment
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "addressBook.h"

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	char command[1] = "\0";
	printf("Ready\n");
	while (command[0] != 'q') {
		fgets(command, BUFSIZ, stdin);
		if (command[0] == 'a') { // Add a contact
			char sIndex[BUFSIZ];
			fgets(sIndex, BUFSIZ, stdin);
			int index = atoi(sIndex);
			char contact[BUFSIZ];
			fgets(contact, BUFSIZ, stdin);
			contact[strlen(contact) - 1] = '\0';
			addContact(index, contact);
		} else if (command[0] == 'd') { // Delete a contact
			char sIndex[BUFSIZ];
			fgets(sIndex, BUFSIZ, stdin);
			int index = atoi(sIndex);
			deleteContact(index);
		} else if (command[0] == 'g') { // Get a contact
			char sIndex[BUFSIZ];
			fgets(sIndex, BUFSIZ, stdin);
			int index = atoi(sIndex);
			getContact(index);
		} else if (command[0] == 'f') { // Get a field
			char sIndex[BUFSIZ];
			fgets(sIndex, BUFSIZ, stdin);
			int index = atoi(sIndex);
			char field[BUFSIZ];
			fgets(field, BUFSIZ, stdin);
			field[strlen(field) - 1] = '\0';
			getField(index, field);
		} else if (command[0] == 'n') { // Get the number of contacts
			getNumber();
		} else if (command[0] == 'l') { // Load a file
			char path[BUFSIZ];
			fgets(path, BUFSIZ, stdin);
			path[strlen(path) - 1] = '\0';
			loadFromFile(path);
		} else if (command[0] == 's') { // Save contacts to a file
			char path[BUFSIZ];
			fgets(path, BUFSIZ, stdin);
			path[strlen(path) - 1] = '\0';
			saveToFile(path);
		} else if (command[0] == 'e') { // Edit a contact
			char sIndex[BUFSIZ];
			fgets(sIndex, BUFSIZ, stdin);
			int index = atoi(sIndex);
			char field[BUFSIZ];
			fgets(field, BUFSIZ, stdin);
			field[strlen(field) - 1] = '\0';
			char newVal[BUFSIZ];
			fgets(newVal, BUFSIZ, stdin);
			newVal[strlen(newVal) - 1] = '\0';
			editContact(index, field, newVal);
		} else if (command[0] == 'o') { // Sort the contacts
			sortContacts();
		} else if (command[0] == 'q') { // Quit
			printf("Complete\n");
			break;
		} else
			printf("Not a valid command\n");
	}
	return EXIT_SUCCESS;
}
