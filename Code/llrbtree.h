#pragma once

#include <iostream>
#include <ostream>
#include <list>

// Defines MAX
// When used, MAX(a,b) will be replaced with ((a > b) ? a : b)
#ifndef MAX
#define MAX(a,b) ((a > b) ? a : b)
#endif

class ListNode {
private:
    std::string movie_name;
    std::string Director;

public:
    ListNode(std::string mov_name, std::string direct);

    friend class LLRBTree;
};

// Underlying class which will be used to implement the BSTree class.
// I.E. BSTree is made up of BSTNode
class LLRBTNode
{
    private:
        int _key;
        LLRBTNode* left;
        LLRBTNode* right;
        bool red;// true if red and false if black
        std::list<ListNode> movie_list;


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

        LLRBTNode* insert(int key, LLRBTNode* root);
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

        void removeFromList(int key, std::string added_movie);
        void printMoviesFromYear(int key, std::ostream& os);

        LLRBTNode* search(int key, LLRBTNode* root);


    bool isKeyInList(int data, LLRBTNode *root);

    void appendList(int key, std::string add_mov);

    void inputToTree(std::string input);

    void removeMovie(std::string rem_mov);
};

int extractYear(std::string input);