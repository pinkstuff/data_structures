// Program to help me understand Linked Lists
#include <iostream>
#include <string>

using namespace std;

class Node {
    public:
    int data;
    Node *next;

    Node(int arg) {
        data = arg;
        next = nullptr;
    }
};

class LinkedList {
    private:
    Node *_last(Node *node){
        if (node->next == nullptr){
            return node;
        }
        return _last(node->next);
    }

    public:
    Node *head = nullptr;

    LinkedList() {}

    LinkedList(int args[], int length){
        // Contruct from array to make life a little bit easier
        // set head to be pointer to first node first node
        head = new Node(args[0]);
        Node *new_node;
        Node *prev;
        prev = head;
        for (int index=1; index<length; index++){
            // set all the others if they exist
            new_node = new Node(args[index]);
            prev->next = new_node;
            prev = prev->next;
        }
    }

    string repr(){
        if (head == nullptr){
            return "- -";
        }
        string output = "";
        string number;
        Node *current = head;
        while (current->next != nullptr){
            number = to_string(current->data);
            output += number + " --> ";
            current = current->next;
        }
        output += to_string(current->data);
        return output;
    }

    void append(int value){
        Node *new_node = new Node(value);
        if( head == nullptr){
            // First element in list
            head = new_node;
        } else {
            Node *old_last = _last(head);
            old_last->next = new_node;
        }
    }

    void push(int value){
        Node *new_node = new Node(value);
        if( head == nullptr){
            // First element in list
            head = new_node;
        } else {
            Node *old_first = head;
            head = new_node;
            new_node->next = old_first;
        }
    }

    void del(int index){
        if (head == nullptr){
            // cant delete from empty list
            throw out_of_range("list index out of range");
        }
        Node *prev = head;
        if (index == 0){
            // case when we are at the front
            // just delete the head and name the next
            // node the new head
            head = head->next;
            delete prev;
            return;
        }
        Node *current = head->next;
        if (current == nullptr){
            // Case where we have 1 element but dont
            // ask for it
            throw out_of_range("list index out of range");
        }
        Node *next = current->next;
        int current_index = 1;
        while (next != nullptr && current_index < index){
            // Keep iterating through list until either we
            // hit the index we want or fall off the edge
            prev = current;
            current = next;
            next = next->next;
            current_index ++;
        }
        if (index == current_index){
            // We have the index we want, kill it dead
            prev->next = next;
            delete current;
            return;
        } else if (index > current_index){
            // We have fall off the edge
            throw out_of_range("list index out of range");
        }

    }

    void ins(int value, int index){
        if (index == 0){
            push(value);
            return;
        }
        Node *current = head;
        if (current == nullptr){
            // Got nothing but asked for non zero index
            throw out_of_range("list index out of range");
        }
        Node *next = current->next;
        if (next == nullptr){
            if (index == 1){
                // single element add on end
                Node *new_node = new Node(value);
                current->next = new_node;
                return;
            }
            // single element but asked for non (1 or 0) index
            throw out_of_range("list index out of range");
        }
        // If we are here we have at least two elements
        int current_index = 1;
        while (next != nullptr && current_index < index){
            // Keep iterating through list until either we
            // hit the index we want or fall off the edge
            current = next;
            next = next->next;
            current_index ++;
        }
        if (index == current_index){
            // We have the index, adding in new node
            Node *new_node = new Node(value);
            new_node->next = next;
            current->next = new_node;
            return;
        } else if (index > current_index){
            // We have fall off the edge
            throw out_of_range("list index out of range");
        }
    }

};


int main(){

    int init_array[5] = {1,2,3,4,5};
    LinkedList mylist = LinkedList(init_array, 5);
    LinkedList myemptylist;

    printf("Original lists\n");
    cout << mylist.repr()<< endl;
    cout << myemptylist.repr()<< endl;

    printf("\nAppend to original lists\n");
    mylist.append(99);
    myemptylist.append(1);
    cout << myemptylist.repr()<< endl;
    cout << mylist.repr()<< endl;

    printf("\nPush to lists\n");
    myemptylist = LinkedList();
    mylist.push(88);
    myemptylist.push(88);
    cout << myemptylist.repr()<< endl;
    cout << mylist.repr()<< endl;

    printf("\nDelete from lists\n");
    mylist.del(5);
    myemptylist.del(0);
    cout << mylist.repr()<< endl;
    cout << myemptylist.repr()<< endl;

    printf("\nAdd to lists\n");
    myemptylist.ins(11, 0);
    myemptylist.ins(44, 1);
    myemptylist.ins(22, 1);
    myemptylist.ins(33, 2);
    cout << myemptylist.repr()<< endl;

return 0;
}
