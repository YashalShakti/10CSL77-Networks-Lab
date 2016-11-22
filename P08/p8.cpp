#include<iostream>
#include<stdio.h>

using namespace std;

struct node {
  int dist[20];
  int from[20];
} rt[10];

int main() {
  int n, distance_matrix[20][20], flag = 1;

  cout << "Enter the number of nodes \n";
  cin >> n;

  cout << "Enter the distance matrix \n";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> distance_matrix[i][j];
      rt[i].dist[j] = distance_matrix[i][j];
      rt[i].from[j] = j;
    }
  }

  cout << "Calculating\n";

  while (flag) {
    flag = 0;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
          if (rt[i].dist[j] > distance_matrix[i][k] + rt[k].dist[j]) {
            rt[i].dist[j] = distance_matrix[i][k] + rt[k].dist[j];
            rt[i].from[j] = k;
            flag = 1;
          }
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    cout << "\nRouting table for router" << i + 1 << ":\nDest\tNextHop\tDist\n";
    for (int j = 0; j < n; j++)
      printf("%d\t%d\t%d\n", j + 1, rt[i].from[j] + 1, rt[i].dist[j]);
  }

  int src, dest;
  cout << "\nEnter source and destination : ";
  cin >> src >> dest;

  src--;
  dest--;
  printf("Shortest path : \n Via router : %d\n Shortest distance : %d \n", rt[src].from[dest] + 1, rt[src].dist[dest]);
  return 0;

}
