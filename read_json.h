// File: read_json.h
// Purpose: helper functions for reading the json text file

#include "book.h"
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <map>
#include "assert.h"


using namespace std;

/* Helper functions */
void read_json_txt(vector<Book>& books, std::istream& in_str);
vector<string> get_content(int start_index, const string& line, const string& type);


/* helper function to prase the json text file */
/* If it was a true json file, we could use "jsoncpp" library to handle it */
/* In this project, I just use my cusomized json parser */
void read_json_txt(vector<Book>& books, std::istream& in_str) {
    string line;
    string book_title = "";

    while (getline(in_str, line)) { // Scan by lines
        if (line.empty()) continue; 
    	char fc = line[0];
    	if (fc == '[' || fc == ']' || fc == '{' || fc == '}') continue;
    	string first_word = "";
    	int start_index = 0;
    	int end_index = 0;
    	bool first_time = true;
    	/* Get the first word within " " of each line */
    	for (int i = 0; i < line.size(); ++i) {
    		if (line[i] == ' ') continue;
    		if (line[i] == '\"' && first_time) {
    			start_index = i;
    			first_time = false;
    		}
    		if (line[i] == ':') {
    			end_index = i;
    			break;
    		}
    	}
    	first_word = line.substr(start_index + 1, end_index - start_index - 2);
    	end_index++;
    	vector<string> content = get_content(end_index, line, first_word); /* get descriptions */
    	if (first_word == "title") book_title = content[0];
    	if (first_word == "description") {
    		Book book(book_title, content);
    		books.push_back(book);
    		book_title = "";
    	} 
    }
}


/* Helper function for read_json_file() */
/* Read the descriptions (without punctuation and white spaces) into a vector<string> */
vector<string> get_content(int start_index, const string& line, const string& type) {
	string s = "";
	vector<string> content;
	start_index += 2;
	s = line.substr(start_index, line.size() - start_index - 2);
    if (type == "title") {
    	content.push_back(s);
    	return content;
    }
    assert(type == "description"); 
    // Get rid of all punctuation 
	for (int i = 0; i < s.size(); ++i) 
		if (ispunct(s[i])) s[i] = ' ';
	stringstream ss(s);
	string token;
	while (getline(ss, token, ' ')) {
		int count = 0;
		// get rid of white spaces
		for (int i = 0; i < token.size(); ++i) { 
			if (token[i] != ' ') {
				/* convert uppercase letter to lowercase*/
				/* we assume keyword search is not case sensitive */
			    token[count++] = tolower(token[i]);
			} 
		}
		if (count != 0) content.push_back(token.substr(0, count));
	}	
	return content;
}