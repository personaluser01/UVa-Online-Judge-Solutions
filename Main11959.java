/*
 * 11959. Dice
 * TOPIC: simulation, dihedral groups
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {

	int [][] perm = new int[][] { 
			{4,2,0,3,1,5}, 
			{0,1,5,2,3,4},
			{2,4,1,3,0,5},
			{0,1,3,4,5,2}
		};
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

	StringTokenizer st;

	public static void main( String [] args ) throws Exception { new Main().go(); }

	public class Dice implements Comparable<Dice> {
		int [] c = new int[6];
		Dice( int [] a ) { for ( int i = 0; i < 6; ++i ) this.c[i] = a[i]; }
		int getTop()    { return this.c[0]; }
		int getBottom() { return this.c[1]; }
		int getFront()  { return this.c[2]; }
		int getLeft()   { return this.c[3]; }
		int getBack()   { return this.c[4]; }
		int getRight()  { return this.c[5]; }
		boolean equals( Dice other ) {
			for ( int i = 0; i < 6; ++i )
				if ( other.c[i] != this.c[i] )
					return false;
			return true;
		}
		Dice rotate( int t ) {
			int []d = new int[6];
			for ( int i = 0; i < 6; ++i ) d[i] = this.c[perm[t][i]];
			return new Dice(d);
		}
		Dice( String a ) {
			int i = 0;
			for ( char g: a.toCharArray() )
				this.c[i++] = g-'0';
		}
		public int compareTo( Dice other ) {
			for ( int i = 0; i < 6; ++i )
				if (this.c[i]<other.c[i])
					return -1;
				else if (this.c[i]>other.c[i])
					return 1;
			return 0;
		}
		void display() {
			for ( int i = 0; i < 6; ++i )
				System.out.printf("%d ",this.c[i]);
			System.out.println("");
		}
	}

	boolean check( Dice a, Dice b, TreeSet<Dice> h ) throws Exception {
		if ( a.equals(b) )
			return true;
		Dice c = a;
		for ( int t = 0; t <= 3; ++t )  {
			c = a.rotate(t);
			if ( !h.contains(c) ) {
				h.add(c);
				if ( check(c,b,h) )
					return true;
			}
		}
		return false;
	}

	void go() throws Exception {
		int ts;
		st = new StringTokenizer(br.readLine());
		ts = Integer.parseInt(st.nextToken());
		while ( ts-- > 0 ) {
			st = new StringTokenizer(br.readLine());
			Dice a = new Dice(st.nextToken());
			Dice b = new Dice(st.nextToken());
			TreeSet<Dice> h = new TreeSet<Dice>();
			if ( check(a,b,h) )
				System.out.println("Equal");
			else
				System.out.println("Not Equal");
			// System.out.println(h.size());
		}
	}
};

