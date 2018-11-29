#include "general_tree.hpp"
#include <vector>
#include <regex>
#include <sstream>


int process(const std::string& input) {
  const std::regex filter {"[^0-9 ]"};

  std::stringstream result;
  std::regex_replace(std::ostream_iterator<char>(result), input.begin(), input.end(), filter, "");
  const std::vector<std::string> results {std::istream_iterator<std::string>{result}, std::istream_iterator<std::string>()};

  if(results.size() < 2 || (results.size() % 2) != 0) {
    std::cerr << "Invalid edge list" << std::endl;
    return 3;
  }

  general_tree::Tree<int> tree;

  for(auto it = results.begin(); it != results.end(); it++) {
    const int a = std::stoi(*it);
    const int b = std::stoi(*(++it));
    tree.addEdge(a, b);
  }

  tree.preorder();
  std::cout << "Count: " << tree.count() << std::endl;
  std::cout << "Height: " << tree.height() << std::endl;
  return 0;
}

int main(int argc, char* argv[]) {
  if(argc < 2) {
    std::cout << "Usage: algo05 \"[(<from>,<to>) [...]]\"" << std::endl;
    return 2;
  }

  if(std::string{argv[1]} == std::string{"custom"}) {
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
    return 0;
  }

  if(std::string{argv[1]} == std::string{"test"}) {
    std::vector<std::string> cases {
      #include "./test_cases.raw"
    };
    for(const auto& test : cases) {
      process(test);
    }
    return 0;
  }

  return process(std::string{argv[1]});
}