/*
 * 234. Switching Channels
 * TOPIC: binary search, recursion, permutations
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {

	final int N = 10, oo = (1<<29);
	int n,m,mask;
	int []c = new int[N], t = new int[N], imp = new int[N], which = new int[1 << N], p = new int[N], bestW = new int[N], q = new int[N];

	Scanner scan = new Scanner(System.in);

	public static void main( String[] args ) throws Exception { new Main().go(); }

	int BIT( int k ) { return 1<<k; 		}
	int L( int k )   { return k&((~(k))+1); }
	int who( int u ) { return which[L(u)];  }
	int MASK( int k ) { return BIT(k)-1; }

	void evaluate() {
		int []w = new int[6], pref = new int[N+N];
		int i,j,k,low,high,mid;

		for ( pref[0] = 0, i = 0; i < n; ++i )
			pref[i+1] = pref[i] + p[i];
		for ( i = 0; i < m; ++i ) {
			if ( t[i] >= pref[n] ) {
				w[imp[i]] += Math.abs(t[i]-pref[n]);
				continue ;
			}
			assert t[i] < pref[n];
			assert t[i] >= pref[0];
			for ( low = 0, high = n; low+1<high; ) 
				if ( pref[mid=(low+high)/2] <= t[i] )
					low = mid;
				else high = mid;
			w[imp[i]] += Math.min(Math.abs(pref[high]-t[i]),Math.abs(t[i]-pref[low]));
		}
		for ( k = 4; k >= 0 && w[k] == bestW[k]; --k );
		if ( k > 0 && w[k] < bestW[k] ) {
			for ( i = 0; i <= 4; ++i ) bestW[i] = w[i];
			for ( i = 0; i < n; ++i ) q[i] = p[i];
		}
	}

	void f( int k ) {
		int i,j,u;
		if ( k == n ) {
			evaluate();
			return ;
		}
		for(u=((~mask)&MASK(n));u>0&&(i=who(u))>=0;p[k]=c[i],mask|=BIT(i),f(k+1),mask&=~BIT(i),u&=~L(u));
	}

	void go() throws Exception {
		int i,j,k,cs = 0;
		for ( i = 0; i < N; ++i )
			which[BIT(i)] = i;
		while ( (n=scan.nextInt())!=0 ) {
			for ( i = 0; i < n; c[i++] = scan.nextInt() );
			for ( m = scan.nextInt(), i = 0; i < m; ++i ) {
				imp[i] = 5-scan.nextInt();
				t[i] = scan.nextInt();
			}
			System.out.println("Data set "+(++cs));
			for ( j = 1; j == 1; )
				for ( j = 0, i = 0; i < m-1; ++i )
					if ( t[i] > t[i+1] ) {
						j = 1; k = t[i]; t[i] = t[i+1]; t[i+1] = k; k = imp[i]; imp[i] = imp[i+1]; imp[i+1] = k;
					}
			for ( mask = 0, i = 0; i <= 4; ++i ) bestW[i] = +oo;
			for ( i = 0; i < n; q[i] = c[i], ++i );
			System.out.print("  Order:");
			for ( k = 0, f(0), i = 0; i <= 4; k += bestW[i++] );
			for ( i = 0; i < n; System.out.print(" "+q[i++]) );
			System.out.println("\n  Error: "+k);
		}
	}
};

