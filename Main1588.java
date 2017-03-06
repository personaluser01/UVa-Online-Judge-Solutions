/*
 * 1588. Kickdown
 * TOPIC: ad hoc
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 0x80;
	int m,n;
	String s,t;
	int[]a = new int[N], b = new int[N], c = new int[N], d = new int[N];
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception { new Main().go(); }
	boolean f( int k ) {
		int i,j;
		for ( j = 0, i = k; i < m && j < n; ++j, ++i )
			if ( a[i]+b[j] == 2 )
				return false;
		return true;
	}
	int g( int k ) { return Math.max(k+n,m); }
	void go() throws Exception {
		int i,j,k,ans;
		for ( ;scan.hasNext(); ) {
			s = scan.next(); m = s.length();
			t = scan.next(); n = t.length();
			for ( i = 0; i < m; ++i )
				a[i] = s.charAt(i)-'1';
			for ( j = 0; j < n; ++j )
				b[j] = t.charAt(j)-'1';
			//for ( i = 0; i < n; ++i )
			//	b[i] = 1-b[i];
			for ( k = 0; k <= m && !f(k); ++k );
			ans = g(k);
			for ( i = 0; i < m; ++i )
				c[i] = a[i];
			for ( j = 0; j < n; ++j )
				d[j] = b[j];
			for ( i = 0; i < m; ++i )
				b[i] = c[i];
			for ( j = 0; j < n; ++j )
				a[j] = d[j];
			k = m; m = n; n = k;
			for ( k = 0; k <= m && !f(k); ++k );
			ans = Math.min(ans,g(k));
			System.out.println(ans);
		}
	}
};

