#include <iostream>
using namespace std;

size_t min(size_t a, size_t b)
{
	return (a < b ? a : b);
}

size_t OptimalCostOfBST(size_t n, size_t *arr)
{
	size_t *s = new size_t[n];
	size_t **dp = new size_t*[n];
	for (size_t i = 0; i < n; i++) dp[i] = new size_t[n];

	for (size_t i = 0; i < n; i++) dp[i][i] = 0;
	s[0] = arr[0];

	for (size_t i = 1; i < n; i++) s[i] = s[i - 1] + arr[i];
	for (size_t t = 1; t < n; t++)
	{
		for (size_t i = 0; i < n; i++)
		{
			if (i + t >= n)	break;
			size_t mn = -1;
			for (size_t j = i; j <= i + t; j++)
			{
				mn = min(mn, (j >= i + 1 ? s[j - 1] - (i < 1 ? 0 : s[i - 1]) + dp[i][j - 1] : 0) +
					(j + 1 <= i + t ? s[i + t] - s[j] + dp[j + 1][i + t] : 0));
			}
			dp[i][i + t] = mn;
		}
	}

	size_t res = dp[0][n - 1];
	delete[] s;
	for (size_t i = 0; i < n; i++) delete[] dp[i];
	delete[] dp;
	return res;
}

int main()
{
	size_t n; 
	cin >> n;

	size_t *arr = new size_t[n];
	for (size_t i = 0; i < n; i++) cin >> arr[i];

	cout << OptimalCostOfBST(n, arr) << endl;

	delete[] arr;
	system("pause");
	return 0;
}