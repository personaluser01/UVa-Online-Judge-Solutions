/*
 * 11490. Just Another Problem
 * TOPIC: ad hoc, maths
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final long MOD = 100000007L;
	long s;
	Scanner scan = new Scanner(System.in);
	public static void main( String[] args ) throws Exception { new Main().go(); }
	class OrderedComparator implements Comparator<Long> {
		public int compare( Long a, Long b ) {
			long x = b-a;
			if ( x == 0 ) return 0;
			if ( x < 0 ) return -1;
			return 1;
		}
	}
	void go() throws Exception {
		long i,j,k,x,a,b;
		for (;(s=scan.nextLong())!=0;) {
			Set<Long> q = new TreeSet<Long>(new OrderedComparator());
			for ( k = 1; (j=6*k*k) < s; ++k ) {
				a = s-j;
				b = 7*k;
				if ( a >= 0 && 0 == (a%b) ) 
					q.add(a/b);
			}
			if ( q.size() == 0 ) {
				System.out.println("No Solution Possible\n");
				continue ;
			}
			Iterator<Long> iterator = q.iterator();
			while ( iterator.hasNext() ) {
				i = iterator.next();
				System.out.println("Possible Missing Soldiers = "+((((2*i)%MOD)*i)%MOD));
			}
			System.out.println("");
		}
	}
};

