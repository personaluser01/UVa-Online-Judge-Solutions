/*
 * 12096. SetStackComputer
 * TOPIC: nwerc2006, simulation, tricky
 * status: Accepted
 */
import java.util.regex.*;
import java.util.*;
import java.io.*;

class Main {

	Scanner scan = new Scanner(System.in);

	Map<MySet,Integer> m;
	Map<Integer,MySet> im;

	class MySet extends TreeSet<Integer> implements Comparable<MySet> {
		public int compareTo( MySet other ) {
			int []x = new int[this.size()];
			int []y = new int[other.size()];
			int m = 0,n = 0;
			for ( Integer t: this )
				x[m++] = t;
			for ( Integer t: other )
				y[n++] = t;
			for ( int i = 0; i < n && i < m; ++i )
				if ( x[i] != y[i] )
					return x[i]<y[i]?-1:1;
			if ( m < n ) return -1;
			if ( m > n ) return 1;
			return 0;
		}
	}

	int insert( MySet s ) {
		if ( m.containsKey(s) ) 
			return m.get(s);
		int V = m.size();
		m.put(s,V++);
		im.put(V-1,s);
		return V-1;
	}

	public static void main( String [] args ) throws Exception { new Main().go(); }

	int union( int x, int y ) {
		MySet res = new MySet();
		MySet X = im.get(x), Y = im.get(y);
		for ( int i: X )
			res.add(i);
		for ( int i: Y )
			res.add(i);
		return insert(res);
	}

	int intersect( int x, int y ) {
		MySet res = new MySet();
		MySet X = im.get(x), Y = im.get(y);
		for ( int i: X )
			if ( Y.contains(i) )
				res.add(i);
		return insert(res);
	}

	int add( int x, int y ) {
		MySet X = im.get(x), Y = im.get(y);
		MySet Z = new MySet();
		Z.add(y);
		int z = insert(Z);
		MySet res = new MySet();
		for ( int i: X )
			res.add(i);
		res.add(z);
		return insert(res);
	}

	void go() throws Exception {
		int i,j,k,ts=scan.nextInt(),commands;
		String cmd;
		for ( ;ts-->0; ) {
			commands = scan.nextInt();
			Stack<Integer> r = new Stack<Integer>();
			m = new TreeMap<MySet,Integer>();
			im = new TreeMap<Integer,MySet>();
			while ( commands-- > 0 ) {
				cmd = scan.next();
				switch ( cmd ) {
					case "PUSH": i = insert(new MySet());
								 r.push(i);
								 break ;
					case "DUP":  r.push(r.peek());
								 break ;
					case "UNION": int a = r.pop(), b = r.pop();
								  r.push(union(a,b));
								  break ;
					case "INTERSECT": a = r.pop(); b = r.pop();
									  r.push(intersect(a,b));
									  break ;
					case "ADD": a = r.pop(); b = r.pop();
								r.push(add(b,a));
								break ;
				}
				System.out.println(im.get(r.peek()).size());
			}
			System.out.println("***");
		}
	}
}

