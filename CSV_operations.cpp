#include "CSV_operations.h"
#include "linkedList.h"
#include "movie_node.h"
//the file will only be read once and every time the actor name has an index deddicated to it using hash
//now if the name already exists, we'll just add the movieNode to their name
//and if they dont well create a new node for them and check for collisions 
//same for genres
int reader::split(const string& line, string fields[]) {
    //cout << "Spliting..." << endl;
    string curr = "";
    int currentindex = 0;
    //ISSUE ENCOUNTERED: some movie names have commas in them so we need to parse them more carefully 
    //"Crazy, Stupid, Love. "
    for (int i = 0; i < line.length(); i++) {
        char newestcharacter = line[i];
        if (line[i] == '"') {
            //if quotations are encountered then we parsecarefuly
            //basically we read until the next quotation is encountered
            i++;
            curr += line[i]; //store the first letter
            i++;
            while (line[i] != '"') {
                curr += line[i];
                i++;
            }
            //when it is encountrerd again skipit
            i++;
            fields[currentindex++] = curr;
            curr = "";
            continue;
        }
        if (newestcharacter == ',') {
            //each field ends here
            fields[currentindex++] = curr;
            curr = "";
        }
        else {
            //form field
            curr += newestcharacter;
        }
    }
    fields[currentindex++] = curr;
    //cout << "Splitting ended..." << endl;
    return currentindex;
}

void reader::read_file() {
    cout << "Reading file..." << endl;
    ifstream file("dataset.csv");
    if (!file.is_open()) {
        //exp handle
        throw runtime_error("Can't open your CSV file :/");
    }
    string line;
    //readline
    getline(file, line); //reads the first header line from the file
    //we dont need it 
    int movieNodesMade = 0;
    while (getline(file, line)) {
        //skip empty
        countForRecords++;
        //cout << "Records read: " << countForRecords << endl;
        if (line == "") {
            //cout << "Missing values..." << endl;
            continue;
        }
        string fields[28]; //stores each data element in the line 
        int count = split(line, fields); //each field stores data 
        //the data we do need is 
        //string movieName;
        //string directorName;
        //linkedList actorsList;
        //linkedList genresList;
        //double rating;
        //int releaseYear;
        //
        //check for matching field count
        if (count < 28) {
            //cout << "Missing values.." << endl;
            continue;
        }
        movieNodesMade++;
        //new movie 
        //if all the neccessary values are present we need to put them in our movie node 
        //linked list for actors and genres
        //cout << "Creating linked lists..." << endl;

        //forcefully cleaning the name
        if (fields[11].size() > 2) {
            fields[11].erase(fields[11].size() - 2, 2);
        }

        linkedList actors;
        linkedList genres;
        //cout << "Linked lists created..." << endl;

        //node for each linked list is a simple node
        //genres-> exist as a list like Action|Adventure|Fantasy|Sci-Fi
        //so we must parse it as well for that we can use sstream

        //genres index-> 9
        stringstream ss(fields[9]);
        string genre = "";
        while (getline(ss, genre, '|')) {
            genres.insert(new node(genre));
        }
        //cout << "Genres entered.." << endl;

        //and actors names are indexes 6, 14, 10
        node* actor1 = new node(fields[10]);
        node* actor2 = new node(fields[6]);
        node* actor3 = new node(fields[14]);

        //now we insert them into our linked list
        actors.insert(actor1);
        actors.insert(actor2);
        actors.insert(actor3);
        //cout << "actors inserted..." << endl;
        //we have a linked list for movies and genres
        //now we create a movienode 
        //string name, string directorName, linkedList actorsList, linkedList genresList, double rating, int releaseYear
        double rating = atof(fields[25].c_str());
        int releaseYear = atoi(fields[23].c_str());
        
        movieNode* movie = new movieNode(fields[11], fields[1], actors, genres, rating, releaseYear);
        movieNode* movieForTree = new movieNode(*movie);
        //cout << "Total movie nodes: " << movieNodesMade << endl;
        moviesT.insert(movieForTree); //seprate becasue inserting the same node in tewoplaces 2was messing with the left/right pointers
        //now that we have actor name and movie node we can make a moie node for 
        hashTabA.insertInHash(fields[10], movie);
        hashTabA.insertInHash(fields[6], movie);
        hashTabA.insertInHash(fields[14], movie);

    }
    hashTabA.display();
    file.close();
    cout << "CSV loaded to LL" << endl;
}


