# Game with best score

The reasoning that led us to the solution we implemented consists of the following points:

* **Problem definition**: the first step in solving any problem is to understand it completely. In this case, the
  problem is
  defined as finding the path with the maximum score on a board of n x n. Each square of the board has a value that is
  added to the player's score when the player passes through that square. The player can move right or down from any
  square, and the game ends when the player moves off the board.
* **Optimal substructure**: Once the problem has been defined, the next step is to identify whether it has an optimal
  substructure. A problem has an optimal substructure if the optimal solution to the problem can be constructed from the
  optimal solutions to its subproblems. In this case, the maximum score that can be obtained from a cell is the value of
  the cell plus the maximum between the maximum scores that can be obtained from the cells to the right and below. This
  indicates that the problem has an optimal substructure.
* **Tabulation**: Since the problem has an optimal substructure, the dynamic programming technique can be used to solve
  it.
  Dynamic programming is a technique used to solve optimization problems that have an optimal substructure. Instead of
  solving the same subproblem multiple times, dynamic programming solves each subproblem once and stores the results in
  a table (in this case, a dp matrix) for use in future subproblems. This improves the efficiency of the algorithm.
* **Path tracing**: In addition to the dp matrix, a matrix of pairs is used to trace the path leading to the maximum
  score
  from each cell. Each pair in the matrix represents the cell from which the current cell with the maximum score was
  reached. This allows reconstructing the optimal path once all the maximum scores have been computed.
* **Searching for the maximum score**: Finally, the maximum score is searched for in the dp matrix. The box with the
  maximum
  score represents the end of the path with the maximum score. The path from this box to the beginning is followed using
  the pair matrix.

## Why dynamic programming?

This reasoning leads to an efficient algorithm that solves the problem using dynamic programming with the top-down type.
The efficiency comes from the fact that each subproblem is solved only once and the results are stored for use in future
subproblems.

This is why the proposed algorithm uses dynamic programming of the "Top-Down" type.  
Dynamic programming is an optimization technique used to solve problems that have an optimal substructure and
overlapping subproblems. Optimal substructure means that the optimal solution to the problem can be constructed from the
optimal solutions to its subproblems. Subproblem superposition means that some subproblems are solved multiple times.

Top-down dynamic programming, also known as memoization, is a form of dynamic programming that starts by solving the
original problem and then decomposes the problem into smaller subproblems as they are needed. Instead of solving all
subproblems as in the bottom-up dynamic programming approach, the top-down approach only solves the subproblems that are
necessary to solve the original problem.

### Why top-down dynamic programming?

The reasoning behind the choice of top-down dynamic programming to solve the maximum-scoring path problem on an n x n
board is as follows:

* **Optimal substructure**: the problem has an optimal substructure, since the maximum score that can be obtained from a
  square is the value of the square plus the maximum among the maximum scores that can be obtained from the squares to
  the right and below. This means that the optimal solution to the problem can be constructed from the optimal solutions
  to its subproblems.
* **Overlapping subproblems**: The problem has an overlap of subproblems, since the maximum score that can be obtained
  from
  a box is computed multiple times if it is not stored. This means that the problem is a good candidate for dynamic
  programming.
* **Memoization**: Top-down dynamic programming uses memoization to store the results of subproblems in a dp matrix.
  This
  avoids having to recalculate the same values over and over again, which improves the efficiency of the algorithm.
* **Path tracing**: In addition to the dp matrix, a pairwise matrix is used to trace the path leading to the maximum
  score
  from each cell. This allows reconstructing the optimal path once all maximum scores have been computed.
* **Efficiency**: Top-down dynamic programming is more efficient than the brute-force approach, which would try all possible
  combinations of moves. The efficiency comes from the fact that each subproblem is solved only once and the results are
  stored for use in future subproblems.

## Pseudocode
```
1. Initialize a dp matrix of size n x n with all elements as -1
2. Initialize a pair matrix path of size n x n to track the path
3. Define the function solve(i, j) that returns the maximum score that can be obtained from the cell (i, j)
   3.1 If (i, j) is outside the board, return 0
   3.2 If dp[i][j] is not -1, return dp[i][j]
   3.3 Calculate the maximum score that can be obtained by moving down (solve(i + 1, j)) and to the right (solve(i, j + 1))
   3.4 If the maximum score is obtained by moving down, update path[i][j] with (i + 1, j) and dp[i][j] with down + board[i][j]
   3.5 If the maximum score is obtained by moving to the right, update path[i][j] with (i, j + 1) and dp[i][j] with right + board[i][j]
   3.6 Return dp[i][j]
4. For each cell (i, j) on the board:
   4.1 Call solve(i, j)
   4.2 If dp[i][j] is greater than max_score, update max_score with dp[i][j] and max_i, max_j with i, j
5. Initialize a boolean matrix isPath of size n x n with all elements as false
6. While (max_i, max_j) is not (-1, -1):
   6.1 Mark isPath[max_i][max_j] as true
   6.2 Update (max_i, max_j) with path[max_i][max_j]
7. For each cell (i, j) on the board:
   7.1 If isPath[i][j] is true, print the cell with a green background
   7.2 Otherwise, print the cell without changing the color
```