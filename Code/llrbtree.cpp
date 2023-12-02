#include "llrbtree.h"

/*
 * Node Class Functions
*/
// notes 

/*csc 212 pocject
orgianze by year -> input a year and it outputs all movies in the list that
once the node is found search my array martic for ttile and director
if year is repeated add things to to repacted year to node already existing */

// Constructor for LLRBTNode class
LLRBTNode::LLRBTNode(int data){
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
    this->red = true; // Initialize color as red
}

// Destructor for LLRBTNode class
LLRBTNode::~LLRBTNode(){

}

/*
 * Tree Class Functions
*/

/*
 * Private Functions
*/

// Check if a node is red

// Recursive function to insert a node into the Red-Black Tree
LLRBTNode* LLRBTree::insert(int data, LLRBTNode* root){
    if (!root) {
        return new LLRBTNode(data);
    }

    // Go left if data < data at this Node
    if(data < root->data){
        root->left = insert(data, root->left);
    // Go right otherwise
    }else{
        root->right = insert(data, root->right);
    }

    if (CheckRed(root->right) && !CheckRed(root->left))  // rotates left
     {
        root =  rotateLeft(root);
    }
    if (CheckRed(root->left) && CheckRed(root->left->left)) // rotates right
    {
        root = rotateRight(root);
    }
    if (CheckRed(root->right) && CheckRed(root->left)) // flip colors
     {
        flipColors(root);
    }
    return root;
}
void LLRBTree::makeRootBlack() {
    if (_root) {
        _root->red = false; // makes the top node the right color
    }
}
bool LLRBTree::CheckRed(LLRBTNode* root) // checks color
{
    if(root == nullptr) 
    {
        return false;
    }
    return root->red;
}

// Flip the colors of a node and its children
void LLRBTree::flipColors(LLRBTNode* root)
{
    root->red = !root->red;
    root->left->red = !root->left->red;
    root->right->red = !root->right->red;
}

// Function to perform a left rotation
LLRBTNode* LLRBTree::rotateLeft(LLRBTNode* root) {
    LLRBTNode* x = root->right;
    root->right = x->left;
    x->left = root;
    x->red = root->red;
    root->red = true; // Red-Black Tree property: Parent is always black
    return x;
}

// Function to perform a right rotation
LLRBTNode* LLRBTree::rotateRight(LLRBTNode* root) {
    LLRBTNode* x = root->left;
    root->left = x->right;
    x->right = root;
    x->red = root->red;
    root->red = true; // Red-Black Tree property: Parent is always black
    return x;
}


// Recursive function to perform pre-order traversal
void LLRBTree::preorder(LLRBTNode* root, std::ostream& os){
    if(!root){
        return;
    }

    os << root->data << ":" << root->red << " ";
    this->preorder(root->left, os);
    this->preorder(root->right, os);
    return;
}

// Recursive function to perform in-order traversal
void LLRBTree::inorder(LLRBTNode* root, std::ostream& os){
    if(!root){
        return;
    }

    this->inorder(root->left, os);
    os << root->data << ":" << root->red << " ";
    this->inorder(root->right, os);
    return;
}

// Recursive function to perform post-order traversal
void LLRBTree::postorder(LLRBTNode* root, std::ostream& os){
    if(!root){
        return;
    }

    this->postorder(root->left, os);
    this->postorder(root->right, os);
    os << root->data << ":" << root->red << " ";
    return;
}

// Recursive function to calculate the height of the tree
int LLRBTree::height(LLRBTNode* root){
    if(!root){
        return -1;
    }
    int left = height(root->left);
    int right = height(root->right);

    return (left > right ? left + 1 : right + 1);
}
LLRBTNode* LLRBTree::find_ios(LLRBTNode* root, bool& disconnect){
    if(!root->left){
        disconnect = true;
        return root;
    }
    LLRBTNode* temp = find_ios(root->left, disconnect);

    if(disconnect){
        root->left = nullptr;
        disconnect = false;
    }

    return temp;
}
bool LLRBTree::search(int data, LLRBTNode* root){ // search function that recurvseie finds the node and return true or false 
    if(!root){
        return false;
    }

    if(data == root->data){
        return true;
    }

    if(data < root->data){
        return this->search(data, root->left);
    }else{
        return this->search(data, root->right);
    }
}
/*
 * Public Functions
*/

// Constructor for LLRBTree class
LLRBTree::LLRBTree(){
    this->_root = nullptr;
}

// Destructor for LLRBTree class
LLRBTree::~LLRBTree(){
    delete this->_root; // Delete the root node and its children
}

// Public function to insert a node into the Red-Black Tree
void LLRBTree::insert(int data){
    this->_root = this->insert(data, this->_root); // Call the private insert function
}

// Public function to get the height of the tree
int LLRBTree::height(){
    return this->height(this->_root); // Call the private height function
}

// Public function to perform pre-order traversal
void LLRBTree::preorder(std::ostream& os){
    this->preorder(this->_root, os); // Call the private preorder function
    os << "\n";
}

// Public function to perform in-order traversal
void LLRBTree::inorder(std::ostream& os){
    this->inorder(this->_root, os); // Call the private inorder function
    os << "\n";
}

// Public function to perform post-order traversal
void LLRBTree::postorder(std::ostream& os){
    this->postorder(this->_root, os); // Call the private postorder function
    os << "\n";
}



void LLRBTree::appendList(int key, ListNode add_mov) { // finds the node that matchs the key and adds the lists to th already existing node
     LLRBTNode* temp = search();
     temp->movie_list.insert(add_mov);


}
void LLRBTree::removeFromList(int key, ListNode rem_mov) { // removes movies from an already existing node
    LLRBTNode* temp = search();
    temp->movie_list.remove(rem_mov);
}
void LLRBTree::printMoviesFromYear(int key) { // prints movies from a node that is found
    LLRBTNode* temp = search();
    std::cout <<
}
