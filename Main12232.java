/*
 * 12232. Exlusive OR
 * TOPIC: ad hoc, data structures, bfs
 * status: TLE
 */
import java.io.*;
import java.util.*;

class Main {

	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

	Map<Integer,Map<Integer,Integer>> m;

	final static int N = (1<<15), B = 20, oo = (1<<29);
	static long BIT( int k ) { return (1l<<k); }
	static long MASK( int k ) { return BIT(k)-1L; }
	static int L( int k ) { return (k)&((~k)+1); }
	static int []who = new int[1<<21];

	public static void main( String ... args ) throws Exception { 
		for ( int i = 0; i < 21; ++i )
			who[1<<i] = i;
		new Main().go();
	}

	int []value = new int[N];
	int n;

	long enc( int x, int y, int z ) { return ((long)x)|(((long)y)<<20)|(((long)z)<<40); }

	boolean propagate( long r ) {

		Queue<Long> q = new LinkedList<Long>();
		int x,y,z,i,j,k,val,newval;

		for ( q.add(r); !q.isEmpty(); ) {
			long u = q.poll();
			x = (int)(u&MASK(20));
			y = (int)((u>>20)&MASK(20));
			val = (int)(u>>40);
			for ( Map.Entry<Integer,Integer> entry: m.get(x).entrySet() ) {
				z = entry.getKey();
				if ( z == y ) continue ;
				newval = val^entry.getValue();
				i = Math.min(z,y);
				j = Math.max(z,y);
				if ( m.get(i).containsKey(j) && m.get(i).get(j) == newval )
					continue ;
				if ( !m.get(i).containsKey(j) ) {
					m.get(i).put(j,newval);
					q.add(enc(i,j,newval));
				}
				else return false ;
			}
			for ( Map.Entry<Integer,Integer> entry: m.get(y).entrySet() ) {
				z = entry.getKey();
				if ( z == x ) continue ;
				newval = val^entry.getValue();
				i = Math.min(z,x);
				j = Math.max(z,x);
				if ( m.get(i).containsKey(j) && m.get(i).get(j) == newval )
					continue ;
				if ( !m.get(i).containsKey(j) ) {
					m.get(i).put(j,newval);
					m.get(j).put(i,newval);
					q.add(enc(i,j,newval));
				}
				else return false ;
			}
		}
		return true ;
	}

	int []Z;
	boolean []seen;

	int g( int u, int []v ) {
		int i,j,uu,vv,x,y;
		if ( seen[u] ) return Z[u];
		for ( uu = u; uu > 0; uu &= ~L(uu) ) 
			for ( i = who[L(uu)], vv = uu&~L(uu); vv > 0; vv &= ~L(vv) ) {
				j = who[L(vv)];
				x = Math.min(v[i],v[j]);
				y = Math.max(v[i],v[j]);
				if ( m.get(x).containsKey(y) && g(u&~L(uu)&~L(vv),v) < +oo )
					return Z[u] = m.get(x).get(y)^g(u&~L(uu)&~L(vv),v);
			}
		seen[u] = true ;
		return Z[u];
	}

	int f( int []v, int len ) throws Exception {
		int i,j,l = 0,res = 0, mask = 0;
		int []u;

		for ( i = 0; i < len; ++i ) 
			if ( m.get(v[i]).containsKey(n) ) 
				value[v[i]] = m.get(v[i]).get(n);
		for ( i = 0; i < len; ++i )
			if ( value[v[i]] == -1 )
				++l;
		u = new int[l];
		for ( l = 0, i = 0; i < len; ++i )
			if ( value[v[i]] == -1 ) 
				u[l++] = v[i];
			else res ^= value[v[i]];
		Z = new int[1<<l];
		for ( i = 1; i < (1<<l); Z[i++] = +oo );
		seen = new boolean[1<<l];
		seen[0] = true ;
		return g((int)MASK(l),u)<+oo?res^g((int)MASK(l),u):-1;
	}

	void go() throws Exception {
		String s,cmd;
		StringTokenizer st;
		boolean inconsistent;
		int i,j,k,val,qr,cs = 0,x,y,ff;
		int []idx = new int[16];
		long res;

		for (;(s=br.readLine()) != null; bw.write("\n") ) {
			st = new StringTokenizer(s);
			n = Integer.parseInt(st.nextToken());
			qr = Integer.parseInt(st.nextToken());
			if ( n == 0 && qr == 0 ) break ;
			for ( value[n] = 0, i = 0; i < n; value[i++] = -1 );
			m = new HashMap<Integer,Map<Integer,Integer>>();
			for ( i = 0; i <= n; ++i )
				m.put(i,new HashMap<Integer,Integer>());
			bw.write("Case "+(++cs)+":\n");
			for ( ff = 0, inconsistent = false; qr-- > 0; ) {
				s = br.readLine();
				if ( inconsistent ) continue ;
				st = new StringTokenizer(s);
				switch ( cmd = st.nextToken() ) {
					case "I": res = 0; ++ff;
							  i = Integer.parseInt(st.nextToken());
							  j = Integer.parseInt(st.nextToken());
							  if ( st.hasMoreTokens() ) {
									 val = Integer.parseInt(st.nextToken());
									 x = Math.min(i,j);
									 y = Math.max(i,j);
									 if ( m.get(x).containsKey(y) && m.get(x).get(y) != val )
											inconsistent = true ;
									 else if ( !m.get(x).containsKey(y) ) {
											 m.get(x).put(y,val);
											 m.get(y).put(x,val);
											 res = enc(x,y,val);
									 }
							  }
							  else {
									 val = j;
									 if ( value[i] != -1 && value[i] != val ) 
											inconsistent = true ;
									 else if ( value[i] == -1 ) {
											value[i] = val;
											m.get(i).put(n,val);
											res = enc(i,n,val);
									 }
							  }
							  if ( !inconsistent && !propagate(res) )
									 inconsistent = true ;
							  break ;
					case "Q": k = Integer.parseInt(st.nextToken());
							  for ( i = 0; i < k; idx[i++] = Integer.parseInt(st.nextToken()) );
							  val = f(idx,k);
							  if ( val == -1 ) 
									 bw.write("I don't know.\n");
							  else bw.write(val+"\n");
							  break ;
				}
				if ( inconsistent ) 
					bw.write("The first "+(ff)+" facts are conflicting.\n");
			}
		}
		bw.flush();
	}
};
