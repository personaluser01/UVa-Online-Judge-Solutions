/*
 * 860. Entropy Text Analyzer
 * TOPIC: regex
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	BufferedReader br;
	Pattern p = Pattern.compile("([^,\\.::!?\"\\(\\)\n\\s]+)");
	Matcher m;
	Map<String,Integer> q;
	int n;
	final double e = Math.log(10.00), tol = 1e-9;
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	class cmp01 implements Comparator<String> {
		public int compare( String a, String b  ) {
			return a.compareToIgnoreCase(b);
		}
	}
	boolean readInput() throws Exception {
		String s,t;
		q = new TreeMap<String,Integer>(new cmp01());
		for ( n = 0; (t=br.readLine())!=null && !t.equals("****END_OF_INPUT****") && !t.equals("****END_OF_TEXT****"); ) 
			for ( m = p.matcher(t); m.find(); ++n ) 
				if ( q.containsKey(s=m.group(1)) ) {
					int k = q.get(s);
					q.put(s,k+1);
				}
				else q.put(s,1);
		return !t.equals("****END_OF_INPUT****");
	}
	void go() throws Exception {
		double s,w;
		if ( br == null )
			br = new BufferedReader(new InputStreamReader(System.in,"ISO-8859-1"));
		while ( readInput() ) {
			s = 0;
			for ( Map.Entry<String,Integer> entry: q.entrySet() ) 
				s += entry.getValue()*Math.log10(entry.getValue());
			w = Math.log10(n)-s/n;
			System.out.printf("%d %.1f %.0f\n",n,w,((1-s/n/Math.log10(n))*100+tol));
		}
	}
};

