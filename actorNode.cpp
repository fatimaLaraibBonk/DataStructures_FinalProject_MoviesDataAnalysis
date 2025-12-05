#include "actorNode.h"
using namespace std;

//actorNode cpp file

void actorNode::addMovie(movieNode* movie) {
	//adds movie to the movie node tree
	//movie insertion is not wokring 
	this->moviesOfActor.insert(movie); //this part inserts the movie in the tree 
	//cout << "Movie added for " << actorName << ": ";
	movie->getMovieName();
	//cout << endl;
}
void actorNode::display() {
	//displays movies for that actor 
	cout << "All movies by actor: " << actorName << ": ";
	moviesOfActor.display();
}

