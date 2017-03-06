/*
 * 12172. Matchsticks
 * TOPIC: dp
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 0x80, oo = (1<<29);
	Scanner scan = new Scanner(System.in);
	int n,maxlen,minlen;
	int []d = {6,2,5,5,4,5,6,3,7,6};
	boolean [][]z = new boolean[N][N];
	public static void main( String [] args ) throws Exception {
		new Main().go();
	};
	String findmin( int n, int len, boolean f ) {
		if ( len == 1 ) {
			for ( int i = (f?1:0); i < 10; ++i )
				if ( d[i] == n ) {
					return Integer.toString(i);
				}
			return "0";
		}
		for ( int i = (f?1:0); i < 10; ++i )
			if ( d[i] <= n && z[n-d[i]][len-1] ) 
				return Integer.toString(i)+findmin(n-d[i],len-1,false);
		return "0";
	};
	String findmax( int n, int len, boolean f ) {
		if ( len == 1 ) {
			for ( int i = 9; i >= (f?1:0); --i )
				if ( d[i] == n ) 
					return Integer.toString(i);
			return "0";
		}
		for ( int i = 9; i >= (f?1:0); --i )
			if ( d[i] <= n && z[n-d[i]][len-1] ) 
				return Integer.toString(i)+findmax(n-d[i],len-1,false);
		return "0";
	};

	void go() throws Exception {
		int ts = scan.nextInt(),i,j,k;
		for ( i = 0; i < 10; z[d[i++]][1] = true );
		for ( i = 1; i < N; ++i )
			for ( k = 0; k < N; ++k )
				if ( z[k][i] )
					for ( j = 0; j < 10; ++j )
						if ( d[j]+k < N )
							z[d[j]+k][i+1] = true ;
		for ( ;ts-->0; ) {
			n = scan.nextInt();
			maxlen = -oo;
			minlen = +oo;
			for ( i = 0; i < N; ++i )
				if ( z[n][i] ) {
					maxlen = Math.max(maxlen,i);
					minlen = Math.min(minlen,i);
				}
			System.out.println(findmin(n,minlen,true) + " " + findmax(n,maxlen,true));
		}
	};
};

