#include <iostream>
#include <vector>
#include <list>
#include <memory>

namespace general_tree {
    template <typename T>
    class Node {
    private:
        T m_value;
        std::vector<std::shared_ptr<Node<T>>> m_pChildren;
    public:
        Node(const T value)
        : m_value(value) {

        }
        T getValue() {
            return m_value;
        }
        size_t count() const {
            size_t counter = 0;
            for(const auto& child : m_pChildren) {
                counter += child->count();
            }
            return counter + 1;
        }
        size_t height() const {
            size_t counter = 0;
            for(const auto& child : m_pChildren) {
                size_t childHeight = child->height();
                if(childHeight > counter) {
                    counter = childHeight;
                }
            }
            return counter + 1;
        }
        static bool replaceNode(std::shared_ptr<Node<T>>& replacement, std::shared_ptr<Node<T>>& current) {
            if(current->m_value == replacement->m_value) {
                current = replacement;
                return true;
            }
            for(auto& child : current->m_pChildren) {
                if(replaceNode(replacement, child)) {
                    return true;
                }
            }
            return false;
        }
        static bool findNode(T value, std::shared_ptr<Node<T>>& out) {
            for(auto& child : out->m_pChildren) {
                // out = child;
                if(findNode(value, child)) {
                    return true;
                }
            }
            return false;
        }
        static bool addEdge(const T n1, const T n2, std::shared_ptr<Node<T>>& current) {
            if(current->m_value == n1) {
                current->m_pChildren.push_back(std::make_shared<Node<T>>(n2));
                return true;
            }
            for(auto& child : current->m_pChildren) {
                // current = child;
                if(addEdge(n1, n2, child)) {
                    return true;
                }
            }
            return false;
        }
        static void preorder(std::shared_ptr<Node<T>>& current) {
            std::cout << current->m_value << " ";
            for(auto& child : current->m_pChildren) {
                preorder(child);
            }
        }
    };

    template <typename T>
    class Tree {
    private:
        std::shared_ptr<Node<T>> m_pRoot;
        std::list<std::pair<T, T>> m_danglingEdges;
        std::shared_ptr<Node<T>> findNode(T value) {
            if(!m_pRoot) {
                return nullptr;
            }

            auto newPtr = m_pRoot;
            Node<T>::findNode(newPtr);
            return newPtr;
        }
        void integrateDanglingEdges() {
            for(auto it = m_danglingEdges.begin(); it != m_danglingEdges.end();) {
                if(Node<T>::addEdge(it->first, it->second, m_pRoot)) {
                    m_danglingEdges.erase(it);
                    it = m_danglingEdges.begin();
                }
                it++;
            }
        }
    public:
        Tree() {

        }
        void addEdge(T n1, T n2) {
            // std::cout << "dangling: " << m_danglingEdges.size() << std::endl;
            if(!m_pRoot) {
                m_pRoot = std::make_shared<Node<T>>(n1);
            }

            bool addedNodeToMainTree = Node<T>::addEdge(n1, n2, m_pRoot);

            if(addedNodeToMainTree) {
                integrateDanglingEdges();
            } else {
                m_danglingEdges.push_back(std::pair<T, T>{n1, n2});
            }
        }
        void preorder() {
            if(!m_pRoot) {
                std::cout << "empty" << std::endl;
                return;
            }
            Node<T>::preorder(m_pRoot);
            std::cout << std::endl;
        }
        int count() {
            if(!m_pRoot) {
                return 0;
            } else {
                return static_cast<int>(m_pRoot->count());
            }
        }
        int height(){
            if(!m_pRoot) {
                return -1;
            } else {
                return static_cast<int>(m_pRoot->height()) - 1;
            }
        }
    };
}


