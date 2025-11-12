#include <iostream>
#include <concepts>

using namespace std;

// Macros para que possa funcionar para qualquer valor em K
#define PAI(x, K) (((x) - 1) / K)
#define FILHO(x, K, i) ((K) * (x) + (i) + 1)

template <typename T>