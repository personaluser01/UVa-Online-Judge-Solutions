/*
 * 11840. Tic-Tac-Toe
 * TOPIC: sprague-grundy, nim, combinatorial game theory
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = (1<<15), oo = (1<<29);
	int n;
	String s;
	char []g;
	public static void main( String [] args ) throws Exception { new Main().go(); }
	int []z = new int[N];
	int calc_z( int k ) {
		int t;
		k = Math.max(k,0);
		if ( z[k] < +oo ) return z[k];
		Set<Integer> q = new HashSet<Integer>();
		for ( t = 0; t <= k-1; q.add(calc_z(t-2)^calc_z(k-t-3)), ++t );
		for ( t = 0; q.contains(t); ++t );
		return z[k] = t;
	}
	void go() throws Exception {
		int i,j,k,m;
		for ( z[0] = 0, i = 1; i < N; z[i++] = +oo );
		for(;(n=scan.nextInt())!=0;) {
			s = scan.next();
			g = new char[n+2];
			for ( i = 0; i < n; g[i+1] = s.charAt(i), ++i );
			for ( k = 0, i = 1; i <= n-1 && k == 0; ++i )
				if ( g[i] == 'X' && g[i+1] == 'X' ) k = 1;
			for ( i = 2; i <= n-1 && k == 0; ++i )
				if ( g[i-1] == 'X' && g[i+1] == 'X' ) k = 1;
			if ( k == 1 ) {
				System.out.println("S");
				continue ;
			}
			int []a = new int[n+4];
			for ( m = 0, i = 1; i <= n; a[m++] = k, i = j+1 )
				for ( k = 0, j = i; j <= n && g[j] == '.'; ++j, ++k );
			if ( g[n] == 'X' ) a[m++] = 0;
			if ( m >= 2 )
				for ( a[0] -= 2, a[m-1] -= 2, i = 1; i <= m-2; a[i++] -= 4 );
			for ( i = 0; i < m; a[i] = Math.max(a[i],0), ++i );
			for ( k = 0, i = 0; i < m; k ^= calc_z(a[i++]) );
			System.out.println(k!=0?"S":"N");
		}
	}
};

