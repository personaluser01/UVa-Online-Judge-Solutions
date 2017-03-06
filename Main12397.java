/*
 * status: Accepted
 * TOPIC: roman numerals, recursion
 */
import java.io.*;
import java.util.*;
import java.math.*;

class Main {
	public static void main( String [] args ) throws Exception { new Main().go(); }
	String conv( int n ) {
		if ( n == 0 ) return new String("");
		if ( n >= 1000 ) 
			return new String("M")+conv(n-1000);
		if ( n >= 900 )
			return new String("CM")+conv(n-900);
		if ( n >= 500 )
			return new String("D")+conv(n-500);
		if ( n >= 400 )
			return new String("CD")+conv(n-400);
		if ( n >= 100 )
			return new String("C")+conv(n-100);
		if ( n >= 90 )
			return new String("XC")+conv(n-90);
		if ( n >= 50 )
			return new String("L")+conv(n-50);
		if ( n >= 40 )
			return new String("XL")+conv(n-40);
		if ( n >= 10 )
			return new String("X")+conv(n-10);
		if ( n == 9 )
			return new String("IX");
		if ( n >= 5 )
			return new String("V")+conv(n-5);
		if ( n == 4 )
			return new String("IV");
		return new String("I")+conv(n-1);
	}
	void go() throws Exception {
		int i,j,k,n;
		String s;
		StringTokenizer st;
		Scanner scan = new Scanner(System.in);
		Map<String,Integer> m = new HashMap<String,Integer>();
		m.put("I",1);
		m.put("V",2);
		m.put("X",2);
		m.put("L",2);
		m.put("C",2);
		m.put("D",3);
		m.put("M",4);
		for ( ;scan.hasNext(); ) {
			s = conv(scan.nextInt()); n = 0;
			for ( char c: s.toCharArray() ) 
				n += m.get(Character.toString(c));
			System.out.println(n);
		}
	}
};

