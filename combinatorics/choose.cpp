// O(k) time
unsigned long long choose(unsigned long long n, unsigned long long k) {
    if (k > n) {
        return 0;
    }
    // since C(n, k) = C(n, n-k)
    if (k > n-k)
	k = n-k;

    unsigned long long r = 1;
    for (unsigned long long d = 1; d <= k; ++d) {
        r *= n--;
        r /= d;
    }
    return r;
}

// found here:
// https://stackoverflow.com/questions/1838368/calculating-the-amount-of-combinations

// improved by looking at:
// https://www.geeksforgeeks.org/space-and-time-efficient-binomial-coefficient/