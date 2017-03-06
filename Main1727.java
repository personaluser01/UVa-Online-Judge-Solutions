/*
 * 1727. Counting Weekend Days
 * TOPIC: java date, java calendar, built-in functions
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.Calendar.*;
import java.util.Date.*;

class Main {
	Scanner scan = new Scanner(System.in);
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	public static void main( String ... args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		int i,j,k,month = 0, Day = 0;
		for ( int ts = scan.nextInt(); ts-->0; ) {
			String mo = scan.next().toLowerCase(), day = scan.next().toLowerCase();
			Calendar c = Calendar.getInstance();
			for ( Map.Entry<String,Integer> entry: c.getDisplayNames(Calendar.MONTH,Calendar.SHORT,Locale.US).entrySet() ) 
				if ( entry.getKey().toLowerCase().equals(mo) ) {
					month = entry.getValue();
					break ;
				}
			for ( Map.Entry<String,Integer> entry: c.getDisplayNames(Calendar.DAY_OF_WEEK,Calendar.SHORT,Locale.US).entrySet() )
				if ( entry.getKey().toLowerCase().equals(day) ) {
					Day = entry.getValue();
					break ;
				}
			c.set(Calendar.MONTH,month);
			c.set(Calendar.DAY_OF_MONTH,1);
			k = c.getActualMaximum(Calendar.DAY_OF_MONTH);
			if ( month == 1 && k == 29 ) k = 28;
			int []d = new int[k+1];
			for ( i = 1; i <= k; ++i ) {
				d[i] = Day++;
				if ( Day == 8 ) Day = 1;
			}
			for ( j = 0, i = 1; i <= k; ++i )
				if ( d[i] == 6 || d[i] == 7 ) ++j;
			bw.write(j+"\n");
		}
		bw.flush();
	}
}

