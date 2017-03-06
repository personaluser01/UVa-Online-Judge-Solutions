/*
 * 614. Mapping the Route
 * TOPIC: recursion, traversal, pretty-printing
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	int N = 0x20, Q = N*N,sx,sy,tx,ty;
	int []dx = {0,-1,0,1};
	int []dy = {-1,0,1,0};
	int [][]c = new int[N][N], id = new int[N][N], e = new int[N][N];
	boolean [][]g = new boolean[Q][Q];
	int m,n,V;
	public static void main( String [] args ) throws Exception { new Main().go(); }
	boolean vc( int x, int y ) { return 0 <= x && x < m && 0 <= y && y < n; }
	void buildRoof( int n ) {
		for ( int j = 0; j < n; ++j ) System.out.print("+---");
		System.out.println("+");
	}
	boolean f( int x, int y, int px, int py, int step ) {
		int nx,ny;
		e[x][y] = step;
		if ( tx == x && ty == y ) return true;
		for ( int i = 0; i < 4; ++i ) {
			if ( !vc(nx=x+dx[i],ny=y+dy[i])||!g[id[x][y]][id[nx][ny]]||(px==nx&&py==ny)||e[nx][ny]==0 ) continue ;
			if ( f(nx,ny,x,y,step+1) ) return true;
		}
		e[x][y] = 0;
		return false;
	}
	void go() throws Exception {
		Scanner scan = new Scanner(System.in);
		int i,j,k,cs = 0,x,y,nx,ny,u,v;
		while ( true ) {
			m = scan.nextInt(); n = scan.nextInt(); sx = scan.nextInt(); sy = scan.nextInt(); tx = scan.nextInt(); ty = scan.nextInt();
			if ( m == 0 && n == 0 && sx == 0 && sy == 0 && tx == 0 && ty == 0 ) break ;
			for ( V = i = 0; i < m; ++i ) for ( j = 0; j < n; ++j ) { c[i][j] = scan.nextInt(); id[i][j] = V++; e[i][j] = -1; }
			for ( i = 0; i < V; ++i ) for ( j = 0; j < V; ++j ) g[i][j] = false;
			for ( i = 0; i < m; ++i )
				for ( j = 0; j < n; ++j ) {
					if ( c[i][j] == 0 ) {
						nx = i+dx[2]; ny = j+dy[2];
						if ( vc(nx,ny) ) g[id[i][j]][id[nx][ny]] = g[id[nx][ny]][id[i][j]] = true;
						nx = i+dx[3]; ny = j+dy[3];
						if ( vc(nx,ny) ) g[id[i][j]][id[nx][ny]] = g[id[nx][ny]][id[i][j]] = true;
					}
					if ( c[i][j] == 1 ) {
						nx = i+dx[3]; ny = j+dy[3];
						if ( vc(nx,ny) ) g[id[i][j]][id[nx][ny]] = g[id[nx][ny]][id[i][j]] = true;
					}
					if ( c[i][j] == 2 ) {
						nx = i+dx[2]; ny = j+dy[2];
						if ( vc(nx,ny) ) g[id[i][j]][id[nx][ny]] = g[id[nx][ny]][id[i][j]] = true;
					}
				}
			--tx; --ty; f(sx-1,sy-1,-1,-1,1);
			System.out.println("Maze "+(++cs));
			System.out.println("");
			buildRoof(n);
			for ( i = 0; i < m; ++i ) {
				System.out.print("|");
				for ( u = j = 0; j < n; ++j ) {
					nx=i+dx[3]; ny=j+dy[3];
					if ( !vc(nx,ny) || !g[id[i][j]][id[nx][ny]] )
						u |= (1 << j);
					nx=i+dx[2]; ny=j+dy[2];
					if ( e[i][j] == 0 ) System.out.print("???");
					else if ( e[i][j] == -1 ) System.out.print("   ");
					else System.out.print(String.format("%3d",e[i][j]));
					if ( !vc(nx,ny) || !g[id[i][j]][id[nx][ny]] ) 
						System.out.print("|");
					else System.out.print(" ");
				}
				System.out.println("");
				for ( j = 0; j < n; ++j )
					if ( 0 == ((u>>j)&1) )
						System.out.print("+   ");
					else 
						System.out.print("+---");
				System.out.println("+");
			}
			System.out.println("\n");
		}
	}
};

