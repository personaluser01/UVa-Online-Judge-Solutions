/*
 * 11797. Drutojan Express
 * TOPIC: queue
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int MAXT = 0x400;
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	StringTokenizer st;
	String s,cur;
	int m,T,n=5;
	int [] c = new int[n];
	Queue<Integer> []q;
	String[] names = {"Ja","Sam","Sha","Sid","Tan"};
	Map<String,Integer> e = new HashMap<String,Integer>();
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		int ts,cs = 0,i,j,k,t;
		for ( i = 0; i < n; ++i ) e.put(names[i],i);
		for ( ts = Integer.parseInt(br.readLine()); ts-- > 0; ) {
			st = new StringTokenizer(br.readLine());
			m = Integer.parseInt(st.nextToken());
			T = Integer.parseInt(st.nextToken());
			cur = st.nextToken();
			q = new LinkedList[n];
			for ( i = 0; i < n; ++i ) {
				q[i] = new LinkedList<Integer>();
				st = new StringTokenizer(br.readLine());
				k = Integer.parseInt(st.nextToken());
				for (;k-- > 0; q[i].add((Integer)e.get(st.nextToken())));
			}
			System.out.println("Case "+(++cs)+":");
			for ( i = 0; i < n; ++i ) c[i] = 0;
			for ( i = 0; i < n && !cur.equals(names[i]); ++i );
			for ( t = 0; t < T; j = q[i].poll(), q[i].add(j), i = j ) {
				c[i] += Math.min(T-t,m);
				if ( (t+=m) >= T ) break ;
				if ( (t+=2) >= T ) break ;
			}
			for ( i = 0; i < n; ++i )
				System.out.println(names[i]+" "+c[i]);
		}
	}
};

