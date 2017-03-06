/*
 * 10237. Bishops
 * TOPIC: dp, recurrence, board transformation, very neat, best
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.math.BigInteger;

class Main {
	final int N = 32, BLACK = 1, WHITE = 0;
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	class Board {
		int m,n,A;
		Board() {A=m=n=0;};
		Board( int mm, int nn, int AA ) {
			this.m=mm; this.n=nn; this.A=AA;
		};
	};
	void display( int [][]g, int m, int n, int lift ) {
		for ( int i = 0; i < m; ++i ) {
			for ( int j = 0; j < m; ++j )
				if ( g[i][j] == -1 )
					System.out.printf("%2c",'.');
				else if ( g[i][j] == 0 )
					System.out.printf("%2c",(lift<=i&&i<=lift+n-1&&lift<=j&&j<=lift+n-1?Character.toUpperCase('o'):'o'));
				else System.out.printf("%2c",(lift<=i&&i<=lift+n-1&&lift<=j&&j<=lift+n-1?Character.toUpperCase('X'):'x'));

			System.out.println();
		}
		System.out.println();
	}
	Board getTwoBoards( int n, int color ) {
		int i,j,k,l,t,m,lift,x,y,nx,ny,w,h,A;
		int [][]g;
		int []leftmost, rightmost;
		m = n+n+n+2;
		g = new int[m][m];
		leftmost = new int[m];
		rightmost = new int[m];
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < m; ++j )
				g[i][j] = -1;
		lift = n/2-1+(n%2);
		for ( t = BLACK, i = 0; i < n; ++i, t ^= 1 )
			for ( k = t, j = 0; j < n; g[i+lift][j+lift] = k, k ^= 1, ++j );
		for ( x = lift, y = lift, t = g[x][y], k = 1; k <= lift; g[nx = x+k][ny = y-k] = t, ++k );
		for ( x = lift, y = lift, t = g[x][y], k = 1; k <= lift; g[nx = x-k][ny = y+k] = t, ++k );
		for ( x = n-1+lift, y = n-1+lift, t = g[x][y], k = 1; k <= lift; g[nx = x-k][ny = y+k] = t, ++k );
		for ( x = n-1+lift, y = n-1+lift, t = g[x][y], k = 1; k <= lift; g[nx = x+k][ny = y-k] = t, ++k );
		for ( x = lift+n-1, y = lift, t = g[x][y], k = 1; k <= lift; g[nx = x+k][ny = y+k] = t, ++k );
		for ( x = lift+n-1, y = lift, t = g[x][y], k = 1; k <= lift; g[nx = x-k][ny = y-k] = t, ++k );
		for ( x = lift, y = n-1+lift, t = g[x][y], k = 1; k <= lift; g[nx = x+k][ny = y+k] = t, ++k );
		for ( x = lift, y = n-1+lift, t = g[x][y], k = 1; k <= lift; g[nx = x-k][ny = y-k] = t, ++k );
		for ( y = 0; y < m; leftmost[y++] = x )
			for ( x = 0; x < m && g[x][y] == -1; ++x );
		for ( y = 0; y < m; rightmost[y++] = x )
			for ( x = m-1; m >= 0 && x >= 0 && g[x][y] == -1; --x );
		for ( y = 0; y < m; ++y ) 
			if ( leftmost[y] <= rightmost[y] )
				for ( t = g[x = leftmost[y]][y]; x <= rightmost[y]; g[x][y] = t, t ^= 1, ++x );
		// display(g,m,n,lift);
		for ( A = 0, t = color; t <= color; ++t ) {
			for ( x = -1, j = 0; j < m && x == -1; ++j )
				for ( i = 0; i < m && x == -1; ++i )
					if ( g[i][j] == t ) { x = i; y = j; }
			for ( nx = x, ny = y, w = 0; g[nx][ny] != -1 && (++w>=1); ++nx, ++ny );
			for ( nx = x, ny = y, h = 0; nx >= 0 && g[nx][ny] != -1 && (++h>=1); --nx, ++ny );
			for ( x = 0; x < m; ++x )
				for ( y = 0; y < m; ++y )
					if ( g[x][y]==color && !(lift<=x && x<=lift+n-1 && 0<=y && y<=lift+n-1) )
						++A;
			return new Board(Math.min(w,h),Math.max(w,h),A);
		}
		return new Board();
	}
	BigInteger [][][]z = new BigInteger[N][N][N*N];
	int []bts = new int[1<<21];
	BigInteger MINUS_ONE = new BigInteger("-1");

	BigInteger calcZ( int m, int n, int K ) {
		int u,i,j,k,l,A,B,s,wing,up,down;
		BigInteger ax;
		boolean []row,col;
		BigInteger [][]f;
		boolean ok;
		int []left,right;

		assert m+1 == n || m == n;

		if ( !z[m][n][K].equals(MINUS_ONE) )
			return z[m][n][K];

		if ( K > m ) return z[m][n][K] = BigInteger.ZERO;

		left = new int[m+1];
		right = new int[m+1];
		wing = (m-2+(m%2))/2;
		for ( k = wing, i = 0; k >= 1; ++i, --k ) {
			left[i] = k; right[i] = n-k-1;
		}
		up = i;
		for ( k = wing, i = m-1; k >= 1; --i, --k ) {
			left[i] = k; right[i] = n-k-1;
		}
		down = i;
		for ( i = up; i <= down; ++i ) {
			left[i] = 0; right[i] = n-1;
		}

		if ( m*n <= 19 ) {
			row = new boolean[m+1];
			col = new boolean[n+1];
			long w = 0;
			for ( w = 0, u = 0; u < (1<<(m*n)); ++u ) {
				if ( bts[u] != K ) continue ;
				for ( i = 0; i <= m; row[i++] = false );
				for ( j = 0; j <= n; col[j++] = false );
				for ( ok = true, i = j = 0, l = 0; l < (m*n) && ok; ++l ) {
					if ( 1 == ((u>>l)&1) ) {
						if ( row[i] || col[j] || !(left[i]<=j&&j<=right[i]) ) 
							ok = false ;
						row[i] = col[j] = true ;
					}
					if ( ++j == n ) { ++i; j = 0; }
				}
				if ( ok ) ++w;
			}
			return z[m][n][K] = new BigInteger(Long.toString(w));
		}
		//System.out.println("m = "+m+", n = "+n+", wing = "+wing);
		//for ( i = 0; i < m; ++i )
		//	System.out.println("["+left[i]+","+right[i]+"]");
		s = 2*wing;
		A = ((wing+1)*wing)*2; B = m*n-A;

		// for ( ax = 0, i = 0; i < m; ++i )
		//	ax += right[i]-left[i]+1;
		//System.out.println(B+" "+ax);
		// assert ax == B;
		f = new BigInteger[m+3][m+3];
		for ( i = 0; i <= m+2; ++i )
			for ( j = 0; j <= m+2; ++j )
				f[i][j] = BigInteger.ZERO;
		f[0][0] = new BigInteger("1");
		for ( k = 1; k <= K+1 && k <= A && k <= m; f[k][0] = calcZ(s,s,k), ++k );
		for ( j = 1; j <= n; ++j ) {
			for ( i = 0; i+j-1 <= m && i+j-1 <= n; ++i ) {
				// ax = ((long)(m-i-j+1)*(n-i-j+1))*f[i][j-1]-((long)(i+1))*f[i+1][j-1];
				ax = (f[i][j-1].multiply(new BigInteger(Integer.toString((m-i-j+1)*(n-i-j+1))))).subtract(f[i+1][j-1].multiply(new BigInteger(Integer.toString(i+1))));
				// assert ax%j == 0;
				f[i][j] = ax.divide(new BigInteger(Integer.toString(j)));
			}
		}
		return z[m][n][K] = f[0][K];
	}

	void go() throws Exception {
		int i,j,k,m,n,K,t;
		BigInteger w;
		Board[]p = new Board[2];
		for ( i = 0; i < (1<<21); ++i )
			bts[i] = bts[i>>1]+(i&1);
		for ( i = 0; i < N; ++i )
			for ( j = 0; j < N; ++j )
				for ( k = 0; k < N*N; ++k )
					z[i][j][k] = MINUS_ONE;
		for ( z[0][0][0] = BigInteger.ONE;; ) {
			 n = scan.nextInt();
			 K = scan.nextInt();
			 if ( n == 0 && K == 0 ) break ;
			 if ( K > n*n ) {
				System.out.println("0");
				continue ;
			 }
			 if ( n == 1 ) {
				System.out.println("1");
				continue ;
			 }
			 for ( t = WHITE; t <= BLACK; ++t ) 
				p[t] = getTwoBoards(n,t);
			 for ( w = BigInteger.ZERO, k = 0; k <= K; ++k )
				w = w.add(calcZ(p[WHITE].m,p[WHITE].n,k).multiply(calcZ(p[BLACK].m,p[BLACK].n,K-k)));
			 System.out.println(w.toString());
		}
	}
};

