/*
 * 230. Borrowers
 * TOPIC: map, manipulations, ad hoc, easy
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	Pattern bookItem = Pattern.compile("(\".*\")\\s+by\\s+(.*)");
	Pattern item = Pattern.compile("(BORROW|RETURN)\\s+(\".*\")");
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	boolean []inStock = new boolean[1 << 15];
	int n;
	public static void main ( String [] args ) throws Exception { new Main().go(); }
	class Book implements Comparable<Book> {
		String title,author;
		Book( String t, String a ) {
			this.title = t;
			this.author = a;
		}
		public int compareTo( Book other ) {
			if ( this.author.compareTo(other.author) == 0 ) {
				if ( this.title.compareTo(other.title) == 0 )
					return 0;
				if ( this.title.compareTo(other.title) < 0 )
					return -1;
				return 1;
			}
			if ( this.author.compareTo(other.author) < 0 )
				return -1;
			return 1;
		}
	}

	Book []B = new Book[1 << 15];
	List<Book> b = new ArrayList<Book>();
	List<Book> e = new ArrayList<Book>();
	List<Book> t = new ArrayList<Book>();
	Map<String,Book> w = new HashMap<String,Book>();
	Map<Book,Integer> id = new HashMap<Book,Integer>();
	Set<Book> h = new TreeSet<Book>();

	void readLibrary() throws Exception {
		String s;
		for ( n = 0; !(s=br.readLine()).equals("END"); ) {
			Matcher m=bookItem.matcher(s);
			if ( m.find() ) {
				B[n++] = new Book(m.group(1),m.group(2));
				inStock[n-1] = true;
			}
		}
		for ( int i = 0; i < n; b.add(B[i++]) );
		Collections.sort(b);
		for ( int i = 0; i < n; ++i ) {
			w.put(b.get(i).title,b.get(i));
			// System.out.println(b.get(i).title+" by "+b.get(i).author);
			id.put(b.get(i),i);
		}
	}

	void Borrow( String s ) {
		e.add(w.get(s));
		t.remove(w.get(s));
		h.add(w.get(s));
	}

	void Return( String s ) {
		e.remove(w.get(s));
		t.add(w.get(s));
		h.remove(w.get(s));
	}

	void go() throws Exception {
		String s;
		readLibrary();
		int i,j,k;

		while ( !(s=br.readLine()).equals("END") ) {
			Matcher m = item.matcher(s);
			if ( m.find() ) {
				if ( m.group(1).equals("BORROW") ) 
					Borrow(m.group(2));
				else 
					Return(m.group(2));
			}
			else {
				if ( s.equals("SHELVE") ) {
					Collections.sort(t);
					for ( Book r: t ) {
						if ( (i = id.get(r)) == 0 ) {
							System.out.println("Put "+r.title+" first");
							continue ;
						}
						while ( --i >= 0 && h.contains((Object)b.get(i)) );
						if ( i == -1 ) {
							System.out.println("Put "+r.title+" first");
							continue ;
						}
						System.out.println("Put "+r.title+" after "+b.get(i).title);
					}
					t.clear();
					System.out.println("END");
				}
			}
		}
	}
};

