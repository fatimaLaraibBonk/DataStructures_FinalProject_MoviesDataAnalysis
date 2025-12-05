#include "movie_node.h"

movieNode::movieNode(string name, string directorName, linkedList actorsList, linkedList genresList, double rating, int releaseYear){
    this->movieName=name;
    this->directorName=directorName;
    this->actorsList=actorsList;
    this->genresList=genresList;
    this->rating=rating;
    this->releaseYear=releaseYear;
    this->height = 0;
    this->left=nullptr;
    this->right=nullptr;
}
void movieNode::display(){
    cout<<"Displaying Movie Information: "<<endl;
    cout<<"Name: "<<this->movieName<<endl;
    cout<<"Director's name: "<<this->directorName<<endl;
    cout<<"Actors Involved: "<<endl;
    this->actorsList.display();
    cout<<"Genres: "<<endl;
    this->genresList.display();
    cout<<"Rating: "<<this->rating<<endl;
    cout<<"Release Year: "<<this->releaseYear<<endl;
}