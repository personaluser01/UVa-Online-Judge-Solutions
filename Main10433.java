/*
 */
import java.io.*;
import java.util.*;
import java.math.BigInteger;

class Main {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	public static void main ( String [] args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		BigInteger b,B;
		String s;
		while ( (s=br.readLine())!=null ) {
			b = new BigInteger(s);
			B = b.multiply(b);
			if ( B.toString().endsWith(s) )
				System.out.println("Automorphic number of "+(s.length())+"-digit.");
			else
				System.out.println("Not an Automorphic number.");
		}
	}
};

