/*
 * 1330. City Game
 * TOPIC: largest unoccupied rectangle in a matrix
 * status: Accepted
 */
import java.util.*;
import java.io.*;

class Main {
	private final static int N = 0x400;
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	char [][]g = new char[N][N];
	int f( int []h, int n ) {
		int i,j,k,ans = 0;
		int []left = new int[n+1], right = new int[n+1];
		Deque<Integer> q = new LinkedList<>();
		for ( h[0] = -1, q.addLast(0), i = 1; i <= n; left[i] = (i-q.peekLast()), q.addLast(i++) )
			for ( ;!q.isEmpty() && h[q.peekLast()] >= h[i]; q.pollLast() ) ;
		for ( h[n+1] = -1, q.addLast(n+1), i = n; i >= 1; right[i] = (q.peekLast()-i), q.addLast(i--) ) 
			for ( ;!q.isEmpty() && h[q.peekLast()] >= h[i]; q.pollLast() ) ;
		for ( i = 1; i <= n; ++i )
			ans = Math.max(ans,(right[i]+left[i]-1)*h[i]);
		return ans;
	}
	void go() throws Exception {
		int i,j,k,ts = scan.nextInt(),ans,m,n;
		int []h;
		for ( ;ts-->0; ) {
			m = scan.nextInt();
			n = scan.nextInt();
			for ( ans = 0, i = 0; i < m; ++i )
				for ( j = 0; j < n; ++j )
					g[i][j] = scan.next().charAt(0);
			h = new int[n+2];
			for ( i = m-1, j = 0; j < n; ++j )
				for ( k = i; k >= 0 && g[k][j] == 'F'; ++h[j+1], --k ) ;
			for ( ;i >= 0; ) {
				ans = Math.max(ans,f(h,n));
				if ( --i < 0 ) break ;
				for ( j = 1; j <= n; ++j )
					if ( --h[j] < 0 )
						for ( h[j] = 0, k = i; k >= 0 && g[k][j-1] == 'F'; ++h[j], --k ) ;
			}
			System.out.println(ans*3);
		}
	}
};
