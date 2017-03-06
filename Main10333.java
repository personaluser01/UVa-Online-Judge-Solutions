/*
 * 10333. The Tower of ASCII
 * TOPIC: formatting, maths, young tableau, transposition
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = (1<<12);
	Scanner scan = new Scanner(System.in);
	int h,n,m,cs = 0,len;
	int []a = new int[N], b = new int[N];
	char [][]g = new char[N][N];
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		int i,j,k,p,q=0,row,col,l,r;
		for ( StringBuilder sb; scan.hasNext(); ) {
			sb = new StringBuilder(); h = scan.nextInt();
			if ( h == 1 ) { System.out.println("Tower #"+(++cs)); System.out.printf("  \n\n"); continue; }
			for ( k = 0; k <= h; ++k ) {
				p = (int)Math.sqrt(q=1+8*(h-k));
				assert p*p <= q;
				if ( p*p == q ) break ;
			}
			n = (int)((Math.sqrt(q)-1)/2);
			m = (int)((1+Math.sqrt(1+8*(h-(n+k))))/2.00);
			assert m*(m-1)/2+n+k == h;
			assert m == n;
			for ( len = 0, a[len++] = n+k, i = m-1; i >= 1; a[len++] = i-- );
			for ( k = 0, i = 0; i < len-1; ++i )
				assert a[i] > a[i+1];
			for ( k = 0, i = 0; i < len; k += a[i++] );
			assert k == h;
			for ( i = 0, b[i++] = a[0]+a[1], j = 2; j < len; b[i++] = a[j++] );
			for ( i = 0; i < 2*h; ++i )
				for ( j = 0; j < 2*h; g[i][j++] = ' ' );
			for ( row = h-1, col = 0, i = 0; i < len; g[++row][++col] = '*', g[row--][++col] = '*', ++i )
				for ( k = a[i]; k-- > 0; g[row--][col] = '#' );
			for ( ++row, i = len-2; i >= 0; --i, --col ) 
				for ( g[row][++col] = '*', g[row][++col] = '*', ++col, k = b[i]; k-- > 0; g[row++][col] = '#' );
			assert row == h;
			for ( i = 0; i < h; ++i, sb.append("\n") ) {
				for ( j = 0; g[i][j] != '#'; ++j );
				for ( l = g[i][j+1]=='*'?j+2:j, j = l; g[i][++j] == ' ';);
				for ( r = j, j = l+1; j <= r-1; g[i][j++] = '.' );
				if ( g[i][j] == '*' ) r += 2;
				for ( j = 0; j <= r; sb.append(g[i][j++]) );
			}
			System.out.println("Tower #"+(++cs)+"\n"+sb.toString());
		}
	}
};

