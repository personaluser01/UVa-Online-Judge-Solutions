/*
 * 10339. Waching Watches
 * TOPIC: ad hoc, maths
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.lang.Math.*;

class Main {
	Scanner scan = new Scanner(System.in);
	int m,n;
	public static void main( String[] args ) throws Exception { new Main().go(); }
	int f( int x ) { if ( x == 0 ) return 12; return x; } 
	void go() throws Exception {
		while ( scan.hasNext() ) {
			m = scan.nextInt();
			n = scan.nextInt();
			double d = 43200.00/Math.abs(m-n), kd = d*(86400.00-m)/86400.00;
		    int	mins = (int)Math.floor(1440.00*((kd%0.5)+1e-7)+0.5);
			System.out.printf("%d %d %02d:%02d\n",m,n,f(mins/60),(mins%60));
		}
	}
};

