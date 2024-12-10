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
    Node* next;
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

    // add customer to end of the line
    void enqueue(const string& personName, const string& beverage) {
        Node* newNode = new Node{personName, beverage, nullptr};    // create a new node
        // if not head meaning the queue is empty, both head and tail point to the new node which is the new customer
        if (!head) {
            head = tail = newNode;
        }
        // otherwise, if there is already a person in the line, then add the new node to the end. Update tail pointer
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // remove customer from the front of the line
    void dequeue() {
        
        if (!head) {
            return;  // if the queue is empty, no need to remove any customers
        }

        // remove a customer from the queue
        Node* temp = head;  // temp pointer to current node
        head = head->next;  // move head pointer up one position
        delete temp;        // delete where the temp node is pointing

        // if the queue is empty now, reset tail pointer
        if (!head) {
            tail = nullptr;
        }
    }

    // check if the queue is empty
    bool isEmpty() const {
        return head == nullptr;
    }

    // get the customer at the front of the line
    Node* checkFront() const {
        return head;
    }

};


// function declaration
void simulateRound(LinkedList& queue, const vector<string>& names, const vector<string>& drinks);


// main function
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
        string name = names[rand() % names.size()];      // gets a random name
        string drink = drinks[rand() % drinks.size()];   // gets a random drink  
        custQueue.enqueue(name, drink);                  // add a customer to the queue
    }

    // simulate queue, 10 rounds
    for (int round = 0; round < 10, round++;) {
        cout << "Round: " << round << ":\n";
        simulateRound(custQueue, names, drinks);         // coffee booth simulation
        cout << endl;
    }

    return 0;
}


// function definition
void simulateRound(LinkedList& queue, const vector<string>& names, const vector<string>& drinks) {
    
    // if the queue is not empty, serve the customer at the front
    if (!queue.isEmpty()) {
        Node* current = queue.checkFront();
        cout << current->custName << " has been served a " << current->bevOrder << ".\n";
        // remove customer from the queue
        queue.dequeue();
    } 
    // else, there is the queue is empty, nobody is in line
    else {
        cout << "No customers in line.\n";
    }

    // 50% probability that someone will join the queue
    if (rand() % 2 == 0) {
        string name = names[rand() % names.size()];      // gets a random name
        string drink = drinks[rand() % drinks.size()];   // gets a random drink  
        queue.enqueue(name, drink);                      // add a customer to the queue
        cout << "New customer: " << name << " joined the queue\n";
    }
    cout << endl;
}