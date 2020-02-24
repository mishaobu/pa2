#include <iostream>
#include<climits> 
#include <string>
#include<bits/stdc++.h> 

#include <vector>
using namespace std; 


struct Node {
    ~Node() {
        if (next) delete next;
    }
    Node(int x) {
        value = x;
        count = 1;
    }
    int value = 0;
    int count = 0;
    int locInHeap = 0;
    Node* next = NULL;
};

void swap(Node *&x, Node *&y); 
  
class MinHeap { 
    Node **harr; // pointer to array of elements in heap 
    int capacity; 
    int heap_size;
public: 
    MinHeap(int capacity); 
  
    // to heapify a subtree with the root at given index 
    void MinHeapify(int i); 
  
    int parent(int i) { return (i-1)/2; } 
    int left(int i) { return (2*i + 1); } 
    int right(int i) { return (2*i + 2); } 
    
    void printHeap();
    void printHeapIndex();
    void deleteKey(int i);
    Node* extractMin(int store_val, bool b); 
  
    // Returns the minimum key (key at root) from min heap 
    Node* getMin() { return harr[0]; } 
    void insertKey(Node* k); 
}; 
  
// Constructor: Builds a heap from a given array a[] of given size 
MinHeap::MinHeap(int cap) { 
    heap_size = 0; 
    capacity = cap;
    harr = new Node*[cap];
    for (int i = 0; i<cap; i++) harr[i] = NULL;
} 
  
// Inserts a new key 'k' 
void MinHeap::insertKey(Node* k) { 
    if (heap_size == capacity) { 
        cout << "\nOverflow: Could not insertKey\n"; 
        return; 
    } 

    // First insert the new key at the end 
    heap_size++; 
    int i = heap_size - 1; 

    harr[i] = k; 

    //Fix the min heap property if it is violated 
    while (i != 0 && (harr[parent(i)])->value > (harr[i]->value)) { 
       swap(harr[i], harr[parent(i)]); 
       i = parent(i); 
    } 

} 
  
  
// Method to remove minimum element (or root) from min heap 
Node* MinHeap::extractMin(int store_val = -99999, bool b = false) { 
    if (heap_size <= 0) {
        cout << "min item not present since table is empty" << endl;
        return NULL; 
    }
    harr[0]->count -= 1;
    if (harr[0]->count > 0) {
        cout << "min item = " << harr[0]->value << ", count decremented, new count = " << harr[0]->count << endl;
        return NULL;
    }
    else {
    if (heap_size == 1) { 
        heap_size--; 
        if (store_val == -99999) cout << "min item " << harr[0]->value << " successfully deleted" << endl;
        else if (b == false) cout << "min item " << store_val << " successfully deleted" << endl;
        else cout << "item successfully deleted" << endl;
        return harr[0]; 
    } 
  
    // Store the minimum value, and remove it from heap 
    if (store_val == -99999) cout << "min item " << harr[0]->value << " successfully deleted" << endl;
    else if (b == false) cout << "min item " << store_val << " successfully deleted" << endl;
    else cout << "item successfully deleted" << endl;
     Node* root = harr[0]; 
    harr[0] = harr[heap_size-1]; 
    harr[0]->locInHeap = 0;
    heap_size--; 
    MinHeapify(0); 
  
    return root; 
    }
} 
  
  
// A recursive method to heapify a subtree with the root at given index 
// This method assumes that the subtrees are already heapified 
void MinHeap::MinHeapify(int i) { 
    int l = left(i); 
    int r = right(i); 
    int smallest = i; 
    if (l < heap_size && harr[l]->value < harr[i]->value) 
        smallest = l; 
    if (r < heap_size && harr[r]->value < harr[smallest]->value) 
        smallest = r; 
    if (smallest != i) { 
        swap(harr[i], harr[smallest]); 
        MinHeapify(smallest); 
    } 
} 
  
void swap(Node*& x, Node*& y) { 
    //int x_temp = x->locInHeap;
    Node* temp = x; 
    //x->locInHeap = y->locInHeap;
    //y->locInHeap = x_temp;
    x = y; 
    y = temp; 
} 

unsigned modulo( int value, unsigned m) {
    int mod = value % (int)m;
    if (value < 0) {
        mod += m;
    }
    return mod;
}

int toHashTable(int x, Node** hashTable, MinHeap &h) { 
    int index = modulo(x,43);
    if (hashTable[index] == NULL) {
        hashTable[index] = new Node(x);
        h.insertKey(hashTable[index]);
        cout << "item successfully inserted, count = " << hashTable[index]->count << endl;
        return 0;
    }
    else {
        Node* curr = hashTable[index];
        Node* prev = NULL;
        while(curr){
            if (!curr) {
                prev->next = new Node(x);
                h.insertKey(prev->next);
                cout << "item successfully inserted, count = " << prev->next->count << endl;
                return 0;
            }
            else if (curr->value == x) {
                curr->count += 1;
                cout << "item successfully inserted, count = " << curr->count << endl;
                return index;
            }
            prev = curr;
            curr = curr->next;
        }
        if (!curr) {
                prev->next = new Node(x);
                h.insertKey(prev->next);
                cout << "item successfully inserted, count = " << prev->next->count << endl;
                return 0;
        }
    }
    cout << "Error, end of toHashTable()" << endl;
    return -1;
}



int deleteFromHeap(int n) { return 0;}

int deleteFromHashTable(int x, Node** hashTable, MinHeap &minHeap) { 
    int index = modulo(x,43);
    int value;
    if (hashTable[index] == NULL) {
        cout << "Key doesn't exist in table" << endl;
        return -1;
    } 
    else {
        Node* curr = hashTable[index];
        Node* prev = NULL;

        while(curr){
            if (!curr) {
                cout << "Key doesn't exist in table" << endl;
                return -1;
            }
            if (curr->value == x) {
                if (curr->count > 1) {
                    //curr->count -=1;
                    return 0;
                } 
                else {
                    if (curr->next) {
                        if (prev) {
                            prev->next = curr->next;
                            //deleteFromHeap(curr->locInHeap);
                            value = curr->value;
                            return value;
                        } 
                        else {
                            hashTable[index] = curr->next;
                            //deleteFromHeap(curr->locInHeap);
                            value = curr->value;
                            return value;
                        }
                    }
                    else {
                        hashTable[index] = NULL;
                        //deleteFromHeap(curr->locInHeap);
                        value = curr->value;
                        return value; 
                    }            
                }
            }
            prev = curr;
            curr = curr->next;
        }
    }
    return -1;
}

Node* findInHashTable(int n, Node** hashTable) {
    int index = modulo(n,43);
    if (hashTable[index] == NULL) {
        return NULL;
    }
    else {
        Node* curr = hashTable[index];
        while(curr) {
            if (curr->value == n) {
                return curr;
            }
            curr = curr->next;
        }
    }
    return NULL;
}


void MinHeap::deleteKey(int i) { 
    int store_val = harr[i]->value;
    harr[i]->value = INT_MIN;
    while (i != 0) { 
       swap(harr[i], harr[parent(i)]); 
       i = parent(i); 
    } 
    extractMin(store_val, true); 
} 

void MinHeap::printHeap() {
    for (int i = 0; i < heap_size; i++) {
        cout << harr[i]->value << " ";
    }
    cout << endl;
}

void MinHeap::printHeapIndex() {
    for (int i = 0; i < heap_size; i++) {
        cout << harr[i]->locInHeap << " ";
    }
    if(heap_size > 0) cout << endl;
}

void doOperation(string op, int n, Node** hashTable, MinHeap &h) {
    if (op == "insert" || op == " insert") {
        toHashTable(n, hashTable, h);
    }
    else if (op == "lookup"|| op == " lookup") {
        Node* result = findInHashTable(n, hashTable);
        if (result == NULL) cout << "item not found" << endl;
        else cout << "item found, count = " << result->count << endl;
    }
    else if (op == "print"|| op == " print") {
        h.printHeap();
    } 
    else if (op == "deleteMin"|| op == " deleteMin") {
        Node* n = h.extractMin();
        if (n) deleteFromHashTable(n->value, hashTable, h);
    }
    else if (op =="delete"|| op == " delete") {
        Node* result = findInHashTable(n, hashTable);
        //cout <<"hey wat up" << result->value << endl;
        if (result == NULL) cout << "item not present in the table" << endl;
        else if (result->count > 1) {
            result->count -= 1;
            cout << "item successfully deleted" << endl;
        }
        else if (result->count == 1) {
            h.deleteKey(result->locInHeap);
            deleteFromHashTable(n, hashTable, h);
        }
    }
    else if (op == "printLocs") {
        h.printHeapIndex();
    }
    else { "error wtf"; }
}

int main(int argc, char* argv[]) {
    Node* hashTable[43];
    MinHeap h(100);
    for (int i = 0; i<43; i++) hashTable[i] = NULL;

    if (argc != 2) exit(-1);
    string s = argv[1];

    string strarr[100];
    for (int i = 0; i<43; i++) strarr[i] = "";

    int numArgs = 0;
    bool newArg = false;

    string v = argv[1];
    for (int i = 0; i < v.length(); i++) {
        if (v[i] == ' ' || v[i] == ',') {
            newArg = true;
            continue;
        }
        else {
            if (newArg == true) numArgs += 1;
            newArg = false;
            string s(1, v[i]);
            strarr[numArgs] = strarr[numArgs] + s;
        }
    } 

    for (int i =0; i<numArgs+1; i++) {
        if (strarr[i] == "insert" || strarr[i] == "lookup" || strarr[i] == "delete") {
            doOperation(strarr[i], stoi(strarr[i+1]), hashTable, h);
            i += 1;
            //cout << strarr[i] << endl;

        }
        else {
            //cout << strarr[i] << endl;
            doOperation(strarr[i], 0, hashTable, h);
        }
    }
    return 0;
}