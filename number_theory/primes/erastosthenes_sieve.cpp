// O (n log log n) (n = size)
bool* erastosthenes_sieve(int size) {
    bool *prime = new bool[size+1]; // suppose every number [0,...,size] is prime
    for (int i = 0; i < size+1; i++) prime[i] = true;
    prime[0] = false; // zero is not a prime
    prime[1] = false; // one is not a prime
    int m = sqrt(size);

    for (int i = 2; i <= m; i++)
        if (prime[i])
            for (int j = i*i; j <= n; j += i)
                prime[j] = false;

    return prime;
}