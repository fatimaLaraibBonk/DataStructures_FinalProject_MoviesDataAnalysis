#ifndef HASH_H
#define HASH_H
#include "movie_node.h"
#include "actorNode.h"
//in hash we need to store actor
class hashTableForActors{
    int tableSize;
    actorNode** hashArray;
    public:
    hashTableForActors() {
       cout << "Creating hash table for actors: " << endl;
       tableSize = 7507; //prime hashing to lessen number of collisions 
       hashArray = new actorNode*[tableSize]();
       for (int i = 0; i < tableSize; i++) {
           hashArray[i] = nullptr;
       }
    }
    int hashFunc(string data) {
        //recieves either actor name or genre and retuns a hash value for it 
        int length = data.size();
        int hashVal = length % tableSize;
        return hashVal;
    }
    void insertInHash(const string& name, movieNode* movie) {
        //recieves weither actor node, or normal node for a linked along witht the movie nod e
        //function inserts value in hash 
        int hashVal = hashFunc(name);
        if (hashArray[hashVal] == nullptr) {
            hashArray[hashVal] =new actorNode(name);
            //for this certain actor we append the movie 
            hashArray[hashVal]->addMovie(movie);
            return;
        }
        //basically if its the same actor -> we need to append the movie node to their name
        //and if its the same genre-> we also need to append the movie node to that name
        //for handling genre information we require a genre node, where we have the genre name and the list of movies belonging to that genre  
        if (hashArray[hashVal]->actorName == name) {
            hashArray[hashVal]->addMovie(movie);
            return;
        }
        //else if collision then we append it to next
        actorNode* temp = hashArray[hashVal];
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = new actorNode(name);
        temp->addMovie(movie);
        return;

    }
    void deleteFromHash(string data) {
        //this function deletes value from hash 
        //deletes by value 
    }
    actorNode* search(string const& name) {
        //function searches up a value from hash and returns 
        int hashVal = hashFunc(name);
        if (hashArray[hashVal] == nullptr) {
            cout << "This actor does not exist in the database." << endl;
            return nullptr;
        }
        else {
            actorNode* ats = hashArray[hashVal];
            while (ats != nullptr && ats->actorName != name)
                ats = ats->next;
            if (ats == nullptr) {
                cout << "This actor does not exist in the database" << endl;
                return nullptr;
            }
            cout << "Actor Details: " << endl;
            ats->display();
            return ats;
        }
    }
    void display() {
        //displays full hash->using it for debugging purposes
        for (int i = 0; i < tableSize; i++) {
            if (hashArray[i] == nullptr) continue;
            actorNode* temp = hashArray[i];
            while (temp != nullptr) {
                cout << temp->actorName << endl;
                //displaying all movies the avtors have been in 
                temp->display();
                temp = temp->next;
            }
        }
    }
    ~hashTableForActors() {
        cout << "Freeing memory from hash" << endl;
        delete[] hashArray;
    }
};
#endif 