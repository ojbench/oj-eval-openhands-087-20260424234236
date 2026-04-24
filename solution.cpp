
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int D;
    long long n;
    cin >> D >> n;
    
    // Calculate total number of nodes and leaf nodes
    int total_nodes = (1 << D) - 1;  // 2^D - 1
    int leaf_start = 1 << (D - 1);   // 2^(D-1), first leaf node
    int leaf_count = 1 << (D - 1);   // 2^(D-1), number of leaf nodes
    
    // Initialize all switches to closed (0)
    vector<int> switches(total_nodes + 1, 0);  // 1-indexed
    
    // Initialize virtual switches at leaf positions
    vector<int> leaf_switches(leaf_count, 0);  // 0-indexed for leaf positions
    
    int last_position = 0;
    
    // Simulate each ball
    for (long long ball = 0; ball < n; ball++) {
        int current = 1;  // Start at root
        
        // Fall through the tree until reaching a leaf
        while (current < leaf_start) {
            if (switches[current] == 0) {
                // Switch is closed, open it and go left
                switches[current] = 1;
                current = current * 2;  // Left child
            } else {
                // Switch is open, close it and go right
                switches[current] = 0;
                current = current * 2 + 1;  // Right child
            }
        }
        
        // Ball has landed at leaf position 'current'
        // Toggle the virtual switch at this leaf position
        int leaf_index = current - leaf_start;  // Convert to 0-indexed
        leaf_switches[leaf_index] = 1 - leaf_switches[leaf_index];
        
        last_position = current;
    }
    
    // Output the final position of the last ball
    cout << last_position << endl;
    
    // Output the state of all leaf node switches (from left to right)
    for (int i = 0; i < leaf_count; i++) {
        cout << leaf_switches[i];
        if (i < leaf_count - 1) {
            cout << " ";
        }
    }
    cout << endl;
    
    return 0;
}