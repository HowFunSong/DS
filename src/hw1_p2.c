#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 100000


int parent[MAXN];
int height[MAXN];

// Initialize the sets
void initialize(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = -1; // Each element is the root of its own set with height -1
        height[i] = 0;  // Initial height is 0
    }
}

// Find the root of a set (with path compression)
int find(int x) {

    if (parent[x] < 0) {
        return x; // x is the root of its own set
    } else {
        // Path compression: Update the parent to the root of the set
        parent[x] = find(parent[x]);
        return parent[x];
    }

}

// Perform a union operation using height rule
void unionSets(int a, int b) {

    int rootA = find(a);
    int rootB = find(b);
    // printf("%d %d", rootA,rootB);
    if (rootA == rootB) {
        return; // a and b are already in the same set
    }
    
    // Attach the smaller tree (by height) to the root of the larger tree
    if (height[rootA] < height[rootB]) {
        parent[rootA] = rootB;
    } else if (height[rootA] > height[rootB]) {
        parent[rootB] = rootA;
    } else {
        // Heights are equal, attach either one and increase the height
        parent[rootB] = rootA;
        height[rootA]++;
    }
    return ;
}

// Check if two elements are in the same set
int sameSet(int a, int b) {
    return find(a) == find(b);
}

int main() {
    int t;
    
    scanf("%d", &t);
    // printf("There are(a) %d test case\n",t);
    while (t--) {
        int n, ops;
        scanf("%d %d", &n, &ops);
        // printf("There a %d node, and %d operation\n", n, ops);
        initialize(n);

        while (ops--) {
            char op[10];
            int a, b;
            // printf("Enter operation\n");
            scanf("%s", &op);
        
            if (strcmp(op,"union")==0) {
                // Union operation
                // printf("Union, enter two node : ");
                scanf("%d %d", &a, &b);
                unionSets(a, b);
                // printf("Successfully union!\n");
            } else if (strcmp(op,"find")==0) {
                // Find operation
                // printf("Find, Find root of node, enter node : ");
                scanf("%d", &a);
                // printf("the root of %d is %d\n", a,find(a));
                printf("%d\n",find(a));

            } else if (strcmp(op,"same")==0) {
                // Same operation
                // printf("Is Same, compare two node is at same tree, enter two node : ");
                scanf("%d %d", &a, &b);
                // printf("the anser is %s\n", sameSet(a, b) ? "true" : "false");
                printf("%s\n", sameSet(a, b) ? "true" : "false");
            }
        }
    }

    return 0;
}
