/*
 * TOPIC: ad hoc, simulation
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {

	boolean []used,occupied;
	String []s,w,c = new String[0x100];
	int n,m,cur;

	public static void main ( String [] args ) throws Exception { new Main().go(); }

	void putNext( int idx ) {
		int i,j,k = w[idx].length();
		j = 0;
		for ( i = cur; j < k; i = (i+1)%n )
			if ( !occupied[i] ) {
				if ( ++j == k ) break ;
			}
		occupied[i] = true;
		c[cur = i] = s[idx];
	}

	void go() throws Exception {
		Scanner scan = new Scanner(System.in);
		int i,j,k;
		for (;(n=scan.nextInt())!=0;) {
			s = new String[n];
			w = new String[n];
			used     = new boolean[n];
			occupied = new boolean[n];
			for ( i = 0; i < n; ++i ) {
				s[i] = scan.next();
				w[i] = scan.next();
			}
			cur = 0;
			for ( i = 0; i < n; ++i ) occupied[i] = false;
			for ( i = 0; i < n; putNext(i++) );
			for ( i = 0; i < n; ++i ) {
				if ( i == 0 )
					System.out.print(c[i]);
				else System.out.print(" "+c[i]);
			}
			System.out.println("");
		}
	}
};

