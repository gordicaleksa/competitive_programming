// brute forces
void factor(int n) {          
	 	int i;          
		for(i=2;i<=(int)sqrt(n);i++) {            
			while(n % i == 0) {              
				cout << i << " ";             
				n /= i;            
			}          
		}          
		if (n > 1) cout << n << endl;    
}   