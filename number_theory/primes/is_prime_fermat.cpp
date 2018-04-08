long long mulmod(long long a,long long b,long long c){
    long long x = 0,y=a%c;
    while(b > 0){
        if((b&1) == 1){
            x = (x+y)%c;
        }
        y = (y << 1)%c;
        b >>= 1;
    }
    return x%c;
}

long long modulo(long long a,long long b,long long c){
    long long x=1,y=a; // long long is taken to avoid overflow of intermediate results
    while(b > 0){
        if((b&1) == 1){
            x= mulmod(x,y,c);
        }
        y = mulmod(y,y,c); // squaring the base
        b >>= 1;
    }
    return x%c;
}

/* Fermat's test for checking primality, the more iterations the more is accuracy */
/* will fail w.h.p. on Carmichael numbers :( */
bool is_prime_fermat(long long p,int iterations){
    if(p == 1){ // 1 isn't prime
        return false;
    }
    for(int i=0;i<iterations;i++){
        // choose a random integer between 1 and p-1 ( inclusive ), C++11 has better random gens this is a C one.
        long long a = rand()%(p-1)+1;
        // modulo is the function we developed above for modular exponentiation.
        if(modulo(a,p-1,p) != 1){
            return false; /* p is definitely composite */
        }
    }
    return true; /* p is probably prime */
}