/*
 * 12281. Hyper Box
 * TOPIC: fibonacci
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final long LIM = 2000000008L;
    final int N = (1<<21);
	Scanner scan = new Scanner(System.in);
	long []f = new long[N];
	long ax;
	int n = 0,m;
	public static void main( String [] args ) throws Exception { new Main().go(); }
	long g( long m ) {
		int low,high,mid;
		if ( m == 0 ) return 0L;
		if ( f[n-1] == m ) return f[n-1];
		for ( low = 0, high = n-1; low+1<high; ) {
			mid = (low+high)/2;
			if ( f[mid] > m ) high = mid;
			else low = mid;
		}
		assert f[low] <= m;
		assert f[high] > m;
		return f[low];
	}
	long H( long x ) {
		long s = 0L;
		for (;x > 0; x -= g(x), ++s );
		return s;
	}
	void go() throws Exception {
		int i,j,k,ts = scan.nextInt(),cs = 0;
		for ( f[0] = 1, f[1] = 2, i = 2, n = 2; i < N && (f[i]=f[i-1]+f[i-2]) < LIM; ++i, ++n );
		for( ++n; ts-->0;) {
			for ( m = scan.nextInt(), ax = 1L, i = 0; i < m; ++i, ax *= H(scan.nextLong()) );
			System.out.println("Case "+(++cs)+": "+ax);
		}
	}
};

