/*
 * 12439. February 29
 * status: Accepted
 * TOPIC: gregorian calendar, leap year, inclusion exclusion, pie
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;
import java.lang.Math;

class Main {
	Pattern p = Pattern.compile("\\s*([A-Za-z]+)\\s*(\\d+)\\s*,\\s+(\\d+)");
	Map<String,Integer> q = new HashMap<String,Integer>();
	public static void main( String [] args ) throws Exception { new Main().go(); }
    int YA,YB;

	Integer getMonth( String s ) { return q.get(s); }

	boolean isLeap( int x ) {
		return (0==(x%4))&&(0<(x%100)||0==(x%400));
	}

	GregorianCalendar getDate( String s ) {
		Matcher m = p.matcher(s);
		m.find();
		String mon = m.group(1);
		int day = Integer.parseInt(m.group(2));
		int year = Integer.parseInt(m.group(3));
		Calendar c = new GregorianCalendar();
        if ( isLeap(year) )
            year = 2000;
		c.set(Calendar.DAY_OF_MONTH,day);
		c.set(Calendar.MONTH,getMonth(mon));
		c.set(Calendar.YEAR,year);
		return (GregorianCalendar)c;
	}
    int getYear( String s ) {
        Matcher m = p.matcher(s);
		m.find();
		String mon = m.group(1);
		int day = Integer.parseInt(m.group(2));
		int year = Integer.parseInt(m.group(3));
        return year;
    }

	int f( int n, int k ) {
        return n/k;
	}
	int g( int n, int k ) {
        if ( 0 == (n%k) )
            return n/k;
        return n/k+1;
	}
    boolean prior( GregorianCalendar c ) {
        return c.get(Calendar.MONTH) <= 0 || (c.get(Calendar.MONTH) == 1 && c.get(Calendar.DAY_OF_MONTH) <= 29);
    }
    boolean after( GregorianCalendar c ) {
        return c.get(Calendar.MONTH) >= 2 || (c.get(Calendar.MONTH) == 1 && c.get(Calendar.DAY_OF_MONTH) >= 29);
    }

	void go() throws Exception {
		int i,j,k,ts,cs = 0,n,ans = 0,ii,jj,A,B,C,U,AB,AC,BC,ABC;
		String s;
		StringTokenizer st;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
		q.put("January",0);
		q.put("February",1);
		q.put("March",2);
		q.put("April",3);
		q.put("May",4);
		q.put("June",5);
		q.put("July",6);
		q.put("August",7);
		q.put("September",8);
		q.put("October",9);
		q.put("November",10);
		q.put("December",11);
		while ( ts-- > 0 ) {
			Calendar a = getDate(s = br.readLine());
            YA = getYear(s);
			Calendar b = getDate(s = br.readLine()),c;
            YB = getYear(s);
			ans = 0;
			
			if ( YA == YB ) {
                if ( isLeap(YA) ) 
                    if ( prior((GregorianCalendar)a) && after((GregorianCalendar)b) )
                        ++ans;
				System.out.println("Case "+(++cs)+": "+ans);
				continue ;
			}

            if ( isLeap(YA) ) 
                if ( prior((GregorianCalendar)a) )
                    ++ans;
            ++YA;

            if ( isLeap(YB) ) 
                if ( after((GregorianCalendar)b) )
                    ++ans;
            --YB;
			i = YA;
			j = YB;
			if ( i == j ) {
				if ( isLeap(i) )
					++ans;
			}
			else if ( i < j ) {
				A = f(j,4)-g(i,4)+1;
				B = f(j,100)-g(i,100)+1;
				C = f(j,400)-g(i,400)+1;
				U = j-i+1;
				AB = B; AC = C; BC = C; ABC = C;
				ans += A-B+C;
			}
			System.out.println("Case "+(++cs)+": "+ans);
		}
	}
};

