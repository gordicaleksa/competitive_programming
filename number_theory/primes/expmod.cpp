/* This function calculates (a^b)%c */
// works only when a,b,c are ints
// if we need long long include mulmod(x,y,c), mulmod(y,y,c), still 2*c must be long long for it to work
int modulo(int a,int b,int c){
    long long x=1,y=a; // long long is taken to avoid overflow of intermediate results
    while(b > 0){
        if((b&1) == 1){
            x=(x*y)%c;
        }
        y = (y*y)%c; // squaring the base
        b >>= 1;
    }
    return x%c;
}