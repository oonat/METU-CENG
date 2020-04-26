#include <iostream>

#include "LinkedList.hpp"

int main() {
    LinkedList<int> llist;

    llist.printAllNodes();

    llist.insertAtTheEnd(1);
    llist.insertAtTheEnd(7);
    llist.insertAtTheEnd(4);

    llist.printAllNodes();

    llist.removeNode(llist.findNode(4));

    llist.printAllNodes();

    return 0;
}