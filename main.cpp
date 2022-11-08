// EulerHacker091.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cinttypes>

using namespace std;

int gcd(int a, int b, int& x, int& y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	int x1, y1;
	int d = gcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - y1 * (a / b);
	return d;
}

bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
	g = gcd(abs(a), abs(b), x0, y0);
	if (c % g) {
		return false;
	}

	x0 *= c / g;
	y0 *= c / g;
	if (a < 0) x0 = -x0;
	if (b < 0) y0 = -y0;
	return true;
}

void shift_solution(int & x, int & y, int a, int b, int cnt) {
	x += cnt * b;
	y -= cnt * a;
}

int find_all_solutions(int a, int b, int c, int n) {
	if (b == 0) return n;

	int x, y, g;
	if (!find_any_solution(a, b, c, x, y, g))
		return 0;
	a /= g;
	b /= g;

	int sign_a = a > 0 ? +1 : -1;
	int sign_b = b > 0 ? +1 : -1;

	shift_solution(x, y, a, b, ( -x) / b);
	if (x < 0)
		shift_solution(x, y, a, b, sign_b);
	if (x > n)
		return 0;
	int lx1 = x;

	shift_solution(x, y, a, b, (n - x) / b);
	if (x > n)
		shift_solution(x, y, a, b, -sign_b);
	int rx1 = x;

	shift_solution(x, y, a, b,  y / a);
	if (y < 0)
		shift_solution(x, y, a, b, -sign_a);
	if (y > n)
		return 0;
	int lx2 = x;

	shift_solution(x, y, a, b, -(n - y) / a);
	if (y > n)
		shift_solution(x, y, a, b, sign_a);
	int rx2 = x;

	if (lx2 > rx2)
		swap(lx2, rx2);
	int lx = max(lx1, lx2);
	int rx = min(rx1, rx2);

	if (lx > rx)
		return 0;
	return (rx - lx) / abs(b);
}

int main()
{
	int n = 50;

	int64_t sol = 0;

	for(int a = 1; a <= n; a++)
	{
		for(int b = 0; b < a; b++)
		{
			sol += find_all_solutions(a, b, a*a + b*b, n);
		}
	}

	sol = sol + sol;

	sol += n*n;

	for (int a = 1; a <= n; a++)
	{
		sol += find_all_solutions(a, a, 2*a*a, n);
		
	}

	cout << sol << endl;

    return 0;
}
