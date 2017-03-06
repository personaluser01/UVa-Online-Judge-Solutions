/*
 * 274. Cat And Mouse
 * TOPIC: bfs
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 0x80,CAT = 0,MOUSE = 1,Q = 0x400;
	int n,cat,mouse,head,tail,cnt;
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String s;
	int [][]deg = new int[2][N],seen = new int[2][N], d = new int[2][N];
	int []yes = new int[2],q = new int[Q];
	int [][][]adj = new int[2][N][N];
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void dfs( int t, int x ) {
		int i,y;
		for ( seen[t][x] = yes[t], i = 0; i < deg[t][x]; ++i )
			if ( seen[t][y=adj[t][x][i]] != yes[t] )
				dfs(t,y);
	}
	boolean visit( int src, int x, int dist ) {
		int y,i;
		if ( src == x && dist > 0 )
			return true;
		if ( seen[MOUSE][x] == yes[MOUSE] )
			return false;
		for ( seen[MOUSE][x] = yes[MOUSE], i = 0; i < deg[MOUSE][x]; ++i )
			if ( seen[CAT][y=adj[MOUSE][x][i]] != yes[CAT] ) 
				if ( visit(src,y,dist+1) ) return true;
		return false;
	}
	void go() throws Exception {
		int i,j,k,ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken()),t,l;
		boolean ans1,ans2;
		for ( br.readLine(); ts-->0; ) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			n = Integer.parseInt(st.nextToken());
			cat = Integer.parseInt(st.nextToken())-1;
			mouse = Integer.parseInt(st.nextToken())-1;
			for ( t = 0; t <= 1; ++t )
				for ( ++yes[t], i = 0; i < n; ++i ) 
					deg[t][i] = 0;
			for (;(s = br.readLine()) != null; ) {
				st = new StringTokenizer(s);
				i = Integer.parseInt(st.nextToken());
				j = Integer.parseInt(st.nextToken());
				if ( i == -1 && j == -1 ) break ;
				--i; --j;
				adj[CAT][i][deg[CAT][i]++] = j;
			}
			for (;(s = br.readLine()) != null; ) {
				if ( s.equals("") ) break ;
				st = new StringTokenizer(s);
				i = Integer.parseInt(st.nextToken())-1;
				j = Integer.parseInt(st.nextToken())-1;
				adj[MOUSE][i][deg[MOUSE][i]++] = j;
			}
			dfs(CAT,cat); dfs(MOUSE,mouse);
			for ( ans1 = false, i = 0; i < n && !ans1; ++i )
				if ( seen[CAT][i] == yes[CAT] && seen[MOUSE][i] == yes[MOUSE] ) 
					// if ( d[CAT][i] == d[MOUSE][i] )
						ans1 = true;
			++yes[MOUSE]; ans2 = visit(mouse,mouse,0);
			if ( ans1 ) System.out.print("Y"); else System.out.print("N"); 
			if ( ans2 ) System.out.println(" Y"); else System.out.println(" N"); 
			if ( ts > 0 ) System.out.println("");
		}
	}
};

