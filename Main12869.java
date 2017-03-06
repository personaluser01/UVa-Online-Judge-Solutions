/*
 * 12869. Zeroes
 * TOPIC: maths
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception { new Main().go(); }
	long f( long n ) {
		long s = 0, ax = 5L, L = (long)(Math.log((double)n)/Math.log(5.00));
		for ( int i = 1; i <= L; ++i ) {
			s += n/ax;
			ax *= 5L;
		}
		return s;
	}
	long g( long m, long n ) {
		return (long)(Math.floor(Math.log((double)n)/Math.log(5.00)))-(long)(Math.ceil(Math.log((double)m)/Math.log(5.00)))+1;
	}
	long F( long n ) {
		return n/5;
	}
	void go() throws Exception {
		long m,n;
		for (;true;) {
			m = scan.nextLong();
			n = scan.nextLong();
			if ( m == 0 && n == 0 ) break ;
			System.out.println(F(n)-F(m)+1);
		}
	}
};

