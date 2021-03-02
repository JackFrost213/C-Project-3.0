/*
 * array_functions.cpp
 *
 *  Created on: March 1, 2021
 *      Author: Hunter
 */

#include <algorithm>
#include "../includes/utilities.h"
#include "../includes/array_functions.h"
#include "../includes/fileio.h"

using namespace std;
using namespace constants;

namespace KP{
	//remove all elements from vector that tracks words and their occurrences
	void clear(std::vector<constants::entry>  &entries){
		vector<entry> new_arr;
		entries = new_arr;
	}

	//return how many unique words are in the vector
	int getSize(std::vector<constants::entry>  &entries){
		vector<string> temp;
		for(entry e : entries){
			if(std::find(temp.begin(), temp.end(), e.word) == temp.end()){
				temp.push_back(e.word);
			}
		}
		return temp.size();
	}

	//get word at location i iff i<size(see above function), otherwise return the last word
	//(this is lazy, should throw an exception instead)
	std::string getWordAt(std::vector<constants::entry>  &entries, int i){
		return entries.at(i).word;
	}

	//get number_occurences at location i iff i<size(see above function), otherwise return the last number_occurences
	//(this is lazy, should throw an exception instead)
	int getNumbOccurAt(std::vector<constants::entry>  &entries,int i){
		return entries.at(i).number_occurences;
	}

	/*loop through the entire file, one line at a time
	 * call processLine on each line from the file
	 * returns false: myfstream is not open
	 *         true: otherwise*/
	bool processFile(std::vector<constants::entry> &entries,std::fstream &myfstream){
		if(!myfstream.is_open())
			return false;

		string line;
		while(!myfstream.eof()){
			getline(myfstream, line);
			processLine(entries, line);
		}


		return true;
	}

	/*take 1 line and extract all the tokens from it
	feed each token to processToken for recording*/
	void processLine(std::vector<constants::entry>  &entries,std::string &myLine){
		stringstream ss(myLine);
		string tempToken;

		while(getline(ss, tempToken, CHAR_TO_SEARCH_FOR)){
			processToken(entries, tempToken);
		}
	}

	/*NOTE: first call strip_unwanted_chars from utilities to get rid of rubbish chars in the token
	 * if the token is an empty string after this then return since we are not tracking empty strings
	 *
	 * Keep track of how many times each token seen, in other words look thru the entries vector that
	 * holds entry structs to see if there is a struct that has entry.word==token,
	 * if so increment entry.number_occurences, otherwise create a new entry struct for the token,
	 * set entry.number_occurences=1 and add it to the entries vector*/
	void processToken(std::vector<entry>  &entries,std::string &token){
		bool found = false;
		strip_unwanted_chars(token);
		for(entry &e : entries){
			string upper_word = e.word;
			toUpper(upper_word);
			if(e.word == token || upper_word == token){
				e.number_occurences += 1;
				found = true;
			}
		}

		if(!found && token != ""){
			entry temp;
			temp.word = token;
			string upperToken = token;
			toUpper(upperToken);
			temp.word_uppercase = upperToken;
			temp.number_occurences = 1;
			entries.push_back(temp);
		}
	}

	bool compareEntriesA(const entry& x, const entry& y){
		string x_word_upper = x.word;
		toUpper(x_word_upper);

		string y_word_upper = y.word;
				toUpper(y_word_upper);

		if(x_word_upper.compare(y_word_upper) > 0)
			return false;

		//if(x.word.compare(y.word) <= 0)

		return true;
	}

	bool compareEntriesD(const entry& x, const entry& y){
		string x_word_upper = x.word;
				toUpper(x_word_upper);

				string y_word_upper = y.word;
						toUpper(y_word_upper);

				if(x_word_upper.compare(y_word_upper) <= 0)
					return false;

		//if(x.word.compare(y.word) > 0)

		return true;
	}

	bool compareEntriesNumOccurences(const entry& x, const entry& y){
			if(x.number_occurences > y.number_occurences)
				return true;

			//if(x.word.compare(y.word) > 0)

			return false;
		}

	/*
	 * Sort entries based on so enum value.
	 * Please provide a solution that sorts according to the enum
	 * The presence of the enum implies a switch statement based on its value
	 * See the course lectures and demo projects for how to sort a vector of structs
	 */
	void sort(std::vector<constants::entry>  &entries, constants::sortOrder so){
		if(so == NONE){
			return;
		}

		if(so == ASCENDING){
			std::sort(entries.begin(), entries.end(), compareEntriesA);
		}

		if(so == DESCENDING){
			std::sort(entries.begin(), entries.end(), compareEntriesD);
				}

		if(so == NUMBER_OCCURRENCES){
			std::sort(entries.begin(), entries.end(), compareEntriesNumOccurences);
		}
	}
}
