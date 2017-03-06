/*
 * 10980. Lowest Price in Town
 * TOPIC: dp, recurrence relation
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.lang.Math.*;

class Main {
	double tol = 1e-9;
	int N = 0x200, M = 0x20;
   	long oo = (1L<<45);
	long [][]z = new long[M][N];
	long []ans = new long[N];
	public static void main ( String [] args ) throws Exception { new Main().go(); }
	String f( long x ) {
		long xx = x;
		long d = (xx%10);
		xx -= d; xx /= 10;
		long t = (xx%10);
		xx /= 10;
		return Long.toString(xx)+"."+Long.toString(t)+Long.toString(d);
	}
	void go() throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int []t = new int[M];
		int []c = new int[M];
		int i,j,k,n,m,cs = 0,p;
		String s;
		StringTokenizer st;
		while ( (s = br.readLine()) != null ) {
			st = new StringTokenizer(s);
			p = (int)(100*(Double.parseDouble(st.nextToken())+tol));
			m = Integer.parseInt(st.nextToken());
			for ( i = 0; i <= m; ++i )
				for ( k = 0; k < N; ++k )
					z[i][k] = p*k;
			for ( i = 1; i <= m; ++i ) {
				st = new StringTokenizer(s = br.readLine());
				c[i] = Integer.parseInt(st.nextToken());
				t[i] = (int)(100*(Double.parseDouble(st.nextToken())+tol));
				for ( k = 0; k < N; ++k )
					for ( j = 0; j*c[i] <= k; ++j )
						if ( z[i][k] > z[i-1][k-j*c[i]]+j*t[i] )
							z[i][k] = z[i-1][k-j*c[i]]+j*t[i];
			}
			ans[N-1] = z[m][N-1];
			for ( k = N-2; k >= 0; --k ) 
				ans[k] = Math.min(z[m][k],ans[k+1]);
			System.out.println("Case "+(++cs)+":");
			st = new StringTokenizer(s = br.readLine());
			for (;st.hasMoreTokens();) {
				n = Integer.parseInt(st.nextToken());
				System.out.println("Buy "+n+" for $"+f(ans[n]));
			}
		}
	}
};

