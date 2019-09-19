class Q4 {
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

    static int max = Integer.MAX_VALUE;

    static int n = 5;

    public static int minCost(int cost[][]) {
    // minimum cost to reach station i from station 0 is stored in the array dist[i]
        int dist[] = new int[n];
        for (int i=0; i<n; i++)
           dist[i] = max; // set the all values of distance array to the Integer maximum value

           dist[0] = 0;

        // Go through every station
        // check if using it as an intermediate station gives best path
        for (int i=0; i<n; i++)
           for (int j=i+1; j<n; j++)
              if (dist[j] > dist[i] + cost[i][j])
                 dist[j] = dist[i] + cost[i][j];

        return dist[n-1];
    }



    public static void main(String [] args) {
    	int r = minCost(cost);

    	if(r == answer)
    	    System.out.println("Your implementation might be correct");
    	else
    	    System.out.println("Too bad. Try again (" + r + ")");
        }
}
