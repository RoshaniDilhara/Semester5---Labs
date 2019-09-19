class Q1 {
    static int [][] cost = {{0, 3, 12, 23, 41}, // cost from 0
			    {0, 0,  2,  4, 34}, // cost from 1
			    {0, 0,  0,  12, 3}, // cost from 2
			    {0, 0,  0,  0, 12}, // cost from 3
			    {0, 0,  0,  0,  0}  // cost from 4
    };

    static int iMax = 5;
    static int jMax = 5;

    // Just for testing, min cost from 0 to 4 should be 8.
    static int answer = 8;

    public static int minCost(int i, int j) {

      // If source is same as destination
      // or destination is next to source
      if (1 == j || i+1 == j)
        return cost[i][j];

      // Initialize min cost as direct ticket from
      // source 'i' to destination 'j'.
      int min = cost[i][j];

      // Try every intermediate vertex to find minimum
      for (int k = i+1; k<j; k++)
      {
          int c = minCost(i, k) +
                  minCost(k, j);
          if (c < min)
             min = c;
      }
      return min;

    }

    public static void main(String [] args) {
	int r = minCost(0,4);
	if(r == answer)
	    System.out.println("Your implementation might be correct");
	else
	    System.out.println("Too bad. Try again (" + r + ")");
    }
}
