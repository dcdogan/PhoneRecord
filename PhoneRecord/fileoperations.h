#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "record.h"

using namespace std;


struct File{
	char* filename;
	FILE *phonebook;
	void create();
	void close();
	void add(Phone_Record *);
	int search(char []);
	void remove(int recordnum);
	void update(int recordnum, Phone_Record *);
    void moveToTemp();
};
#endif
