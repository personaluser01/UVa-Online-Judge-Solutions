/*
 * 1583. Digit Generator
 * TOPIC: easy dp, precalc
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	int []g = new int[1<<21];
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		int ts,n,m;
		for ( n = 0; n < (1 << 21); ++n ) {
			String s = Integer.toString(n);
			m = n;
			for ( char c: s.toCharArray() ) 
				m += (int)(c-'0');
			if ( m <= 1000000 && g[m] == 0 ) 
				g[m] = n;
		}
		Scanner scan = new Scanner(System.in);
		for ( ts = scan.nextInt(); ts-- > 0; System.out.println(g[n = scan.nextInt()]) );
	}
};

