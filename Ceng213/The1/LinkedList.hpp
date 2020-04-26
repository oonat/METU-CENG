#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>

#include "Node.hpp"

template <class T>
class LinkedList
{
    public: 
        LinkedList();
        LinkedList(const LinkedList &obj);

        ~LinkedList();

        Node<T> *getFirstNode() const; 
        Node<T> *getHead() const;
        Node<T> *getTail() const;
        int getNumberOfNodes();
        bool isEmpty(); 

        void insertAtTheFront(const T &data); 
        void insertAtTheEnd(const T &data); 
        void insertAfterGivenNode(const T &data, Node<T> *prev); 

        void removeNode(Node<T> *node);
        void removeAllNodes();

        Node<T> *findNode(const T &data); 

        void printAllNodes();
        void printReversed();

        LinkedList &operator=(const LinkedList &rhs);

    private: 

    private: 
        Node<T> *head;
        Node<T> *tail;
};

template<class T>
LinkedList<T>::LinkedList()
{
    Node<T>*dummyhead = new Node<T>;
    Node<T>*dummytail = new Node<T>;

    head = dummyhead;
    tail = dummytail;

    head->next = tail;
    tail->prev =head;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList &obj)
{   Node<T>* current = (obj.head)->next;

    
	Node<T>*dummyhead = new Node<T>;
    Node<T>*dummytail = new Node<T>;

    head = dummyhead;
    tail = dummytail;

    head->next = tail;
    tail->prev = head;

     
    
    while(current != obj.tail){
    	this->insertAtTheEnd(current->element);
    	current = current->next;
    }

    
}

template<class T>
LinkedList<T>::~LinkedList()
{
    Node<T>* tmp, *current=head;

    
    while(current != tail){
    	tmp = current;
    	current = current->next;
    	delete tmp;
        }
    
    
    delete current;
}

template<class T>
Node<T> * LinkedList<T>::getFirstNode() const
{
    if(head->next == tail)       
          return NULL;      
        else        
          return head->next;
}

template<class T>
Node<T> * LinkedList<T>::getHead() const
{
    return head;
}

template<class T>
Node<T> * LinkedList<T>::getTail() const
{
    return tail;
}

template<class T>
int LinkedList<T>::getNumberOfNodes() 
{
	int i = 0;
	Node<T>*current = head->next;
    
    
    while(current != tail){
    	i++;
    	current = current->next;
        }

    return i;
}

template<class T>
bool LinkedList<T>::isEmpty()
{
    return head->next == tail;
}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data)
{
    /* TODO */
    Node<T>* newitem = new Node<T>;

    newitem->element = data;
    newitem->prev = head;
    newitem->next = head->next;
    head->next->prev = newitem;
    head->next = newitem; 
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data)
{   
    Node<T> *newitem = new Node<T>;
    newitem->element = data;
    
    newitem->next = tail;
    newitem->prev = tail->prev;
    tail->prev->next = newitem;
    tail->prev = newitem;

}

template<class T>
void LinkedList<T>::insertAfterGivenNode(const T &data, Node<T> *prev)
{   
    Node<T>* newitem = new Node<T>;
    Node<T>* current = head;
    int a = 0;
    
    newitem->element = data;

    
	while(current != tail){
       if(current == prev){
       	 a = 1;
         break;
       }
       current = current->next;
	}

    if(a == 0)
      return;

    
    if(prev->next == NULL)
       return;

    newitem->next = prev->next;
    newitem->prev = prev;
    prev->next->prev = newitem;
    prev->next = newitem;
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{   Node<T>* current = head->next;
	int a = 0;

	
	while(current != tail){
       if(current == node){
       	 a = 1;
         break;
       }
       current = current->next;
	}

	if(a == 1){
    node->next->prev = node->prev;
    node->prev->next = node->next;

    delete node;
    }else{
    	
    	return ;
    }
}

template<class T>
void LinkedList<T>::removeAllNodes()
{
    Node<T>* tmp, *current = head->next;

    while(current != tail){
    	tmp = current;
    	current = current->next;
    	delete tmp;
        }

        head->next = tail;
        tail->prev = head;
}

template<class T>
Node<T> * LinkedList<T>::findNode(const T &data)
{
    Node<T>* current = head->next;

    while(current != tail){
    	if(current->element == data)
    	  return current;
    	current = current->next;
    }

    return NULL;
}

template<class T>
void LinkedList<T>::printAllNodes()
{   Node<T>* current = head->next;

	while(current != tail){
		std::cout<<current->element<<std::endl;
		current = current->next;
	}

    
}

template<class T>
void LinkedList<T>::printReversed()
{   Node<T>* current = tail->prev;

	while(current != head){
		std::cout<<current->element<<std::endl;
		current = current->prev;
	}
}

template<class T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList &rhs)
{    
    
    if(this != &rhs){
    Node<T>* current = (rhs.head)->next;
    
    this->removeAllNodes();

    
    while(current != rhs.tail){
    	this->insertAtTheEnd(current->element);
    	current = current->next;
    }

  }

    return *this;
}

#endif 
