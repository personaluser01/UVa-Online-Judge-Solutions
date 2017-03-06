/*
 * 12650.
 * TOPIC: sorted set
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		int m,n,i,j,k;
		Scanner scan = new Scanner(System.in);
		SortedSet<Integer> s;
		while ( scan.hasNext() ) {
			n = scan.nextInt();
			m = scan.nextInt();
			s = new TreeSet<Integer>();
			for ( i = 0; i < n; ++i ) s.add(i);
			for ( i = 0; i < m; ++i ) {
				j = scan.nextInt();
				s.remove(j-1);
			}
			Iterator it = s.iterator();
			if ( s.isEmpty() ) {
				System.out.println("*");
				continue ;
			}
			for ( ;it.hasNext(); )
				System.out.print((((int)it.next())+1)+" ");
			System.out.println("");
		}
	}
};

