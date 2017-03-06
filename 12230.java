/*
 * 12230. Crossing Rivers
 * TOPIC: probability, expectation, mean, neat
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.text.*;

class Main {
	private static final int N = 0x10;
	InputStreamReader R = new InputStreamReader(System.in);
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	NumberFormat nf = NumberFormat.getInstance();
	int ts = 0,n,D;
	{
		nf.setMinimumFractionDigits(3);
		nf.setMaximumFractionDigits(3);
	}
	int []p = new int[N],L = new int[N],v = new int[N];
	public static void main( String ... args ) throws Exception { 
		new Main().go();
	}
	int rd() throws Exception {
		int ch,n = 0;
		for(;(ch = R.read()) != -1 && !('0'<=(char)ch&&(char)ch<='9'););
		for ( n = ch-'0'; (ch=R.read())!=-1 && '0'<=(char)ch&&(char)ch<='9'; n = 10*n+ch-'0' );
		return n;
	}
	void go() throws Exception {
		int i,j,k,t;
		for (;;) {
			n = rd(); D = rd();
			if ( n == 0 && D == 0 ) break ;
			double ans = D;
			for ( i = 0; i < n; ++i ) {
				p[i] = rd();
				L[i] = rd();
				v[i] = rd();
				ans += 2*(L[i]+0.0)/v[i]-L[i];
			}
			bw.write("Case "+(++ts)+": "+nf.format(ans)+"\n\n");
		}
		bw.flush();
	}
}

