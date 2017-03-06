/*
 * 12205. Happy Telephones
 * TOPIC: ad hoc
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = (1<<14), M = 0x80, BS = 0x80;
	int m,n;
	int []x = new int[N], y = new int[N];
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		int i,j,k,l,t,u,v;
		while ( true ) {
			n = scan.nextInt();
			m = scan.nextInt();
			if ( m == 0 && n == 0 ) break ;
			for ( l = 0; l < n; ++l ) {
				scan.next(); scan.next();
				x[l] = scan.nextInt(); y[l] = (x[l]+scan.nextInt())-1;
			}
			for ( ;m-- > 0; System.out.println(k) ) {
				i = scan.nextInt(); j = i+scan.nextInt()-1;
				for ( k = 0, l = 0; l < n; ++l )
					if ( !(j < x[l] || y[l] < i) ) ++k;
			}
		}
	}
};

