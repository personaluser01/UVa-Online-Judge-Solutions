/*
 * 12092. Paint the Roads
 * TOPIC: maxflow, parametrized flows, mincost circulation, saturating the arcs, negatuve cycles, bellman ford
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {

	private static final int MAXV = (0x40*2), MAXE = (1<<21), oo = (1<<29);
	int n,m,K,V,E,src,indeed;
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	Reader R = new InputStreamReader(System.in);
	int []to = new int[MAXE], next = new int[MAXE], last = new int[MAXE], flow = new int[MAXE], up = new int[MAXE], low = new int[MAXE], visited = new int[MAXV], p = new int[MAXV];
	EdgeCost []cost = new EdgeCost[MAXE], d = new EdgeCost[MAXV];
	EdgeCost ZERO = new EdgeCost(0,0), INF = new EdgeCost(1,0);

	int luje() throws Exception {
		int ch,n = 0;
		while ( (ch = R.read()) != -1 && !('0'<=(char)ch && (char)ch<='9') );
		for ( n = ch-'0'; (ch = R.read()) != -1 && '0' <= (char)ch && (char)ch <= '9'; n = 10*n+ch-'0' );
		return n;
	}

	public static void main( String ... args ) throws Exception {
		new Main().go();
	}

	private class EdgeCost implements Comparable<EdgeCost> {
		int a,b;

		public EdgeCost( int a, int b ) {
			this.a = a; this.b = b;
		}

		@Override
		public int compareTo( EdgeCost other ) {
			if ( this.a == other.a ) 
				return this.b == other.b?0:(this.b<other.b?-1:1);
			return this.a<other.a?-1:1;
		}

		EdgeCost sub( EdgeCost other ) {
			return new EdgeCost(this.a-other.a,this.b-other.b);
		}
		EdgeCost add( EdgeCost other ) {
			return new EdgeCost(this.a+other.a,this.b+other.b);
		}
		EdgeCost negate() {
			return new EdgeCost(-this.a,-this.b);
		}

		@Override
		public String toString() {
			StringBuilder sb = new StringBuilder();
			if ( a != 0 ) 
				return "-1\n";
			return Integer.toString(b)+"\n";
		}
	}

	void addArcs( int x, int y, int l, int u, EdgeCost w ) {
		int i = E++, j = E++;
		to[i] = y; next[i] = last[x]; last[x] = i; up[i] =  u; low[i] =  l; flow[i] = 0; cost[i] = w;
		to[j] = x; next[j] = last[y]; last[y] = j; up[j] = -l; low[j] = -u; flow[j] = 0; cost[j] = w.negate();
	}

	int easyCompare( EdgeCost a, EdgeCost b, EdgeCost c ) {
		int A1 = a.a, A2 = b.a+c.a, B1 = a.b, B2 = b.b+c.b;
		if ( A1 == A2 ) {
			if ( B1 == B2 ) return 0;
			return B1<B2?-1:1;
		}
		return A1<A2?-1:1;
	}

	int getTailOfNegativeCycle() {
		int x,y,i,j;
		boolean flag;

		for ( flag = true, visited[src] = ++indeed, d[src] = ZERO, j = 0; j < V && flag; ++j )
			for ( flag = false, i = 0; i < E; ++i )
				if ( visited[x=to[i^1]]==indeed && up[i]>flow[i] && (visited[y=to[i]]!=indeed || easyCompare(d[y],d[x],cost[i]) > 0) ) {
					visited[y] = indeed;
					d[y] = d[x].add(cost[p[y]=i]);
					flag = true ;
				}

		for ( i = 0; i < E; ++i ) 
			if ( visited[x=to[i^1]]==indeed && up[i]>flow[i] && (visited[y=to[i]]!=indeed || easyCompare(d[y],d[x],cost[i]) > 0) ) {
				d[y] = d[x].add(cost[p[y]=i]);
				return y;
			}
		return -1;
	}

	void mincostCirculation() throws Exception {
		int x,y,df;
		EdgeCost c = new EdgeCost(0,0);
		while ( (y=getTailOfNegativeCycle())>=0 ) {
			for ( visited[x=y]=++indeed, x=to[p[y]^1]; visited[x]!=indeed; visited[x]=indeed, x=to[p[x]^1] );
			for ( df = up[p[x]]-flow[p[x]], y = to[p[x]^1]; y != x; df = Math.min(df,up[p[y]]-flow[p[y]]), y = to[p[y]^1] );
			assert df > 0;
			for ( flow[p[x]] += df, flow[p[x]^1] -= df, y = to[p[x]^1]; y != x; flow[p[y]] += df, flow[p[y]^1] -= df, y = to[p[y]^1] );
		}
		for ( int i = 0; i < E; ++i ) {
			c.a += cost[i].a*flow[i];
		   	c.b += cost[i].b*flow[i];
		}
		c.a /= 2; c.b /= 2;
		bw.write(c.toString());
	}

	void go() throws Exception {
		int i,j,k,l;
		for ( int ts = luje(); ts-->0; ) {
			n = luje();
			m = luje();
			K = luje();
			for ( E = 0, V = 2*n+1, src = V-1, i = 0; i < V; last[i++] = -1 );
			for ( i = 0; i < n; ++i ) {
				addArcs(i,i+n,K,K,ZERO);  flow[E-2] = K; flow[E-1] = -K;
				addArcs(i+n,i,0,+oo,INF); flow[E-2] = K; flow[E-1] = -K; 
				addArcs(src,i,0,+oo,ZERO); addArcs(src,i+n,0,+oo,ZERO);
			}
			for ( l = 0; l < m; ++l ) {
				i = luje();
				j = luje();
				k = luje();
				addArcs(i+n,j,0,1,new EdgeCost(0,k));
			}
			mincostCirculation();
		}
		bw.flush();
	}
};

