// bst.cpp
// CS24 Final Exam
// Implements class bst
// YOUR NAME(S), DATE

#include "bst.h"

#include <iostream>
using std::cout;



bst::bst(vector<int>&v){
    root = nullptr;
    for(auto obj: v){
        //cout << obj << endl;
        insert(obj);
    }
}

bst::~bst(){
    clear(root);
}

void bst::clear(bstNode *n){
    //cout << !n << endl;
    if(!n){
        return;
    }
    clear(n->left);
    clear(n->right);
    delete n;
}



bool bst::insert(int value) {
    if (root == nullptr){
        root = new bstNode(value);
        return true;
    }else{
        return insert(value, root);
    }

    return false; 

}


// recursive helper for insert (assumes n is never 0)

bool bst::insert(int value, bstNode *n) {

    if(value < n->info){
        if(n->left == nullptr){
            n->left = new bstNode(value);
            n->left->parent = n;
            return true;
        } else {
            return insert(value, n->left);
        }
    } else if (value > n->info) {
        if (n->right == nullptr){
            n->right = new bstNode(value);
            n->right->parent = n;
            return true;
        } else {
            return insert(value, n->right);
        }
    } else {
        return false;
    }

}


void bst::deleteSubtree(int key){
    clear(getNodeFor(key, root));
}
int bst::countLeaves(bstNode *n) const{
    if(!n){
        return 0;
    }
    if(!n->left && !n->right){
        return 1;
    }
    return countLeaves(n->left) + countLeaves(n->right);
}

int bst::countParentsWithTwoChildren(bstNode *n) const{
    if(!n){
        return 0;
    }
    if(n->left && n->right){
        return 1;
    }
    return countLeaves(n->left)+countLeaves(n->right);
}

int bst::height(bstNode *n) const{
    if(!root){
        return -1;
    }
    if(!n){
        return 0;
    }
    int left = 1+ height(n->left);
    int right = 1+ height(n->right);
    return (left>right) ? left : right;

}
void bst::outputPreOrder(bstNode *n, vector<int>& output) const{
    if(!n){
        return;
    }
    output.push_back(n->info);
    //cout << n->info << endl;
    outputPreOrder(n->left, output);
    outputPreOrder(n->right, output);
}

void bst::outputInOrder(bstNode *n, vector<int>& output) const{
    if(!n){
        return;
    }
    outputInOrder(n->left, output);
    output.push_back(n->info);
    outputInOrder(n->right, output);
}

typename bst::bstNode* bst::getNodeFor(int value, bstNode* n) const{
    while (n != nullptr) {
        if (value == n->info) {
            return n; 
        }
        else if (value < n->info) {
            return getNodeFor(value, n->left);
        } else {
            return getNodeFor(value, n->right);
        }
    }
    return nullptr; // Node doesn't exist in tree
}
