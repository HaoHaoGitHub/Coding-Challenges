// File: genre_table.h
// Purpose: Header for declaration of genre_table class and associated functions

#ifndef __genre_table_h_
#define __genre_table_h_


#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

class Genre_table {
public:
	// Constructor
	Genre_table() {}
	Genre_table(multimap<string, pair<string, int> > keyword_map, 
		        map<string, map<string, int> > genre_key_map) {
		keyword_map_ = keyword_map;
		genre_key_map_ = genre_key_map;
	}

	// Assessors
	void read_genre_csv(std::istream& in_str);
	const multimap<string, pair<string, int> > keyword_map() const {return keyword_map_;}
	const map<string, map<string, int> > genre_key_map() const {return genre_key_map_;}


private:
	/* mutimap all duplicates of the key values */
	std::multimap<std::string, std::pair<std::string, int> > keyword_map_;
	/* The following variavle is not used in this project, but is a good way to store the input informations */
	/* For future use */
	map<std::string, std::map<std::string, int> > genre_key_map_; 
};

// Helper function to read sample_genre_keyword_value.csv
// And store the data into a multimap
void Genre_table::read_genre_csv(std::istream& in_str){
    string line;
    int count = 0;
    while (getline(in_str, line)) {
    	if (++count == 1) continue; /* The first line is title */
    	stringstream ss(line);
    	string token;
    	vector<string> temp_line;
    	while (getline(ss, token, ',')) { /* get rid of the comma */
    		int start_index = 0;
    		int end_index = token.size() - 1;
    		/* Get rid of the white spaces at the beginning and end */
    		if (token[start_index] == ' ') start_index ++;
    		if (token[end_index] == ' ') end_index --;
    		temp_line.push_back(token.substr(start_index, end_index - start_index + 1));
    	}
    	/* keyword_map_ */
    	pair<string, int> tp = make_pair(temp_line[0], atoi(temp_line[2].c_str()));
    	keyword_map_.insert(make_pair(temp_line[1], tp));
    	/* genre_key_map_ */
    	map<string, int> tm = genre_key_map_[temp_line[0]];
    	tm[temp_line[1]] = atoi(temp_line[2].c_str());
        genre_key_map_[temp_line[0]] = tm;
    }
}


#endif