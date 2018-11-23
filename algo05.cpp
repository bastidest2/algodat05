#include "general_tree.hpp"
#include <vector>


int main(int argc, char* argv[]) {
  if(argc < 2) {
    std::cout << "Usage: algo05 \"[(<from>,<to>) [...]]\"" << std::endl;
    return 2;
  }

  if(std::string{argv[1]} == std::string{"test"}) {
    general_tree::Tree<int> tree;
    tree.addEdge(7, 5);
    tree.addEdge(1, 3);
    tree.addEdge(5, 8);
    tree.addEdge(5, 1);
    tree.addEdge(1, 6);
    tree.addEdge(1, 4);
    tree.addEdge(7, 9);
    tree.addEdge(7, 2);
    tree.preorder();
    std::cout << "Count: " << tree.count() << std::endl;
    std::cout << "Height: " << tree.height() << std::endl;
  }

  return 0;
}