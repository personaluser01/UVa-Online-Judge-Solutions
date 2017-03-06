/*
 * 13012. Tea Tasting
 * TOPIC: trivial
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		int i,j,k,t;
		while ( scan.hasNext() ) {
			t = scan.nextInt();
			for ( k = i = 0; i < 5; ++i )
				if ( t == scan.nextInt() ) ++k;
			System.out.println(k);
		};
	}
};

