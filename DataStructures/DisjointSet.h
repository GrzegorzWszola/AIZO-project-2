#ifndef DISJOINTSET_H
#define DISJOINTSET_H

class DisjointSet {
    int* parent;
    int* size;

public:
    DisjointSet(int p) {
        parent = new int[p];
        size = new int[p];
        for (int i = 0; i < p; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    ~DisjointSet() {
        delete[] parent;
        delete[] size;
    }

    //Finding the root of the graph
    int find(int u) {
        int root = parent[u];

        if (parent[root] != root) {
            return parent[u] = find(root);
        }
        return root;
    }

    //Unioning 2 graphs together based on size
    void unionBySize(int i, int j) {
        int irep = find(i);
        int jrep = find(j);
        if (irep == jrep)
            return;

        int isize = size[irep];
        int jsize = size[jrep];

        if (isize < jsize) {
            parent[irep] = jrep;
            size[jrep] += size[irep];
        }
        else {
            parent[jrep] = irep;
            size[irep] += size[jrep];
        }
    }
};

#endif //DISJOINTSET_H
