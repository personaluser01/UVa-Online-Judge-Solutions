/*
 * 426. Fifth Bank of Swamp County
 * TOPIC: output formatting
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	final int N = (1<<16);
	Pattern p = Pattern.compile("(\\d\\d)/(\\d\\d)/(\\d\\d)\\s+(\\d+)\\s*([^. 	]*)([.]?)(\\S*)");
	int n;
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String []t = new String[N];
	public static void main( String [] args ) throws Exception {
		new Main().go();
	};
	class Cheque implements Comparable<Cheque> {
		int id,dd,mm,yy,x,y;
		boolean is;
		Cheque() {};
		Cheque( int id, int dd, int mm, int yy, int x, int y ) {
			this.x = x; this.y = y; this.id = id; this.dd = dd; this.mm = mm; this.yy = yy;
			is = false ;
		};
		public int compareTo( Cheque other ) { return this.id-other.id; };
		public String toString() {
			return String.format("%4d%c %6d.%02d %02d/%02d/%02d",id,is?'*':' ',x,y,yy,mm,dd);
		};
	};
	void go() throws Exception {
		int i,j,k,ts = Integer.parseInt(br.readLine()),dd,mm,yy,x,y,rows,cols;
		for( br.readLine(); ts-->0;) {
			for ( n=0; (t[n]=br.readLine())!=null && !t[n].equals(""); ++n );
			Set<Cheque> s = new TreeSet<Cheque>();
			for ( i = 0; i < n; ++i ) {
				Matcher m = p.matcher(t[i]);
				m.find();
				yy = Integer.parseInt(m.group(1));
				mm = Integer.parseInt(m.group(2));
				dd = Integer.parseInt(m.group(3));
				k = Integer.parseInt(m.group(4));
				String sx = m.group(5);
				if ( !sx.equals("") )
					x = Integer.parseInt(sx);
				else x = 0;
				if ( m.group(6).equals("") ) y = 0;
				else if ( m.group(7).equals("") ) y = 0;
				else y = Integer.parseInt(m.group(7));
				if ( x+y/100.00 >= 1000000 ) continue ;
				if ( y >= 100 ) y /= 10;
				s.add(new Cheque(k,dd,mm,yy,x,y));
			}
			Cheque []c = new Cheque[n]; k = 0;
			for ( Cheque e: s ) 
				c[k++] = e;
			n = k;
			for ( i = 1; i < n; c[i].is = (c[i].id!=c[i-1].id+1), ++i );
				for ( k = n; 0 != (k%3); ++k );
				rows = k/3;
				for ( i = 0; i < rows; ++i ) {
					System.out.print(c[i]);
					if ( i+rows < n ) {
						System.out.print("   "+c[i+rows]);
						if ( i+rows+rows < n )
							System.out.println("   "+c[i+rows+rows]);
						else System.out.println();
					}
					else System.out.println();
				}
			if ( ts > 0 ) System.out.println();
		}
	};
};

