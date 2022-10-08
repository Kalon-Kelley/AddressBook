#ifndef ADDRESSBOOK_H_
#define ADDRESSBOOK_H_

typedef struct person Person; // structure type definition for person structure
struct person{ // person structure with 6 fields 4 strings and 2 person pointers.
	char last_name[256];
	char first_name[256];
	char email[256];
	char phone_number[256];
	Person* next;
	Person* prev;
};

// function declarations for addressBook.c file
Person *createPerson(char *last, char *first, char *email, char *phone);
void addContact(int index, char *contact);
void deleteContact(int index);
void getContact(int index);
void getField(int index, char *field);
void getNumber();
void loadFromFile(char *path);
void saveToFile(char *path);
void editContact(int index, char *field, char *newVal);
void sortContacts();
int compareFunc(const void* a, const void* b);

#endif /* ADDRESSBOOK_H_ */
