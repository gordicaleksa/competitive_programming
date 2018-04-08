/* this function calculates (a*b)%c taking into account that a*b might overflow */
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