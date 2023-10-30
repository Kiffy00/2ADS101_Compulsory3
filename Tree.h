#include <iostream>
#include <vector>

/// <summary>
/// Represents a node within a tree.
/// </summary>
/// <param name="T">The type of data stored within the node.</param>
template<typename T>
class TreeNode {
public:
    T data;
    std::vector<TreeNode<T>*> children;
    TreeNode<T>* parent;

    /// <summary>
    /// Initializes a new instance of the TreeNode class with specified data.
    /// </summary>
    /// <param name="data">The data stored within the node.</param>
    TreeNode(const T& data) : data(data), parent(nullptr) {}

    /// <summary>
    /// Determines whether the node is the root of a tree.
    /// </summary>
    /// <returns>true if the node is a root; otherwise, false.</returns>
    bool isRoot() const {
        return parent == nullptr;
    }

    /// <summary>
    /// Determines whether the node is a leaf (has no children).
    /// </summary>
    /// <returns>true if the node is a leaf; otherwise, false.</returns>
    bool isLeaf() const {
        return children.empty();
    }
    
    /// <summary>
    /// Adds a new child node with the specified data to the current node.
    /// </summary>
    /// <param name="data">The data for the new child node.</param>
    /// <returns>A pointer to the newly created child node.</returns>
    TreeNode<T>* addChild(const T& data) {
        TreeNode<T>* child = new TreeNode(data);

        child->parent = this;
        children.push_back(child);
        return child;
    }

    /// <summary>
    /// Destructor for the TreeNode class. Deletes self last automatically.
    /// </summary>
    ~TreeNode() {
        for (auto child : children) {
            delete child;
        }
    }
};

/// <summary>
/// Represents a tree data structure.
/// </summary>
/// <param name="T">The type of data stored within each node.</param>
template<typename T>
class Tree {
private:
    TreeNode<T>* root;

public:
    /// <summary>
    /// Initializes a new instance of the Tree class with an initial root node.
    /// </summary>
    /// <param name="rootData">The data for the root node.</param>
    Tree(const T& rootData) : root(new TreeNode<T>(rootData)) {}

    /// <summary>
    /// Determines whether the tree has any nodes.
    /// </summary>
    /// <returns>true if the tree is empty; otherwise, false.</returns>
    bool isEmpty() const {
        return root == nullptr;
    }

    /// <summary>
    /// Counts the number of directed nodes in the entire tree.
    /// </summary>
    /// <returns>The size of the tree.</returns>
    int size() const {
        return countNodes(root);
    }

    /// <summary>
    /// Calculates the depth (or height) of the tree.
    /// </summary>
    /// <returns>The depth of the tree.</returns>
    int depth() const {
        return computeDepth(root);
    }

    /// <summary>
    /// Retrieves the root node of the tree.
    /// </summary>
    /// <returns>A pointer to the root node.</returns>
    TreeNode<T>* getRoot() const {
        return root;
    }

    /// <summary>
    /// Inserts a new node with the specified data at a random leaf node in the tree.
    /// </summary>
    /// <param name="data">The data for the new node.</param>
    void insertRandom(const T& data) {
        TreeNode<T>* current = root;

        while (!current->isLeaf()) {
            int randomIndex = rand() % current->children.size();
            current = current->children[randomIndex];
        }
        current->addChild(data);
    }

    /// <summary>
    /// Inserts a new node with the specified data as a child of the given parent node.
    /// </summary>
    /// <param name="parent">A pointer to the parent node.</param>
    /// <param name="data">The data for the new node.</param>
    void insertAsChild(TreeNode<T>* parent, const T& data) {
        parent->addChild(data);
    }

    /// <summary>
    /// Deletes the specified node and its children from the tree.
    /// </summary>
    /// <param name="node">A pointer to the node to delete.</param>
    void deleteNode(TreeNode<T>* node) {
        if (!node)
            return;

        if (node->isRoot()) {
            delete root;
            root = nullptr;
        }
        else {
            TreeNode<T>* parentNode = node->parent;

            auto it = std::find(parentNode->children.begin(), parentNode->children.end(), node);
            if (it != parentNode->children.end()) {
                parentNode->children.erase(it);
                delete node;  // here it deletes all children of the node due to the destructor
            }
        }
    }

    /// <summary>
    /// Destructor for the Tree class. Cleans up dynamically allocated memory.
    /// </summary>
    ~Tree() {
        delete root;
    }

private:
    /// <summary>
    /// Recursively counts the number of nodes in the subtree rooted at the given node.
    /// </summary>
    /// <param name="node">A pointer to the starting node.</param>
    /// <returns>The number of nodes in the subtree.</returns>
    int countNodes(TreeNode<T>* node) const {
        if (!node) 
            return 0;

        int count{ 1 }; // count self
        for (TreeNode<T>* child : node->children) {
            count += countNodes(child);
        }
        return count;
    }

    /// <summary>
    /// Recursively calculates the depth of the subtree rooted at the given node.
    /// </summary>
    /// <param name="node">A pointer to the starting node.</param>
    /// <param name="currentDepth">The current depth, which defaults to 0 for initial calls.</param>
    /// <returns>The depth of the subtree.</returns>
    int computeDepth(TreeNode<T>* node, int currentDepth = 0) const {
        if (!node)
            return currentDepth;

        int maxDepth = currentDepth;
        for (TreeNode<T>* child : node->children) {
            maxDepth = std::max(maxDepth, computeDepth(child, currentDepth + 1));
        }

        return maxDepth;
    }
};