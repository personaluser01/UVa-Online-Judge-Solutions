/*
 * 12445. Happy 12
 * TOPIC:
 * status:
 */
import java.io.*;
import java.util.*;

class Main {
	final int SH = 4;
	final long MOD = (1L<<13), oo = (1L<<29);
	final int n = 12, N = 12, M = 6;
	long BIT( int k ) { return (1L << k); }
	long MASK( int k ) { return BIT(k)-1L; }
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception { new Main().go(); }

		long u;
		long getItemAt( long u, int k ) { return (u>>(k*SH))&MASK(SH); }
		long setItemAt( long u, int k, long val ) {
			u &= ~(MASK(SH)<<(k*SH));
			u |= (val << (k*SH));
			return u;
		}
		long permFromArray( long []c ) {
			long u = 0;
			for ( int i = 0; i < n; ++i )
				u |= (c[i] << (i*SH));
			return u;
		}
		long permFromString( String s ) {
			long u = 0;
			String []t = s.split(",");
			for ( int i = 0; i < n; ++i )
				u |= ((Long.parseLong(t[i])-1)<<(i*SH));
			return u;
		}
		long Multiply( long u, long other ) {
			long v = 0;
			for ( int i = 0; i < n; ++i ) 
				v = setItemAt(v,i,getItemAt(other,(int)getItemAt(u,i)));
			return v;
		}
		String toStr( long u ) {
			String s = "";
			for ( int i = 0; i < n; ++i )
				s += " "+Long.toString(getItemAt(u,i));
			return s;
		}

	long []p = new long[M];
	long Target;
	String []a = {"2,3,4,5,6,12,7,8,9,10,11,1","12,1,2,3,4,5,7,8,9,10,11,6","1,2,3,4,5,12,6,7,8,9,10,11","1,2,3,4,5,7,8,9,10,11,12,6","2,3,4,5,6,7,8,9,10,11,12,1","12,1,2,3,4,5,6,7,8,9,10,11"};
	String T = "1,2,3,4,5,6,7,8,9,10,11,12";

	Queue<Long> q = new LinkedList<Long>();
	HashMap<Long,Long> m = new HashMap<Long,Long>();
	TreeMap<Long,Long> []h = new TreeMap[(int)MOD];

	int H( long p ) {
		return (int)(p & (MOD-1L));
	}

	void bfs( long src, long lim ) {
		long i,j,k,w = (1L<<29);
		for(;q.size()>0;q.poll());
		m.clear(); m.put(src,0L); q.add(src);
		for(;q.size()>0;) {
			long u = q.poll(),v; k = m.get(u);
			if ( h[H(u)].containsKey(u) ) {
				if ( h[H(u)].get(u)+k < w ) w = h[H(u)].get(u)+k;
				continue ;
			}
			if ( k >= w ) continue ;
			for ( i = 0; k <= 17-lim && i < M; ++i )
				if ( !m.containsKey(v=Multiply(u,p[(int)i])) ) { m.put(v,k+1); q.add(v); }
		}
		System.out.println(w<(1L<<29)?w:19);
		if ( w == +oo )
			w = 19;
		for ( Map.Entry<Long,Long> me : m.entrySet() )
			h[H(me.getKey())].put(me.getKey(),me.getValue());
	}
	void precalc( long lim ) {
		long i,j,k,ky;
		for ( i = 0; i < MOD; ++i ) {
			h[(int)i] = new TreeMap<Long,Long>();
			h[(int)i].clear();
		}
		for(;q.size()>0;q.poll());
		h[H(Target)].put(Target,0L); q.add(Target);
		for(;q.size()>0;) {
			long u = q.poll(),v; k = h[H(u)].get(u);
			for ( i = 0; k < lim && i < M; ++i ) {
				v = Multiply(u,p[(int)i]);
				if ( !h[(int)(ky = H(v))].containsKey(v) ) { h[(int)ky].put(v,k+1); q.add(v); }
			}
		}
	}

	void go() throws Exception {
		long ts = scan.nextLong(),i,j,k,lim,s;
		long []c = new long[N];
		for ( i = 0; i < M; p[(int)i] = permFromString(a[(int)i]), ++i );
		Target = permFromString(T);
		precalc(lim=9);
		for (;ts-->0;) {
			for ( i = 0; i < n; ++i ) 
				c[(int)i] = scan.nextLong()-1;
			s = permFromArray(c);
			/*
			System.out.println(s.toStr());
			System.out.println(Target.toStr());
			*/
			bfs(s,lim);
		}
	}
};


