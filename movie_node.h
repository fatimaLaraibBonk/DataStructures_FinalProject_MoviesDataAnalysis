//movie node class
#include "linkedList.h"
class movieNode{
    private:
    string movieName;
    string directorName;
    linkedList actorsList;
    linkedList genresList;
    double rating;
    int releaseYear;
    movieNode* left;
    movieNode* right;
    public:
    movieNode(){}
    movieNode(string name, string directorName, linkedList actorsList, linkedList genresList, double rating, int releaseYear);
    void display();
};