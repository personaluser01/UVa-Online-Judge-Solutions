/*
 * 10371. Time Zones
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;


class Main {
    public static void main( String [] args ) throws Exception { new Main().go(); }
    void go() throws Exception {
        Map<String,Double> m = new HashMap<String,Double>();
        m.put("UTC",+0.0); m.put("GMT",+0.0);
        m.put("BST",+1.0); m.put("IST",+1.0);
        m.put("WET",+0.0); m.put("WEST",+1.0);
        m.put("CET",+1.0); m.put("CEST",+2.0);
        m.put("EET",+2.0); m.put("EEST",+3.0);
        m.put("MSK",+3.0); m.put("MSD",+4.0);
        m.put("AST",-4.0); m.put("ADT",-3.0);
        m.put("NST",-3.5); m.put("NDT",-2.5);
        m.put("EST",-5.0); m.put("EDT",-4.0);
        m.put("CST",-6.0); m.put("CDT",-5.0);
        m.put("MST",-7.0); m.put("MDT",-6.0);
        m.put("PST",-8.0); m.put("PDT",-7.0);
        m.put("HST",-10.0);m.put("AKST",-9.0);
        m.put("AKDT",-8.0);m.put("AEST",+10.0);
        m.put("AEDT",+11.0);m.put("ACST",+9.5);
        m.put("ACDT",+10.5); m.put("AWST",+8.0);
        StringTokenizer st;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int i,j,k,ts,t,h,minutes;
		double dt;
        ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
		String s,am,from,to;
		Pattern p = Pattern.compile("(\\d+):(\\d+)");
		Matcher M;

        while ( ts-- > 0.0 ) {
            st = new StringTokenizer(br.readLine());
			s = st.nextToken();
			if ( s.equals("noon") )
				t = 12*60;
			else if ( s.equals("midnight") )
				t = 0;
			else {
				M = p.matcher(s);
				M.find();
				h = Integer.parseInt(M.group(1));
				minutes = Integer.parseInt(M.group(2));
				t = 60*h+minutes;
				am = st.nextToken();
				t %= (12*60);
				if ( am.equals("p.m.") ) 
					t += (12*60);
			}
			from = st.nextToken();
			to = st.nextToken();
			dt = (-m.get(from)+m.get(to))*60 + 48*60;
			t += (int)(dt);
			t %= (24*60);
			if ( 0 == t )
				System.out.println("midnight");
			else if ( t == 12*60 )
				System.out.println("noon");
			else {
				if ( t > 12*60 )
					am = new String("p.m.");
				else am = new String("a.m.");
				t %= (12*60);
				h = t/60; minutes = t%60;
				if ( am.equals("a.m.") && h == 0 )
					h = 12;
				if ( am.equals("p.m.") && h == 0 )
					h = 12;
				System.out.printf("%d:%02d ",h,minutes);
				System.out.println(am);
			}
        }
    }
};

