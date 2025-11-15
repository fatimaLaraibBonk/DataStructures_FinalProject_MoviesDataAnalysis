//15-11-2025
//CSV header file
//Huzaifa Rahman, Fatima Laraib
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdexcept>


using namespace std;

struct movienode {
    string fields[28];
    movienode* next;

    movienode() {
        next = nullptr;
    }
};

class movielist {
public:
    movienode* head;
    movielist() {
        head = nullptr;
    }
    void insert(movienode* node);
};


class reader {
public:
    void read_file();

private:
    int split(const string& line, string fields[]);
};