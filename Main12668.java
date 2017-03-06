/*
 * 12668. Attacking Rooks
 * TOPIC: bipartite graph
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 0x80, Q = N*N, S = 0, T = 1;
	int n,yes,head,tail,cnt;
	char [][]g = new char[N][N];
	int [][]row = new int[N][N], col = new int[N][N], adj = new int[Q][N+N], mate = new int[2][Q];
	int []deg = new int[Q],seen = new int[Q], m = new int[2], q = new int[Q];
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception { new Main().go(); }
	int enc( int x, int y ) { return x|(y<<7); }
	boolean altPath( int x ) {
		int i,y;
		if ( seen[x] == yes )
			return false;
		for ( seen[x] = yes, i = 0; i < deg[x]; ++i )
			if ( mate[T][y = adj[x][i]] == -1 || altPath(mate[T][y]) ) {
				mate[T][mate[S][x]=y]=x;
				return true;
			}
		return false;
	}
	int bpm() {
		int x,i,j,k;
		boolean flag;
		for ( head = tail = cnt = 0, x = 0; x < m[S]; ++x ) {
			q[tail] = x; tail = (tail+1)&(Q-1); ++cnt;
		}
		do {
			for ( flag = false, k = cnt, ++yes; k-->0; ) {
				x = q[head]; head = (head+1)&(Q-1); --cnt;
				if ( altPath(x) ) flag = true;
				else {
					q[tail] = x; tail = (tail+1)&(Q-1); ++cnt;
				}
			}
		} while ( flag );
		return m[S]-cnt;
	}
	void go() throws Exception {
		int i,j,k,t,x,y;
		while ( scan.hasNext() ) {
			n = scan.nextInt();
			for ( i = 0; i < n; ++i ) 
				g[i] = scan.next().toCharArray();
			for ( t = S; t <= T; ++t ) m[t] = 0;
			for ( i = 0; i < n; ++i ) 
				for ( j = 0; j < n; ++j ) {
					if ( j == 0 || g[i][j-1] == 'X' ) ++m[S];
					if ( g[i][j] == '.' ) row[i][j] = m[S]-1;
				}
			for ( j = 0; j < n; ++j )
				for ( i = 0; i < n; ++i ) {
					if ( i == 0 || g[i-1][j] == 'X' ) ++m[T];
					if ( g[i][j] == '.' ) col[i][j] = m[T]-1;
				}
			for ( x = 0; x < m[S]; ++x ) deg[x] = 0;
			for ( t = S; t <= T; ++t )
				for ( x = 0; x < m[t]; ++x )
					mate[t][x] = -1;
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < n; ++j )
					if ( g[i][j] == '.' ) {
						x = row[i][j]; y = col[i][j];
						adj[x][deg[x]++] = y;
					}
			System.out.println(bpm());
		}
	}
};

