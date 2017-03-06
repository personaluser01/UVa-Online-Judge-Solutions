/*
 * 1194. Machine Scheduling
 * TOPIC: bipartite graph
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 0x80,S = 0,T = 1,Q = 0x400;
	Scanner scan = new Scanner(System.in);
	int yes,cnt,head,tail,edges,ans;
	int []n = new int[2], seen = new int[N],q = new int[Q];
	boolean [][]g = new boolean[N][N];
	int [][]deg = new int[2][N],mate = new int[2][N];
	int [][][]adj = new int[2][N][N];
	public static void main( String [] args ) throws Exception { new Main().go(); }
	boolean alt_path( int x ) {
		int i,y;
		if ( seen[x] == yes ) return false;
		for ( seen[x] = yes, i = 0; i < deg[S][x]; ++i )
			if ( mate[T][y=adj[S][x][i]]==-1 || alt_path(mate[T][y]) ) {
				mate[T][mate[S][x]=y]=x;
				return true;
			}
		return false;
	}
	int pop() { int x = q[head]; head = (head+1)&(Q-1); --cnt; return x; }
	void push( int x ) { q[tail] = x; ++cnt; tail = (tail+1)&(Q-1); }
	void bpm() {
		int x,k;
		boolean flag;
		for ( head=tail=cnt=0, x=0; x<n[0]; push(x++) );
		assert cnt == n[0];
		do {
			for ( flag = false, k = cnt; (++yes) > 0 && (k--) > 0; )
				if ( alt_path(x=pop()) ) flag=true;
				else push(x);
		} while ( flag );
		boolean []used = new boolean[n[1]+1];
		for ( k = 0, x = 0; x < n[0]; ++x )
			if ( mate[S][x] != -1 ) {
				assert !used[mate[S][x]];
				used[mate[S][x]] = true;
				++k;
			}
		System.out.println(k);
	}
	void go() throws Exception {
		int i,j,k,l,t;
		for (;(n[0]=scan.nextInt())!=0; bpm() ) {
			for ( n[1] = scan.nextInt(), t = 0; t <= 1; ++t )
				for ( i = 0; i <= n[t]; ++i ) {
					deg[t][i] = 0;
					mate[t][i] = -1;
				}
			for ( i = 0; i <= n[0]; ++i )
				for ( j = 0; j <= n[1]; ++j )
					g[i][j] = false;
			for ( ans = 0, edges = k = scan.nextInt(); k-- > 0; ) {
				l = scan.nextInt();
				i = scan.nextInt();
				j = scan.nextInt();
				if ( i == 0 || j == 0 ) { continue ; }
				if ( g[i][j] ) { ++ans; continue; }
				adj[S][i][deg[S][i]++] = j;
				adj[T][j][deg[T][j]++] = i;
				g[i][j] = true;
			}
		}
	}
};

