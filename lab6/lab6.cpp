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
        Node* removeElementsRecursive(Node* node, int val) {
            if (!node) return nullptr;
            node->next = removeElementsRecursive(node->next, val);
            if (node->data == val) {
                Node* temp = node->next;
                delete node;
                return temp;
            } else {
                return node;
            }
        }

        void removeElements(int val) {
            head = removeElementsRecursive(head, val);
        }

};

void readFromFile(LinkedList& list, string filename){
    ifstream inputfile(filename);
    while(!inputfile.eof()) {
        int temp;
        inputfile >> temp;
        list.addToEnd(temp);
    }
    inputfile.close();
}

void outputToFile(LinkedList& list, string filename){
    ofstream outputfile(filename);
    Node* temp = list.head;
    while(temp) {
        outputfile << temp->data << " ";
        temp = temp->next;
    }
    outputfile.close();
}

int main(int argc, char *argv[]){
    // ./lab6 input.txt 5 output.txt
    if (argc != 4) {
        cout << "Invalid Arguments";
        exit(1);
    }

    LinkedList list;
    int valueToRemove = strtol(argv[2], nullptr, 0);
    readFromFile(list, argv[1]);
    list.removeElements(valueToRemove);
    outputToFile(list, argv[3]);
}