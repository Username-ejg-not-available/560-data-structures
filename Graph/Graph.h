#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

class Graph {
public:
    struct Edge {
        int Front, Back;
        double Weight;
        Edge() : Front(-1), Back(-1), Weight(-1) {}
        Edge(int f, int b, double w) : Front(f), Back(b), Weight(w) {}
        Edge(const Edge& copy) {
            Front = copy.Front;
            Back = copy.Back;
            Weight = copy.Weight;
        }
        friend std::ostream& operator<<(std::ostream& os, Edge e) {
            os << "(" << e.Front << "," << e.Back << "){" << e.Weight << "}";
            return os;
        }
        operator int() const { return Weight; }
    };

    class Vertex {
    private:
        int _numEdges;
    public:
        int id;
        struct Edge* EdgesOut;
        Vertex() : _numEdges(-1), id(-1), EdgesOut(nullptr) {}
        Vertex(int id, int num) : _numEdges(num), id(id) {
            EdgesOut = new Edge[num];
        }
        ~Vertex() { if (EdgesOut != nullptr) delete[] EdgesOut; }
        void addEdge(struct Edge e) { EdgesOut[e.Back - 1] = e; }
    };

    Graph(int);
    ~Graph();
    void addEdge(Edge);
    void BFS() const;
    void DFS() const;
    void Kruskal() const;
    void Prim() const;
    struct Vertex* getVertex(int) const;
    void print() const;
private:
    int _numVert;
    Vertex** _vertices;

    void DFS(Vertex*, Edge* tree, Edge* back, int& s1, int& s2, bool[]) const;
};
#endif