#include "Graph.h"
#include "DisjointSet.h"
#include "MinHeap.h"

bool compareArray(bool* a, int n);

Graph::Graph(int verts) {
    this->_numVert = verts;
    this->_vertices = new Vertex*[verts];
    for (int i = 0; i < _numVert; i++) {
        this->_vertices[i] = new Vertex(i + 1, _numVert);
    }
}

Graph::~Graph() {
    for (int i = 0; i < this->_numVert; i++) delete this->_vertices[i];
    delete[] this->_vertices;
}

void Graph::addEdge(Edge e) {
    if (e.Front > _numVert || e.Front < 1 || e.Back > _numVert || e.Back < 1)
        throw(std::runtime_error("Invalid Edge."));
    this->_vertices[e.Front - 1]->addEdge(e);
}

Graph::Vertex* Graph::getVertex(int i) const {
    if (i < 0 || i > this->_numVert) return nullptr;
    return this->_vertices[i];
}

void Graph::print() const {
    for (int i = 0; i < _numVert; i++) {
        std::cout << i + 1 << ": ";
        for (int j = 0; j < _numVert; j++) {
            std::cout << this->_vertices[i]->EdgesOut[j] << ", ";
        }
        std::cout << "\n";
    }
}

void Graph::BFS() const {
    if (!this->_numVert) return;
    Edge tree[_numVert * _numVert];
    Edge cross[_numVert * _numVert];
    bool visited[_numVert];
    for (int i = 0; i < _numVert; i++) visited[i] = false;
    visited[0] = true;
    int size1 = 0, size2 = 0;
    for (int i = 0; i < this->_numVert; i++) {
        for (int j = i + 1; j < this->_numVert; j++) {
            if (this->_vertices[i]->EdgesOut[j].Weight == -1) continue;
            if (visited[this->_vertices[i]->EdgesOut[j].Back - 1]) {
                cross[size2] = this->_vertices[i]->EdgesOut[j];
                size2++;
            }
            else {
                tree[size1] = this->_vertices[i]->EdgesOut[j];
                size1++;
                visited[this->_vertices[i]->EdgesOut[j].Back - 1] = true;
            }
        }
    }
    std::cout << "Tree Edges: ";
    for (int i = 0; i < size1; i++) {
        std::cout << "(" << tree[i].Front << ", " << tree[i].Back << ") ";
    }
    std::cout << "\nCross Edges: ";
    for (int i = 0; i < size2; i++) {
        std::cout << "(" << cross[i].Front << ", " << cross[i].Back << ") ";
    }
    std::cout << "\n";
}

void Graph::DFS() const {
    if (!this->_numVert) return;
    Edge* tree = new Edge[_numVert * _numVert];
    Edge* back = new Edge[_numVert * _numVert];
    int s1 = 0, s2 = 0;
    bool visited[_numVert];
    for (int i = 0; i < _numVert; i++) visited[i] = false;
    visited[0] = true;
    DFS(this->_vertices[0], tree, back, s1, s2, visited);
    std::cout << "Tree Edges: ";
    for (int i = 0; i < s1; i++) {
        std::cout << "(" << tree[i].Front << ", " << tree[i].Back << ") ";
    }
    std::cout << "\nBack Edges: ";
    for (int i = 0; i < s2; i++) {
        std::cout << "(" << back[i].Front << ", " << back[i].Back << ") ";
    }
    std::cout << "\n";
    delete[] tree;
    delete[] back;
}

void Graph::DFS(Vertex* v, Edge* tree, Edge* back, int& s1, int& s2, bool vis[]) const {
    std::cout << v->id << "\n";
    vis[v->id - 1] = true;
    for (int i = 0; i < _numVert; i++) {
        if (v->EdgesOut[i].Weight == -1 || v->EdgesOut[i].Front >= v->EdgesOut[i].Back) continue;
        if (vis[v->EdgesOut[i].Back - 1]) {
            back[s2] = v->EdgesOut[i];
            s2++;
            continue;
        }
        tree[s1] = v->EdgesOut[i];
        s1++;

        DFS(this->_vertices[v->EdgesOut[i].Back - 1],tree,back,s1,s2,vis);
    }
}

void Graph::Kruskal() const {
    Graph* mst = new Graph(_numVert);
    DisjointSet<int>* djs = new DisjointSet<int>();
    MinHeap<Edge>* edges = new MinHeap<Edge>();
    //create vertex sets and a heap of edges
    for (int i = 1; i < this->_numVert + 1; i++) {
        djs->add(i);
        for (int j = i; j < this->_numVert; j++) {
            if (this->_vertices[i - 1]->EdgesOut[j].Weight == -1) continue;
            Edge tempEdge(this->_vertices[i - 1]->EdgesOut[j]);
            edges->add(tempEdge);
        }
    }
    int mstEdges = 0;
    //add cheapest edges if they don't create a loop
    while (!edges->isEmpty()) {
        if (djs->find(edges->peek().Front) != djs->find(edges->peek().Back)) {
            mst->addEdge(edges->peek());
            djs->unionByRank(edges->peek().Front,edges->peek().Back);
            mstEdges++;
        }
        edges->pop();
    }

    //print
    if (mstEdges == this->_numVert - 1) {
        int total = 0;
        for (int i = 1; i < _numVert + 1; i++) {
            for (int j = i; j < _numVert; j++) {
                if (mst->getVertex(i - 1)->EdgesOut[j].Weight == -1) continue;
                std::cout << mst->getVertex(i - 1)->EdgesOut[j] << " ";
                total += mst->getVertex(i - 1)->EdgesOut[j].Weight;
            }
        }

        std::cout << "\nTotal cost = " << total << "\n";
    } else {
        std::cout << "\nNo tree exists using Kruskal's algorithm.\n";
    }
    delete mst;
    delete djs;
    delete edges;
}

/*void Graph::Prim() const {
    Graph* temp = new Graph(_numVert);
    bool U[_numVert];
    for (int i = 0; i < _numVert; i++) U[i] = false;
    U[0] = true;

    while (!compareArray(U, _numVert)) {
        Edge min;
        min.Weight = 0x7FFFFFFF;//int_max
        for (int i = 1; i < _numVert + 1; i++) {
            if (!U[i - 1]) continue;
            for (int j = 0; j < _numVert; j++) {
                //if edge doesnt exist, make like a tree and leaf
                if (this->_vertices[i - 1]->EdgesOut[j].Weight == -1) continue;
                //if dest Vertex in set U, make like a tree and leaf
                if (U[this->_vertices[i - 1]->EdgesOut[j].Back - 1]) continue;
                if (this->_vertices[i - 1]->EdgesOut[j].Weight < min.Weight) min = Edge(this->_vertices[i - 1]->EdgesOut[j]);
            }
        }
        //add edge and its inverse self to temp, add Vertex to U
        temp->addEdge(min);
        int tempval = min.Front;
        min.Front = min.Back;
        min.Back = tempval;
        temp->addEdge(min);
        U[min.Front - 1] = true;
    }

    int total = 0;
    for (int i = 1; i < _numVert + 1; i++) {
        for (int j = i; j < _numVert; j++) {
            if (temp->getVertex(i - 1)->EdgesOut[j].Weight == -1) continue;
            std::cout << temp->getVertex(i - 1)->EdgesOut[j] << " ";
            total += temp->getVertex(i - 1)->EdgesOut[j].Weight;
        }
    }

    std::cout << "\nTotal cost = " << total << "\n";

    delete temp;
}*/

void Graph::Prim() const {
    Graph* mst = new Graph(this->_numVert);
    MinHeap<Edge>* q = new MinHeap<Edge>();
    bool visited[_numVert];
    int mstEdges = 0;

    //init
    visited[0] = true;
    for (int i = 1; i < this->_numVert; i++) {
        visited[i] = false;
        if (this->_vertices[0]->EdgesOut[i].Weight != -1) {
            q->add(this->_vertices[0]->EdgesOut[i]);
        }
    }

    q->print();
    std::cout << "\n";

    while (!q->isEmpty() && !compareArray(visited, _numVert)) {
        Edge mincost = q->peek();
        q->pop();
        std::cout << "Popped: \n";
                        q->print();
                        std::cout << "\n";
        
        mst->addEdge(mincost);
        mst->addEdge(Edge(mincost.Back, mincost.Front, mincost.Weight));
        visited[mincost.Back - 1] = true;
        mstEdges++;
        //update q
        for (int i = 1; i < this->_numVert + 1; i++) {
            for (int j = i; j < _numVert; j++) {
                Edge e = this->_vertices[i - 1]->EdgesOut[j];
                if (e.Weight == -1) continue;
                //remove bad edge
                try {
                    if (mincost.Back == e.Back) {
                        q->remove(e);
                        std::cout << "Removed: " << e << "\n";
                        q->print();
                        std::cout << "\n";
                    }
                } catch (std::runtime_error& e) {}
            }
        }
        for (int i = 0; i < this->_numVert; i++) {
            //add good edge
            Edge e = this->_vertices[mincost.Back - 1]->EdgesOut[i];
            if (e.Weight == -1) continue;
            if (!visited[e.Back - 1]) {
                q->add(e);
                std::cout << "Added: " << e << "\n";
                        q->print();
                        std::cout << "\n";
            }
        }
    }

    //print
    if (mstEdges == this->_numVert - 1) {
        int total = 0;
        for (int i = 1; i < _numVert + 1; i++) {
            for (int j = i; j < _numVert; j++) {
                if (mst->getVertex(i - 1)->EdgesOut[j].Weight == -1) continue;
                std::cout << mst->getVertex(i - 1)->EdgesOut[j] << " ";
                total += mst->getVertex(i - 1)->EdgesOut[j].Weight;
            }
        }

        std::cout << "\nTotal cost = " << total << "\n";
    } else {
        std::cout << "\nNo tree exists using Prim's algorithm.\n";
    }

    delete q;
    delete mst;
}

bool compareArray(bool* a, int n) {
    for (int i = 0; i < n; i++) {
        if (!a[i]) return false;
    }
    return true;
}