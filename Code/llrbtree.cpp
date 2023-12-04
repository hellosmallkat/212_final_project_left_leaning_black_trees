#include <sstream>
#include <regex>
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
    this->key = data;
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
LLRBTNode* LLRBTree::insert(int key, LLRBTNode* root){
    if (!root) {
        return new LLRBTNode(key);
    }


    // Go left if key < key at this Node
    if(key < root->key){
        root->left = insert(key, root->left);
    // Go right otherwise
    }else{
        root->right = insert(key, root->right);
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

    os << root->key << ":" << root->red << " ";
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
    os << root->key << ":" << root->red << " ";
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
    os << root->key << ":" << root->red << " ";
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
bool LLRBTree::isKeyInList(int data, LLRBTNode* root){ // search function that recurvseie finds the node and return true or false
    if(!root){
        return false;
    }

    if(data == root->key){
        return true;
    }

    if(data < root->key){
        return this->search(data, root->left);
    }else{
        return this->search(data, root->right);
    }
}

LLRBTNode* LLRBTree::search(int key, LLRBTNode* root){ // search function that recurvseie finds the node of a certain key and returns a pointer to it.
    if(!root){
        return nullptr;
    }

    if(key == root->key){
        return root;
    }

    if(key < root->key){
        return this->search(key, root->left);
    }else{
        return this->search(key, root->right);
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



void LLRBTree::appendList(int key, std::string add_mov) { // finds the node that matchs the key and adds the lists to th already existing node
    //Now that we know the key exists, we create a listNode object to push to the list at that key.

    //Parse String for title and directors

    std::string director, title;
    std::regex regexPattern(R"((.*?)\s*\(\d{4}\)\s*-\s*(.*?)(?=\s*-\s*|$))");
    std::smatch match;
    if(std::regex_search(add_mov, match, regexPattern)) {
        title = match[1].str();
        director = match[2].str();
    }
    //with the title and director strings, we now create a new list node to push to the movie list @ the key's year

    ListNode added_node(title, director);
    LLRBTNode* ptr = search(key, _root);
    ptr->movie_list.push_back(added_node);

}

void LLRBTree::removeMovie(std::string rem_mov) {
    //First grab the year as our key from the remove command
    int year = extractYear(rem_mov);
    size_t openParenthesisPos = rem_mov.find('(');

    // Check if the opening parenthesis is found
    if (openParenthesisPos != std::string::npos) {
        // Remove the year and parentheses
        rem_mov = rem_mov.substr(0, openParenthesisPos);

        // Remove trailing whitespace if any
        size_t lastNonWhitespace = rem_mov.find_last_not_of(" \t");
        if (lastNonWhitespace != std::string::npos) {
            rem_mov.erase(lastNonWhitespace + 1);
        }
    }

    removeFromList(year, rem_mov);
}





void LLRBTree::removeFromList(int key, std::string rem_mov) { // removes movies from an already existing node this call has the parameters of the key that the list is at, with rem_mov being a parsed movie Title
    //First we need to call our search function in order to find where our movie we want to remove exists.

    LLRBTNode *ptr = search(key, _root);
    std::list<ListNode> temp = ptr->movie_list;
    for (auto iter = temp.begin(); iter != temp.end();) {
        if (iter->movie_name == rem_mov) {
//          Iterate through the list existing at the key and then delete the movie existing at the list there.
            temp.erase(iter);
            ptr->movie_list = temp;
            return;
        }
        else {
            ++iter;
        }
    }
}
void LLRBTree::printMoviesFromYear(int key, std::ostream& os) { // prints movies from a node that is found
    LLRBTNode* ptr = search(key, _root);
    std::list<ListNode> temp = ptr->movie_list;
    os << "Movies released in the year " << key << ": \n";
    for (auto iter = temp.begin(); iter != temp.end();) {
        os << "Title: " << iter->movie_name << " Director: " << iter->Director;
        os << std::endl;
    }
}

ListNode::ListNode(std::string mov_name, std::string direct) {
    movie_name = mov_name;
    Director = direct;
}


void LLRBTree::inputToTree(std::string input) {
    //parse for key, which is the year the movie came out;
    int key;
    key = extractYear(input);
    if(isKeyInList(key, this->_root)) {
        //If the key is in the list, append the string as a ListNode in the list @ that key value;
        appendList(key, input);
    }
    else {
        insert(key, _root);
        appendList(key, input);
    }

}


//This was given by chat-gpt
int extractYear(std::string movieInfo) {
    std::regex yearRegex(R"(\b(\d{4})\b)");  // Match a four-digit year

    std::smatch match;
    if (std::regex_search(movieInfo, match, yearRegex)) {
        // The first capturing group contains the matched year
        std::stringstream ss(match[1].str());
        int year = 0;
        ss >> year;

        // Check if extraction was successful
        if (!ss.fail()) {
            return year;
        }
    }
}

