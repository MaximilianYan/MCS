#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <limits>
#include <list>

using namespace std;

class List {
public:
    class Node {
    public:
        Node* next;
        Node* prev;
        long long int value;
    private:
    };

    List() : tail(nullptr) {}

    Node* tail;

    Node* add(long long int value) {
        if (tail == nullptr) {
            tail = new Node;
            tail->next = tail;
            tail->prev = tail;
            tail->value = value;
            return tail;
        }

        Node* next = tail->next;
        tail->next = new Node;
        tail->next->next = next;
        tail->next->prev = tail;
        next->prev = tail->next;
        tail->next->value = value;

        tail = tail->next;
        return tail;
    }

    void erase(Node* node) {
        node->next->prev = node->prev;
        node->prev->next = node->next;
        if (tail == node) tail = node->prev;
        if (tail == node) tail = nullptr;
        delete node;
    }

    ~List() {
        while (tail) erase(tail->next);
    }
};

int main() {
    long long int n = 0, k = 0;
    cin >> n >> k;

    --k;

    List nums;
    for (long long int i = 1; i <= n; ++i) {
        nums.add(i);
    }

    List::Node* ptr = nums.tail->next;
    long long int pos = 0;

    do {
        long long int target = (pos + k) % n;

        while (pos != target) {
            pos += 1;
            pos %= n;
            ptr = ptr->next;
        }

        ptr = ptr->next;
        nums.erase(ptr->prev);
    } while (--n > 1);

    cout << nums.tail->value << endl;

    return 0;
}
