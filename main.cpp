#include <iostream>
#include "CSV_operations.h"
#include "linkedList.h"

using namespace std;
//flow of code: 
//FIRST ITERATION
//first we parse the file and make movieNodes
//actor nodes made using hashing, each actor node has its own tree of movies
//HASH TABLE FOR ACTORS DONE 
//SECOND ITERATION
//ACTORS HASH AND ACTOR LOOKUP DONE
//MOVIE LOOK UP VIA TREE
//THIRD ITERATION

int main() {
    reader r;
    r.read_file();
    //search by actor
    //search by movie
    //search by genre
    //search by acting range
    while (true) {
        cout << "Search movie by name: " << endl;
        string movieName;
        getline(cin, movieName);
        //find actor name and tell all the movie they have been in 
        //we have the has ready we just need to search 
        r.hashTabA.search(movieName);

    }
    return 0;
}
