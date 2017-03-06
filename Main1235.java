/*
 * 1235. Anti Brute Force Lock
 * TOPIC: mst, greedy
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.lang.Math.*;

class Main {

	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	int n,N = 0x200;
	int []d = new int[N];
	int []D = new int[N];
	String []e = new String[N];
	String ini = new String("0000");

	public static void main ( String [] args ) throws Exception { new Main().go(); }

	int V( char ch ) { return ch-'0'; }

	int f( String a, String b ) {
		int k = 0;
		for ( int i = 0; i < 4; ++i ) 
			k += Math.min((V(a.charAt(i))-V(b.charAt(i))+10)%10,(V(b.charAt(i))-V(a.charAt(i))+10)%10);
		return k;
	}

	void go() throws Exception {
		int i,j,k,ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken()),w,ans;
		boolean []inq = new boolean[N];
		while ( ts-- > 0 ) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			n = Integer.parseInt(st.nextToken());
			for ( i = 0; i < n; ++i ) {
				e[i] = st.nextToken();
				D[i] = d[i] = f(ini,e[i]);
				inq[i] = true;
			}
			w=d[j=0];
			for ( k = 1; k < n; ++k )
				if ( d[k] < w )
					w = d[j = k];
			for ( i = 0; i < n; ++i )
				if ( i != j ) d[i] = f(e[i],e[j]);
			inq[j] = false; ans = w;
			for ( k = 1; k < n; ++k ) {
				j = -1; w = (1<<29);
				for ( i = 0; i < n; ++i )
					if ( inq[i] )
						if ( j == -1 || d[i] < w )
							w = d[j = i];
				ans += w; inq[j] = false;
				for ( i = 0; i < n; ++i ) 
					if ( inq[i] )
						d[i] = Math.min(d[i],f(e[j],e[i]));
			}
			System.out.println(ans);
		}
	}

};

