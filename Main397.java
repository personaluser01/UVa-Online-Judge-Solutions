/*
 * 397 Equation Elation
 * TOPIC: regex
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	Pattern mult = Pattern.compile("([+-]?\\d+)\\s*\\*\\s*([+-]?\\d+)");
	Pattern divi = Pattern.compile("([+-]?\\d+)\\s*\\/\\s*([+-]?\\d+)");
	Pattern add = Pattern.compile("([+-]?\\d+)\\s*\\+\\s*([+-]?\\d+)");
	Pattern sub = Pattern.compile("([+-]?\\d+)\\s*\\-\\s*([+-]?\\d+)");
	Pattern e = Pattern.compile("(([\\+\\-\\*\\/]\\s*)\\+\\s*(\\d+))");
	public static void main( String [] args ) throws Exception { new Main().go(); }
	long f( String a, String b, String c ) {
		long x = Long.parseLong(a), y = Long.parseLong(b);
		if ( c.equals("+") )
			return x+y;
		if ( c.equals("/") )
			return x/y;
		if ( c.equals("*") )
			return x*y;
		if ( c.equals("-") )
			return x-y;
		return 0L;
	}
	String cleanUp( String s ) {
		while ( s.charAt(0) == '+' )
			s = s.substring(1);
		Matcher m = e.matcher(s);
		while ( m.find() && m.groupCount() >= 3) {
			s = s.substring(0,m.end(2))+s.substring(m.start(3));
			m = e.matcher(s);
		}
		return s;
	}
	void go() throws Exception {
		String s;
		int cs = 0;
		boolean flag;
		for ( ;(s=br.readLine()) != null; ) {
			if ( ++cs > 1 ) System.out.println("");
			s = cleanUp(s);
			for ( System.out.println(s), flag = false; !flag;) {
				Matcher m = mult.matcher(s);
				Matcher d = divi.matcher(s);
				boolean bm = m.find(), bd = d.find();
				if ( !bm && !bd ) {
					Matcher a = add.matcher(s);
					Matcher u = sub.matcher(s);
					boolean ba = a.find(), bs = u.find();
					if ( !ba && !bs ) 
						flag = true;
					else if ( !ba && bs ) {
						s = s.substring(0,u.start())+f(u.group(1),u.group(2),"-")+s.substring(u.end(),s.length());
					}
					else if ( ba && !bs ) {
						s = s.substring(0,a.start())+f(a.group(1),a.group(2),"+")+s.substring(a.end(),s.length());
					}
					else {
						if ( a.start() < u.start() ) {
							s = s.substring(0,a.start())+f(a.group(1),a.group(2),"+")+s.substring(a.end(),s.length());
						}
						else {
							s = s.substring(0,u.start())+f(u.group(1),u.group(2),"-")+s.substring(u.end(),s.length());
						}
					}
				}
				else if ( !bm && bd ) {
					s = s.substring(0,d.start())+f(d.group(1),d.group(2),"/")+s.substring(d.end(),s.length());
				}
				else if ( bm && !bd ) {
					s = s.substring(0,m.start())+f(m.group(1),m.group(2),"*")+s.substring(m.end(),s.length());
				}
				else {
					if ( m.start() < d.start() ) {
						s = s.substring(0,m.start())+f(m.group(1),m.group(2),"*")+s.substring(m.end(),s.length());
					}
					else {
						s = s.substring(0,d.start())+f(d.group(1),d.group(2),"/")+s.substring(d.end(),s.length());
					}	
				}
				if ( !flag ) System.out.println(s);
			}
		}
	}
};

