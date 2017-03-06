/*
 * 12870. Fishing
 * TOPIC: dp
 * status:
 */
import java.io.*;
import java.util.*;

class Main {
	final int SH = 7, N = (1<<SH), oo = (1<<29);
	Scanner scan = new Scanner(System.in);
	int m,n,K,w;
	int [][]c = new int[N][N];
	int []z = new int[1<<(SH+SH+SH+1)];
	public static void main( String [] args ) throws Exception { new Main().go(); }
	int BIT( int k ) { return (1<<k); }
	int MASK( int k ) { return BIT(k)-1; }
	boolean vc( int x, int y ) { return 0<=x&&x<m&&0<=y&&y<n; }
	int f( int x, int y, int k, int t ) { return x|(y<<SH)|(k<<(SH+SH))|(t<<(SH+SH+SH)); }
	void go() throws Exception {
		int i,j,k,ts = scan.nextInt(),u,v,x,y,dx,dy,nx,ny,t,nt;
		for(;ts-->0;){
			m = scan.nextInt(); 
			n = scan.nextInt();
			K = Math.max(m,n);
			for ( i = 0; i < m; ++i )
				for ( j = 0; j < n; ++j )
					c[i][j] = scan.nextInt();
			Queue<Integer> q = new LinkedList<Integer>(), Q = new LinkedList<Integer>();
			for ( i = 0; i < m; ++i )
				for ( j = 0; j < n; ++j )
					for ( k = 0; k <= K; ++k )
						for ( t = 0; t <= 1; ++t )
							z[f(i,j,k,t)] = -oo;
			for ( i = 0; i < m; ++i )
				for ( j = 0; j < n; ++j ) { z[u=f(i,j,1,1)]=-c[i][j]; q.add(u); }
			while ( q.size() > 0 ) {
				u = q.poll();
				x = u&MASK(SH);
				y = (u>>SH)&MASK(SH);
				k = (u>>(SH+SH))&MASK(SH);
				t = u>>(SH+SH+SH);
				if ( k == 0 ) {
					Q.add(f(x,y,k,t));
					continue ;
				}
				if ( t == 0 ) {
					for ( dx = 0; dx <= 1; ++dx )
						for ( dy = 0; dy <= 1; ++dy )
							if ( dx+dy >= 1 && vc(nx=x+dx,ny=y+dy) ) {
								if ( z[v=f(nx,ny,k,0)] < z[u] ) {
									z[v] = z[u]; q.add(v);
								}
								if ( z[v=f(nx,ny,k-1,1)] < z[u]-c[nx][ny] ) {
									z[v] = z[u]-c[nx][ny]; q.add(v);
								}
							}
				}
				else {
					if ( !vc(nx=x+1,ny=y+1) ) continue ;
					if ( z[v=f(nx,ny,k,0)]<z[u] ) {
						z[v]=z[u];
						q.add(v);
					}
					if ( z[v=f(nx,ny,k-1,1)] < z[u]-c[nx][ny] ) {
						z[v]=z[u]-c[nx][ny];
						q.add(v);
					}
				}
			}
			for ( w = -oo; Q.size() > 0; ) {
				u = Q.poll();
				x = u&MASK(SH);
				y = (u>>SH)&MASK(SH);
				k = (u>>(SH+SH))&MASK(SH);
				t = (u>>(SH+SH+SH));
				if ( k == 0 ) 
					if ( w < z[u] ) w = z[u];
				if ( t == 0 ) {
					for ( dx = 0; dx <= 1; ++dx )
						for ( dy = 0; dy <= 1; ++dy )
							if ( dx+dy >= 1 && vc(nx=x+dx,ny=y+dy) ) {
								if ( z[v=f(nx,ny,k,0)] < z[u] ) {
									z[v] = z[u]; Q.add(v);
								}
								if ( k >= 1 && z[v = f(nx,ny,k-1,1)] < z[u]-c[nx][ny] ) {
									z[v] = z[u]-c[nx][ny]; Q.add(v);
								}
								if ( k+1 <= K && z[v = f(nx,ny,k+1,1)] < z[u] ) {
									z[v] = z[u]; Q.add(v);
								}
								if ( k+2 <= K && z[v = f(nx,ny,k+2,1)] < z[u]+c[nx][ny] ) {
									z[v] = z[u]+c[nx][ny]; Q.add(v);
								}
							}
				}
				else {
					if ( !vc(nx=x+1,ny=y+1) ) continue ;
					if ( z[v=f(nx,ny,k,0)] < z[u] ) { z[v]=z[u]; Q.add(v); }
					if ( k >= 1 && z[v = f(nx,ny,k-1,1)] < z[u]-c[nx][ny] ) {
						z[v] = z[u]-c[nx][ny];
						Q.add(v);
					}
					if ( k+1 <= K && z[v = f(nx,ny,k+1,1)] < z[u] ) {
						z[v] = z[u];
						Q.add(v);
					}
					if ( k+2 <= K && z[v = f(nx,ny,k+2,1)] < z[u]+c[nx][ny] ) {
						z[v] = z[u]+c[nx][ny];
						Q.add(v);
					}
				}
			}
			System.out.println(Math.max(0,w));
		}
	}
};

