#include "InvertedIndex.hpp"

#include <fstream>

InvertedIndex::InvertedIndex() {

}

InvertedIndex::InvertedIndex(const InvertedIndex &obj) {

    this->invertedIndex = obj.invertedIndex; // uses operator= of BST
}

InvertedIndex::~InvertedIndex() {

}

BST<IIData> &InvertedIndex::getInvertedIndex() {

    return invertedIndex;
}

InvertedIndex &InvertedIndex::addDocument(const std::string &documentName) {

    std::ifstream file(documentName.c_str(), std::ifstream::in);

    std::string word;
    for (int position = 1; (file >> word); ++position) {
        BSTNode<IIData> *theNode = invertedIndex.find(IIData(word));

        /* TODO */
        if(theNode == NULL){
            IIData newdata(word);
            newdata.addOccurrence(documentName,position);
            invertedIndex.insert(newdata);
        }else{
            theNode->data.addOccurrence(documentName,position);
        }
        
        
    }

    file.close();

    return *this;
}

InvertedIndex &InvertedIndex::removeDocument(const std::string &documentName) {
    /* TODO */
    if(getInvertedIndex().getRoot() == NULL)
        return *this;
    else{
        remove_helper(getInvertedIndex().getRoot(),documentName);
        return *this;
    }

}

void InvertedIndex::remove_helper(BSTNode<IIData>* node, const std::string &documentName){
    if(node->left == NULL && node->right == NULL){
            node->data.removeOccurrences(documentName);
            if(node->data.getOccurrences().empty())
                invertedIndex.remove(node->data);
        
    }else if(node->left != NULL && node->right == NULL){
        remove_helper(node->left,documentName);
            node->data.removeOccurrences(documentName);
            if(node->data.getOccurrences().empty())
                invertedIndex.remove(node->data);
        
    }else if(node->right != NULL && node->left == NULL){
        remove_helper(node->right,documentName);
            node->data.removeOccurrences(documentName);
            if(node->data.getOccurrences().empty())
                invertedIndex.remove(node->data);
        
    }else{
        remove_helper(node->left,documentName);
        remove_helper(node->right,documentName);
            node->data.removeOccurrences(documentName);
            if(node->data.getOccurrences().empty())
                invertedIndex.remove(node->data);
        
    }
}

InvertedIndex &InvertedIndex::searchWord(const std::string &word) {

    BSTNode<IIData> *theNode = invertedIndex.find(IIData(word));

    if (theNode == NULL) {
        std::cout << "The word \"" << word << "\" does not exist in inverted index." << std::endl;
    } else {
        std::cout << theNode->data << std::endl;
    }

    return *this;
}

InvertedIndex &InvertedIndex::printInvertedIndex() {

    invertedIndex.printInorder();

    return *this;
}

InvertedIndex &InvertedIndex::operator=(const InvertedIndex &rhs) {

    this->invertedIndex = rhs.invertedIndex; // uses operator= of BST

    return *this;
}
