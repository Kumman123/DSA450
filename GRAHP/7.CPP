// C++ program to find minimum steps to reach to
// specific cell in minimum moves by Knight

#include <bits/stdc++.h>
using namespace std;

// structure for storing a cell's data
struct cell {
	int x, y;
	int dis;
	cell() {}
	cell(int x, int y, int dis)
		: x(x)
		, y(y)
		, dis(dis)
	{
	}
};

// Utility method returns true if (x, y) lies
// inside Board
bool isInside(int x, int y, int N)
{
	if (x >= 1 && x <= N && y >= 1 && y <= N)
		return true;
	return false;
}

// Method returns minimum step
// to reach target position
int minStepToReachTarget(int knightPos[], int targetPos[],
						int N)
{
	// x and y direction, where a knight can move
	int dx[] = { -2, -1, 1, 2, -2, -1, 1, 2 };
	int dy[] = { -1, -2, -2, -1, 1, 2, 2, 1 };

	// queue for storing states of knight in board
	queue<cell> q;

	// push starting position of knight with 0 distance
	q.push(cell(knightPos[0], knightPos[1], 0));

	cell t;
	int x, y;
	bool visit[N + 1][N + 1];

	// make all cell unvisited
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			visit[i][j] = false;

	// visit starting state
	visit[knightPos[0]][knightPos[1]] = true;

	// loop until we have one element in queue
	while (!q.empty()) {
		t = q.front();
		q.pop();

		// if current cell is equal to target cell,
		// return its distance
		if (t.x == targetPos[0] && t.y == targetPos[1])
			return t.dis;

		// loop for all reachable states
		for (int i = 0; i < 8; i++) {
			x = t.x + dx[i];
			y = t.y + dy[i];

			// If reachable state is not yet visited and
			// inside board, push that state into queue
			if (isInside(x, y, N) && !visit[x][y]) {
				visit[x][y] = true;
				q.push(cell(x, y, t.dis + 1));
			}
		}
	}
}

// Driver code
int main()
{
	int N = 30;
	int knightPos[] = { 1, 1 };
	int targetPos[] = { 30, 30 };

	// Function call
	cout << minStepToReachTarget(knightPos, targetPos, N);
	return 0;
}










/*
    Time Complexity: O(1)
    Space Complexity: O(1)
*/

int minimumKnightMoves(int x, int y) {
   // Reducing the search space to 1st quadrant
   x = abs(x);
   y = abs(y);

   // Reducing the search space to upper half of the first quadrant
   if (x > y) {
      swap(x, y);
   }

   // Border case for (0, 1) and (1, 1)
   if (x == 0 && y == 1) {
      return 3;
   }
   if (x == 1 && y == 1) {
      return 2;
   }

   // Using formula based on patterns formed
   if (y >= 2 * x) {
      return (y + 1) / 2 + (y / 2 - x) % 2;
   }
   else {
      return (y + x) / 3 + (y + x) % 3;
   }
}