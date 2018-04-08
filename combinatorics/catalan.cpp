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

// A binomial coefficient based function to find nth catalan number
// O(n) time
unsigned long long catalan(unsigned int n)
{
    // Calculate value of 2nCn
    unsigned long long c = choose(2*n, n);
 
    // return 2nCn/(n+1)
    return c/(n+1);
}