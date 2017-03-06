/*
 * 12504. Updating a Dictionary
 * TOPIC: regex, sets, maps, java collections
 * status: in progress
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	Pattern p = Pattern.compile("([a-z]+):([0-9]+)");
	Matcher m;
	String []a = {"+","-","*"};
	boolean flag,ok;
	public static void main( String [] args ) throws Exception { new Main().go(); };
	void go() throws Exception {
		String s,t;
		int ts = Integer.parseInt(br.readLine()),i;
		for (;ts-->0;) {
			s = br.readLine();
			Map<String,String> S = new TreeMap<String,String>();
			for ( m = p.matcher(s); m.find(); S.put(m.group(1),m.group(2)) );
			t = br.readLine();
			Map<String,String> T = new TreeMap<String,String>(), R = new TreeMap<String,String>();
			for ( m = p.matcher(t); m.find(); R.put(m.group(1),m.group(2)) ) 
				if ( S.containsKey(m.group(1)) ) {
					if ( !S.get(m.group(1)).equals(m.group(2)) )
						T.put(m.group(1),"*");
				}
				else T.put(m.group(1),"+");
			for ( String e: S.keySet() )
				if ( !R.containsKey(e) ) 
					T.put(e,"-");
			StringBuilder sb = new StringBuilder();
			for ( ok = false, i = 0; i < 3; ++i, ok |= flag ) {
				flag = false;
				for ( Map.Entry<String,String> e: T.entrySet() ) 
					if ( e.getValue().equals(a[i]) ) {
						if ( !flag ) sb.append(a[i]);
						else sb.append(",");
						sb.append(e.getKey());
						flag = true ;
					}
				if ( flag ) sb.append("\n");
			}
			if ( !ok ) System.out.println("No changes\n");
			else System.out.println(sb.toString());
		};
	};
};

