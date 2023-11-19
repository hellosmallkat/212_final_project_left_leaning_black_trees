#pragma once

#include <iostream>
#include <ostream>

// Defines MAX
// When used, MAX(a,b) will be replaced with ((a > b) ? a : b)
#ifndef MAX
#define MAX(a,b) ((a > b) ? a : b)
#endif

// Underlying class which will be used to implement the BSTree class.
// I.E. BSTree is made up of BSTNode
class LLRBTNode
{
    private:
        int data;
        LLRBTNode* left;
        LLRBTNode* right;
        bool red;// true if red and false if black


    public:
        LLRBTNode(int data);
        ~LLRBTNode();

    friend class LLRBTree;
};

// Public versions: accept a single parameter so the usage of the class is neat.
// Private version: implement the functions recursively
class LLRBTree
{
    private:
        LLRBTNode* _root;

        LLRBTNode* insert(int data, LLRBTNode* root);
       // LLRBTNode* remove(int data, LLRBTNode* root);
        LLRBTNode* find_ios(LLRBTNode* root, bool& disconnect);
        //LLRBTNode* color(int data, LLRBTNode* root);
        //LLRBNode* find_ios(LLRBNode* root, bool& disconnect)
        LLRBTNode* rotateRight(LLRBTNode* root);
        LLRBTNode* rotateLeft(LLRBTNode* root);
        bool CheckRed(LLRBTNode* root);
        void flipColors(LLRBTNode* root);
        int height(LLRBTNode* root);

        void preorder(LLRBTNode* root, std::ostream& os);
        void inorder(LLRBTNode* root, std::ostream& os);
        void postorder(LLRBTNode* root, std::ostream& os);


    public:
        LLRBTree();
        ~LLRBTree();
void makeRootBlack();
        void insert(int data);
        //void remove(int data);
          void preorder(std::ostream& os = std::cout);
        void inorder(std::ostream& os = std::cout);
        void postorder(std::ostream& os = std::cout);
        int height();




};
