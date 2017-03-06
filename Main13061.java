/*
 * 13061. Going Shopping with Grandma (I)
 * TOPIC: dp
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = 2*0x400;
	final long MOD = 9999959999L, oo = MOD+1;
	long [][]z = new long[N][N];
	long calc_z( int m, int n ) {
		if ( m >= N || n >= N )
			return 0;
		if ( z[m][n] < +oo )
			return z[m][n];
		if ( m == 0 && n == 0 )
			return z[m][n] = 1L;
		if ( m == 0 ) 
			return z[m][n] = (1+calc_z(m,n-1))%MOD;
		if ( n == 0 )
			return z[m][n] = (1+calc_z(m-1,1))%MOD;
		return z[m][n] = (((1+calc_z(m-1,n+1))%MOD)+calc_z(m,n-1))%MOD;
	}
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		int i,j,k,m,n;
		for ( i = 0; i < N; ++i )
			for ( j = 0; j < N; ++j )
				z[i][j] = +oo;
		for(;;) {
			m = scan.nextInt();
			n = scan.nextInt();
			if ( m == 0 && n == 0 )
				break ;
			System.out.println(calc_z(m,n));
		}
	}
};

