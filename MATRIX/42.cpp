// An efficient method to find maximum value of mat[d]
// - ma[a][b] such that c > a and d > b
#include <bits/stdc++.h>
using namespace std;
#define N 5

// The function returns maximum value A(c,d) - A(a,b)
// over all choices of indexes such that both c > a
// and d > b.
int findMaxValue(int mat[][N])
{
	//stores maximum value
	int maxValue = INT_MIN;

	// maxArr[i][j] stores max of elements in matrix
	// from (i, j) to (N-1, N-1)
	int maxArr[N][N];

	// last element of maxArr will be same's as of
	// the input matrix
	maxArr[N-1][N-1] = mat[N-1][N-1];

	// preprocess last row
	int maxv = mat[N-1][N-1]; // Initialize max
	for (int j = N - 2; j >= 0; j--)
	{
		if (mat[N-1][j] > maxv)
			maxv = mat[N - 1][j];
		maxArr[N-1][j] = maxv;
	}

	// preprocess last column
	maxv = mat[N - 1][N - 1]; // Initialize max
	for (int i = N - 2; i >= 0; i--)
	{
		if (mat[i][N - 1] > maxv)
			maxv = mat[i][N - 1];
		maxArr[i][N - 1] = maxv;
	}

	// preprocess rest of the matrix from bottom
	for (int i = N-2; i >= 0; i--)
	{
		for (int j = N-2; j >= 0; j--)
		{
			// Update maxValue
			if (maxArr[i+1][j+1] - mat[i][j] >
											maxValue)
				maxValue = maxArr[i + 1][j + 1] - mat[i][j];

			// set maxArr (i, j)
			maxArr[i][j] = max(mat[i][j],
							max(maxArr[i][j + 1],
								maxArr[i + 1][j]) );
		}
	}

	return maxValue;
}

// Driver program to test above function
int main()
{
	int mat[N][N] = {
					{ 1, 2, -1, -4, -20 },
					{ -8, -3, 4, 2, 1 },
					{ 3, 8, 6, 1, 3 },
					{ -4, -1, 1, 7, -6 },
					{ 0, -4, 10, -5, 1 }
					};
	cout << "Maximum Value is "
		<< findMaxValue(mat);

	return 0;
}




for(int i = 0; i < n; i++)
	{
		dp[i][0] = min(dp[i-1][0] , mat[i][0]);
	}















#include <bits/stdc++.h> 
int findMaxValue(vector<vector<int>>& mat, int n) {
	int maxval = INT_MIN;
	vector<vector<int>> dp{n , vector<int>(n)};
	
	dp[0][0] = mat[0][0];

	for(int i = 1; i < n; i++)
	{
		dp[i][0] = min(dp[i-1][0] , mat[i][0]);
	}
	for(int j = 1; i < n; i++)
	{
		dp[0][j] = min(dp[0][j-1] , mat[i][0]);
	}

	for(int i = 1; i < n; i++){
		for(int j = 1; j < n; j++){
			maxval = max(maxval , mat[i][j] - dp[i-1][j-1]);
			dp[i][j] = min(mat[i][j] , min(dp[i-1][j] ,dp[i][j-1]));
		}
	}
	return maxval;
}