/*
 * 1456. Cellular Network
 * TOPIC: dp
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.text.*;

class Main {
	Scanner scan = new Scanner(System.in);
	int m,n;
	final static int N = 0x80;
	final static double oo = (1<<29);
	double []p,z[],pref;
	public static void main( String [] args ) throws Exception { new Main().go(); }
	double seg( int i, int j ) { return pref[j+1]-pref[i]; }
	double calc_z( int k, int l ) {
		if ( k == 0 ) {
			if ( l < n ) return +oo;
			assert( l == n );
			return z[k][n] = 0;
		}
		if ( k > n-l )
			return z[k][l] = +oo;
		if ( z[k][l] < +oo )
			return z[k][l];
		assert k >= 1;
		for ( int j = l; j < n; ++j ) 
			if ( calc_z(k-1,j+1) < +oo )
				z[k][l] = Math.min(z[k][l],(j-l+1)*seg(l,n-1)+z[k-1][j+1]);
		return z[k][l];
	}
	void go() throws Exception {
		int i,j,k,ts = scan.nextInt(),total=0;
		for ( ;ts-->0; ) {
			n = scan.nextInt();
			m = scan.nextInt();
			p = new double[n];
			int []cc = new int[n];
			for(total=0,i=0;i<n;total+=(cc[i]=scan.nextInt()),++i);
			for ( i = 0; i < n; ++i ) 
				p[i] = ((double)cc[i])/total;
			pref = new double[n+1];
			Arrays.sort(p);
			for ( i = 0, j = n-1; i < j; ++i, --j ) {
				double t = p[i]; p[i] = p[j]; p[j] = t;
			}
			for ( i = 1; i <= n; ++i )
				pref[i] = pref[i-1]+p[i-1];
			for ( i = 0; i < n-1; ++i )
				assert p[i] >= p[i+1];
			z = new double[m+1][n+1];
			for ( i = 0; i <= m; ++i )
				for ( j = 0; j <= n; z[i][j++] = +oo );
			System.out.println(String.format("%.4f",calc_z(m,0)));
		}
	}
}

