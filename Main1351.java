/*
 * 1351. String Compression
 * TOPIC: dp
 * status: Accepted
 */
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	String s;
	int n;
	final static int N = 0x100, oo = (1<<29);
	int [][]z;

	public static void main( String ... args ) throws Exception { new Main().go(); }

	int kmp( char []c, int startIndex, int n ) {
		int i,j,k,t;
		int []p = new int[n+2];
		char []x = new char[n+2];

		for ( i = 0; i < n; x[i+1] = c[startIndex+i], ++i );

		for ( p[0] = j = -1, i = 1; i <= n; p[i++] = ++j ) 
			for ( ;j+1 != 0 && x[i] != x[j+1]; j = p[j] );

		return p[n];

	}

	void go() throws Exception {
		int i,j,k,ts = scan.nextInt(),reps,len,m,t;
		char []c,p;
		for ( ;ts-->0; ) {
			n = (c = (s = scan.next()).toCharArray()).length;
			z = new int[n+1][n+1];
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < n; ++j )
					z[i][j] = +oo;
			for ( i = 0; i < n; ++i ) z[i][i] = 1;
			for ( k = 2; k <= n; ++k )
				for ( i = 0; (j = (i+k-1)) < n; ++i ) {
					z[i][j] = Math.min(k,z[i][j]);
					for ( t = i+1; t <= j-1; ++t )
						if ( z[i][t] < +oo && z[t+1][j] < +oo )
							if ( z[i][t]+z[t+1][j] < z[i][j] )
								z[i][j] = z[i][t]+z[t+1][j];
					if ( (m=kmp(c,i,k)) > 0 && (m%(k-m)) == 0 ) {
						// System.out.println(s.substring(i,j+1)+" "+i+" "+j+" has a period of length "+(k-m));
						if ( z[i][j] > z[i][i+k-m-1]+2+(""+(reps=(k/(len=k-m)))).length() ) {
							z[i][j] = z[i][i+k-m-1]+2+(""+reps).length();
						}
					}
				}
			System.out.println(z[0][n-1]);
		}
	}
}

