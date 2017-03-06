/*
 * 12348. Fun Coloring
 * TOPIC: ad hoc, bitmasks
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {

	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	StringTokenizer st;
	final int N = 0x80;

	public static void main( String []args ) throws Exception { new Main().go(); }

	int []u = new int[N], cnt = new int[1 << 22];
	boolean []isBad = new boolean[1 << 22];
	int m,n,mask;

	boolean f() {
		for ( int i = 0; i < m; ++i )
			if ( cnt[u[i]] > 1 )
				if ( (mask&u[i])==u[i] || (~mask&u[i])==u[i] )
					return false; 
		return true;
	}

	void go() throws Exception {
		int i,j,k,l,t,ts = Integer.parseInt(br.readLine());
		boolean ok;
		String s = "";
		for ( k = 0; k < (1<<22); ++k )
			cnt[k] = cnt[k>>1]+(k&1);
		for(;ts-->0;br.readLine(),s+=(ok?"Y":"N")){
			st = new StringTokenizer(br.readLine());
			n = Integer.parseInt(st.nextToken());
			m = Integer.parseInt(st.nextToken());
			for ( i = 0; i < m; ++i ) 
				for(u[i]=0,st=new StringTokenizer(br.readLine());st.hasMoreTokens();u[i]|=(1<<(Integer.parseInt(st.nextToken())-1)));
			for ( ok = false, mask = 0; mask < (1<<n) && !(ok|=f()); ++mask );
		}
		System.out.print(s);
	}
};


