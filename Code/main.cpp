#include "llrbtree.h"
#include <fstream>
#include <sstream>

void print_tree(LLRBTree* tree, int mode, std::ofstream& os);

int main(int argc, char*argv[]){
    std::ifstream ifs(argv[1]);
    if(ifs.fail()) {
        std::cerr << "Couldn't find input file\n";
    }
    int mode = std::stoi(argv[2]);

    std::string fname(argv[3]);

    std::ofstream fs(fname);

    LLRBTree tree;

    std::string line;

    // Parse the file and insert into the tree
    while(std::getline(ifs, line)) {
        tree.inputToTree(line);
    }

    tree.makeRootBlack();

//    print_tree(&tree, mode, fs);\
//    fs << "Tree Height: " << tree.height() << std::endl;
    tree.printMoviesFromYear(1994,fs);
    fs.close();
}

/*
 * pre = 1
 * in = 2
 * post = 4
 * pre+in = 3
 * pre+post = 5
 * in+post = 6
 * pre+in+post = 7
 */
void print_tree(LLRBTree* tree, int mode, std::ofstream& os){
    if(mode == 1 || mode == 3 || mode == 5 || mode == 7){
        tree->preorder(os);
    }
    if(mode == 2 || mode == 3 || mode == 6 || mode == 7){
        tree->inorder(os);
    }
    if(mode == 4 || mode == 5 || mode == 6 || mode == 7){
        tree->postorder(os);
    }
}
