//15-11-2025
//CSV header file
//Huzaifa Rahman, Fatima Laraib
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "hash.h"
#include "movie_node.h"
using namespace std;


class reader {
public:
    moviesTree moviesT;
    hashTableForActors hashTabA;
    int countForRecords;
    void read_file();
    int split(const string& line, string fields[]);
    reader() {
        countForRecords = 0;
    }
};