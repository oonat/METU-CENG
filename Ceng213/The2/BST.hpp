#ifndef BST_HPP
#define BST_HPP

#include <iostream>

#include "BSTNode.hpp"

template <class T>
class BST {
public: 
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot();

    void insert(const T &data);
    void remove(const T &data);
    BSTNode<T> *find(const T &data);
    void printInorder();

    BST<T> &operator=(const BST<T> &rhs);

private: 
    void printInorder(BSTNode<T> *node);
    void destructor_helper(BSTNode<T> *node);
    void copy_helper(BSTNode<T> *node);
    BSTNode<T>* remove_finder(BSTNode<T> *node, const T &data);
    BSTNode<T>* successor_finder(BSTNode<T> *node);

private: 
    BSTNode<T> *root;
};

#endif 

template <class T>
BST<T>::BST() {
    /* TODO */
    root = NULL;
}

template <class T>
BST<T>::BST(const BST<T> &obj) {
    /* TODO */
    if(obj.root == NULL)
    	root = NULL;
    else{
    	root = NULL;
    	copy_helper(obj.root);
    }
}

template <class T>
void BST<T>::copy_helper(BSTNode<T> *node) {
    if(node->right == NULL && node->left == NULL){
       this->insert(node->data);
    }else{
    	
    	this->insert(node->data);
    	if(node->left != NULL && node->right == NULL)
    	copy_helper(node->left);
        else if(node->right != NULL && node->left == NULL)
    	copy_helper(node->right);
        else{
        	copy_helper(node->left);
        	copy_helper(node->right);
        }
    }

}

template <class T>
BST<T>::~BST() {
    /* TODO */
    
	if(root== NULL)
		return;
	else{
    destructor_helper(root);
    root = NULL;
    }
}

template <class T>
void BST<T>::destructor_helper(BSTNode<T> *node){
	
	if(node == NULL)
		return;
    else if(node->right == NULL && node->left == NULL)
    	delete node;
    else{
    	if(node->left != NULL && node->right == NULL){
    		destructor_helper(node->left);
    	    delete node;
        }else if(node->right != NULL && node->left == NULL){
        	destructor_helper(node->right);
        	delete node;
        }else{
            destructor_helper(node->left);
            destructor_helper(node->right);
            delete node;
        }
    }
}

template <class T>
BSTNode<T> *BST<T>::getRoot() {
    /* TODO */
    if(root == NULL)
      return NULL;
    else
      return root;
}

template <class T>
void BST<T>::insert(const T &data) {
    /* TODO */
    BSTNode<T>* newnode = new BSTNode<T>(data,NULL,NULL);
    BSTNode<T>* current = root;
    BSTNode<T>* prev = root;
    
    
    if(root == NULL){
    	root = newnode;
    }else{
 
    while(current != NULL){
    	 prev = current;
         if(current->data<data)
         	current = current->right;
         else
         	current = current->left;
    }
    
    if(prev->data<data)
    	prev->right = newnode;
    else
    	prev->left = newnode;
}
}

template <class T>
void BST<T>::remove(const T &data) {
    /* TODO */
   BSTNode<T>* delete_parent = remove_finder(root,data);
   
   
   if(delete_parent == NULL)
     return;
   
   else if(root->data == data){
     if(root->right == NULL && root->left == NULL){
        delete root;
        root = NULL;
     }else if(root->left != NULL && root->right == NULL){
       BSTNode<T>* tmp = root;
       root = root->left;
       delete tmp;
     }else if(root->right != NULL && root->left == NULL){
       BSTNode<T>* tmp = root;
       root = root->right;
       delete tmp;
     }else{
       BSTNode<T>* successor_parent = successor_finder(root->right);
       
       if(root->right->left == NULL){
         BSTNode<T>* tmp = root;
         root->right->left = root->left;
         root = root->right;
         delete tmp;
       }else{
       BSTNode<T>* tmp = successor_parent->left->right;
       BSTNode<T>* tmp_node = root;
       successor_parent->left->left = root->left;
       successor_parent->left->right = root->right;
       root = successor_parent->left;
       successor_parent->left = tmp;
       delete tmp_node;
       }
     }
   }else{
      BSTNode<T>* delete_parent = remove_finder(root,data);
      if(delete_parent->data < data){
        BSTNode<T>* delete_node = delete_parent->right;
        
        if(delete_node->left == NULL && delete_node->right == NULL){
          delete delete_node;
          delete_parent->right = NULL;
        }else if(delete_node->left != NULL && delete_node->right == NULL){
          BSTNode<T>* tmp = delete_node->left;
          delete delete_node;
          delete_parent->right = tmp;
        }else if(delete_node->right != NULL && delete_node->left == NULL){
          BSTNode<T>* tmp = delete_node->right;
          delete delete_node;
          delete_parent->right = tmp;
        }else{
          BSTNode<T>* successor_parent = successor_finder(delete_node->right);
          
          if(delete_node->right->left == NULL){
             BSTNode<T>* tmp = delete_node->right;
             delete_node->right->left = delete_node->left;
             delete delete_node;
             delete_parent->right = tmp;
          }else{
            BSTNode<T>* tmp = successor_parent->left->right;
            BSTNode<T>* tmp_node = delete_node;
            successor_parent->left->left = delete_node->left;
            successor_parent->left->right = delete_node->right;
            delete_parent->right = successor_parent->left;
            successor_parent->left = tmp;
            delete tmp_node;
          }


        }







      }else{
       
       BSTNode<T>* delete_node = delete_parent->left;
        
        if(delete_node->left == NULL && delete_node->right == NULL){
          delete delete_node;
          delete_parent->left = NULL;
        }else if(delete_node->left != NULL && delete_node->right == NULL){
          BSTNode<T>* tmp = delete_node->left;
          delete delete_node;
          delete_parent->left = tmp;
        }else if(delete_node->right != NULL && delete_node->left == NULL){
          BSTNode<T>* tmp = delete_node->right;
          delete delete_node;
          delete_parent->left = tmp;
        }else{
          BSTNode<T>* successor_parent = successor_finder(delete_node->right);
          
          if(delete_node->right->left == NULL){
             BSTNode<T>* tmp = delete_node->right;
             delete_node->right->left = delete_node->left;
             delete delete_node;
             delete_parent->left = tmp;
          }else{
            BSTNode<T>* tmp = successor_parent->left->right;
            BSTNode<T>* tmp_node = delete_node;
            successor_parent->left->left = delete_node->left;
            successor_parent->left->right = delete_node->right;
            delete_parent->left = successor_parent->left;
            successor_parent->left = tmp;
            delete tmp_node;
          }





      }









   }

}

}

template <class T>
BSTNode<T>* BST<T>::remove_finder(BSTNode<T>* node, const T &data) {
   BSTNode<T>* current = root;
   BSTNode<T>* prev = root;

   while(current != NULL){
   	if(current->data == data)
   		return prev;
   	else{
   		prev = current;
   		if(current->data<data)
   			current = current->right;
   		else
   			current = current->left;
   		}
   }
  
  return NULL;
}

template <class T>
BSTNode<T>* BST<T>::successor_finder(BSTNode<T>* node){
	BSTNode<T>* current = node;
  BSTNode<T>* prev = node;

	while(current->left != NULL){
    prev = current;
		current = current->left;
	}
	return prev;
}

template <class T>
BSTNode<T> *BST<T>::find(const T &data) {
    /* TODO */
    BSTNode<T>* current = root;

    while(current != NULL){
    	if(current->data == data)
    		return current;
    	else if(current->data <data)
    		current = current->right;
    	else
    		current = current->left;
    }
    return NULL;
}

template <class T>
void BST<T>::printInorder() {

    if (root == NULL) {
        std::cout << "{}" << std::endl;
    } else {
        std::cout << "{" << std::endl;
        printInorder(root);
        std::cout << std::endl << "}" << std::endl;
    }
}

template <class T>
void BST<T>::printInorder(BSTNode<T> *node) {

    if (node == NULL)
        return;

    printInorder(node->left);
    if (node->left) {
        std::cout << "," << std::endl;
    }
    std::cout << "\t" << node->data;
    if (node->right) {
        std::cout << "," << std::endl;
    }
    printInorder(node->right);
}

template <class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) {
    /* TODO */

    
    destructor_helper(root);
    root = NULL;
    
    
    if(rhs.root == NULL)
    	root = NULL;
    else
    	copy_helper(rhs.root);

   return *this;
}
