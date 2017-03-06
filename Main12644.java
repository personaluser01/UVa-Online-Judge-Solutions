/*
 * 12644. Vocabulary
 * TOPIC: bipartite graph
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 0x400,S = 0,T = 1,A = 26,Q = (1<<15);
	StringTokenizer st;
	String s;
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	int []n = new int[2],seen = new int[N],q = new int[Q];
	int [][]deg = new int[2][N], mate = new int[2][N];
	int yes,head,tail,cnt;
	String [][]w = new String[2][N];
	int [][][]signature = new int[2][N][A], adj = new int[2][N][N];
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	boolean covers( int i, int j ) {
		for ( int k = 0; k < A; ++k )
			if ( signature[S][i][k] < signature[T][j][k] )
				return false;
		return true;
	}
	boolean altPath( int x ) {
		int i,y;
		if ( seen[x] == yes )
			return false;
		for ( seen[x] = yes, i = 0; i < deg[S][x]; ++i )
			if ( mate[T][y=adj[S][x][i]] == -1 || altPath(mate[T][y]) ) {
				mate[S][x] = y;
				mate[T][y] = x;
				return true;
			}
		return false;
	}
	int bpm() {
		int x,k;
		boolean flag;
		head = tail = cnt = 0;
		for ( x = 0; x < n[S]; ++x ) {
			q[tail] = x; ++cnt;
			tail = (tail+1)&(Q-1);
		}
		do {
			for ( flag = false, k = cnt, ++yes; k-- > 0; ) {
				x = q[head]; --cnt; head = (head+1)&(Q-1);
				if ( altPath(x) ) 
					flag = true;
				else {
					q[tail] = x; ++cnt; tail = (tail+1)&(Q-1);
				}
			}
		} while ( flag );
		return n[S]-cnt;
	}
	void go() throws Exception {
		int i,j,k,t;
		while ( (s = br.readLine()) != null ) {
			st = new StringTokenizer(s);
			n[S] = Integer.parseInt(st.nextToken());
			n[T] = Integer.parseInt(st.nextToken());
			for ( t = S; t <= T; ++t )
				for ( i = 0; i < n[t]; ++i ) {
					w[t][i] = br.readLine();
					for ( k = 0; k < A; ++k )
						signature[t][i][k] = 0;
					for ( char c: w[t][i].toCharArray() ) 
						if ( 'a' <= c && c <= 'z' )
							++signature[t][i][(int)(c-'a')];
				}
			for ( t = S; t <= T; ++t )
				for ( i = 0; i < n[t]; mate[t][i] = -1, deg[t][i++] = 0 );
			for ( i = 0; i < n[S]; ++i )
				for ( j = 0; j < n[T]; ++j )
					if ( covers(i,j) ) {
						adj[S][i][deg[S][i]++] = j;
						adj[T][j][deg[T][j]++] = i;
					}
			System.out.println(bpm());
		}
	}
};

