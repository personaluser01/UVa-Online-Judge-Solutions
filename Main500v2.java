/*
 * 500. Table
 * TOPIC: ad hoc, formatting
 * status: Accepted
 */
import java.util.*;
import java.util.regex.*;
import java.io.*;

class Main {
	final static int N = 0x800;
	Pattern rawElem = Pattern.compile("\\u2502[^\\u2502]*",Pattern.UNICODE_CHARACTER_CLASS);
	Pattern elem = Pattern.compile("[^\\u2502\\s].*\\S",Pattern.UNICODE_CHARACTER_CLASS);
	Pattern e = Pattern.compile("[^\\u2502\\s]",Pattern.UNICODE_CHARACTER_CLASS);
	int m,n;
	int []columnWidth;
	Map<Integer,List<String>> q;
	Map<Integer,Type> type;

	static int []cp = {0x2502,0x2524,0x2510,0x2514,0x2534,0x252C,0x251C,0x2500,0x253C,0x2518,0x250C};

	enum Specials {
		S179(cp[0]),S180(cp[1]),S191(cp[2]),S192(cp[3]),S193(cp[4]),S194(cp[5]),S195(cp[6]),S196(cp[7]),S197(cp[8]),S217(cp[9]),S218(cp[10]);
		char ch;
		String name;
		Specials( int x ) {
			name = (ch = (char)x)+"";
		}
		public String toString() {
			return name;
		}
	}
	enum Type {
		REGULAR, RULE;
	}

	static Set<Character> specials;

	static {
		specials = new HashSet<>();
		for ( int x: cp )
			specials.add((char)x);
	}

	public static void main( String ... args ) throws Exception {
		new Main().go();
	}

	boolean isEmptyString( String s ) {
		for ( int i = 0; i < s.length(); ++i )
			if ( !Character.isWhitespace(s.charAt(i)) )
				return false ;
		return true ;
	}

	boolean isRule( String s ) {
		Set<Character> q = new HashSet<Character>();
		for ( int i = 0; i < s.length(); ++i )
			if ( Character.isWhitespace(s.charAt(i)) || !specials.contains(s.charAt(i)) )
				return false ;
		for ( int i = 0; i < s.length(); ++i )
			if ( specials.contains(s.charAt(i)) )
				q.add(s.charAt(i));
		return q.size() >= 2;
	}

	List<String> getProfile( String s ) {
		List<String> res = new ArrayList<>();
		for ( int i = 0; i < s.length(); ++i )
			if ( specials.contains(s.charAt(i)) && s.charAt(i) != Specials.S196.ch )
				res.add(""+s.charAt(i));
		return res ;
	}

	void Assert( boolean x ) {
		if ( !x ) { int trap = 1/0; }
	}

	void printRule( List<String> lst, BufferedWriter bw ) throws Exception {
		for ( int i = 0; i <= lst.size()-2; ++i ) {
			bw.write(lst.get(i));
			for ( int k = 0; k < columnWidth[i]; ++k )
				bw.write(Specials.S196.toString());
		}
		bw.write(lst.get(lst.size()-1));
		bw.write('\n');
		if ( lst.size() != n+1 )
			Assert(false);
	}

	boolean isEmptyRow( List<String> lst ) {
		for ( String t: lst )
			if ( !t.equals("") )
				return false ;
		return true ;
	}

	void go() throws Exception {
		int i,j,k,ts,total;
		String s;
		Set<Integer> colSizes;
		char ch;

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in,"IBM850"));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out,"IBM850"));

		for ( ts = Integer.parseInt(br.readLine()), br.readLine(); ts-->0; ) {
			columnWidth = new int[N];
			type = new HashMap<>();
			q = new HashMap<>();
			colSizes = new HashSet<>();

			for ( n = -1, m = 0; (s=br.readLine()) != null && !isEmptyString(s=s.trim()); ++m ) {
				Assert( s.indexOf("\r") == -1 );
				if ( isRule(s) ) {
					type.put(m,Type.RULE);
					q.put(m,getProfile(s));
					if ( n == -1 )
						n = q.get(m).size()-1;
					else {
						Assert( n == q.get(m).size()-1 );
					}
					continue ;
				}
				for ( Iterator<Character> it = specials.iterator(); it.hasNext(); )
					if ( (ch = it.next()) != Specials.S179.ch && s.indexOf(ch) != -1 ) {
						System.out.println("This "+ch);
						Assert(false);
					}
				type.put(m,Type.REGULAR);
				q.put(m,new ArrayList<String>());
				for ( Matcher rm = rawElem.matcher(s); rm.find(); ) {
					Matcher mt = elem.matcher(rm.group()); 
					if ( mt.find() ) {
						q.get(m).add(" "+mt.group()+" ");
					}
					else {
						Matcher mm = e.matcher(rm.group());
						if ( mm.find() ) {
							q.get(m).add(" "+mm.group()+" ");
						}
						else q.get(m).add("");
					}
				}
				if ( n == -1 )
					n = q.get(m).size()-1;
				else {
					Assert( n == q.get(m).size()-1 );
				}
				// colSizes.add(n = q.get(m).size()-1);
				n = Math.max(n,q.get(m).size()-1);
				// if ( isEmptyRow(q.get(m)) ) --m;
			}
			// Assert(colSizes.size() == 1);
			for ( total = 0, j = 0; j < n; total += columnWidth[j++]  ) 
				for ( i = 0; i < m; ++i ) 
					//if ( type.get(i) == Type.REGULAR )
						if ( j+1 <= q.get(i).size() )
							columnWidth[j] = Math.max(columnWidth[j],q.get(i).get(j).length());
			Assert(total <= 255);
			for ( i = 0; i < m; ++i ) {
				if ( type.get(i) == Type.RULE ) {
					printRule(q.get(i),bw);
					continue ;
				}
				// if ( isEmptyRow(q.get(i)) ) continue ;
				for ( j = 0; j < n; ++j ) {
					bw.write(Specials.S179.toString());
					bw.write(q.get(i).get(j));
					for ( k = 1+q.get(i).get(j).length(); k <= columnWidth[j]; ++k )
						bw.write(' ');
				}
				bw.write(Specials.S179.toString());
				bw.write('\n');
			}
			if ( m == 0 ) {
				bw.write("");
			}
			for ( i = 1; i < m; ++i )
				if ( type.get(i) == Type.RULE && type.get(i-1) == Type.RULE )
					Assert( false );
			if ( ts > 0 ) bw.write("\n");
			Assert( type.get(0) == Type.RULE ); //uncommenting either of these gives RTE
			Assert( type.get(m-1) == Type.RULE );
			// if ( ts > 0 ) System.out.println();
		}
		bw.flush();
	}
}

