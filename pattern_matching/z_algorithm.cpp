// time: O(n) 
void Z(const string s, int *z) {
	int L = 0, R = 0;
	int n = s.length();
	for (int i = 1; i < n; i++) {
		if (i > R) {
			L = R = i;
			while (R < n && s[R - L] == s[R]) R++;
			z[i] = R - L; R--;
		}
		else {
			int k = i - L;
			if (z[k] < R - i + 1) z[i] = z[k];
			else {
				L = i;
				while (R < n && s[R - L] == s[R]) R++;
				z[i] = R - L; R--;
			}
		}
	}
}