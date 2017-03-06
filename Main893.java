/*
 * status: Accepted
 * TOPIC: Gregorian calendar
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	public static void main( String [] args ) {
		Main m = new Main();
		m.doIt();
	}
	void doIt() {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String s;
		StringTokenizer st;
		GregorianCalendar g;
		long i,j,k;
		int dd,mm,yy;
		try {
			while ( (s=br.readLine()) != null ) {
				st = new StringTokenizer(s);
				assert( st.hasMoreTokens() );
				k = Integer.parseInt(st.nextToken());
				assert( st.hasMoreTokens() );
				dd = Integer.parseInt(st.nextToken());
				assert( st.hasMoreTokens() );
				mm = Integer.parseInt(st.nextToken());
				assert( st.hasMoreTokens() );
				yy = Integer.parseInt(st.nextToken());
				if ( dd == 0 && mm == 0 && yy == 0 ) break ;
				g = new GregorianCalendar();
				g.set(Calendar.DAY_OF_MONTH,dd);
				g.set(Calendar.MONTH,mm-1);
				g.set(Calendar.YEAR,yy);
				g.add(Calendar.DAY_OF_MONTH,(int)k);
				System.out.println(g.get(Calendar.DAY_OF_MONTH)+" "+(g.get(Calendar.MONTH)+1)+" "+g.get(Calendar.YEAR));
			}
		}
		catch ( IOException e ) {
			System.out.println(e.toString());
		}
	}
};

