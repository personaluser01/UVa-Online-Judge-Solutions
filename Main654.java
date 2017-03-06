/*
 * 645. Ratio
 * TOPIC: ad hoc, maths, ratios, fractions
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.lang.Math.*;

class Main {
	long m,n;
	int len;
	long []H = new long[1 << 20],K = new long[1 << 20];
	Queue<Long> q = new LinkedList<Long>();
	ArrayList<Long> L;
	double rat,tol = 1e-11;
	public static void main ( String [] args ) throws Exception {
		new Main().go();
	}
	void contFrac( long m, long n ) {
		long t;
		q.add(m/n);
		if ( 0 != (t=(m%n)) )
			contFrac(n,t);
	}
	long getH( long k ) {
		if ( k == -1 ) return 1;
		if ( k == -2 ) return 0;
		return H[(int)k];
	}
	long getK( long k ) {
		if ( k == -1 ) return 0;
		if ( k == -2 ) return 1;
		return K[(int)k];
	}
	long gcd( long x, long y ) {
		if ( y == 0 ) return x;
		return gcd(y,x%y);
	}
	void D( long m, long n ) {
		long k = gcd(m,n);
		m /= k; n /= k;
		System.out.println(m+"/"+n);
	}
	boolean betterFit( long a, long b, long c, long d ) {
		return Math.abs((a+.0)/b-rat) <= Math.abs((c+.0)/d-rat)-tol;
	}
	void go() throws Exception {
		Scanner scan = new Scanner(System.in);
		int ts = 0;
		long a,b,M,N,d,i,j,k,quot,up,A,B,ii,jj,pm,pn;
		double val;
		while ( scan.hasNext() ) {
			m = scan.nextLong();
			n = scan.nextLong();
			if ( ++ts > 1 ) System.out.println("");
			/*
			contFrac(m,n);
			L = new ArrayList<Long>(q);
			while ( !q.isEmpty() ) q.poll();
			len = L.size();
			for ( k = 0; k < len; ++k ) {
				H[(int)k] = L.get((int)k)*getH(k-1)+getH(k-2);
				K[(int)k] = L.get((int)k)*getK(k-1)+getK(k-2);
				i = gcd(H[(int)k],K[(int)k]);
				System.out.println((H[(int)k]/i)+"/"+(K[(int)k]/i));
			}
			*/
			up = (quot=m/n)+1;
			if ( n*up-m > m-quot*n )
				M = quot;
			else M = up;
			N = 1;
			k = gcd(m,n);
			m /= k; n /= k;
			rat = (m+.0)/n;
			val = (M+.0)/N;
			d = 1;
			pm = -1; pn = -1;
			do {
				if ( !(pm == M && pn == N) ) {
					D(M,N);
					pm = M; pn = N;
				}
				ii = M; jj = N;
				A = (long)Math.floor((N+d)*val)-2;
				B = (long)Math.ceil ((N+d)*val)+2;
				for ( i = Math.max(A,1); i <= B; ++i ) {
					if ( gcd(N+d,i) != 1 )
						continue ;
					if ( betterFit(i,N+d,ii,jj) ) {
						ii = i; jj = N+d;
					}
				}
				if ( !(ii == M && jj == N) ) {
					M = ii; N = jj;
					assert gcd(M,N) == 1;
					val = (M+.0)/N;
					d = 1;
				}
				else ++d;
			} while ( !(pm == m && pn == n) );
		}
	}
};

