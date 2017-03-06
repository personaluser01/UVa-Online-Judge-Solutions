/*
 * 12893. Count It
 * TOPIC: bits
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception { new Main().go(); }
	long L( long k ) { return k & (~k+1); }
	void go() throws Exception {
		for ( long ans, n, ts = scan.nextLong(); ts-- > 0; System.out.println(ans) ) 
			for ( ans = 0, n = scan.nextLong(); n > 0; n &= ~L(n), ++ans );
	}
};

