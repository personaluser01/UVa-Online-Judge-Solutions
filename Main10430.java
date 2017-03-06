/*
 * 10430. Dear God
 * TOPIC: maths
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.math.BigInteger;

class Main {
	int n,t,ts = 0;
	Scanner scan = new Scanner(System.in);
	BigInteger p,q,g;
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		System.out.println("Dear GOD, Pardon Me");
		for ( ;scan.hasNext(); ) {
			if ( ++ts > 1 ) System.out.println("");
			t = scan.nextInt();
			n = scan.nextInt();
			if ( t == 1 ) {
				System.out.println("X = "+(n-1));
				System.out.println("K = 1");
				continue ;
			}
			BigInteger T = new BigInteger(Integer.toString(t));
			BigInteger A = T.pow(n);
			A = A.multiply(T.subtract(BigInteger.ONE));
			BigInteger B = T.pow(n).subtract(BigInteger.ONE);
			g = A.gcd(B);
			p = A.divide(g);
			q = B.divide(g);
			System.out.println("X = "+q.toString());
			System.out.println("K = "+p.toString());
		}
	}
};

