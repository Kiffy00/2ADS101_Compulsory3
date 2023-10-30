#include <iostream>
#include <map>
#include <vector>
#include <queue>

/// <summary>
/// Represents a node within a graph.
/// </summary>
/// <param name="Key">The type of the key identifying the node.</param>
/// <param name="T">The type of data stored within the node.</param>
template<typename Key, typename T>
class GraphNode {
public:
    Key id;
    T data;
    std::vector<GraphNode<Key, T>*> adj;

    GraphNode(const Key& id, const T& data) : id(id), data(data) {}
};

/// <summary>
/// Initializes a new instance of the GraphNode class with specified id and data.
/// </summary>
/// <param name="id">The key identifier of the node.</param>
/// <param name="data">The data stored within the node.</param>
template<typename Key, typename T>
class Graph {
private:
    std::map<Key, GraphNode<Key, T>*> nodes;

public:
    /// <summary>
    /// Initializes a new instance of the Graph class with an initial vertex.
    /// </summary>
    /// <param name="id">The key identifier of the initial vertex.</param>
    /// <param name="data">The data stored within the initial vertex.</param>
    Graph(const Key& id, const T& data) {
        nodes[id] = new GraphNode<Key, T>(id, data);
    }

    /// <summary>
    /// Adds a new vertex to the graph.
    /// </summary>
    /// <param name="id">The key identifier of the vertex.</param>
    /// <param name="data">The data stored within the vertex.</param>
    void addVertex(const Key& id, const T& data) {
        if (!nodes[id]) {
            nodes[id] = new GraphNode<Key, T>(id, data);
        }
    }

    /// <summary>
    /// Adds an undirected edge between two vertices.
    /// </summary>
    /// <param name="src">The source vertex key.</param>
    /// <param name="dest">The destination vertex key.</param>
    void addEdge(const Key& src, const Key& dest) {
        if (!nodes[src] || !nodes[dest])
            return;

        nodes[src]->adj.push_back(nodes[dest]);
        nodes[dest]->adj.push_back(nodes[src]);
    }

        /// <summary>
    /// Removes an undirected edge between two vertices.
    /// </summary>
    /// <param name="src">The source vertex key.</param>
    /// <param name="dest">The destination vertex key.</param>
    void removeEdge(const Key& src, const Key& dest) {
        if (!nodes[src] || !nodes[dest])
            return;

        auto it = std::find(nodes[src]->adj.begin(), nodes[src]->adj.end(), nodes[dest]);
        if (it != nodes[src]->adj.end())
            nodes[src]->adj.erase(it);

        it = std::find(nodes[dest]->adj.begin(), nodes[dest]->adj.end(), nodes[src]);
        if (it != nodes[dest]->adj.end())
            nodes[dest]->adj.erase(it);
    }

    /// <summary>
    /// Removes a vertex and all its associated edges from the graph.
    /// </summary>
    /// <param name="id">The key identifier of the vertex to remove.</param>
    void removeVertex(const Key& id) {
        if (!nodes[id])
            return;

        for (auto& node : nodes) {
            auto it = std::find(node.second->adj.begin(), node.second->adj.end(), nodes[id]);
            if (it != node.second->adj.end())
                node.second->adj.erase(it);
        }

        delete nodes[id];
        nodes.erase(id);
    }

    /// <summary>
    /// Returns the number of vertices in the graph.
    /// </summary>
    /// <returns>The size of the graph.</returns>
    int size() const {
        return nodes.size();
    }

    /// <summary>
    /// Determines whether the graph has any vertices.
    /// </summary>
    /// <returns>true if the graph is empty; otherwise, false.</returns>
    bool isEmpty() const {
        return nodes.empty();
    }

    /// <summary>
    /// Performs Breadth-First Search from a starting vertex.
    /// </summary>
    /// <param name="startId">The starting vertex key.</param>
    void bfs(const Key& startId) {
        if (!nodes[startId])
            return;

        std::map<GraphNode<Key, T>*, bool> visited;
        std::queue<GraphNode<Key, T>*> q;

        q.push(nodes[startId]);
        visited[nodes[startId]] = true;

        while (!q.empty()) {
            GraphNode<Key, T>* curr = q.front();
            std::cout << curr->data << " ";
            q.pop();

            for (auto& neighbor : curr->adj) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        std::cout << std::endl;
    }

    /// <summary>
    /// Destructor for the Graph class. Nodes are explicitly removed before the automated map destructor removes its keys and pointers.
    /// </summary>
    ~Graph() {
        for (auto& nodePair : nodes) {
            delete nodePair.second;
        }
    }
};
