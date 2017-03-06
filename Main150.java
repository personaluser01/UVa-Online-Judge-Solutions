/*
 * 150. Double Time
 * TOPIC: DateTime, Java built-in libraries
 * status: Accepted
 */
import java.util.regex.*;
import java.util.*;
import java.io.*;
import java.text.*;
import java.time.*;

class Main {
	static boolean isLeapYear( int year ) {
		return year%4 == 0 && year%100 != 0 || year%400 == 0;
	}

	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

	static Map<String,Integer> whichMonth = new TreeMap<String,Integer>();
	static Map<Integer,String> int2DayOfWeek = new TreeMap<Integer,String>();
	static Map<String,Integer> dayOfWeek2Int = new TreeMap<String,Integer>();
	static GregorianCalendar base;
	static int[]days = {31,28,31,30,31,30,31,31,30,31,30,31};
	static String []M = {"January","February","March","April","May","June","July","August","September","October","November","December"};
	static String []D = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
	static MyDate B;
	static int []pref = new int[3030];
	static int howManyLeapYears( int x, int y ) {
		if ( x > y ) return 0;
		return pref[y]-pref[x-1];
	}

	static {
		for ( int i = 0; i < M.length; ++i )
			whichMonth.put(M[i],i);
		for ( int i = 0; i < D.length; ++i ) {
			dayOfWeek2Int.put(D[i],i+1); 
			int2DayOfWeek.put(i+1,D[i]);
		}
		base = new GregorianCalendar(1582,9,15);
		B = new MyDate(5,9,1582,6);
		for ( int i = 1583; i < 3030; ++i )
			pref[i] = isLeapYear(i)?1:0;
		for ( int i = 1583; i < 3030; ++i )
			pref[i] += pref[i-1];
	}

	public static void main( String ... args ) throws Exception {
		new Main().go();
	}

	static class MyDate {
		int day,month,year,dwk;
		MyDate() {}
		MyDate( int day, int month, int year, int dwk ) {
			this.day = day;
			this.month = month;
			this.year = year;
			this.dwk = dwk;
		}
		void inc() {
			if ( ++dwk == 8 ) dwk = 1;
			if ( ++day == days[month]+1 ) {
				if ( isLeapYear(year) && month == 1 ) return ;
				if ( ++month == 12 ) {
					month = 0;
					++year;
				}
				day = 1;
			}
			else if ( day > days[month]+1 ) {
				assert month == 1 && isLeapYear(year);
				++month;
				day = 1;
			}
		}
		void dec() {
			if ( --dwk == 0 ) dwk = 7;
			if ( --day == 0 ) {
				if ( --month == -1 ) {
					month = 11;
					--year;
				}
				if ( isLeapYear(year) && month == 1 )
					day = 29;
				else day = days[month];
			}
		}
	}

	static int next( int d ) {
		switch ( d ) {
			case 1: return 2;
			case 2: return 3;
			case 3: return 4;
			case 4: return 5;
			case 6: return 7;
			case 7: return 1;
		}
		return 0;
	}

	void go() throws Exception {

		String s;
		StringTokenizer st;
		MyDate md = new MyDate();

		for ( ;(s = br.readLine()) != null && !s.equals("#"); ) {
			boolean flag = false;
			st = new StringTokenizer(s);
			String dayOfWeek = st.nextToken(), day = st.nextToken(), month = st.nextToken(), year = st.nextToken();
			GregorianCalendar gc = new GregorianCalendar(md.year = Integer.parseInt(year),md.month = whichMonth.get(month),md.day = Integer.parseInt(day));
			if ( gc.get(Calendar.DAY_OF_WEEK) == (md.dwk = dayOfWeek2Int.get(dayOfWeek)) ) {
				flag = true;
				gc.setGregorianChange(new Date(Long.MAX_VALUE));
				System.out.println(int2DayOfWeek.get(gc.get(Calendar.DAY_OF_WEEK))+" "+gc.get(Calendar.DAY_OF_MONTH)+(flag?"*":"")+" "+M[gc.get(Calendar.MONTH)]+" "+gc.get(Calendar.YEAR));
			}
			else {
				int old_dwk = md.dwk, ds = 0;
				if ( md.year >= 1900 ) {
					if ( md.month > 1 || md.month == 1 && md.day >= 17 )
						ds = 13;
					else ds = 12;
				}
				else if ( md.year >= 1800 ) {
					if ( md.month > 1 || md.month == 1 && md.day >= 18 )
						ds = 12;
					else ds = 11;
				}
				else if ( md.year >= 1700 ) {
					if ( md.month > 1 || md.month == 1 && md.day >= 19 )
						ds = 11;
					else ds = 10;
				}
				else {
					ds = 10;
				}
				ds = Math.max((md.year-1)/100-(md.year-1)/400-2,ds);
				while ( ds--> 0 ) md.inc();
				md.dwk = old_dwk;
				System.out.println(int2DayOfWeek.get(md.dwk)+" "+md.day+(flag?"*":"")+" "+M[md.month]+" "+md.year);
			}
		}
	}
}


