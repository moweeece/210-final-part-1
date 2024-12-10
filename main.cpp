// COMSC-210 | Mauricio Espinosa | Final Part 1

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <deque>    // for muffin booth
using namespace std;

// Coffee customer struct to hold name and beverage order
struct coffeeNode {
    string custName;
    string bevOrder;
    coffeeNode* next;
};

// linked list for the line/queue
class LinkedList {
private:
    coffeeNode* head;  // pointer to the front of the queue
    coffeeNode* tail;  // pointer to the back of the queue

public:
    // constructor initializing head and tail to nullptr
    LinkedList() : head(nullptr), tail(nullptr) {}

    // destructor
    ~LinkedList() {
        while (head) {
            coffeeNode* temp = head;  // temp pointer to current node
            head = head->next;  // move head pointer up one position
            delete temp;        // delete where the temp node is pointing
        }
    }

    // add customer to end of the line
    void enqueue(const string& personName, const string& beverage) {
        coffeeNode* newNode = new coffeeNode{personName, beverage, nullptr};    // create a new node
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
        coffeeNode* temp = head;  // temp pointer to current node
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
    coffeeNode* checkFront() const {
        return head;
    }

};


// Muffin customer struct to hold name
struct muffinNode {
    string muffinCust;
};

// Friendship bracelet customer struct to hold name
struct braceletNode {
    string braceletCust;
};


// function declaration
void simulateCoffeeRound(LinkedList& queue, const vector<string>& names, const vector<string>& drinks);
void simulateMuffinRound(deque<muffinNode>& muffinLine, const vector<string>& muffinNames);
void simulateBraceletRound(vector<braceletNode>& braceletLine, const vector<string>& braceletNames);


// main function
int main() {

    // seed random
    srand(static_cast<unsigned>(time(0)));

    // vector of sample customer names and beverage options
    vector<string> names = {"Mauricio", "Mochi", "Danielle", "Patricia", "John", "Matt"};
    vector<string> drinks = {"Latte", "Mocha", "Hot Chocolate", "Espresso", "Soda", "Flat White"};
    // vector for bracelet names
    vector<string> braceletNames = {"Art", "Megan", "Freddy", "Jason", "Jack", "Chucky"};

    // linked list for the actual queue
    LinkedList coffeeQueue;

    // Deque for muffin booth
    deque<muffinNode> muffinQueue;

    // vecotr for friendship booth
    vector<braceletNode> braceletQueue;    

    // initialize the coffee queue with 3 random customers
    for (int i = 0; i < 3; i++) {
        string name = names[rand() % names.size()];      // gets a random name
        string drink = drinks[rand() % drinks.size()];   // gets a random drink  
        coffeeQueue.enqueue(name, drink);                  // add a customer to the queue
    }

    // initialize the muffin queue with 3 random customers
    for (int j = 0; j < 3; j++) {
        string muffinName = names[rand() % names.size()];            // gets a random name
        muffinQueue.push_back(muffinNode{muffinName});                // add a customer to the queue
    }

    // initialize the bracelet queue with 3 random customers
    for (int k = 0; k < 3; k++) {
        string braceletName = braceletNames[rand() % braceletNames.size()];      // gets a random name
        braceletQueue.push_back(braceletNode{braceletName});                    // add a customer to the queue
    }

    // simulate queue, 10 rounds
    for (int round = 0; round < 10, ++round;) {
        cout << "Round: " << round << ":\n";
        simulateCoffeeRound(coffeeQueue, names, drinks);         // coffee booth simulation
        simulateMuffinRound(muffinQueue, names);                 // muffin booth simulation
        simulateBraceletRound(braceletQueue, names);                 // muffin booth simulation
        cout << endl;
    }

    return 0;
}


// function definition
void simulateCoffeeRound(LinkedList& coffeeLine, const vector<string>& coffeeNames, const vector<string>& drinks) {
    
    // seed random
    srand(static_cast<unsigned>(time(0)));
    
    cout << "Coffee Booth: \n"; 
    // if the queue is not empty, serve the customer at the front
    if (!coffeeLine.isEmpty()) {
        coffeeNode* current = coffeeLine.checkFront();
        cout << current->custName << " has been served a " << current->bevOrder << ".\n";
        // remove customer from the queue
        coffeeLine.dequeue();
    } 
    // else, there is the queue is empty, nobody is in line
    else {
        cout << "No customers in line.\n";
    }

    // 50% probability that someone will join the queue
    if (rand() % 2 == 0) {
        string name = coffeeNames[rand() % coffeeNames.size()];      // gets a random name
        string drink = drinks[rand() % drinks.size()];   // gets a random drink  
        coffeeLine.enqueue(name, drink);                      // add a customer to the queue
        cout << "New customer: " << name << " joined the coffee queue\n";
    }
    cout << endl;
}

void simulateMuffinRound(deque<muffinNode>& muffinLine, const vector<string>& muffinNames) {
    
    // seed random
    srand(static_cast<unsigned>(time(0)));
    
    cout << "Muffin Booth: \n"; 
    // if the queue is not empty, serve the customer at the front
    if (!muffinLine.empty()) {
        string muffinCustServed = muffinLine.front().muffinCust;
        cout << muffinCustServed << " has been served a muffin!\n";

        // remove customer from the queue
        muffinLine.pop_front();
    } 
    // else, there is the queue is empty, nobody is in line
    else {
        cout << "No customers in line.\n";
    }

    // 50% probability that someone will join the queue
    if (rand() % 2 == 0) {
        string muffinName = muffinNames[rand() % muffinNames.size()];      // gets a random name 
        muffinLine.push_back(muffinNode{muffinName});                                  // add a customer to the queue
        cout << "New customer: " << muffinName << " joined the muffin queue\n";
    }
    cout << endl;

}


void simulateBraceletRound(vector<braceletNode>& braceletLine, const vector<string>& braceletNames) {
    
    // seed random
    srand(static_cast<unsigned>(time(0)));
    
    cout << "Friendship Bracelet Booth: \n"; 
    // if the queue is not empty, serve the customer at the front
    if (!braceletLine.empty()) {
        string braceletCustServed = braceletLine.front().braceletCust;
        cout << braceletCustServed << " has been served a muffin!\n";

        // remove customer from the queue
        braceletLine.erase(braceletLine.begin());
    } 
    // else, there is the queue is empty, nobody is in line
    else {
        cout << "No customers in line.\n";
    }

    // 50% probability that someone will join the queue
    if (rand() % 2 == 0) {
        string braceletName = braceletNames[rand() % braceletNames.size()];      // gets a random name 
        braceletLine.push_back(braceletNode{braceletName});                                  // add a customer to the queue
        cout << "New customer: " << braceletName << " joined the muffin queue\n";
    }
    cout << endl;

}