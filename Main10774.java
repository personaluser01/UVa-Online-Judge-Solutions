/*
 * 10774. Repeated Josephus
 * TOPIC: dp
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final static int N = 30100, oo = (N+N);
	int []z = new int[N];
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	int f( int n ) {
		if ( z[n] < +oo )
			return z[n];
		if ( n == 1 ) return z[n] = 0;
		return z[n] = (2*((f(n>>1)+(n&1))%(n>>1))+1);
	}
	int survivor( int n ) {
		return f(n);
	}
	void go() throws Exception {
		int i,j,k,ts = scan.nextInt(),cs = 0,n;
		for ( i = 0; i < N; z[i++] = +oo );
		for ( ;ts-->0; ) {
			for ( n = scan.nextInt()+1, k = 0; (i=survivor(n)) != n-1; n = i+1, ++k );
			System.out.println("Case "+(++cs)+": "+k+" "+(n-1));
		}
	}
}

