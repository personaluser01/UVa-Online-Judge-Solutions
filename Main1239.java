/*
 * 1239. Greatest K-Palindrome Substring
 * TOPIC: ad hoc
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 0x400;
	int m,n;
	Scanner scan = new Scanner(System.in);
	String s;
	char []c;
	public static void main( String []args ) throws Exception { new Main().go(); }
	boolean f( int k ) {
		int i,j,l,t,e=(1<<29);
		for ( i = 0; (j = i+k-1) < n && e > m; ++i ) 
			for ( e = 0, l = i, t = j; l < t && e <= m; ++l, --t )
				if ( c[l] != c[t] ) ++e;
		return e <= m;
	}
	void go() throws Exception {
		int l,t,i,j,k,len,ts = scan.nextInt(),good,bad,mid,e;
		for (;ts-->0;) {
			s = scan.next();
			m = Integer.parseInt(scan.next());
			n = s.length();
			c = new char[n];
			for ( i = 0; i < n; ++i ) c[i] = s.charAt(i);
			if ( f(bad=n) ) {
				System.out.println(n);
				continue ;
			}
			for ( len = 1, i = 0; i < n; ++i ) {
				for ( e = 0, l = i-1, t = i+1; t < n && l >= 0 && e <= m; --l, ++t ) {
					if ( c[l] != c[t] ) ++e;
					if ( e <= m ) len = Math.max(len,(t-l+1));
				}
			}
			for ( i = 0; i < n; ++i ) {
				for ( e = 0, t = i+1, l = i; l >= 0 && t < n && e <= m; ++t, --l )  {
					if ( c[t] != c[l] ) ++e;
					if ( e <= m ) len = Math.max(len,(t-l+1));
				}
			}
			System.out.println(len);
		}
	}
};

