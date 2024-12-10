// COMSC-210 | Mauricio Espinosa | Final Part 1

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// customer struct to hold name and beverage order
struct Node {
    string custName;
    string bevOrder;
};

// linked list for the line/queue
class LinkedList {
private:
    Node* head;  // pointer to the front of the queue
    Node* tail;  // pointer to the back of the queue

public:
    // constructor initializing head and tail to nullptr
    LinkedList() : head(nullptr), tail(nullptr) {}

    // destructor
    ~LinkedList() {
        while (head) {
            Node* temp = head;  // temp pointer to current node
            head = head->next;  // move head pointer up one position
            delete temp;        // delete where the temp node is pointing
        }
    }
};



int main() {

    // seed random
    srand(time(0));

    // vector of sample customer names and beverage options
    vector<string> names = {"Mauricio", "Mochi", "Danielle", "Patricia", "John", "Matt"};
    vector<string> drinks = {"Latte", "Mocha", "Hot Chocolate", "Espresso", "Soda", "Flat White"};

    // linked list for the actual queue
    LinkedList custQueue;

    // initialize the queue with 3 random customers
    for (int i = 0; i < 3; i++) {
        string name = names[rand() % names.size()];
        string drink = drinks[rand() % drinks.size()];
    }



    return 0;
}