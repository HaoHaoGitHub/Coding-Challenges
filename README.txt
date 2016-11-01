Name: Hao Chen  
Email: chenh15@rpi.edu

Take-home challenge 
I use C++11 for this challenge.
=======================================================================================

1. Steps necessary to run my program
   1) g++ -std=c++11 main.cpp
   2) ./a.out sample_book_json.txt sample_genre_keyword_value.csv output.csv
      argv[0]       argv[1]                 argv[2]                 argv[3]
   3) open output.csv to see the results

2. Interesting trade-offs or edge cases you ran into
   trade-offs: see explanations below
   edge cases: see explanations below

3. Approximately how long you spent
   I spent around 2 hours to complete my first version and then spent extra 3 or 4 hours 
   to test and optimize my codes

========================================================================================
The following explains my codes logic and what data structures I was using: 
- Files:      
     File Name                           Description
      main.cpp                           main program
     genre_table.h       class stores information of sample genre keyword values
      book.h             class stores book informations, including book title and description
     read_json.h                stores read_json_txt helper functions

- Basic logic and data structures
1. I first read each book’s information into the Book object, and then store all books into a vector:

 +—————+—————+—————+——————————————
 |book1|book2|book3| . . . .           This vector contains all books’ information.
 +—————+—————+—————+——————————————

2. Then read the sample genre keyword values into genreTable object and store the information into a multimap:
(because there exists duplicates) 
The structure of the multimap is multimap<string, pair<string, int> > keyword_map;
i.e.   
  ==>   keyword           <genre,   points> 
     cerebral literary    <fiction, 7>
         death            <mystery, 8>
      distance future     <action, 4>
      distance future     <sci-fi, 8>
        dystopian         <sci-fi, 7>
        explosive         <mystery, 4>
       fast paced         <action, 7>
         fight            <action, 6>
       great man          <biography, 7>
       great women        <biography, 7>
       literary           <literary fiction, 9>
        murder            <mystery, 5>
        space             <sci-fi, 6>
       subplot            <literary fiction, 5> 

The reason I use this structure is that multimap have log(n) search time for keywords (n = # of keywords).

3. Loop over all books in the vector one by one and output the genre points result
   
   The book.output_genre_scores() member function:
    
   It firstly construct a hashtable containing all useful keywords in the description 
   and the # of times it occurs.  
   ==> std::unordered_map<string, int> keywords_hashtable_
   It basically contains all keywords (both one word and two continuous words): 

   e.g.    “In a not too distant future”, we have hash table like   
           ==>   In               1
                 a                1
                 not              1
                 too              1 
                 distant          1
                 future           1
                 In a             1
                 a not            1
                 not too          1
                 too distant      1
                 distant future   1

   The reason I use the hashtbale is because it has O(1) search, which is very fast.
   However, you might think it took too much space memory. 

   In order to reduce the space memory, I have used the following method:
   I only put the “useful keywords” inside of the hashtable. In other words, when I was looping 
   over the vector of description keywords, I first checked whether this keywords(or its substring) exists 
   in the genreTable (keyword map). If it exits, then put the keywords inside of the hashtable. 

   e.g. For the first book: Hunger Games, the hashtable of its descriptions is as follows:
             ==> distant future   1 
                 fight            2
        Then, we can calculate the genre score for “action” is [(4+6)/2]*(1+2) = 15. 

   Assume the number of words in the description is m, the order notation of getting the genre points for 
   each book is m * log(n). If the num of books is k. Then the total order notation is k * m * log(n). 

   ==> One thing I should mention is that: all the words of the description are stored in a vector<string>
       originally. The keywords_hashtable_ will only be constructed if I call the output_genre_scores() function. 
   
   
 
   Tradeoff: space-time tradeoff. As you can see above, I use a hashtable/maps to store the keywords information, 
             it improves the running speed a lot (especially when the input is very large). However, it takes 
             more space memory than only using an vector or array of strings. 
   
   Owing to the time limitation, I wrote my customized read_json_txt() function, It can only parse txt that has the same 
   format of the given one (you can not manually type in, you need to directly transfer the json format file to txt, 
   otherwise, you will see some weird symbols because of the difference of punctuations), and it also doesn’t take into 
   account an empty file. Besides, some of the functions, algorithms, and data structures are not the best ones. 
   If I were given more time, I would make it better. 

   edge cases: 
   1. The keywords can be the same among different genres
   2. The scores can be a double (not necessarily an int) 
   3. Not case sensitive. I used tolower() function 
   4. punctuations & white spaces
   5. If the count exceeds INT_MAX
   6. If the description exceeds the maximum length of string
   7. If the input files is empty()
   8. If there are too many books or if there are too many keywords
   9. If a book has no description or title




I appreciate you taking the time to review my materials.
 
Hao Chen 
Oct 11, 2016

   
   
   
   


   

   
        
  
   
     
     
                  
 














