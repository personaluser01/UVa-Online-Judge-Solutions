/*
 * 13025.
 * TOPIC: java calendar
 * ststus: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	String []m = {"January","February","March","April","May","June","July","August","September","October","November","December"};
	String []d = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
	public static void main( String [] args ) throws Exception { new Main().go(); };
	void go() throws Exception {
		Calendar cal = Calendar.getInstance();
		cal.set(Calendar.YEAR,2013);
		cal.set(Calendar.MONTH,4);
		cal.set(Calendar.DAY_OF_MONTH,29);
		StringBuilder sb = new StringBuilder();
		sb.append(m[cal.get(Calendar.MONTH)]+" ");
		sb.append(Integer.toString(cal.get(Calendar.DAY_OF_MONTH))+", "+Integer.toString(cal.get(Calendar.YEAR)));
		sb.append(" "+d[cal.get(Calendar.DAY_OF_WEEK)-1]);
		System.out.println(sb);
	};
};

