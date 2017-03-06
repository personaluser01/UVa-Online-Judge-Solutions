/*
 * 12667. Last Blood
 * TOPIC: ad hoc
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 0x10, T = 0x80, oo = (1<<29);
	Scanner scan = new Scanner(System.in);
	int [][]z = new int[N][T];
	public static void main( String [] args ) throws Exception {
		new Main().go();
	};
	void go() throws Exception {
		int i,j,k,t,n,sb,w,l;
		while ( scan.hasNext() ) {
			n = scan.nextInt();
			t = scan.nextInt();
			sb = scan.nextInt();
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < t; ++j )
					z[i][j] = -oo;
			for ( l = 0; sb-->0; ++l ) {
				k = scan.nextInt();
				j = scan.nextInt()-1;
				String pr = scan.next(), verdict = scan.next();
				i = pr.charAt(0)-'A';
				if ( z[i][j] > -oo || verdict.equals("No") ) 
					continue ;
				z[i][j] = (l<<10)|k;
			}
			for ( i = 0; i < n; ++i ) {
				for ( w = -oo, k = -1, j = 0; j < t; ++j )
					if ( w < z[i][j] )
						w = z[i][k = j];
				System.out.print((char)(i+'A')+" ");
				if ( w == -oo )
					System.out.println("- -");
				else System.out.println((z[i][k]&1023)+" "+(1+k));
			}
		}
	}
};

