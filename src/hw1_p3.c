#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge in the graph
struct Edge {
    int source, target, weight;
};

// Structure to represent a disjoint-set (used for cycle detection)
struct DisjointSet {
    int *parent, *rank;
    int size;
};

// Create a new disjoint-set of size V
struct DisjointSet* createSet(int V) {
    struct DisjointSet* set = (struct DisjointSet*)malloc(sizeof(struct DisjointSet));
    set->size = V;
    set->parent = (int*)malloc(V * sizeof(int));
    set->rank = (int*)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) {
        set->parent[i] = i; // Each vertex is its own parent initially
        set->rank[i] = 0;   // Rank is initially 0
    }

    return set;
}

// Find the set to which a vertex belongs (with path compression)
int find(struct DisjointSet* set, int vertex) {
    if (set->parent[vertex] != vertex)
        set->parent[vertex] = find(set, set->parent[vertex]); // Path compression
    return set->parent[vertex];
}

// Perform union of two sets (with union by rank)
void unionSets(struct DisjointSet* set, int x, int y) {
    int rootX = find(set, x);
    int rootY = find(set, y);

    if (rootX == rootY) return;

    if (set->rank[rootX] < set->rank[rootY])
        set->parent[rootX] = rootY;
    else if (set->rank[rootX] > set->rank[rootY])
        set->parent[rootY] = rootX;
    else {
        set->parent[rootY] = rootX;
        set->rank[rootX]++;
    }
}

// Compare function for sorting edges by weight in ascending order
int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

// Kruskal's algorithm to find the minimum spanning tree
long long kruskalMST(struct Edge* edges, int V, int E) {
    //sort edge 
    qsort(edges, E, sizeof(struct Edge), compareEdges);

    struct DisjointSet* set = createSet(V);

    long long minCost = 0;
    int edgeCount = 0;

    for (int i = 0; i < E; i++) {
        int source = edges[i].source;
        int target = edges[i].target;

        if (find(set, source) != find(set, target)) {
            minCost += (long long)edges[i].weight;
            unionSets(set, source, target);
            edgeCount++;
        }

        if (edgeCount == V - 1) // We have found V-1 edges
            break;
    }

    free(set->parent);
    free(set->rank);
    free(set);

    return minCost;
}

int main() {
    int V, E;
    // printf("Enter the vertex and edge number : ");
    scanf("%d %d", &V, &E);

    struct Edge* edges = (struct Edge*)malloc(E * sizeof(struct Edge));

    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].source, &edges[i].target, &edges[i].weight);
    }

    long long minCost = kruskalMST(edges, V, E);
    printf("%lld\n", minCost);

    free(edges);

    return 0;
}
