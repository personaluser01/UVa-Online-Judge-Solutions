/*
 * 12820. Cool Word
 * TOPIC: ad hoc
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	int ans,n,cs;
	public static void main( String [] args ) throws Exception { new Main().go(); };
	int f( String s ) {
		int []c = new int[256];
	   	long u = 0,v = 0;
		for ( char a: s.toCharArray() )
			if ( 'a' <= a && a <= 'z' )
				v |= (1L << (a-'a'));
			else if ( 'A' <= a && a <= 'Z' )
				v |= (1L << (a-'a'+26));
		if ( (v&(v-1)) == 0 )
			return 0;
		for ( char a: s.toCharArray() )
			if ( 'a' <= a && a <= 'z' )
				++c[(int)(a-'a')];
			else if ( 'A' <= a && a <= 'Z' )
				++c[(int)(a-'A'+26)];
		for ( int i = 0; i < 26; ++i )
			if ( c[i] > 0 && ((u>>c[i])&1) == 1 ) {
				return 0;
			}
			else u |= (1L<<c[i]);
		for ( int i = 26; i < 52; ++i )
			if ( c[i] > 0 && ((u>>c[i])&1) == 1 ) {
				return 0;
			}
			else u |= (1L<<c[i]);
		return 1;
	};
	void go() throws Exception {
		for (;scan.hasNext() && (n=scan.nextInt()) != 0; System.out.println("Case "+(++cs)+": "+ans) ) 
			for ( ans = 0; n-->0; ans += f(scan.next()) );
	};
};

