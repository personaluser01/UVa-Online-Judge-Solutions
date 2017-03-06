/*
 * 1647. Computer Transformation
 * TOPIC: recurrent relations, matrix powers, linear transformation
 * status: Accepted
 * 4 --> 3
 * 5 --> 5
 * 7 --> 21
 */
import java.io.*;
import java.util.*;
import java.math.BigInteger;

class Main {
	final int N = 6, M = 0x400;
	Scanner scan = new Scanner(System.in);
	int n;
	class Mat {
		BigInteger [][]c = new BigInteger[N][N];
		Mat( String a ) {
			for ( int k = 0, i = 0; i < N; ++i )
				for ( int j = 0; j < N; ++j, ++k )
					c[i][j] = BigInteger.valueOf(a.charAt(k)-'0');
		}
		Mat() {
			for ( int i = 0; i < N; ++i )
				for ( int j = 0; j < N; ++j )
					if ( i == j )
						c[i][j] = BigInteger.valueOf(1);
					else c[i][j] = BigInteger.valueOf(0);
		}
		Mat mul( Mat other ) {
			Mat res = new Mat("000000000000000000000000000000000000");
			for ( int i = 0; i < N; ++i )
				for ( int j = 0; j < N; ++j ) 
					for ( int k = 0; k < N; ++k )
						res.c[i][j] = res.c[i][j].add(this.c[i][k].multiply(other.c[k][j]));
			return res;
		}
		Mat pw( int n ) {
			Mat res = new Mat(), x = new Mat("000000000000000000000000000000000000");
			for ( int i = 0; i < N; ++i )
				for ( int j = 0; j < N; ++j )
					x.c[i][j] = this.c[i][j].add(BigInteger.ZERO);
			for (;n>0; n>>=1, x = x.mul(x) ) 
				if ( (n&1)==1 ) 
					res = res.mul(x);
			return res;
		}
		void pr() {
			for ( int i = 0; i < N; ++i, System.out.println("") ) 
				for ( int j = 0; j < N; ++j ) 
					System.out.print(this.c[i][j].toString()+" ");
		}
	}
	public static void main( String[] args ) throws Exception { new Main().go(); }
	Mat []m = new Mat[M];
	Mat A = new Mat("110000110000000100011000100001000010");
	void go() throws Exception {
		int i,j,k;
		for ( i = 0; i < N; ++i ) m[i] = null;
		m[0] = new Mat();
		for (;scan.hasNext();) {
			n = scan.nextInt()-1;
			// n = scan.nextInt();
			if ( m[n] == null )
				m[n] = A.pw(n);
			BigInteger r = BigInteger.valueOf(0);
			r = r.add(m[n].c[2][0]);
			r = r.add(m[n].c[2][1]);
			r = r.add(m[n].c[2][3]);
			System.out.println(r.toString());
		}
	}
};

