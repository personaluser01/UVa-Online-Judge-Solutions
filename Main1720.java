/*
 * 1720. Weather Report
 * TOPIC: huffman tree
 * status: in progress
 */
import java.io.*;
import java.util.*;
import java.text.*;

class Main {
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	Reader r = new InputStreamReader(System.in);
	int n;
	double tol = 1e-9;
	private final static int N = 32;
	double []p = new double[4], len = new double[4];
	NumberFormat nf = NumberFormat.getInstance();
	{
		nf.setMinimumFractionDigits(6);
		nf.setMaximumFractionDigits(6);
	}
	double rd() throws Exception {
		double n = 0, m = 0;
		int ch,len = 0;
		for ( ;(ch = r.read()) != -1 && !('0'<=(char)ch && (char)ch<='9') && ch != '.'; );
		if ( ch == -1 ) return -1;
		if ( ch == '.' ) {
			for ( ;(ch = r.read()) != -1 && '0'<=(char)ch && (char)ch<='9'; ++len, m = 10*m+ch-'0' );
			return m/Math.pow(10,len);
		}
		for ( n = ch-'0'; (ch = r.read()) != -1 && '0'<=(char)ch && (char)ch<='9'; n = 10*n+ch-'0' );
		if ( ch == '.' ) {
			for ( ;(ch = r.read()) != -1 && '0'<=(char)ch && (char)ch<='9'; ++len, m = 10*m+ch-'0' );
			return n+m/Math.pow(10,len);
		}
		return n;
	}
	class Pair implements Comparable<Pair> {
		String code;
		int len;
		double p;
		Pair( String s, double p ) {
			this.code = s;
			this.p = p;
		}
		public int compareTo( Pair other ) {
			if ( Math.abs(p-other.p) < tol )
				return 0;
			return p<other.p?-1:1;
		}
	}
	class Entry implements Comparable<Entry> {
		List<Pair> lst;
		double weight;
		public int compareTo( Entry other ) {
			if ( Math.abs(this.weight-other.weight) < tol )
				return 0;
			return weight<other.weight?-1:1;
		}
		Entry( List<Pair> lst ) {
			this.lst = lst;
			int i;
			for ( weight = 0, i = 0; i < lst.size(); ++i )
				weight += lst.get(i).p;
		}
		Entry( Pair p ) {
			this.lst = new ArrayList<Pair>();
			int i;
			lst.add(p);
			for ( weight = 0, i = 0; i < lst.size(); ++i )
				weight += lst.get(i).p;
		}
		Entry merge( Entry other ) {
			List<Pair> x = new ArrayList<>();
			for ( Pair a: this.lst ) 
				x.add(new Pair("0"+a.code,a.p));
			for ( Pair a: other.lst ) 
				x.add(new Pair("1"+a.code,a.p));
			return new Entry(x);
		}
	}
	public static void main( String ... args ) throws Exception {
		int k;
		for ( fac[0] = 1, k = 1; k <= 20; ++k )
			fac[k] = fac[k-1]*k;
		new Main().go();
	}
	private static long []fac = new long[N];
	void go() throws Exception {
		int i,j,k,t;
		double ans = 0,pi,pj,pk,pt;
		for ( ;(n=(int)rd())!=-1; ) {
			for ( ans = 0, i = 0; i < 4; p[i++] = rd() );
			PriorityQueue<Entry> pq = new PriorityQueue<>();
			for ( i = 0; i < 4; ++i ) pq.add(new Entry(new Pair("",p[i])));
			while ( pq.size() >= 2 ) {
				Entry x = pq.poll(), y = pq.poll();
				pq.add(x.merge(y));
			}
			Entry x = pq.poll();
			assert x.lst.size() == 4;
			Pair []e = new Pair[4];
			i = 0;
			for ( Pair a: x.lst )
				e[i++] = a;
			for ( i = 0; i < 4; ++i ) {
				e[i].len = e[i].code.length();
				System.out.println(e[i].code+" "+e[i].p);
			}
			for ( i = 0; i <= n; ++i )
				for ( pi = Math.pow(e[0].p,i), j = 0; i+j <= n; ++j )
					for ( pj = Math.pow(e[1].p,j), k = 0; i+j+k <= n; ++k ) {
						pk = Math.pow(e[2].p,k);
						t = n-i-j-k;
						pt = Math.pow(e[3].p,t);
						//ans += fac[n]/fac[i]/fac[j]/fac[k]/fac[t]*pi*pj*pk*pt*(i*e[0].len+j*e[1].len+k*e[2].len+t*e[3].len);
						ans += pi*pj*pk*pt*(i*e[0].len+j*e[1].len+k*e[2].len+t*e[3].len);
					}
			/*
			for ( Pair t: x.lst )
				System.out.println(t.code+" "+t.p);
			*/
			bw.write(nf.format(ans)+"\n");
		}
		bw.flush();
	}
}

