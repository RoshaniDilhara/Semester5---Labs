class Fib {

    public static int fib_r(int x) {
	if(x <= 2) return 1;
	return fib_r(x-1) + fib_r(x-2);
    }

    public static int fib_i(int x) {
	int a=1, b=1, fib=1, i=2;
	while(i<x) {
	    fib = a + b;
	    a = b;
	    b = fib;
	    i+=1;
	}
	return fib;
    }


    public static void main(String [] args) {
	int x = 40;

  for (int j=0;j<=x ;j++ ) {
    long startTime = System.nanoTime();
    long fibr = fib_r(j);
    // System.out.println("Fib of " + j + " = " + fib_r(j));
    long endTime   = System.nanoTime();
    long totalTime = endTime - startTime;
    System.out.print((totalTime)/1000000+",");
  }

System.out.println(".............................................................");

  for (int j=0;j<=x ;j++ ) {
    long startTime_i = System.nanoTime();
    long fibi = fib_i(j);
    // System.out.println("Fib of " + j + " = " + fib_r(j));
    long endTime_i   = System.nanoTime();
    long totalTime_i = endTime_i - startTime_i;
    System.out.print((totalTime_i)/1000000+",");
  }

    }
}
