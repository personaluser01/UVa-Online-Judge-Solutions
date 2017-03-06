/*
 * 427. FlatLand Piano Movers
 * TOPIC: trigonometry
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	Pattern p = Pattern.compile("(\\d+)\\s*,\\s*(\\d+)");
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String s,t;
	Matcher m;
	int w,h,a,b;
	public static void main( String [] args ) throws Exception { new Main().go(); }
	String f( int x, int y ) {
		if ( w > x ) return "N";
		double ang = (w+.00), tau = 0.001;
		for ( double phi = 0; phi <= Math.PI/2; phi += tau )
			if ( Math.abs(x*Math.sin(phi)+y*Math.cos(phi)-h*Math.cos(phi)*Math.sin(phi))<ang )
				return "N";
		return "Y";
	}
	void go() throws Exception {
		for(;(s=br.readLine())!=null&&!s.equals("");System.out.println(t)) 
			for(m=p.matcher(s),m.find(),t=new String(""),a=Integer.parseInt(m.group(1)),b=Integer.parseInt(m.group(2)),w=Math.min(a,b),h=Math.max(a,b);m.find();)
				t+=f(Integer.parseInt(m.group(2)),Integer.parseInt(m.group(1)));
	}
};

