/*
 * 11857. Driving Range
 * status: Accepted
 * TOPIC: MST, Kruskal
 */
import java.io.*;
import java.util.*;

class Main {

	public int []rank = new int[1 << 21];
	public int []p = new int[1 << 21];
	public int E,V;

    public static void main( String [] args ) throws Exception { new Main().go(); }

	class Edge implements Comparable<Edge> {
		public int x,y,w;
		Edge( int x, int y, int w ) {
			this.x = x; this.y = y; this.w = w;
		}
		public int compareTo( Edge other ) {
			if ( w < other.w )
				return -1;
			if ( w > other.w )
				return 1;
			return 0;
		}
	}

	Edge []e;
	
	int find( int x ) { 
		if ( p[x] == x )
			return x;
		return p[x] = find(p[x]);
	}

	void link( int x, int y ) {
		if ( rank[x] > rank[y] ) {
			p[y] = x;
		}
		else {
			p[x] = y;
			if ( rank[x] == rank[y] )
				++rank[y];
		}
	}

	void merge( int x, int y ) { link(find(x),find(y)); }

	void go() throws Exception {
		int i,j,k,l,t,src,dst,m,n,x,y,ans;
		String s;
		StringTokenizer st;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		while ( (s = br.readLine()) != null ) {
			st = new StringTokenizer(s);
			n = Integer.parseInt(st.nextToken());
			m = Integer.parseInt(st.nextToken());
			if ( n == 0 && m == 0 ) break ;
			for ( i = 0; i < n; ++i ) {
				p[i] = i;
				rank[i] = i;
			}
			if ( m > 0 ) e = new Edge[m]; 
			for ( l = 0; l < m; ++l ) {
				st = new StringTokenizer(br.readLine());
				i = Integer.parseInt(st.nextToken());
				j = Integer.parseInt(st.nextToken());
				k = Integer.parseInt(st.nextToken());
				e[l] = new Edge(i,j,k);
			}
			Arrays.sort(e); E = 0; ans = 0;
			for ( l = 0; l < m; ++l ) {
				i = e[l].x; j = e[l].y;
				if ( find(i) == find(j) ) continue ;
				merge(i,j);
				ans = e[l].w;
				++E;
			}
			if ( E < n-1 )
				System.out.println("IMPOSSIBLE");
			else
				System.out.println(ans);
		}
	}
};



