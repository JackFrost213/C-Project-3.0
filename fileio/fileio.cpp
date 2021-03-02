/*
 * fileio.cpp
 *
 *  Created on: March 1, 2021
 *      Author: Hunter
 */

#include "../includes/fileio.h"
#include "../includes/utilities.h"

using namespace std;
using namespace constants;

/*if you are debugging the file must be in the project parent directory
  in this case Project2 with the .project and .cProject files*
  returns True - file opened successfully
          False - file not opened*/
bool openFile(fstream& myfile, const string& myFileName,
		ios_base::openmode mode){

	myfile.open(myFileName.c_str(), mode);

	if(!myfile.is_open())
		return false;

	return true;
}

/*iff myfile is open then close it*/
void closeFile(fstream& myfile){
	if(myfile.is_open()){
		myfile.close();
	}
}

/* serializes all content in entries to file outputfilename
 * check out utils for helpful type conversion functions
 * BTW serialize means the process of translating a data structure
 * into a format that can be stored in a file
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in the vector entries
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writetoFile(vector<entry>  &entries, const string &outputfilename){
	fstream myfile;
	ios_base::openmode mode = ios_base::out;
	bool check = openFile(myfile, outputfilename, mode);

	if(!check)
		return FAIL_FILE_DID_NOT_OPEN;

	if(entries.size() == 0)
		return FAIL_NO_ARRAY_DATA;

	for(entry e : entries){
		myfile << e.word + " " + intToString(e.number_occurences) << endl;
	}
	closeFile(myfile);

	return SUCCESS;
}
