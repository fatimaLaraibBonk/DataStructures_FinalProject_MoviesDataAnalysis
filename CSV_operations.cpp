#include "CSV_operations.h"

void movielist::insert(movienode* node) {
    if (head == nullptr) {
        head = node;
        return;
    }
    movienode* temp = head;
    while (temp->next != nullptr){
        temp = temp->next;
    }
    temp->next = node;
}

int split(const string& line, string fields[]) {
    string curr = "";
    int currentindex = 0;

    for (int i = 0; i < line.length(); i++) {
        char newestcharacter = line[i];
        if (newestcharacter == ',') {
            // each field ends here
            fields[currentindex++] = curr;
            curr = "";
        }
        else{
            //form field
            curr += newestcharacter;
        }
    }
    fields[currentindex++] = curr;
    return currentindex;
}


void reader::read_file() {
    ifstream file("dataset.csv");
    if (!file.is_open()){
        // exp handle
        throw runtime_error("Can't open your CSV file :/");
    }
    movielist list;
    string line;
    //readline
    getline(file, line);
    while (getline(file, line)) {
        //skip empty
        if (line == ""){
            continue;
        }
        string fields[28];
        int count = split(line, fields);
        //check for matching field count
        if (count < 28){
            continue;
        }
        // new movie 
        movienode* node = new movienode();
        for (int i = 0; i < 28; i++) {
            node->fields[i] = fields[i];
        }
        list.insert(node);
    }
    file.close();
    cout << "CSV loaded to LL" << endl;
}
