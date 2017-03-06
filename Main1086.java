/*
 * 1086. Ministers' Major Mess
 * TOPIC: 2-sat
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 0x100, M = 0x200, MAXV = 2*N, S = 0, T = 1;
	Scanner scan = new Scanner(System.in);
	int m,n,cs = 0,V,E,top,mark,K;
	int [][][]adj = new int[2][MAXV][MAXV];
	int [][]deg = new int[2][MAXV], seen = new int[2][MAXV];
	int []scc = new int[MAXV], st = new int[MAXV], yes = new int[2];
	boolean []visited = new boolean[MAXV], present = new boolean[MAXV];
	char []ans = new char[MAXV];
	public static void main( String[] args ) throws Exception { new Main().go(); }
	void addArcs( int x, int y ) {
		adj[S][x^1][deg[S][x^1]++] = y;
		adj[S][y^1][deg[S][y^1]++] = x;
		adj[T][y][deg[T][y]++] = (x^1);
		adj[T][x][deg[T][x]++] = (y^1);
	}
	void undoArcs( int x, int y ) {
		--deg[S][x^1];
		--deg[S][y^1];
		--deg[T][x];
		--deg[T][y];
	}
	void dfs( int t, int x ) {
		int i;
		if ( seen[t][x] == yes[t] )
			return ;
		for ( seen[t][x] = yes[t], i = 0; i < deg[t][x]; ++i )
			dfs(t,adj[t][x][i]);
		if ( t == T ) st[++top] = x;
		else scc[x] = mark;
	}
	boolean isImpossible() {
		int x,t;
		for ( top = 0, ++yes[t = T], x = 0; x < V; dfs(t,x++) );
		for ( mark = 0, ++yes[S]; top > 0; --top )
			if ( seen[S][x=st[top]] != yes[S] ) { dfs(S,x); ++mark; }
		for ( x = 0; x < V; x += 2 )
			if ( scc[x^1] == scc[x] )
				return true;
		return false;
	}
	void assignVotes() {
		int val;
		char []Y = {'-','y','n','?'};
		for ( int i = 0; i < V; i += 2 ) {
			 if ( !present[i>>1] ) { ans[i>>1] = '?'; continue ; }
			val = 0;
			/* x_i = true */
			addArcs(i,i);
			if ( !isImpossible() ) val |= 1;
			undoArcs(i,i);
			addArcs(i^1,i^1);
			if ( !isImpossible() ) val |= 2;
			undoArcs(i^1,i^1);
			ans[i>>1] = Y[val];
		}
		for ( int i = 0; i < V; i += 2 ) 
			System.out.print(ans[i>>1]);
		System.out.println();
	}
	void go() throws Exception {
		int i,j,k,l,t;
		String ch;
		boolean flag;
		int []c = new int[0x10];
		while ( true ) {
			n = scan.nextInt(); m = scan.nextInt();
			if ( m == 0 && n == 0 ) break ;
			System.out.print("Case "+(++cs)+": ");
			for ( V = (n<<1), i = 0; i < n; present[i++] = false );
			for ( i = 0; i <= V; ++i )
				for ( t = S; t <= T; deg[t++][i] = 0 );
			for ( K = 0, i = 0; i < m; ++i ) {
				for ( k = scan.nextInt(), j = 0; j < k; ++j ) {
					t = scan.nextInt()-1;
					ch = scan.next();
					if ( ch.equals("y") ) t = (0|(t<<1));
					else t = (1|(t<<1));
					present[(c[j]=t)>>1] = true;
				}
				if ( k <= 2 ) for ( l = 0; l < k; addArcs(c[l],c[l]), ++l );
				else { for ( l = 0; l < k; ++l ) for ( j = l+1; j < k; addArcs(c[l],c[j++]) ); }
			}
			if ( isImpossible() ) { System.out.println("impossible"); continue ; }
			assignVotes();
		}
	}
};

