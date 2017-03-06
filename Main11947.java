/*
 * 11947. Cancer or Scorpio
 * status: Accepted
 * TOPIC: gregorian calendar
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	Calendar []b = new GregorianCalendar[12];
	Calendar []e = new GregorianCalendar[12];
	String []names = new String[12];
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		int i,j,k,ts;

		b[0] = new GregorianCalendar();
		b[0].set(Calendar.MONTH,0);
		b[0].set(Calendar.DAY_OF_MONTH,21);
		names[0] = new String("Aquarius");

		b[1] = new GregorianCalendar();
		b[1].set(Calendar.MONTH,1);
		b[1].set(Calendar.DAY_OF_MONTH,20);
		names[1] = new String("Pisces");

		b[2] = new GregorianCalendar();
		b[2].set(Calendar.MONTH,2);
		b[2].set(Calendar.DAY_OF_MONTH,21);
		names[2] = new String("Aries");

		b[3] = new GregorianCalendar();
		b[3].set(Calendar.MONTH,3);
		b[3].set(Calendar.DAY_OF_MONTH,21);
		names[3] = new String("Taurus");

		b[4] = new GregorianCalendar();
		b[4].set(Calendar.MONTH,4);
		b[4].set(Calendar.DAY_OF_MONTH,22);
		names[4] = new String("Gemini");

		b[5] = new GregorianCalendar();
		b[5].set(Calendar.MONTH,5);
		b[5].set(Calendar.DAY_OF_MONTH,22);
		names[5] = new String("Cancer");

		b[6] = new GregorianCalendar();
		b[6].set(Calendar.MONTH,6);
		b[6].set(Calendar.DAY_OF_MONTH,23);
		names[6] = new String("Leo");

		b[7] = new GregorianCalendar();
		b[7].set(Calendar.MONTH,7);
		b[7].set(Calendar.DAY_OF_MONTH,22);
		names[7] = new String("Virgo");

		b[8] = new GregorianCalendar();
		b[8].set(Calendar.MONTH,8);
		b[8].set(Calendar.DAY_OF_MONTH,24);
		names[8] = new String("Libra");

		b[9] = new GregorianCalendar();
		b[9].set(Calendar.MONTH,9);
		b[9].set(Calendar.DAY_OF_MONTH,24);
		names[9] = new String("Scorpio");

		b[10] = new GregorianCalendar();
		b[10].set(Calendar.MONTH,10);
		b[10].set(Calendar.DAY_OF_MONTH,23);
		names[10] = new String("Sagittarius");

		b[11] = new GregorianCalendar();
		b[11].set(Calendar.MONTH,11);
		b[11].set(Calendar.DAY_OF_MONTH,23);
		names[11] = new String("Capricorn");

		for ( i = 0; i < 12; ++i ) {
			e[i] = (Calendar)b[(i+1+12)%12].clone();
			e[i].roll(GregorianCalendar.DAY_OF_MONTH,-1);
		}

		String s;
		int cs = 0;
		StringTokenizer st;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
		Pattern p = Pattern.compile("(\\d{2})(\\d{2})(\\d{4})");
		Matcher m;
		while ( ts-- > 0 ) {
			s = br.readLine();
			m = p.matcher(s);
			m.find();
			// assert m.find();
			Calendar c = new GregorianCalendar();
			c.set(Calendar.DAY_OF_MONTH,Integer.parseInt(m.group(2)));
			c.set(Calendar.MONTH,Integer.parseInt(m.group(1))-1);
			c.set(Calendar.YEAR,Integer.parseInt(m.group(3)));
			for ( i = 0; i < 40; ++i )
				c.add(Calendar.DAY_OF_MONTH,7);
			for ( i = 0; i < 12; ++i ) {
				b[i].set(Calendar.YEAR,c.get(Calendar.YEAR));
				e[i].set(Calendar.YEAR,c.get(Calendar.YEAR));
			}
			if ( c.compareTo(b[0]) < 0 ) {
				s = names[11];
			}
			else if ( c.compareTo(b[11]) >= 0 ) {
				s = names[11];
			}
			else {
				// assert c.compareTo(b[0]) >= 0;
				// assert c.compareTo(b[11]) < 0;
				j = -1;
				for ( i = 0; i <= 10 && j == -1; ++i )
					if ( c.compareTo(b[i]) >= 0 && c.compareTo(e[i]) <= 0 ) {
						j = i;
						break ;
					}
				// assert j != -1;
				s = names[j];
			}
			s = s.toLowerCase();
			System.out.printf("%d %02d/%02d/%d ",++cs,c.get(Calendar.MONTH)+1,c.get(Calendar.DAY_OF_MONTH),c.get(Calendar.YEAR));
			System.out.println(s);
		}
	}
};

