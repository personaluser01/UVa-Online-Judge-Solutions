/*
 * 11719. Gridland Airports
 * TOPIC: kirchoff matrix tree theorem, inclusion exclusion
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.math.BigInteger;

class Main {
	Scanner scan = new Scanner(System.in);
	BigInteger MOD = new BigInteger("10000000000000007");

	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	BigInteger myPow( BigInteger x, BigInteger n ) {
		BigInteger ax = new BigInteger("1");
		for (;!n.equals(BigInteger.ZERO); n = n.divide(BigInteger.valueOf(2)) ) {
			if ( n.mod(BigInteger.valueOf(2)).equals(BigInteger.ONE) ) { 
				ax = ax.multiply(x);
				ax = ax.mod(MOD);
			}
			x = x.multiply(x);
			x = x.mod(MOD);
		}
		return ax;
	}
	void go() throws Exception {
		int cs,ts,a,b;
		BigInteger m,n,x;
		for ( ts = scan.nextInt(); ts-- > 0; ) {
			a = scan.nextInt();
			b = scan.nextInt();
			x = BigInteger.valueOf(a).multiply(BigInteger.valueOf(b));
			if ( (a%2) == 0 || (b%2) == 0 ) {
				m = x.divide(BigInteger.valueOf(2));
				n = x.divide(BigInteger.valueOf(2));
			}
			else {
				m = x.divide(BigInteger.valueOf(2)).add(BigInteger.ONE);
				n = x.divide(BigInteger.valueOf(2));
			}
			System.out.println(myPow(n,m.subtract(BigInteger.ONE)).multiply(myPow(m,n.subtract(BigInteger.ONE))).mod(MOD).toString());
		}
	}
};

