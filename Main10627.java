/*
 * 10627. Infinite Race
 * TOPIC: gcd, cool maths, simulation, modulo
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	long f( long u ) { return (u&1); }
	long gcd( long x, long y ) {
		if ( y == 0 )
			return x;
		return gcd(y,x%y);
	}
	long g( long u ) { return (u>>1); }
	void go() throws Exception {
		Scanner scan = new Scanner(System.in);
		long u,v,uu,vv,d,k,i,j,L,T;

		while ( true ) {
			L = (long)scan.nextInt();
			if ( L == 0 ) break ;
			u = (long)scan.nextInt();
			v = (long)scan.nextInt();
			T = (long)scan.nextInt();
			if ( u == 0 && v == 0 ) {
				System.out.println("0");
				continue ;
			}
			if ( u < v ) { k = u; u = v; v = k; }
			k = g(T*(u+v)/L)+f(T*(u+v)/L);
			j = g(T*(u-v)/L)+f(T*(u-v)/L);
			d = gcd(u,v);
			if ( d != 0 ) {
				uu = u/d; vv = v/d;
			}
			else {
				uu = u; vv = v;
			}
			if ( 0 == f(uu-vv) ) {
				System.out.println(k+j);
				continue ;
			}
			i = g(T*d/L)+f(T*d/L);
			System.out.println(k+j-i);
		}
	}
};
