/*
 * 1105. Coffee Central
 * TOPIC: dp
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = 0x400, SH = 0x400, M = N+N;
	int [][]seen = new int[N][N];
	int m,n,shops,qr,yes = 0;
	int [][]g = new int[N][N], dp = new int[M][N], dm = new int[M][N];
	public static void main( String [] args ) throws Exception { new Main().go(); }


	boolean vc(int x, int y) { return 1 <= x && x <= m && 1 <= y && y <= n; }

	int A( int xl, int yl, int xh, int yh ) {
		int k = xh+yh;
		assert( xl+yl == k );
		//System.out.println("before: "+xl+" "+yl+" "+xh+" "+yh);
		if ( xl > m ) {
			yl += xl-m; xl = m;
		}
		if ( yl <= 0 ) {
			xl += yl-1; yl = 1;
		}
		if ( xh <= 0 ) {
			yh += xh-1; xh = 1;
		}
		if ( yh > n ) {
			xh += yh-n; yh = n;
		}
		//System.out.println("after : "+xl+" "+yl+" "+xh+" "+yh);
		//if ( !vc(xl,yl) && !vc(xh,yh) )
		//	return 0;
		if ( yh < yl ) return 0;
		assert xh+yh == k;
		assert xl+yl == k;
		return dp[k][yh]-dp[k][yl-1];
	}
	int B( int xl, int yl, int xh, int yh ) {
		int k = xl-yl+SH;
		assert( xh-yh+SH == k );
		if ( xl <= 0 ) {
			yl -= xl-1; xl = 1;
		}
		if ( yl <= 0 ) {
			xl -= yl-1; yl = 1;
		}
		if ( xh > m ) {
			yh -= xh-m; xh = m;
		}
		if ( yh > n ) {
			xh -= yh-n; yh = n;
		}
		assert( xh-yh+SH == k );
		//if ( !vc(xl,yl) && !vc(xh,yh) )
		//	return 0;
		if ( yh < yl ) return 0;
		return dm[k][yh]-dm[k][yl-1];
	}

	int F( int x, int y, int L ) { return A(x,y-L,x-L,y); }
	int I( int x, int y, int L ) { return B(x-L,y,x,y+L); }
	int H( int x, int y, int L ) { return A(x+L,y,x,y+L); }
	int G( int x, int y, int L ) { return B(x,y-L,x+L,y); }

	int north( int x, int y, int L ) {
		if ( x-L <= 0 ) return 0;
		return g[x-L][y];
	}

	int south( int x, int y, int L ) {
		if ( x+L > m ) return 0;
		return g[x+L][y];
	}

	int west( int x, int y, int L ) {
		if ( y-L <= 0 ) return 0;
		return g[x][y-L];
	}

	int east( int x, int y, int  L ) {
		if ( y+L > n ) return 0;
		return g[x][y+L];
	}

	int enc( int x, int y ) { return x|(y<<10); }

	void go() throws Exception {
		int i,j,k,L,x,y,w,best_w,xx,yy,u,v,nw,cs = 0,headIdx,headSum,tailIdx,tailSum;
		while ( true ) {
			n = scan.nextInt();
			m = scan.nextInt();
			shops = scan.nextInt();
			qr = scan.nextInt();
			if ( m == 0 && n == 0 && shops == 0 && qr == 0 )
				break ;
			for ( i = 1; i <= m; ++i )
				for ( j = 1; j <= n; ++j )
					g[i][j] = 0;
			while ( shops-- > 0 ) {
				j = scan.nextInt();
				i = m-scan.nextInt()+1;
				g[i][j] = 1;
			}
			for ( k = 0; k < M; ++k )
				for ( j = 0; j < N; ++j )
					dp[k][j] = dm[k][j] = 0;
			for ( k = 2; k <= m+n; ++k )
				for ( j = 1; j <= n; ++j )
					if ( k-j <= m && k-j >= 1 )
						dp[k][j] = dp[k][j-1]+g[k-j][j];
			for ( k = 1-n; k <= m-1; ++k )
				for ( j = 1; j <= n; ++j )
					if ( k+j >= 1 && k+j <= m )
						dm[k+SH][j] = dm[k+SH][j-1]+g[k+j][j];
			int []q = new int[n*m], s = new int[n*m];
			System.out.println("Case "+(++cs)+":");
			while ( qr-- > 0 ) {
				L = scan.nextInt(); w = 0; x = y = 1;
				for ( yy = Math.max(1,y-L); yy <= Math.min(y+L,n); ++yy )
					if ( 1 <= yy && yy <= n )
						for ( xx = Math.max(1,x-L+Math.abs(y-yy)); xx <= Math.min(m,x+L-Math.abs(y-yy)); ++xx )
							if ( 1 <= xx && xx <= m )
								w += g[xx][yy];
				headIdx = tailIdx = 0;
				headSum = tailSum = 0;
				q[tailIdx++] = enc(1,1);
				s[tailSum++] = w;
				seen[1][1] = ++yes; best_w = w; xx = 1; yy = 1;
				// System.out.println(H(1,3,1)+" "+g[2][3]+" "+g[1][4]);
				while ( tailIdx > headIdx ) {
					u = q[headIdx++]; w = s[headSum++];
					x = u&1023; y = u>>10;
					// System.out.println("["+L+"]"+x+" "+y+" "+w);
					if ( w > best_w ) {
						best_w = w; xx = x; yy = y;
					}
					else if ( w == best_w ) {
						if ( x > xx || (x == xx && y < yy) ) {
							xx = x; yy = y;
						}
					}
					if ( y+1 <= n && seen[x][y+1] != yes ) {
						nw = w-F(x,y,L)-G(x,y,L)+west(x,y,L)+H(x,y+1,L)+I(x,y+1,L)-east(x,y+1,L);
						seen[x][y+1] = yes;
						q[tailIdx++] = enc(x,y+1);
						s[tailSum++] = nw;
					}
					if ( x+1 <= m && seen[x+1][y] != yes ) {
						nw = w-F(x,y,L)-I(x,y,L)+north(x,y,L)+H(x+1,y,L)+G(x+1,y,L)-south(x+1,y,L);
						seen[x+1][y] = yes;
						q[tailIdx++] = enc(x+1,y);
						s[tailSum++] = nw;
					}
				}
				System.out.println(best_w+" ("+yy+","+(m-xx+1)+")");
			}
		}
	}
}

