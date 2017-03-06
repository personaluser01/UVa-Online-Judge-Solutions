/*
 * 512. Spreadsheet Tracking
 * TOPIC: built-in libraries, linked list
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	int m,n,oo = (1<<29);
	List<List<Integer>> x;
	public static void main( String ... args ) throws Exception {
		new Main().go();
	}
	void exchange( int r0, int c0, int r1, int c1 ) {
		if ( x.size() <= r0 || x.size() <= r1 ) return ;
		if ( x.get(r0).size() <= c0 || x.get(r1).size() <= c1 )
			return ;
		int a = x.get(r0).get(c0), b = x.get(r1).get(c1);
		x.get(r0).set(c0,b);
		x.get(r1).set(c1,a);
	}
	void delColumn( List<Integer> lst ) {
		for ( int j = 0; j < lst.size(); ++j ) 
			for ( int i = 0; i < x.size(); ++i )
				if ( lst.get(j)-j < x.get(i).size() )
					x.get(i).remove(lst.get(j)-j);
	}
	void delRow( List<Integer> lst ) {
		for ( int i = 0; i < lst.size(); ++i )
			if ( x.size() > lst.get(i)-i ) 
				x.remove(lst.get(i)-i);
	}
	void insColumn( List<Integer> lst ) {
		for ( int j = 0; j < lst.size(); ++j )
			for ( int i = 0; i < x.size(); ++i )
				if ( lst.get(j)+j > x.get(i).size() )
					x.get(i).add(-oo);
				else 
					x.get(i).add(lst.get(j)+j,-oo);
	}
	void insRow( List<Integer> lst ) {
		int nn = x.get(0).size();
		List<Integer> l;
		for ( int i = 0; i < lst.size(); ++i )
			if ( lst.get(i)+i < x.size() ) {
				x.add(lst.get(i)+i,l = new LinkedList<>());
				for ( int j = 0; j < nn; l.add(-oo), ++j );
			}
			else x.add(new LinkedList<>());
	}
	private static class Pair {
		int x,y;
		private Pair( int x, int y ) {
			this.x = x;
			this.y = y;
		}
		@Override
		public String toString() {
			return String.format("(%1$d,%2$d)",x,y);
		}
	}
	Pair find( final int t ) {
		for ( int i = 0; i < x.size(); ++i )
			if ( x.get(i).contains(t) )
				return new Pair(i+1,x.get(i).indexOf(t)+1);
		return null;
	}
	void go() throws Exception {
		int i,j,k,r0,c0,r1,c1,cs = 0;
		List<Integer> lst;
		Pair t;
		while ( true ) {
			m = scan.nextInt();
			n = scan.nextInt();
			if ( m == 0 && n == 0 ) break ;
			x = new LinkedList<>();
			for ( i = 0; i < m; ++i ) {
				x.add(lst = new LinkedList<>());
				for ( j = 0; j < n; ++j )
					lst.add(i|(j<<10));
			}
			for ( int comms = scan.nextInt(); comms-->0; ) {
				String cc = scan.next();
				switch ( cc ) {
					case "EX": r0 = scan.nextInt()-1;
							   c0 = scan.nextInt()-1;
							   r1 = scan.nextInt()-1;
							   c1 = scan.nextInt()-1;
							   exchange(r0,c0,r1,c1);
							   break ;
					default:   lst = new ArrayList<>();
							   for ( k = scan.nextInt(); k-->0; lst.add(scan.nextInt()-1) );
							   Collections.sort(lst);
							   switch ( cc ) {
									  case "DC": delColumn(lst); break ;
									  case "DR": delRow(lst); break ;
									  case "IC": insColumn(lst); break ;
									  case "IR": insRow(lst); break ;
									  default: assert false ;
							   }
							   break ;
				}
			}
			if ( cs >= 1 ) System.out.println();
			System.out.println("Spreadsheet #"+(++cs));
			for ( int qr = scan.nextInt(); qr-->0; ) {
				i = scan.nextInt()-1;
				j = scan.nextInt()-1;
				k = i|(j<<10);
				System.out.format("Cell data in (%d,%d) ",i+1,j+1);
				if ( (t = find(k)) == null )
					System.out.println("GONE");
				else System.out.format("moved to %s\n",t);
			}
		}
	}
}

