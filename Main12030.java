/*
 * 12030. Help the Winners
 * TOPIC: DP, bitmasks, bipartite matching
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	int N = 0x10,n;
	int [][] g = new int[N][N];
	int []bts = new int[1<<N];
	long [] z = new long[1<<N];
	long [] q = new long[1<<N];
	long [] F = new long[N];
	long [][]c = new long[N][N];
	long oo = (1L<<62);
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	StringTokenizer st;
	public static void main( String [] args ) throws Exception { new Main().go(); }
	long calc_z( int u ) {
		int i,j;
		if ( z[u] < +oo )
			return z[u];
		if ( u == (1<<n)-1 )
			return z[u]=1;
		z[u] = 0;
		i = bts[u];
		for ( j = 0; j < n; ++j )
			if ( 0 == (u&(1<<j)) )
				if ( g[i][j] == 1 )
					z[u] += calc_z(u|(1<<j));
		return z[u];
	}
	long calc_q( int u ) {
		int i,j;
		if ( q[u] < +oo )
			return q[u];
		if ( u == (1<<n)-1 )
			return q[u]=1;
		q[u] = 0;
		i = bts[u];
		for ( j = 0; j < n; ++j )
			if ( 0 == (u&(1<<j)) )
				if ( g[i][j] != 2 )
					q[u] += calc_q(u|(1<<j));
		return q[u];
	}

	void go() throws Exception {
		int ts,cs = 0,i,j,k,u,t;
		long ans;
		F[0] = 1L;
		for ( int e = 1; e < (long)N; ++e )
			F[e] = F[e-1]*((long)e);
		ts = Integer.parseInt(br.readLine());
		for ( u = 0; u < (1<<N); ++u ) bts[u] = bts[u>>1]+(u&1);
		while ( ts-- > 0 ) {
			n = Integer.parseInt(br.readLine());
			for ( i = 0; i < n; ++i ) {
				st = new StringTokenizer(br.readLine());
				for ( j = 0; j < n; ++j ) 
					g[i][j] = Integer.parseInt(st.nextToken());
			}
			for(u=0;u<(1<<n);++u)q[u]=z[u]=+oo;
			System.out.printf("Case %d: ",++cs);
			ans = calc_q(0)-calc_z(0);
			System.out.println(F[n]-ans);
		}
	}
};


