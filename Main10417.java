/*
 * 10417. Gift Exchanging
 * TOPIC: probability
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = 0x10, A = 5;
	final double tol = 1e-9, E = 100000.00;
	int []c = new int[A], which = new int[1 << N], color = new int[N], o = new int[N];
	int L( int k ) { return ((k)&((~k)+1)); }
	int BIT( int k ) { return 1<<k; }
	int MASK( int k ) { return BIT(k)-1; }
	long[][]p = new  long[N][A];
	long[]cnt = new  long[A], fac = new long[N];
	int n,mask,T,P;
	long Total;
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void rec( int k ) {
		int i,u;
		long w;
		if ( k == n ) {
			for ( w = 1, i = 0; i < n; ++i )
				w *= p[i][color[i]];
			cnt[color[0]] += w; Total += w;
			/*
			for ( i = 0; i < n; ++i )
				System.out.printf("%d ",color[i]);
			System.out.println("");
			*/
			++T;
			return ;
		}
		for ( u = mask; u > 0 && (i=which[L(u)]) >= 0; u &= ~L(u) ) {
			assert c[i] > 0;
			color[k] = i;
			if ( 0 == --c[i] ) mask &= ~BIT(i);
			rec(k+1);
			if ( 1 == ++c[i] ) mask |= BIT(i);
		}
	}
	void go() throws Exception {
		int i,j,k,ts = scan.nextInt();
		for ( k = 0; k < N; which[BIT(k)] = k, ++k );
		for ( fac[0] = 1, i = 1; i < N; ++i )
			fac[i] = fac[i-1]*i;
		for(;ts-->0; ) {
			for ( n = scan.nextInt(), mask = 0, i = 0; i < A; cnt[i++] = 0 )  
				if ( (o[i] = c[i] = scan.nextInt()) > 0 ) mask |= BIT(i);
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < A; ++j )
					p[i][j] = scan.next().charAt(2)-'0';
			for ( P = 1, i = 0; i < A; ++i )
				P *= fac[i];
			for ( T = 0, Total = 0, rec(0), j = -1, i = 0; i < A; ++i )
				if ( c[i] > 0 && (j==-1||cnt[i]*c[j] > cnt[j]*c[i]) ) j=i;
			// System.out.println(cnt[4]+" "+c[4]+" "+fac[c[4]]+" "+Total);
			System.out.printf("%d %.3f\n",j+1,((cnt[j]+0.00)/Total)/c[j]+tol);
		}
	}
};


