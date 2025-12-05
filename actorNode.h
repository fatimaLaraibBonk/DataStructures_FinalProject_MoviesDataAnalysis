#include <iostream>
#include "linkedList.h"
#include "movie_node.h"
using namespace std;

class actorNode {
public:
	//data needeed
	string actorName;
	moviesTree moviesOfActor; //stores those movies that the actor has acted in in a linked list 
	//now initially we are planning to store actors in a hash table 
	//so we need a next pointer
	actorNode* next;
	actorNode(){}
	actorNode(string name) {
		actorName = name;
		next = nullptr;
	}
	void addMovie(movieNode* movie); //this function receives movies that the actor has acted on		
	void display(); //display the actors name along with the movies they have acted in 


};
//actor node header class
