/*
 * 10686. SQF Problems
 * TOPIC: parsing, sets, ad hoc
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	StringTokenizer st;
	Pattern pat = Pattern.compile("([a-z,A-Z]+)");
	int n;
	public static void main( String [] args ) throws Exception { new Main().go(); }
	class Foo {
		String nm;
		int w,p;
		Set<String> a;
		Foo( String nm, int w, int p ) {
			this.nm = nm; this.p = p; this.w = w;
			this.a = new TreeSet<String>();
		}
		void addWord( String h ) { this.a.add(h); }
	}
	Foo []c;
	List<String> e;
	boolean readDesc() throws Exception {
		e = new LinkedList<String>();
		for ( String s; (s = br.readLine()) != null && !s.equals(""); ) 
			for ( Matcher m = pat.matcher(s); m.find(); e.add(m.group(1)) );
		return e.size() > 0;
	}
	String classify() {
		int []cnt = new int[n];
		int i,j,k;
		StringBuilder sb = new StringBuilder();
		for ( Iterator<String> it = e.iterator(); it.hasNext(); ) {
			String s = it.next();
			for ( i = 0; i < n; ++i )
				if ( c[i].a.contains(s) ) {
					++cnt[i];
					c[i].a.remove(s);
				}
		}
		for ( j = 0, i = 0; i < n; ++i ) 
			if ( cnt[i] >= c[i].p ) {
				if ( ++j > 1 ) sb.append(",");
				sb.append(c[i].nm);
			}
		if ( j == 0 ) sb.append("SQF Problem.");
		return sb.toString();
	}
	void go() throws Exception {
		int i,j,k,ts = Integer.parseInt(br.readLine());
		for (;ts-->0;) {
			String t = br.readLine();
			n=Integer.parseInt(t);
			if ( n > 0 ) c = new Foo[n];
			for ( i = 0; i < n; ++i ) {
				st = new StringTokenizer(br.readLine());
				String tmp = st.nextToken();
				j = Integer.parseInt(st.nextToken());
				k = Integer.parseInt(st.nextToken());
				c[i] = new Foo(tmp,j,k);
				for ( int l = 0; l < j; ++l )
					c[i].addWord(new StringTokenizer(br.readLine()).nextToken());
			}
			readDesc(); System.out.println(classify());
		}
	}
};

