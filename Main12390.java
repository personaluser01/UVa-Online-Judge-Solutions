/*
 * 12390. Distributing Ballot Boxes
 * TOPIC: binary search
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = (1<<21), oo = (1<<29);
	public static void main( String [] args ) throws Exception { new Main().go(); };
	int n,m;
	int []c = new int[N];
	boolean f( int M ) {
		int boxes_needed = 0;
		for ( int i = 0; i < n; ++i ) 
			boxes_needed += (int)Math.ceil((c[i]+0.00)/M);
		return boxes_needed <= m;
	};
	void go() throws Exception {
		int i,j,k,good,bad,mid;
		while ( true ) {
			n = scan.nextInt();
			m = scan.nextInt();
			if ( m == -1 && n == -1 ) break ;
			for ( i = 0; i < n; c[i++] = scan.nextInt() );
			for ( bad = 0, good = +oo; bad+1 < good; ) {
				mid = (good+bad)/2;
				if ( f(mid) ) good = mid;
				else bad = mid;
			}
			System.out.println(good);
		};
	};
};

