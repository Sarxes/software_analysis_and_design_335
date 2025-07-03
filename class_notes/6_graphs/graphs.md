# Graphs in C++

## 1. What Is a Graph?

A **graph** is a mathematical structure used to model relationships between objects. It consists of:
- **Vertices (nodes):** The entities
- **Edges (links):** The connections between the entities

Graphs are useful for representing:
- Social networks
- Computer networks
- Road maps
- Dependencies in software build systems
- Many algorithmic problems

### Types of Graphs

1. **Directed vs Undirected**
   - *Directed:* Edges have direction (e.g., a → b)
   - *Undirected:* Edges are bidirectional (e.g., a — b)

2. **Weighted vs Unweighted**
   - *Weighted:* Each edge has a cost or value (e.g., distance, time)
   - *Unweighted:* Edges represent connection only, with no associated cost

3. **Sparse vs Dense**
   - *Sparse:* Relatively few edges
   - *Dense:* Close to the maximum number of edges

---

## 2. Graph Representations in C++

Choosing how to represent a graph depends on the type of graph and the operations you’ll perform.

### Adjacency Matrix

A 2D array `matrix[V][V]` where:
- `matrix[i][j]` is non-zero (or the weight) if there’s an edge from vertex `i` to `j`
- It’s zero if there’s no edge

#### Pros:
- Simple to implement
- Fast edge existence check: O(1)

#### Cons:
- High space usage: O(V²)
- Inefficient for sparse graphs

```cpp
const int V = 5;
int graph[V][V] = {0};

// Add an undirected edge with weight 3 between vertex 0 and 1
graph[0][1] = 3;
graph[1][0] = 3;
```

---

### Adjacency List

Uses an array or vector of lists to store adjacent vertices.

```cpp
std::vector<std::vector<int>> adjList(V);

// For undirected graph
void addEdge(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}
```

#### For weighted graphs:

```cpp
std::vector<std::vector<std::pair<int, int>>> adjList(V);

// pair<destination, weight>
void addEdge(int u, int v, int weight) {
    adjList[u].emplace_back(v, weight);
}
```

#### Pros:
- Space efficient: O(V + E)
- Ideal for sparse graphs

#### Cons:
- Slower to check if an edge exists

---

## 3. Graph Traversal

Graph traversal is visiting all nodes in a structured way.

### Breadth-First Search (BFS)

BFS explores level by level(trees) or neighbor by neighbor(graphs), starting from a source node.

- Uses a queue
- Ideal for shortest path in unweighted graphs

```cpp
void BFS(int start, const std::vector<std::vector<int>>& adjList, std::vector<bool>& visited) {
    std::queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        std::cout << u << " ";

        for (int v : adjList[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}
```

---

### Depth-First Search (DFS)

DFS explores as far as possible down a branch before backtracking.

- Uses recursion or a stack
- Useful for topological sort, cycle detection

```cpp
void DFS(int u, const std::vector<std::vector<int>>& adjList, std::vector<bool>& visited) {
    visited[u] = true;
    std::cout << u << " ";

    for (int v : adjList[u]) {
        if (!visited[v]) {
            DFS(v, adjList, visited);
        }
    }
}
```

---

## 4. Kruskal's Algorithm (Minimum Spanning Tree)

### What is a Minimum Spanning Tree?

Given a connected, undirected, weighted graph, a **Minimum Spanning Tree (MST)** is a subset of edges that:
- Connects all vertices
- Has no cycles
- Has the minimum possible total edge weight

---

### Kruskal’s Algorithm Overview

Steps:
1. Sort all edges in non-decreasing order of weight
2. Initialize a Union-Find (Disjoint Set) to detect cycles
3. Add the smallest edge that doesn’t form a cycle
4. Repeat until we have V-1 edges

### Disjoint Set (Union-Find)

Tracks which vertex belongs to which subset (i.e., connected component)

```cpp
class DisjointSet {
private:
    std::vector<int> parent, rank;

public:
    DisjointSet(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]); // Path compression
        return parent[u];
    }

    void unite(int u, int v) {
        int pu = find(u);
        int pv = find(v);
        if (pu == pv) return;

        if (rank[pu] < rank[pv])
            parent[pu] = pv;
        else if (rank[pu] > rank[pv])
            parent[pv] = pu;
        else {
            parent[pv] = pu;
            rank[pu]++;
        }
    }
};
```

---

### Graph Class with Kruskal's Algorithm

```cpp
class Graph {
private:
    int V;
    std::vector<std::tuple<int, int, int>> edges; // (weight, u, v)

public:
    Graph(int V) : V(V) {}

    void addEdge(int u, int v, int weight) {
        edges.emplace_back(weight, u, v);
    }

    void kruskalMST() {
        std::sort(edges.begin(), edges.end());

        DisjointSet ds(V);
        std::vector<std::tuple<int, int, int>> mst;
        int totalWeight = 0;

        for (const auto& [weight, u, v] : edges) {
            if (ds.find(u) != ds.find(v)) {
                mst.emplace_back(weight, u, v);
                ds.unite(u, v);
                totalWeight += weight;
            }
        }

        std::cout << "Edges in MST:\n";
        for (const auto& [weight, u, v] : mst) {
            std::cout << u << " -- " << v << " [weight: " << weight << "]\n";
        }
        std::cout << "Total MST weight: " << totalWeight << "\n";
    }
};
```

---

### Example Usage

```cpp
int main() {
    Graph g(6);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 8);
    g.addEdge(2, 4, 10);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 3);

    g.kruskalMST();
    return 0;
}
```

---

## Summary

- **Graphs** are versatile data structures.
- Choose **adjacency list** for sparse graphs and **matrix** for dense graphs.
- Use **BFS** for shortest paths in unweighted graphs.
- Use **DFS** for reachability, topological sort, and cycle detection.
- **Kruskal's algorithm** gives the minimum spanning tree using sorting and Union-Find.
