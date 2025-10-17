#include <iostream>
#include <fstream> // for file opening
#include <string>
#include <vector>
#include <cstdlib> // for random
#include <ctime> // reset rand seed every run


using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        string data; // take names not numbers
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(string value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }



    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    // checks if the linked list is empty
    bool empty()
    {
        return head == nullptr; // gives true is list is empty
    }

    int size()
    {
        int count = 0;
        Node* temp = head;
        while (temp)
        {
            count++; // add 1 with each loop
            temp = temp->next;
        }
        return count; // returns the size
    }

    string get_val(int pos)
    {
        Node* temp = head
    }

    string front() {return head ? head->data : "";} // gets the first element
    string back() {return tail ? tail->data : "";} // gets the last element -> needed to handle serving and other thigns
};


// func protos
vector<string> getNames(const string& filename); // read the file
string randName(const vector<string>& names); // generates a random name from the file
void initialCustomers(DoublyLinkedList& line, const vector<string> names); // generate first 5 customers
void serveCustomer(DoublyLinkedList& line); // will serve the frontmost customer
void customerLeft(DoublyLinkedList& line); // will handle the last customer leaving
void randomLeave(DoublyLinkedList& line); // random customer leaving
void newCustomer(DoublyLinkedList& line, const vector<string> names); // adds new customer




int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    // customer status generation here
    
    return 0;
}

// reads the file
vector<string> getNames(const string& filename)
{
    vector<string> names; // name vector
    ifstream file(filename);

    string name; 
    while (getline(file, name))
    {
        if (!name.empty()) // check if line is not blank
            names.push_back(name);
    }
    return names;
}

// returns a unique name given some vector
string randName(const vector<string>& names)
{
    int index = rand() % names.size(); // generate a random index from 0 to the length of names
    return names[index]; // return the name
}

void initialCustomers(DoublyLinkedList& line, const vector<string> names)
{
    for (int i = 0; i < 5; i++)
    {
        string name = randName(names); // generate a name
        line.push_back(name);  // add to linked list
        cout << "\t" << name << " joins the line." << endl;
    }
    cout << "\tResulting line: " << endl; // formatting
    line.print(); // output all the names (current state of the line)
}

void serveCustomer(DoublyLinkedList& line)
{
    if (line.empty()) {return;} // return if there are no customers to serve
    cout << "\t" << line.front() << " is served." << endl;
    line.pop_front(); // remove front customer
}

void customerLeft(DoublyLinkedList& line)
{
    if (line.empty()) {return;} // return if there are no customers to serve
    cout << "\t" << line.back() << " (at the rear) gets frusturated and leaves" << endl;
    line.pop_back(); // remove last customer
}

void randomLeave(DoublyLinkedList& line)
{
    int SIZE = line.size();
    int pos = rand() % SIZE + 1;
    if (pos == 1 || pos == SIZE) {return;} // handled in different functions
    line.delete_pos(pos);

}

void newCustomer(DoublyLinkedList& line, const vector<string> names)
{
    string name = randName(names); // generate new customer
    line.push_back(name);
    cout << "\t" << name << " joins the line" << endl;
}










