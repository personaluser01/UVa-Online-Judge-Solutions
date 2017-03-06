/*
 * 12751. A Interesting Game
 * TOPIC: maths
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	long n,k,x;
	long f( long x, long k ) { return ((x+x+k-1)*k)/2; }
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		int ts,cs = 0;
		for ( ts = scan.nextInt(); ts-- > 0; ) {
			n = scan.nextLong();
			k = scan.nextLong();
			x = scan.nextLong();
			System.out.println("Case "+(++cs)+": "+(f(1,n)-f(x,k)));
		}
	}
};

