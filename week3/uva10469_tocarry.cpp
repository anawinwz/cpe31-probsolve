#include<iostream>
#include<bitset>
using namespace std;
int main() {
  bitset<32> bA, bB;
  bitset<32> sum;
  int A, B;
  while (cin >> A >> B) {
    bA = bitset<32>(A); bB = bitset<32>(B);
    for (int i = 0; i < 32; i++) {
      A = bA[i]; B = bB[i];
      //cout << A << " " << B << endl;
      sum[i] = (!A && B) || (A && !B);
    }
    cout << (int)sum.to_ulong() << endl;
  }
  return 0;
}