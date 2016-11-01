// File: book.h
// Purpose: Header for declaration of books class and associated functions

#ifndef __book_h_
#define __book_h_

#include "genre_table.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "assert.h"

using namespace std;

typedef multimap<string, pair<std::string, int> >::const_iterator mapIter;

class Book {
public: 
	// Constructor
	Book() {}
    Book(std::string book_title, std::vector<std::string> book_description) {
    	book_title_ = book_title;
    	book_description_ = book_description;
    }

	// Assessors
	const std::string& book_title() const {return book_title_;}
	const std::vector<std::string>& book_description() const {return book_description_;}
	const std::unordered_map<string, int>& description_keyword_table() const {
		return keywords_hashtable_;
	}

	// helper functions:
	void construct_keywords_table(const multimap<string, pair<std::string, int> >& keyword_map);
	std::ostream& output_genre_scores(const multimap<string, pair<std::string, int> >& keyword_map,
		                              std::ostream& out_str);


private:
	std::string book_title_;
	std::vector<std::string> book_description_;
	/* keyword map of book description */
	std::unordered_map<string, int> keywords_hashtable_;

};

// Construct the hashtable for the keywords of description
// The keywords include one word and two continous words
void Book::construct_keywords_table(const multimap<string, pair<std::string, int> >& keyword_map) {
	if (keyword_map.find(book_description_[0]) != keyword_map.end())
		keywords_hashtable_[book_description_[0]]++;

	for (int i = 1; i < book_description_.size(); ++i) {
		string one_word = book_description_[i];
		string twos_words = book_description_[i - 1] + " " + book_description_[i];
		Genre_table gt;
		// Only put those useful keywords inside of keywords_hashtable_
		if (keyword_map.find(one_word) != keyword_map.end()) keywords_hashtable_[one_word]++;
		if (keyword_map.find(twos_words) != keyword_map.end()) keywords_hashtable_[twos_words]++;
		// If the keyword is a substring of the word, for example: fighting --> fight
		for (auto i = keyword_map.begin(); i != keyword_map.end(); ++i) {
			if (one_word.find(i->first) != std::string::npos
				&& one_word.size() != (i->first).size()) {
				keywords_hashtable_[i->first]++;
			}
		}
	}
}

// Helper function to output the genre scores results into ostream 
std::ostream& Book::output_genre_scores(const multimap<string, pair<std::string, int> >& keyword_map,
	                                    std::ostream& out_str) {
	
	construct_keywords_table(keyword_map);
	map<string, vector<pair<int, int> > > my_map;

	for (auto i = keywords_hashtable_.begin(); i != keywords_hashtable_.end(); ++i) {
		/* since we have duplicates of keywords, we need to use keyRange to find all of them */
		pair<mapIter, mapIter> keyRange = keyword_map.equal_range(i->first);
		for (auto j = keyRange.first; j != keyRange.second; ++j) {
			string keyword = (*j).second.first;
			int points = (*j).second.second;
		    vector<pair<int, int> > v = my_map[keyword];
		    v.push_back(make_pair(points, i->second));
			my_map[keyword] = v;
		}
	}
    out_str << book_title_ << endl;

    /* Output only the three highest scores */
    map<double, string> score_map;
    /* do the calculations */
	for (auto i = my_map.begin(); i != my_map.end(); ++i) {
		int sum = 0;
		int total_num = 0;
		vector<pair<int,int> > temp_v = i->second;
		int num = temp_v.size();

		for (int j = 0; j < temp_v.size(); ++j) {
			sum += temp_v[j].first;
			// cout << temp_v[j].first;
			total_num += temp_v[j].second;
		}
		double avg = double(sum) / double(num);
		double total_score = avg * total_num;
		score_map[total_score] = i->first;
	}
	int num_of_results = 3;
	for (auto i = score_map.rbegin(); i != score_map.rend() && num_of_results > 0; ++i) {
		out_str << i->second << "," << i->first << endl;
	    --num_of_results;
	}

	out_str << endl;
	out_str << endl;
	return out_str;
}

// Helper compare functions to sort all books in the vector<Book> v
bool alphabetically_first(const Book& book1, const Book& book2) {
	return (book1.book_title() < book2.book_title());
}

#endif
