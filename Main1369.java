/*
 * 1369. Travel
 * TOPIC: mincost circulation, parametrized flow
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {

	private final static int MAXV = 0x400*2, MAXE = (1<<21), MAXN = MAXV, oo = (1<<29);
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	Reader R = new InputStreamReader(System.in);
	int []to = new int[MAXE], next = new int[MAXE], last = new int[MAXV], low = new int[MAXE], up = new int[MAXE], flow = new int[MAXE], seen = new int[MAXV], p = new int[MAXV];
	int []tto = new int[MAXE], nnext = new int[MAXE], llast = new int[MAXV], llow = new int[MAXE], uup = new int[MAXE], fflow = new int[MAXE], theOther = new int[MAXE];
	int m,n,V,E,EE,yes,src;
	EdgeCost []cost = new EdgeCost[MAXE], d = new EdgeCost[MAXV], ccost = new EdgeCost[MAXE];
	EdgeCost ZERO = new EdgeCost(0,0), INF = new EdgeCost(1,0);
	boolean saneInput;

	int lue() throws Exception {
		int ch,n = 0;
		for(;(ch = R.read()) != -1 && !('0'<=(char)ch && (char)ch<='9'););
		for ( n = ch-'0'; (ch = R.read()) != -1 && '0'<=(char)ch && (char)ch<='9'; n = 10*n+ch-'0' );
		return n;
	}

	void addArcs( int x, int y, int l, int u, EdgeCost w ) {
		int i = E++, j = E++;
		to[i] = y; next[i] = last[x]; last[x] = i; cost[i] = w;          low[i] =  l; up[i] =  u; flow[i] = 0;
		to[j] = x; next[j] = last[y]; last[y] = j; cost[j] = w.negate(); low[j] = -u; up[j] = -l; flow[j] = 0;
	}

	private class EdgeCost implements Comparable<EdgeCost> {
		int a,b;
		EdgeCost( int a, int b ) {
			this.a = a; this.b = b;
		}
		@Override
		public int compareTo( EdgeCost other ) {
			return a==other.a?(b==other.b?0:b<other.b?-1:1):a<other.a?-1:1;
		}
		EdgeCost sub( EdgeCost other ) {
			return new EdgeCost(a-other.a,b-other.b);
		}
		EdgeCost add( EdgeCost other ) {
			return new EdgeCost(a+other.a,b+other.b);
		}
		EdgeCost negate() {
			return new EdgeCost(-a,-b);
		}
		public int easyCompare( EdgeCost x, EdgeCost y ) {
			int A = x.a+y.a, B = x.b+y.b;
			return a==A?(b==B?0:b<B?-1:1):a<A?-1:1;
		}
	}

	public static void main( String ... args ) throws Exception {
		new Main().go();
	}

	void saveConfiguration() {
		int i;
		for ( EE = E, i = 0; i < E; ++i ) {
			fflow[i] = flow[i]; tto[i] = to[i]; nnext[i] = next[i]; llow[i] = low[i]; uup[i] = up[i];
			ccost[i] = cost[i];
		}
		for ( i = 0; i < V; ++i ) llast[i] = last[i];
	}

	void restoreConfiguration() {
		int i;
		for ( E = EE, i = 0; i < E; ++i ) {
			flow[i] = fflow[i]; to[i] = tto[i]; next[i] = nnext[i]; low[i] = llow[i]; up[i] = uup[i];
			cost[i] = ccost[i];
		}
		for ( i = 0; i < V; ++i ) last[i] = llast[i];
	}

	int getNegCycleTail() {
		int i,j,x,y;
		boolean flag;
		for ( d[src] = ZERO, seen[src] = ++yes, flag = true, j = 0; j < V && flag; ++j )
			for ( flag = false, i = 0; i < E; ++i )
				if ( seen[x=to[i^1]] == yes && flow[i] < up[i] && (seen[y=to[i]]!=yes||d[y].easyCompare(d[x],cost[i])>0) ) {
					if ( seen[y] != yes ) 
						d[y] = d[x].add(cost[i]);
					else {
						d[y].a = d[x].a+cost[i].a;
						d[y].b = d[x].b+cost[i].b;
					}
					seen[y] = yes; p[y] = i; flag = true ;
				}
		for ( i = 0; i < E; ++i )
			if ( flow[i] < up[i] && seen[x=to[i^1]] == yes && (seen[y=to[i]]!=yes||d[y].easyCompare(d[x],cost[i])>0) ) {
				p[y] = i;
				return y;
			}
		return -1;
	}

	boolean mincostCirculation() {
		int x,y,df,i;
		EdgeCost w = new EdgeCost(0,0);

		while ( (y = getNegCycleTail()) >= 0 ) {
			for ( seen[y]=++yes, x=to[p[y]^1]; seen[x]!=yes; seen[x]=yes, x=to[p[x]^1] );
			for ( df=up[p[x]]-flow[p[x]], y=to[p[x]^1]; y!=x; df=Math.min(df,up[p[y]]-flow[p[y]]), y=to[p[y]^1] );
			assert df > 0;
			for ( flow[p[x]]+=df, flow[p[x]^1]-=df, y=to[p[x]^1]; y!=x; flow[p[y]]+=df, flow[p[y]^1]-=df, y=to[p[y]^1] );
		}

		//System.out.println("E = "+E);
		for ( i = 0; i < E; ++i ) {
			w.a += flow[i]*cost[i].a;
			w.b += flow[i]*cost[i].b;
			assert flow[i] <= up[i];
			assert flow[i] >= low[i];
			/*
			if ( flow[i] > 0 && to[i^1] != src ) {
				System.out.println("From "+(to[i^1]>=n?(to[i^1]-n+1)+"s end":(to[i^1]+1)+" s start")+" to "+(to[i]>=n?(to[i]-n+1)+"s end":(to[i]+1)+"s start"));
			}
			*/
			assert !(flow[i] > 0 && to[i^1] == src);
		}

		assert 0==(w.a&1);
		assert 0==(w.b&1);

		w.a/=2;w.b/=2;
		//System.out.println(w.a+" "+w.b);

		return w.a==0;

	}

	boolean solve( Map<Integer,List<Integer>> m ) {
		int i,j,k,t;

		if ( !saneInput ) 
			return false ;

		for ( t = 0; t < 2; ++t )
			for ( Integer ii: m.get(t) )
				for ( Integer jj: m.get(t^1) ) {
					restoreConfiguration();

					low[ii^1] = low[jj^1] = -1;
					up[ii^1] = up[jj^1] = -1;
					low[ii] = low[jj] = 1;
					up[ii] = up[jj] = 1;
					low[theOther[ii]] = up[theOther[ii]] = 0;
					low[theOther[ii]^1] = up[theOther[ii]^1] = 0;
					low[theOther[jj]] = up[theOther[jj]] = 0;
					low[theOther[jj]^1] = up[theOther[jj]^1] = 0;

					addArcs(to[ii],to[jj^1],0,1,INF); flow[E-2] = 1; flow[E-1] = -1;
					addArcs(to[jj],to[ii^1],0,1,INF); flow[E-2] = 1; flow[E-1] = -1;
					flow[ii] = 1; flow[ii^1] = -1;
					flow[jj] = 1; flow[jj^1] = -1;
					for ( i = 0; i < E; ++i ) {
						assert flow[i] <= up[i];
						assert flow[i] >= low[i];
					}
					if ( mincostCirculation() )
						return true ;
				}
		return false ;
	}

	void go() throws Exception {
		int i,j,k,l,t,s,prev;
		Map<Integer,List<Integer>> idx;
		for ( int ts = lue(); ts-->0; ) {
			n = lue(); m = lue(); saneInput = true ;
			for ( E = 0, V = 2*n+1, src = V-1, i = 0; i < V; last[i++] = -1 );
			for ( i = 0; i < n; ++i ) {
				addArcs(i,i+n,0,1,ZERO);
				addArcs(src,i,0,+oo,ZERO);
				addArcs(src,i+n,0,+oo,ZERO);
			}
			for ( l = 0; l < m; ++l ) {
				i = lue()-1; j = lue()-1;
				addArcs(i+n,j,0,1,ZERO);
				addArcs(j+n,i,0,1,ZERO);
			}
			/* remember the important two roads: */
			idx = new HashMap<Integer,List<Integer>>();
			for ( t = 0, l = 0; l < 2; ++l ) {
				i = lue()-1; j = lue()-1;
				idx.put(l,new ArrayList<Integer>()); prev = -1;
				for ( k = 0; k < E; ++k )
					if ( to[k^1] == i+n && to[k] == j ) {
						++t; idx.get(l).add(k);
						if ( prev == -1 ) prev = k;
						else theOther[theOther[prev] = k] = prev;
					}
					else if ( to[k^1] == j+n && to[k] == i ) {
						++t; idx.get(l).add(k);
						if ( prev == -1 ) prev = k;
						else theOther[theOther[prev] = k] = prev;
					}
			}
			if ( t != 4 ) saneInput = false ;
			assert saneInput;
			/* block the toll roads: */
			for ( l = 0, s = t = lue(); t-->0; ) {
				i = lue()-1; j = lue()-1;
				for ( k = 0; k < E; ++k ) 
					if ( to[k^1] == i+n && to[k] == j ) {
						low[k] = up[k] = 0; ++l;
					}
					else if ( to[k^1] == j+n && to[k] == i ) {
						low[k] = up[k] = 0; ++l;
					}
			}
			assert l == s+s;
			saveConfiguration();
			bw.write(solve(idx)?"YES\n":"NO\n");
		}
		bw.flush();
	}
};

