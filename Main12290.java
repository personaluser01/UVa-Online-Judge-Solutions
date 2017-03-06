/*
 * 12290. Counting Game
 * TOPIC: ad hoc
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = 0x80;
	int m,n,k,cur,dir;
	// int [][][]z = new int[N][N][N];
	public static void main( String [] args ) throws Exception { new Main().go(); }
	int next() {
		if ( cur == n-1 && dir == 1 ) {
			dir = -1;
			cur = n-2;
			return cur;
		}
		if ( cur == 0 && dir == -1 ) {
			dir = 1;
			cur = 1;
			return cur;
		}
		return cur+=dir;
	}
	boolean F( int x ) {
		if ( 0 == (x%7) ) return true;
		return Integer.toString(x).indexOf('7') != -1;
	}
	void go() throws Exception {
		int i,j,l,t,x;
		while ( true ) {
			n = scan.nextInt();
			m = scan.nextInt();
			k = scan.nextInt();
			if ( n == 0 && m == 0 && k == 0 ) break ;
			for ( t = -1, cur = 0, dir = 1, x = 1, l = 0; l != k; next(), ++x ) 
				if ( cur == m-1 && F(x) &&(++l) == k ) t = x;
			System.out.println(t);
		}
	}
};

