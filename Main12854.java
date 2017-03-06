/*
 * 12854. Automated Checking Machine
 * TOPIC: ad hoc
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception { new Main().go(); };
	void go() throws Exception {
		int i,j,k,u,v;
		while ( scan.hasNext() ) {
			for ( u = v = 0, i = 0; i < 5; u |= (scan.nextInt()<<i), ++i );
			for ( i = 0; i < 5; v |= (scan.nextInt()<<i), ++i );
			System.out.println((u^v)!=31?"N":"Y");
		}
	};
};

