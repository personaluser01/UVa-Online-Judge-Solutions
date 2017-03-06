/*
 * 10561. Treblecross
 * TOPIC: sprague-grundy, nim, combinatorial game theory
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 0x100, WHITE = 0, GREY = 1, BLACK = 2;
	int n,m;
	String s;
	Set<Integer> q;
	int []color = new int[N];
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception { new Main().go(); }
	int BIT( int k )  { return 1<<k;     }
	int MASK( int k ) { return BIT(k)-1; }
	int []z = new int[N];
	int []a = new int[N];
	boolean []seen = new boolean[N];
	int calc_z( int k ) {
		int t;
		k = Math.max(k,0);
		if ( seen[k] )
			return z[k];
		Set<Integer> u = new HashSet<Integer>();
		assert color[k] == WHITE;
		color[k] = GREY;
		for ( t = 0; t <= k-1; ++t ) 
			u.add(calc_z(t-2)^calc_z(k-t-3));
		for ( t = 0; u.contains(t); ++t );
		seen[k] = true ;
		color[k] = BLACK;
		return z[k] = t;
	}
	int sg( int[]c, int m ) {
		int res = 0,i;
		for ( i = 0; i < m; res ^= calc_z(c[i++]) );
		return res;
	}
	void go() throws Exception {
		int i,j,k,ts = scan.nextInt(),res,x,y,l,t;
		seen[0] = true; z[0] = 0;
		char []g;
		for (;ts-->0;) {
			n=(s=scan.next()).length();
			StringBuilder sb = new StringBuilder();
			q = new TreeSet<Integer>();
			g = new char[n+5];
			for ( g[0] = 'X', g[n+1] = 'X', i = 1; i <= n; ++i )
				g[i] = s.charAt(i-1);
			for ( i = 0; i < n-1; ++i )
				if ( s.charAt(i) == 'X' && s.charAt(i+1) == 'X' ) { q.add(i-1); q.add(i+2); }
			for ( i = 2; i <= n-1; ++i )
				if ( g[i] == '.' && g[i-1] == 'X' && g[i+1] == 'X' )
					q.add(i-1);
			if ( q.size() > 0 ) {
				for ( Iterator<Integer> it = q.iterator(); it.hasNext(); ) {
					k = it.next();
					if ( k >= 0 && k < n ) {
						if ( sb.toString().length() > 0 )
							sb.append(" ");
						sb.append(Integer.toString(k+1));
					}
				}
				System.out.println("WINNING\n"+sb.toString());
				continue ;
			}
			for ( m = 0, i = 1; i <= n; a[m++] = k, i = j+1 ) 
				for ( k = 0, j = i; j <= n && g[j] == '.'; ++j, ++k );
			if ( g[n] == 'X' ) a[m++] = 0;
			if ( m >= 2 ) 
				for ( a[0] -= 2, a[m-1] -= 2, i = 1; i <= m-2; a[i++] -= 4 );
			for ( i = 0; i < m; a[i] = Math.max(a[i],0), ++i );
			if ( sg(a,m) == 0 ) {
				System.out.println("LOSING\n");
				continue ;
			}
			System.out.println("WINNING");
			int []c = new int[N];
			int mm = 0;
			for ( i = 1; i <= n; ++i ) {
				if ( g[i] == 'X' || i >= 2 && g[i-1] == 'X' || i >= 3 && g[i-2] == 'X' || i+1 <= n && g[i+1] == 'X' || i+2 <= n && g[i+2] == 'X' ) continue ;
				g[i] = 'X';
				for ( mm = 0, l = 1; l <= n; c[mm++] = k, l = j+1 ) 
					for ( k = 0, j = l; j <= n && g[j] == '.'; ++k, ++j );
				if ( g[n] == 'X' ) c[mm++] = 0;
				if ( mm >= 2 ) 
					for ( c[0] -= 2, c[mm-1] -= 2, j = 1; j <= mm-2; c[j++] -= 4 );
				for ( j = 0; j < mm; c[j] = Math.max(c[j],0), ++j );
				if ( sg(c,mm) == 0 ) {
					if ( sb.toString().length() > 0 )
						sb.append(" ");
					sb.append(i);
				}
				g[i] = '.';
			}
			System.out.println(sb.toString());
		}
	}
};

