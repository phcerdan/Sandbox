// Example program
#include <iostream>
#include <string>

int main() {
  int *m = new int[3];
  m[0] = 10;
  m[1] = 20;
  m[2] = 30;
  int *n = new int[3];
  n[0] = 100;
  n[1] = 200;
  n[2] = 300;
  int **a = new int *[2];
  a[0] = m;
  a[1] = n;

  std::cout << *(a[0]) << std::endl;
  std::cout << *(a[0]++) << std::endl;
  std::cout << *(a[0]) << std::endl;
  *(a[0]++) = 5000;
  std::cout << *(a[0]) << std::endl;
  std::cout << "Show all a[0]:" << std::endl;
  std::cout << a[0][0] << std::endl;
  std::cout << a[0][1] << std::endl;
  std::cout << a[0][2] << std::endl;
  std::cout << a[0][-1] << std::endl;
  std::cout << a[0][-2] << std::endl;
}
