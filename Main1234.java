/*
 * 1234. Racing
 * TOPIC: mst, cycles, kruskal
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = (1<<15), M = (1<<18);
	Scanner scan = new Scanner(System.in);
	int ts,m,n,E;
	int []p = new int[N], r = new int[N];
	public static void main( String [] args ) throws Exception { new Main().go(); }
	class Edge implements Comparable<Edge> {
		int x,y,w;
		Edge ( int x, int y, int w ) {
			this.x = x; this.y = y; this.w = w;
		}
		public int compareTo( Edge b ) {
			if ( this.w == b.w ) return 0;
			return this.w>b.w?-1:1;
		}
	}
	void makeSet( int x ) {
		r[p[x]=x]=0;
	}
	void link( int x, int y ) {
		if ( r[x] == r[y] )
			p[y] = x;
		else {
			p[x] = y;
			if ( r[x] == r[y] ) ++r[y];
		}
	}
	int find( int x ) {
		return p[x]=(p[x]==x?x:find(p[x]));
	}
	void merge( int x, int y ) {
		link(find(x),find(y));
	}
	void go() throws Exception {
		int i,j,k,l,t,w;
		for ( ts = scan.nextInt(); ts-->0; System.out.println(w) ) {
			for ( i = 0, n = scan.nextInt(); i < n; makeSet(i++) );
			Edge []e;
			for ( m = scan.nextInt(), e = new Edge[m], l = 0; l < m; ++l ) {
				i = scan.nextInt()-1;
				j = scan.nextInt()-1;
				k = scan.nextInt();
				e[l] = new Edge(i,j,k);
			}
			for ( Arrays.sort(e), w = 0, l = 0; l < m; ++l )
				if ( find(e[l].x) != find(e[l].y) ) {
					merge(e[l].x,e[l].y);
				}
				else w += e[l].w;
		}
	}
};

