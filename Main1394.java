/*
 * 1394. And Then There Was One
 * TOPIC: dp
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	public static final int N = 10008, oo = (1<<29);
	int z[] = new int[N];
	int K;
	public static void main( String ... args ) throws Exception {
		new Main().go();
	}
	int calc_z( int n ) {
		if ( z[n] < +oo )
			return z[n];
		if ( n == 1 ) 
			return z[n] = 0;
		assert z[n] == +oo;
		z[n] = (((calc_z(n-1)+K-1)%(n-1))+1)%n;
		assert calc_z(n-1) >= 0 && calc_z(n-1) <= n-1: "calc_z("+(n-1)+") = "+calc_z(n-1);
		return z[n];
	}
	void go() throws Exception {
		int i,j,k,n,m;
		while ( true ) {
			n = scan.nextInt();
			k = scan.nextInt();
			m = scan.nextInt();
			if ( n == 0 && m == 0 && k == 0 )
				break ;
			for ( K = k, i = 0; i <= n+3; z[i++] = +oo );
			for ( i = 2; i <= n/2; calc_z(i++) );
			i = calc_z(n);
			System.out.println(((i+m-1+n)%n)+1);
		}
	}
}

