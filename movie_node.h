//movie node class
#ifndef MOVIENODE_H
#define MOVIENODE_H
#include "linkedList.h"
class movieNode{
    private:
    string movieName;
    string directorName;
    linkedList actorsList;
    linkedList genresList;
    int height; //stores the height of the node, better then recursively checking for heights all times 
    double rating;
    int releaseYear;
    public:
    movieNode* left;
    movieNode* right;
    movieNode(){}
    movieNode(string name, string directorName, linkedList actorsList, linkedList genresList, double rating, int releaseYear);
    //copy constructor 
    movieNode(const movieNode& other) {
        this->movieName = other.movieName;
        this->directorName = other.directorName;
        this->actorsList = other.actorsList;   // make sure linkedList has proper copy assignment
        this->genresList = other.genresList;   // same here
        this->rating = other.rating;
        this->releaseYear = other.releaseYear;
        this->height = 0;
        this->left = nullptr;
        this->right = nullptr;
    }

    void display();
    string getMovieName() {
        return movieName;
    }
    int getHeight() {
        return height;
    }
    void setHeight(int height) {
        this->height = height;
    }
    movieNode* getRight() {
        return right;
    }
    movieNode* getLeft() {
        return left;
    }
    void setRight(movieNode* right) {
        this->right = right;
    }
    void setLeft(movieNode* left) {
        this->left = left;
    }
};

//movies list too
//AVL implementation-> easier access 
class moviesTree {
private:
    movieNode* root;
public:
    moviesTree() {
        root = nullptr;
    }
    //helper functions for avl trees
    int returnHeight(movieNode* root) {
        if (root == nullptr) return -1;
        int leftHeight = returnHeight(root->left);
        int rightHeight = returnHeight(root->right);
        return max(leftHeight, rightHeight) + 1;
    }
    //insertion code
    movieNode* insertNode(movieNode* root, movieNode* newNode) {
        if (root == nullptr) {
            //if root is empty, we insert at root
            newNode->setLeft(nullptr);
            newNode->setRight(nullptr);
            newNode->setHeight(0);
            return newNode;
        }
        if (newNode->getMovieName() < root->getMovieName()) {
            root->setLeft(insertNode(root->getLeft(), newNode));
            //cout << "Going left.." << endl;
            if (returnHeight(root->getLeft()) - returnHeight(root->getRight()) == 2) {
                if (newNode->getMovieName() < root->getLeft()->getMovieName()) {
                    //cout << "LL rotation" << endl;
                    root = LL(root);
                    //cout << "Rotation done" << endl;
                }
                else {
                    //cout << "RL rttation" << endl;
                    root = LR(root);
                    //cout << "Rotation done" << endl;
                }
                
            }
        }
        else if (newNode->getMovieName() > root->getMovieName()) {
            root->setRight(insertNode(root->getRight(), newNode));
            //cout << "Going right..." << endl;
            if (returnHeight(root->getRight()) - returnHeight(root->getLeft()) == 2) {
                if (newNode->getMovieName() > root->getRight()->getMovieName()) {
                    root = RR(root);
                }
                else {
                    root = RL(root);
                }
            }
        }
        else {
            // movie with the same title already exists
        }
        root->setHeight(max(returnHeight(root->getLeft()), returnHeight(root->getRight())) + 1);
        return root;
    }
    //search function code
    //input-> string, the function searches for that movie and returns it 
    movieNode* searchFunc(movieNode* root, const string &movieTitle) {
        if (root == nullptr) {
            //if nothing is stored then we return nullptr
            return nullptr;
        }
        if (movieTitle < root->getMovieName()) {
            //lecicotgraphhically 
            return searchFunc(root->getLeft(), movieTitle);
        }
        else if (movieTitle > root->getMovieName()) {
            return searchFunc(root->getRight(), movieTitle);
        }
        else {
            return root;
        }

    }
    //deletion code 
    movieNode* remove(movieNode* root, const string& movieTitle) {
        if (root == nullptr) {
            return nullptr;
        }
        //first we try to find the node we want to delete 
        if (movieTitle < root->getMovieName()) {
            root->setLeft(remove(root->getLeft(), movieTitle));
        }
        else if (movieTitle > root->getMovieName()) {
            root->setRight(remove(root->getRight(), movieTitle));
        }
        //when we do find it we need to 
        else {
            movieNode* tempNodePtr;
            //case 1 no right child (no child or only left child)
            if (root->getRight() == 0) {
                tempNodePtr = root;
                root = root->getLeft();
                delete tempNodePtr;
            }
            //case 2 no left child (only right child)
            else if (root->getLeft() == 0) {
                tempNodePtr = root;
                root = root->getRight();
                delete tempNodePtr;
            }
            //case 3 two children
            else {
                tempNodePtr = root->getRight();
                //go right then to the most bottom left
                while (tempNodePtr->getLeft()!=nullptr) {
                    tempNodePtr = tempNodePtr->getLeft();
                }
                tempNodePtr->setLeft(root->getLeft());
                tempNodePtr = root;
                root = root->getRight();
                delete tempNodePtr;
            }
        }

        if (root == 0) {
            return nullptr;
            //if only one node exixsts in tree
        }
        //setting new heights 
        root->setHeight(max(returnHeight(root->getLeft()), returnHeight(root->getRight())) + 1);
        //calculatign balancing factoe 
        int balance = returnHeight(root->getLeft()) - returnHeight(root->getRight());
        if (balance == 2) { 
            int leftBalance = returnHeight(root->getLeft()->getLeft()) - returnHeight(root->getLeft()->getRight()); 
            if (leftBalance >= 0) {
                root = LL(root); 
            } 
            else { root = RR(root); 
            } 
        }
        else if (balance == -2) { 
            int rightBalance = returnHeight(root->getRight()->getLeft()) - returnHeight(root->getRight()->getRight()); 
            if (rightBalance <= 0) { 
                root = RL(root); 
            } 
            else { 
                root = LR(root); 
            } 
        }
        //resetting height after rebalancing 
        root->setHeight(max(returnHeight(root->getLeft()), returnHeight(root->getRight())) + 1);
        return root;
    }

    //rotations code
    movieNode* LL(movieNode* K2) {
        //Rotation for left heavy 
        movieNode* K1 = K2->getLeft();
        K2->setLeft(K1->getRight());
        K1->setRight(K2);
        K2->setHeight(max(returnHeight(K2->getLeft()), returnHeight(K2->getRight())) + 1);
        K1->setHeight(max(returnHeight(K1->getLeft()), returnHeight(K1->getRight())) + 1);
        return K1;
    }

    //left rotation K2 (RR case).
    movieNode* RR(movieNode* K2) {
        //rotation for right heavy 
        movieNode* K1 = K2->getRight();
        K2->setRight(K1->getLeft());
        K1->setLeft(K2);
        K2->setHeight(max(returnHeight(K2->getLeft()), returnHeight(K2->getRight())) + 1);
        K1->setHeight(max(returnHeight(K1->getLeft()), returnHeight(K1->getRight())) + 1);
        return K1;
    }

    //rl double rotation
    movieNode* LR(movieNode* K3) {
        //LR CASE: left heavy, right heavy 
        K3->setLeft(RR(K3->getLeft()));
        return LL(K3);
    }

    //lr double rotation
    movieNode* RL(movieNode* K3) {
        //RL Case: rigth heavy then left heacy 
        K3->setRight(LL(K3->getRight()));
        return RR(K3);
    }
    //display function
    void preorder(movieNode* root) {
        if (root == nullptr) return;
        //root, left, right
        cout << root->getMovieName();
        preorder(root->left);
        preorder(root->right);
    }
    //ACTUAL FUNCTIONS 
    void insert(movieNode* newNode) {
        cout << newNode->getMovieName();
        //cout << "Inserting movie Node: ";
        //cout << newNode->getMovieName();
        //cout << endl;
        root=insertNode(root, newNode);
        cout << "Insertion done" << endl;
    }
    void display() {
        cout << "Displaying all movies: " << endl;
        preorder(root);
        cout << "Display done" << endl;
    }
    void deleteMovie(const string& movieName) {
        cout << "Deleting movie of name: " << endl;
        root=remove(root, movieName);
        cout << "Deletion done!" << endl;
    }
    movieNode* search(const string& movieName) {
        cout << "Searching for movie:  " << movieName << endl;;
        movieNode* tbs= searchFunc(root, movieName);
        tbs->display();
        return tbs;
    }
};
#endif 