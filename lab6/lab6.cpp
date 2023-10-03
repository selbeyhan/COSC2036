#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Node{
    int data;
    Node* next;
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

class LinkedList {
    public:
        Node* head;
        LinkedList() {
            head = nullptr;
        }
        void addToEnd(int data){
            if (!head) {
                head = new Node(data);
                return;
            }
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = new Node(data);
        }
};

void readFromFile(LinkedList& list, string filename){
    ifstream inputfile(filename);
    while(!inputfile.eof()) {
        int temp;
        inputfile >> temp;
        list.addToEnd(temp);
    }
}

int main(int argc, char *argv[]){
    // ./lab6 input.txt 5 input.txt
    if (argc != 4) {
        cout << "Invalid Arguments";
        exit;
    }

    LinkedList list;
    readFromFile(list, argv[1]);
}