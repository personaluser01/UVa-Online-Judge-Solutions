/*
 * 12750. Keep Rafa at Chelsea
 * TOPIC: trivial
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 0x300;
	int n;
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		int i,j,k,l,ts = scan.nextInt(),cs = 0,run;
		boolean decided;
		for ( ;ts-->0; ) {
			n = scan.nextInt();
			System.out.printf("Case %d: ",++cs);
			for ( decided=false, k=0,run=0, i = 0; i < n; ++i ) {
				String t = scan.next();
				if ( decided ) continue ;
				if ( !t.equals("W") ) {
					if ( (++run) == 3 ) {
						k = i;
						decided = true ;
					}
				}
				else run = 0;
			}
			if ( !decided ) System.out.println("Yay! Mighty Rafa persists!");
			else System.out.println(k+1);
		}
	}
};

