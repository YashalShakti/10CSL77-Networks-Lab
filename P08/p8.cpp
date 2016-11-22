#include<iostream>
#include<stdio.h>

using namespace std;

/**
 * Write a program for distance vector algorithm to find suitable path for transmission.
 */


// Simple struct to maintain the distance and paths to various nodes from each node
struct node {
  int distanceTo[20];
  int pathTo[20];
} nodes[10];

int main() {
  int n, distanceMatrix[20][20], flag = 1;

  cout << "Enter the number of nodes \n";
  cin >> n;

  cout << "Enter the distance matrix \n";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> distanceMatrix[i][j];
      nodes[i].distanceTo[j] = distanceMatrix[i][j];
      nodes[i].pathTo[j] = j;
    }
  }

  // Use flag to check if any better path was found and continue until there is no better path
  while (flag) {
    flag = 0;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
          if (nodes[i].distanceTo[j] > distanceMatrix[i][k] + nodes[k].distanceTo[j]) {
            nodes[i].distanceTo[j] = distanceMatrix[i][k] + nodes[k].distanceTo[j];
            nodes[i].pathTo[j] = k;
            flag = 1;
          }
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    cout << "\nRouting table for router " << i + 1 << ":\nDest.\tNextHop\tDist.\n";
    for (int j = 0; j < n; j++)
      printf("%d\t%d\t%d\n", j + 1, nodes[i].pathTo[j] + 1, nodes[i].distanceTo[j]);
  }

  int src, dest;
  cout << "\nEnter source and destination : ";
  cin >> src >> dest;

  src--;
  dest--;
  printf("Shortest path : \n Via router : %d\n Shortest distance : %d \n",
         nodes[src].pathTo[dest] + 1,
         nodes[src].distanceTo[dest]);

  return 0;
}

/*
 * Sample input
 *
  Enter the number of nodes
  3
  Enter the distance matrix
  0 3 2
  2 0 5
  2 2 0
 */
