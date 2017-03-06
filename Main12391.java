/*
 * 12391. Game, Set and Match
 * TOPIC: probability, dp
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final double oo = (1<<29);
	double p,G,S,T;
	double [][]g = new double[7][7], s = new double[9][9], m = new double[4][4], t = new double[10][10];
	long[][]C = new long[20][20];
	double calc_g( int i, int j ) {
		if ( g[i][j] < +oo )
			return g[i][j];
		if ( i == 3 && j == 4 ) 
			return g[i][j] = p*calc_g(3,3);
		if ( i == 4 && j == 3 )
			return g[i][j] = p+(1-p)*calc_g(3,3);
		if ( i == 3 && j == 3 )
			return g[i][j] = (p*p)/(1-2*p+2*p*p);
		if ( i == 0 && j == 4 )
			return g[i][j] = 0;
		if ( i == 4 && j == 0 )
			return g[i][j] = 1;
		if ( i == 4 && i >= j+2 ) 
			return g[i][j] = 1.00;
		if ( j == 4 && i+2 <= j )
			return g[i][j] = 0.00;
		return g[i][j] = p*calc_g(i+1,j)+(1-p)*calc_g(i,j+1);
	};
	double calc_s( int i, int j ) {
		if ( s[i][j] < +oo )
			return s[i][j];
		if ( (i >= 6) && j+2 <= i )
			return s[i][j] = 1.00;
		if ( i+2 <= j && (j >= 6) )
			return s[i][j] = 0.00;
		if ( i == 6 && j == 6 ) {
			s[i][j] = 0;
			for ( int k = 7; k <= 12; ++k )
				s[i][j] += C[k-1][6]*Math.pow(G,7)*Math.pow(1-G,k-7);
			s[i][j] += C[12][6]*Math.pow(G*(1-G),6)*G*G/(1-2*G*(1-G));
			return s[i][j];
		}
		assert i <= 6 && j <= 6;
		return s[i][j] = G*calc_s(i+1,j)+(1-G)*calc_s(i,j+1);
	};
	double DS() {
		double res = 0;
		for ( int k = 5; k <= 9; ++k )
			res += C[k][k+1-6]*Math.pow(G,6)*Math.pow(1-G,k+1-6);
		res += C[10][5]*Math.pow(G,6)*Math.pow(1-G,5)*(G+2*(1-G)*T);
		return S = res;
	}
	double calc_m( int i, int j ) {
		if ( m[i][j] < +oo )
			return m[i][j];
		if ( i >= 2 ) return m[i][j] = 1.00;
		if ( j >= 2 ) return m[i][j] = 0.00;
		return m[i][j] = S*calc_m(i+1,j)+(1-S)*calc_m(i,j+1);
	}
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		int i,j,k;
		for ( i = 0; i < 20; ++i )
			C[i][0] = 1L;
		for ( i = 1; i < 20; ++i )
			for ( j = 1; j <= i; ++j )
				C[i][j] = C[i-1][j]+C[i-1][j-1];
		for ( ;scan.hasNext() && (p=scan.nextDouble()) != -1; ) {
			for ( i = 0; i <= 4; ++i )
				for ( j = 0; j <= 4; ++j )
					g[i][j] = +oo;
			for ( i = 0; i <= 8; ++i )
				for ( j = 0; j <= 8; ++j )
					s[i][j] = +oo;
			for ( i = 0; i <= 3; ++i )
				for ( j = 0; j <= 3; ++j )
					m[i][j] = +oo;
			for ( i = 0; i <= 9; ++i )
				for ( j = 0; j <= 9; ++j )
					t[i][j] = +oo;
			G = calc_g(0,0); 
			for ( T = 0, k = 7; k <= 12; ++k )
				T += C[k-1][6]*Math.pow(p,7)*Math.pow(1-p,k-7);
			T += C[12][6]*Math.pow(p*(1-p),6)*p*p/(1-2*p*(1-p));
			S = DS();
			System.out.printf("%.11f %.11f %.11f\n",G,S,calc_m(0,0));
		}
	}
};

