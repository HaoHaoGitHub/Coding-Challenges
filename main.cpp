// Name: Hao Chen chenh15@rpi.edu
// File: main.cpp

#include "genre_table.h"
#include "read_json.h"
#include "book.h"

using namespace std;


/* Main function */
int main (int argc, char* argv[]) {
	if (argc != 4) {
		cerr << "Usage:\n" << argv[0] << " infile-matchs outfile-statitics\n ";
		return 1;
	}
	ifstream instr1(argv[1]);
	if (!instr1) {
		std::cerr << " Could not open " << argv[1] << " to read\n ";
        return 1;
	}
	ifstream in_str2(argv[2]);
	if (!in_str2) {
		std::cerr << " Could not open " << argv[2] << " to read\n ";
        return 1;
	}
	ofstream out_str(argv[3]);
	if (!out_str) {
		std::cerr << " Could not open " << argv[3] << " to write\n ";
        return 1;
	}

    // read books' information from sample_book_json.txt
    vector<Book> books;
	read_json_txt(books, instr1);
	cout << "The number of books is: " << books.size() << endl;

	// read genres from sample_genre_keyword_value.csv 
    Genre_table genreTable;
	genreTable.read_genre_csv(in_str2);

	auto keyword_map = genreTable.keyword_map();
    sort(books.begin(), books.end(), alphabetically_first);
	// Output the top three genre scores of a book
	for (int i = 0; i < books.size(); ++i) {
		Book book = books[i];
		book.output_genre_scores(keyword_map, out_str);
	}

	return 0;
}






