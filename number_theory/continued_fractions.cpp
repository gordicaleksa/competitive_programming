// continued fraction coefficients
// for example: [8,2,3] = 1/(8+1/(2+1/3))
vector<int> decompose(int a, int b) {
	// Euclid's algorithm
	int r = a % b;
	vector<int> cf;
	cf.push_back(a / b);
	while (r != 0) {
		a = b;
		b = r;
		r = a % b;
		cf.push_back(a / b);
	}
	return cf;
}

double build(vector<int>& cf) {
	// construct semi-convergent from continued fraction
	int num_pp = 1, num_p = cf[0];
	int den_pp = 0, den_p = 1;
	int num = num_p;
	int den = den_p;
	
	for (int i = 1; i < cf.size(); i++) {
		num = cf[i] * num_p + num_pp;
		den = cf[i] * den_p + den_pp;
		num_pp = num_p;
		num_p = num;
		den_pp = den_p;
		den_p = den;
	}
	return (double)num/(double)den;
}