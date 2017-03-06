/*
 * 500. Table
 * TOPIC: ad hoc, formatting
 * status: in progress
 */
import java.util.*;
import java.util.regex.*;
import java.io.*;

class Main {
	final static int N = 0x800;
	Pattern rawElem = Pattern.compile("\\u2502[^\\u2502]*",Pattern.UNICODE_CHARACTER_CLASS);
	Pattern elem = Pattern.compile("[^\\u2502\\s].*\\S",Pattern.UNICODE_CHARACTER_CLASS);
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	int m,n,curMark;
	int []rowLabel,columnWidth;
	List<String> rows;
	Map<Integer,List<String>> q;

	static int []cp = {0x2502,0x2524,0x2510,0x2514,0x2534,0x252C,0x251C,0x2500,0x253C,0x2518,0x250C};
	static Set<Character> specials;
	static {
		specials = new HashSet<>();
		for ( int x: cp )
			specials.add((char)x);
	}

	public static void main( String ... args ) throws Exception {
		new Main().go();
	}

	boolean isEmpty( String s ) {
		for ( char c: s.toCharArray() )
			if ( c != ' ' && c != '\t' && c != '\n' && c != '\r' )
				return false ;
		return true ;
	}

	boolean isHRule( String s ) {
		for ( char c: s.toCharArray() )
			if ( specials.contains(c) && c != (char)cp[0] )
				return true ;
		return false ;
	}

	String createUpper() {
		StringBuilder sb = new StringBuilder();
		sb.append((char)cp[10]);
		for ( int j = 0; j < n; ++j ) {
			for ( int k = 0; k < columnWidth[j]; ++k )
				sb.append((char)cp[7]);
			sb.append(j==n-1?(char)cp[2]:(char)cp[5]);
		}
		return sb.toString();
	}
	String createLower() {
		StringBuilder sb = new StringBuilder();
		sb.append((char)cp[3]);
		for ( int j = 0; j < n; ++j ) {
			for ( int k = 0; k < columnWidth[j]; ++k )
				sb.append((char)cp[7]);
			sb.append(j==n-1?(char)cp[9]:(char)cp[4]);
		}
		return sb.toString();
	}
	String createMid() {
		StringBuilder sb = new StringBuilder();
		sb.append((char)cp[6]);
		for ( int j = 0; j < n; ++j ) {
			for ( int k = 0; k < columnWidth[j]; ++k )
				sb.append((char)cp[7]);
			sb.append(j==n-1?(char)cp[1]:(char)cp[8]);
		}
		return sb.toString();
	}

	boolean emptyRow( int i ) {
		for ( String t : q.get(i) )
			if ( !t.equals(" ") )
				return false ;
		return true ;
	}

	void go() throws Exception {
		int i,j,k,ts,total,prevGroup;
		String s;
		boolean []isEmptyGroup;

		for ( ts = Integer.parseInt(br.readLine()), br.readLine(); ts-->0; ) {
			rowLabel = new int[N];
			columnWidth = new int[N];
			for ( m = 0, curMark = 0, rows = new ArrayList<>(); (s = br.readLine()) != null && !isEmpty(s); ) {
				if ( isHRule(s) ) {
					++curMark;
					continue ;
				}
				rowLabel[m++] = curMark;
				rows.add(s);
			}
			q = new TreeMap<>();
			for ( i = 0; i < m; ++i ) {
				q.put(i,new ArrayList<String>());
				for ( Matcher rm = rawElem.matcher(rows.get(i)); rm.find(); ) {
					Matcher mt = elem.matcher(rm.group(0)); 
					if ( mt.find() ) 
						q.get(i).add(" "+mt.group(0)+" ");
					else q.get(i).add(" ");
				}
			}
			for ( total = 0, n = q.get(m-1).size()-1, j = 0; j < n; total += columnWidth[j++] ) 
				for ( i = 0; i < m; ++i ) 
					columnWidth[j] = Math.max(q.get(i).get(j).length(),columnWidth[j]);

			isEmptyGroup = new boolean[curMark];
			for ( i = 0; i < curMark; isEmptyGroup[i++] = true );
			for ( i = 0; i < m; ++i ) 
				if ( !emptyRow(i) )
					isEmptyGroup[rowLabel[i]] = false ;

			String up = createUpper(), down = createLower(), mid = createMid();

			System.out.println(up); prevGroup = -1;
			for ( i = 0; i < m; ++i ) {
				if ( emptyRow(i) ) continue ;
				if ( prevGroup != -1 && prevGroup != rowLabel[i] )
					System.out.println(mid);
				for ( j = 0; j < n; ++j ) {
					System.out.print((char)cp[0]);
					System.out.print(q.get(i).get(j));
					for ( k = q.get(i).get(j).length()+1; k <= columnWidth[j]; ++k )
						System.out.print(' ');
					prevGroup = rowLabel[i];
				}
				System.out.println((char)cp[0]);
			}
			System.out.println(down);
			if ( ts > 0 ) System.out.println();
		}
	}
}

