#include <iostream>
#include "Tree.h"
#include "Graph.h"

int main() {
    // Tree functionality //
    std::cout << "Tree Demonstration:\n";

    Tree<std::string> tree("Root");
    TreeNode<std::string>* root = tree.getRoot();

    TreeNode<std::string>* child1 = root->addChild("Child1");
    TreeNode<std::string>* child2 = root->addChild("Child2");

    child1->addChild("GrandChild1");
    child1->addChild("GrandChild2");
    child2->addChild("GrandChild3");

    std::cout << "Tree Size: " << tree.size() << "\n";
    std::cout << "Tree Depth: " << tree.depth() << "\n";
    std::cout << "Is Tree Empty? " << (tree.isEmpty() ? "Yes" : "No") << "\n";

    std::cout << "Inserting random node 'RandomChild'\n";
    tree.insertRandom("RandomChild");
    std::cout << "New Tree Size: " << tree.size() << "\n";

    std::cout << "Deleting Child2:\n";
    tree.deleteNode(child2);
    std::cout << "New Tree Size: " << tree.size() << "\n";

    // Graph functionality //
    std::cout << "\nGraph Demonstration:\n";

    Graph<int, std::string> graph(1, "Node1");

    graph.addVertex(2, "Node2");
    graph.addVertex(3, "Node3");
    graph.addVertex(4, "Node4");

    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);

    std::cout << "BFS starting from Node 1:\n";
    graph.bfs(1);

    std::cout << "Removing vertex 3:\n";
    graph.removeVertex(3);
    graph.bfs(1);

    std::cout << "Graph Size: " << graph.size() << "\n";
    std::cout << "Is Graph Empty? " << (graph.isEmpty() ? "Yes" : "No") << "\n";

    return 0;
}

