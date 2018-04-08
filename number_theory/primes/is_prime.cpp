#include <cmath>
using namespace std;

bool is_prime (int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    int m = sqrt(n);

    for (int i = 3; i <= m; i += 2)
        if (n % i == 0) return false;

    return true;
}