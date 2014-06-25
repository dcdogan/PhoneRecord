#include "fileoperations.h"



void File::add(Phone_Record *nrptr){
	fseek(phonebook, 0, SEEK_END);
	fwrite(nrptr, sizeof(Phone_Record), 1, phonebook);
}

void File::create(){	
	filename = "/Users/DoganCan/Desktop/PracticeExercise1/phonebook.txt";
	phonebook = fopen( filename, "r+" );
	if(!phonebook){		
		if(!(phonebook = fopen( filename, "w+" ))){
			cerr << "Cannot open file" << endl;
			exit(1);
		}
	}
}

void File::close(){
	fclose(phonebook);
}

int File::search(char *desired){
	Phone_Record k;
	int index=0;
	bool all=false;
	int found=0;
	if(strcmp(desired,"*")==0)
		all=true;
	fseek(phonebook, 0, SEEK_SET);
	while(!feof(phonebook)){		
		index++;
		fread( &k, sizeof (Phone_Record), 1, phonebook);		
		if(feof(phonebook)) break;

		if(all || strncmp(k.name, desired, strlen(desired))==0){
			cout << index << "." << k.name << " " << k.phonenum << endl;
			found++;
		}
	}	
	return found;
}

void File::update(int recordnum, Phone_Record *nrptr){
	if(fseek(phonebook, sizeof(Phone_Record)*(recordnum-1), SEEK_SET)==0)
		fwrite(nrptr, sizeof(Phone_Record), 1, phonebook);
}

void File::remove(int recordnum){
	Phone_Record emptyrecord={"",""};	
	if(fseek(phonebook, sizeof(Phone_Record)*(recordnum-1), SEEK_SET)==0)
		fwrite(&emptyrecord, sizeof(Phone_Record), 1, phonebook);
    
    moveToTemp();
}


void File::moveToTemp(){
    
    Phone_Record myRecord ;

    
    FILE* tempRecords ;
    char tempFile[] =  "/Users/DoganCan/Desktop/PracticeExercise1/tempRecords.txt";
    
    tempRecords = fopen(tempFile, "w++");
    
    fseek(phonebook, 0, SEEK_SET);
    fseek(tempRecords, 0, SEEK_SET);
    
    while(!feof(phonebook)){
		
        fread( &myRecord, sizeof (Phone_Record), 1, phonebook);
        if(feof(phonebook)) break;
        
        if(!(strcmp(myRecord.name, "") == 1)){
            fseek(tempRecords, 0, SEEK_END);
            fwrite(&myRecord, sizeof(Phone_Record), 1, tempRecords);
        }
		
	}

    fseek(phonebook, 0, SEEK_SET);
    fseek(tempRecords, 0, SEEK_SET);
    
    while(!feof(tempRecords)){
		
        fread( &myRecord, sizeof (Phone_Record), 1, tempRecords);
        if(feof(tempRecords)) break;
        fseek(phonebook, 0, SEEK_END);
        fwrite(&myRecord, sizeof(Phone_Record), 1, phonebook);
		
	}
    
}







