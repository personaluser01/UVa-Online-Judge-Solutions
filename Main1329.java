/*
 * 1329. Corporate Network
 * TOPIC: disjoint-set-union
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 20100;
	String s;
	int n;
	int []p = new int[N], d = new int[N];
	Scanner scan = new Scanner(System.in);
	public static void main ( String [] args ) throws Exception { new Main().go(); }
	int Dist( int i, int j ) { return Math.abs(i-j)%1000; }
	void linkThem( int i, int j ) {
		if ( find(i) != i ) { while (true); }
		d[i] = Dist(i,p[i]=j);
	}
	int find( int i ) {
		int j;
		if ( (j=p[i]) == i ) 
			return i;
		p[i] = find(p[i]);
		d[i] += d[j];
		return p[i];
	}
	void go() throws Exception {
		int ts = scan.nextInt(),i,j,k,l,t;
		for (;ts-->0;) {
			for ( n=scan.nextInt(), i=0; i<n; d[p[i]=i]=0, ++i );
			for (;!(s=scan.next()).equals("O");) 
				if ( s.equals("E") ) {
					find(i=scan.nextInt()-1);
					System.out.println(d[i]);
				}
				else {
					assert s.equals("I");
					i = scan.nextInt()-1; j = scan.nextInt()-1;
					linkThem(i,j);
				}
		}
	}
};

