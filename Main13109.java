/*
 * 13109. Elephants
 * TOPIC: greedy, sorting
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	private static final int N = (1<<17);
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	Reader r = new InputStreamReader(System.in);
	int n,w;
	int []c;
	int rd() throws Exception {
		int ch,n = 0;
		for (;(ch = r.read()) != -1 && !('0'<=(char)ch&&(char)ch<='9'); );
		for ( n = ch-'0'; (ch = r.read()) != -1 && '0' <= (char)ch && (char)ch <= '9'; n = 10*n+ch-'0' );
		return n;
	}
	public static void main( String ... args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		int i,j,k,s;
		for ( int ts = rd(); ts-->0; ) {
			n = rd(); w = rd();
			c = new int[n];
			for ( i = 0; i < n; c[i++] = rd() );
			Arrays.sort(c);
			for ( k = -1, s = 0, i = 0; i < n; ++i )
				if ( (s+=c[i]) > w ) {
					k = i;
					break ;
				}
			if ( s <= w ) k = n;
			bw.write(k+"\n");
		}
		bw.flush();
	}
}
