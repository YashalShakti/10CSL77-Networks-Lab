#include <iostream>
#include <iomanip>
using namespace std;

/**
 * Write a program for congestion control using Leaky bucket algorithm.
 *
 */

int min(int x, int y) {
  return x < y ? x : y;
}

int main() {
  int size, count = 0, drop, time, in[30], sent, rate, i;

  cout << "Enter bucket size (no of packets): ";
  cin >> size;
  cout << "Enter bandwidth (packets/second): ";
  cin >> rate;
  cout << "Enter burst time (seconds): ";
  cin >> time;

  for (i = 1; i <= time; i++) {
    cout << "Enter number of packets at time " << i << ": ";
    cin >> in[i];
  }

  cout << "\nTime |" << " Incoming |" << " Outgoing |" << " InBucket |" << " Drop " << endl;

  for (i = 1; i <= time; i++) {
    count += in[i];
    if (count > size) {
      drop = count - size;
      count = size;
    } else {
      drop = 0;
    }
    sent = min(count, rate);
    count -= sent;
    cout << setw(3) << i << setw(9) << in[i] << setw(11) << sent << setw(11) << count << setw(9) << drop;
    if (drop) {
      cout << " <-- non conforming packets";
    }
    cout << endl;
  }

  for (; count != 0; i++) {
    drop = 0;
    sent = min(count, rate);
    count -= sent;
    cout << setw(3) << i << setw(9) << "0" << setw(11) << sent << setw(11) << count << setw(9) << drop << endl;
  }

  return 0;
}
