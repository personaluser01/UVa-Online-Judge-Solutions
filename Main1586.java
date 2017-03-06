/*
 * 1586. Molar Mass
 * status: Acceptedn
 * TOPIC: regular expresions, regex
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		int i,j,k,l,t,ts,n;
		double w;
		String s;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
		HashMap<String,Double> m = new HashMap<String,Double>();
		m.put("C",12.01); m.put("H",1.008); m.put("O",16.00); m.put("N",14.01);
		Pattern p = Pattern.compile("(\\w\\d*)");
		Matcher M;
		while ( ts-- > 0 ) {
			s = new StringTokenizer(br.readLine()).nextToken();
			w = 0; M = p.matcher(s);
			while ( M.find() ) {
				if ( M.group().length() >= 2 ) 
					w += Integer.parseInt(M.group(1).substring(1))*m.get(M.group(1).substring(0,1));
				else
					w += m.get(M.group(1));
			}
			System.out.printf("%.3f\n",w);
		}
	}
};

