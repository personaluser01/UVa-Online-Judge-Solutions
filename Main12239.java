/*
 * 12239. Bingo!
 * stautus: Accepted
 */
import java.io.*;
import java.util.*;
import java.lang.Math.*;

class Main {
	int n,B,N = 0x80;
	int []c = new int[N];
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	boolean f() {
		boolean []is = new boolean[n+1];
		int i,j,k = 0;
		for ( i = 0; i < B; ++i )
			for ( j = i; j < B; ++j )
				is[Math.abs(c[i]-c[j])] = true;
		for ( i = 0; i <= n; )
			if ( !is[i++] ) return false;
			else ++k;
		return true;
	}
	void go() throws Exception {
		Scanner scan = new Scanner(System.in);
		int i,j,k;
		while ( true ) {
			n = scan.nextInt();
			B = scan.nextInt();
			if ( n == 0 && B == 0 ) break ; 
			for ( i = 0; i < B; ++i ) 
				c[i] = scan.nextInt();
			if ( f() ) System.out.println("Y");
			else System.out.println("N");
		}
	}
};

