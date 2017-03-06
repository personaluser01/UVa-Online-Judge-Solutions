/*
 * 10352. Count the e-Words
 * TOPIC: override
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	Scanner scan = new Scanner(System.in);
	Pattern p = Pattern.compile("(#|[^\\s#]+)");
	Matcher m;
	public static void main( String [] args ) throws Exception { new Main().go(); }
	List<String> w;
	Map<myString,Integer> e;
	class myString implements Comparable<myString> {
		String s;
		String frst;
		Set<String> q;
		myString( String s ) { this.s = s; this.frst = s; this.q = new TreeSet<String>(); this.q.add(this.s); }
		public int compareTo( myString other ) {
			for ( int i = 0; i < 5 && i < this.s.length() && i < other.s.length(); ++i ) {
				if ( i == 2 || this.s.charAt(i) == other.s.charAt(i) ) continue ;
				return this.s.charAt(i)<other.s.charAt(i)?-1:1;
			}
			if ( this.s.length() == other.s.length() || this.s.length() >= 5 && other.s.length() >= 5 ) 
				return 0;
			return this.s.length()<other.s.length()?-1:1;
		}
	}
	/*
	class cmp01 implements Comparator<Map.Entry<myString,Integer>> {
		public int compareTo( Map.Entry<myString,Integer> one, Map.Entry<myString,Integer> other ) {
			return one.getKey().frst.compareTo(other.getKey().frst);
		}
	}
	*/
	class cmp01 implements Comparator<myString> {
		@Override
		public int compare( myString one, myString other ) {
			char []a = one.frst.toCharArray();
			char []b = other.frst.toCharArray();
			if ( one.frst.length() >= 3 )
				a[2] = ' ';
			if ( other.frst.length() >= 3 )
				b[2] = ' ';
			for ( int i = 0; i < a.length&& i < b.length; ++i ) {
				if ( a[i] == b[i] ) continue ;
				return a[i]<b[i]?-1:1;
			}
			if ( a.length == b.length )
				return 0;
			return a.length < b.length ?-1:1;
		}
	}

	boolean isEnd = false ;
	String g() throws Exception {
		String t;
		if ( isEnd ) return null;
		if ( m == null || !m.find() ) {
			if ( scan.hasNext() ) {
				m = p.matcher(scan.next());
				return g();
			}
			else { isEnd = true; return null; }
		}
		t = m.group(1);
		if ( t.equals("#") ) {
			if ( scan.hasNext() ) 
				m = p.matcher(scan.next());
			else m = null;
		}
		return t;
	}
	boolean readInput() throws Exception {
		String s,t = new String();
		for ( w = new LinkedList<String>(); (s=g()) != null && !s.equals("#"); w.add(s) );
		return !isEnd;
	}
	String f( myString s ) {
		StringBuilder sb = new StringBuilder();
		for ( int i = 0; i < 5 && i < s.s.length(); ++i )
			sb.append(s.s.charAt(i));
		return sb.toString();
	}
	void go() throws Exception {
		int i,j,k,cs = 0;
		for ( m = p.matcher(scan.next()); readInput();System.out.println("")) {
			System.out.println("Set #"+(++cs)+":");
			Set<myString> q = new TreeSet<myString>();
			e = new TreeMap<myString,Integer>();
			for ( Iterator<String> it = w.iterator(); it.hasNext(); ) {
				String t = it.next();
				myString tt = new myString(t);
				if ( q.contains(tt) ) {
					int kk = e.get(tt);
					q.remove(tt); q.add(tt);
					e.remove(tt); e.put(tt,kk+1);
				}
				else { q.add(tt); e.put(tt,1); }
			}
			// Map<myString,Integer> E = new TreeMap<myString,Integer>(new cmp01());
			Map<myString,Integer> E = new TreeMap<myString,Integer>(new cmp01());
			for ( Map.Entry<myString,Integer> entry: e.entrySet() ) 
				E.put(entry.getKey(),entry.getValue());
			for ( Map.Entry<myString,Integer> entry: E.entrySet() ) 
				System.out.println(f(entry.getKey())+" "+entry.getValue());
		}
	}
};

