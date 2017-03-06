/*
 * 12797. Letters
 * TOPIC: graph traversal
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 0x80;
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String s;
	int n,ans,limit,yes;
	int []dx = {-1,0,1,0},dy = {0,1,0,-1};
	char [][]c = new char[N][N];
	int [][]seen = new int[N][N];
	public static void main( String []args ) throws Exception { new Main().go(); }
	int BIT( int k )  { return (1<<k); }
	int MASK( int k ) { return BIT(k)-1; }
	boolean vc ( int x, int y ) { return 0 <= x && x < n && 0 <= y && y < n; }
	int f ( char ch ) {
		if ( 'a' <= ch && ch <= 'z' )
			return ch-'a';
		return 10+(ch-'A');
	}

	List<Set<Integer>> g = new ArrayList<Set<Integer>>(N*N);
	Map<Long,Integer> dist;

	void dfs( int x, int y, int u, int cost ) {
		int i,j,k,l,nx,ny;
		if ( cost >= ans || cost > limit ) return ; 
		if ( x == n-1 && y == n-1 ) {
			ans = Math.min(ans,cost);
			return ;
		}
		//if ( ((u>>10)&(u&1023)) > 0 )
		//	return ;
		if ( seen[x][y] != yes ) {
			seen[x][y] = yes;
			g.set(x*n+y,new HashSet<Integer>());
		}
		if ( g.get(x*n+y).contains(u) && dist.get((long)x|((long)y<<7)|((long)u<<14)) <= cost ) 
			return ;
		g.get(x*n+y).add(u);
		dist.put((long)x|((long)y<<7)|((long)u<<14),cost);
		for ( i = 0; i < 4; ++i ) {
			nx = x+dx[i]; ny = y+dy[i];
			if ( !vc(nx,ny) ) continue ;
			k = f(c[nx][ny]);
			if ( k >= 10 ) l = k-10;
			else l = k+10;
			if ( 1==((u>>l)&1) )
				continue ;
			dfs(nx,ny,u|BIT(k),cost+1);
		}
	}

	void go() throws Exception {
		int i,j,k;
		for ( i = 0; i < N; ++i )
			for ( j = 0; j < N; ++j )
				g.add(null);
		for (;(s=br.readLine())!=null;) {
			for ( n = Integer.parseInt(s), i = 0; i < n; ++i ) 
				for ( s = br.readLine(), j = 0; j < n; ++j )
					c[i][j] = s.charAt(j);
			ans = (1<<29);
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < n; ++j )
					g.set(i*n+j,new HashSet<Integer>());
			/*for ( limit = 0; limit <= n*n && ans == (1<<29); ++limit ) {
				++yes; dist = new HashMap<Long,Integer>();
				dfs(0,0,BIT(f(c[0][0])),1);
			}*/
			++yes; dist = new HashMap<Long,Integer>();
			limit = n*n; dfs(0,0,BIT(f(c[0][0])),1);
			if ( ans == (1<<29) ) 
				ans = -1;
			System.out.println(ans);
		}
	}
};

