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

/* Miller-Rabin primality test, iteration signifies the accuracy of the test */
/* slower than Fermat but doesn't break down for specific composite number, 18-20 iterations is ok */
bool is_prime_miller(long long p,int iteration){
    if(p<2){
        return false;
    }
    if(p!=2 && (p&1)==0){
        return false;
    }
    long long s=p-1;
    while((s&1)==0){
        s >>= 1;
    }
    for(int i=0;i<iteration;i++){
        long long a=rand()%(p-1)+1,temp=s;
        long long mod=modulo(a,temp,p);
        while(temp!=p-1 && mod!=1 && mod!=p-1){
            mod=mulmod(mod,mod,p);
            temp <<= 1;
        }
        if(mod!=p-1 && (temp&1)==0){
            return false;
        }
    }
    return true;
}