/*
 * 1263. Mines
 * TOPIC: dfs, scc
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 2015;
	int ts,n,top,mark;
	boolean [][]g = new boolean[N][N];
	boolean []seen = new boolean[N];
	int []xx = new int[N], yy = new int[N], rr = new int[N], st = new int[N], scc = new int[N], indeg = new int[N];
	int [][][]adj = new int[2][N][N];
	int [][]deg = new int[2][N];
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception { new Main().go(); }
	boolean f( int i, int j ) 
	{ return 2*Math.max(Math.abs(xx[i]-xx[j]),Math.abs(yy[j]-yy[i])) <= rr[i]; }
	void reverse_dfs( int x ) {
		int y,i;
		for ( seen[x] = true, i = 0; i < deg[1][x]; ++i )
			if ( !seen[y=adj[1][x][i]] )
				reverse_dfs(y);
		st[++top] = x;
	}
	void dfs( int x ) {
		int y,i;
		for ( indeg[scc[x]=mark] = 0, seen[x]=true, i = 0; i < deg[0][x]; ++i ) 
			if ( !seen[y=adj[0][x][i]] )
				dfs(y);
	}
	boolean [][]h = new boolean[N][N];
	void DFS( int x ) {
		int i,y;
		for ( seen[x] = true, i = 0; i < deg[0][x]; ++i ) {
			if ( !seen[y=adj[0][x][i]] ) DFS(y);
			if ( scc[y] != scc[x] ) {
				if ( !h[scc[x]][scc[y]] )
					++indeg[scc[y]];
				h[scc[x]][scc[y]] = true;
			}
		}
	}
	void go() throws Exception {
		int i,j,k;
		for ( ts = scan.nextInt(); ts-- > 0; ) {
			n = scan.nextInt();
			for ( i = 0; i < n; ++i ) {
				indeg[i] = 0;
				xx[i] = scan.nextInt();
				yy[i] = scan.nextInt();
				rr[i] = scan.nextInt();
			}
			for ( i = 0; i < n; ++i )
				for ( k = 0; k < 2; ++k )
					deg[k][i] = 0;
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < n; ++j )
					if ( i != j && (g[i][j]=f(i,j)) ) {
						adj[0][i][deg[0][i]++] = j;
						adj[1][j][deg[1][j]++] = i;
					}
			for ( i = 0; i < n; ++i ) seen[i] = false;
			for ( top = 0, i = 0; i < n; ++i ) 
				if ( !seen[i] ) reverse_dfs(i);
			for(i=0;i<n;++i)seen[i]=false;
			for(mark=0;top>0;) 
				if(!seen[i=st[top--]]){dfs(i);mark++;}
			for ( i = 0; i < n; ++i ) seen[i] = false;
			for ( i = 0; i < mark; ++i )
				for ( j = 0; j < mark; ++j )
					h[i][j]=false;
			for ( i = 0; i < n; ++i )
				if ( !seen[i] )
					DFS(i);
			for ( k = i = 0; i < mark; ++i )
				if ( indeg[i] == 0 ) 
					++k;
			System.out.println(k);
		}
	}
};

