/*
 * 12895. Armstrong Number
 * TOPIC: trivial
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final long L = 10000000000L;
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception {
		new Main().go();
	};
	long pw( long x, long n ) {
		long ax = 1L;
		for ( ;n>0;n>>=1) {
			if ((n&1)==1) {
				ax *= x;
			}
			x *= x;
		}
		return ax;
	};
	void go() throws Exception {
		long i,j,k,l,t;
		String s;
		for ( int ts = scan.nextInt(); ts-->0; ) {
			t = scan.nextLong();
			char []d = Long.toString(t).toCharArray();
			long n = d.length;
			boolean ok = true ;
			k = 0;
			for ( char c: d ) {
				long x = pw((long)(c-'0'),n);
				k += x;
			}
			System.out.println(k==t?"Armstrong":"Not Armstrong");
		}
	}
};

