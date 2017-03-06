/*
 * 12950. Even Obsession
 * TOPIC: dijkstra
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = (1<<16), MAXV = (1<<20), MAXE = (1<<21), oo = (1<<29);
	Scanner scan = new Scanner(System.in);
	int n,m,V,E,cnt;
	int []to = new int[MAXE], next = new int[MAXE], last = new int[MAXV], cost = new int[MAXE], d = new int[MAXV], pos = new int[MAXV], heap = new int[MAXE];
	int enc( int x, int t ) { return t|(x<<1); };
	void bubble( int i, int j ) {
		int t;
		t = heap[i]; heap[i] = heap[j]; heap[j] = t;
		t = pos[heap[i]]; pos[heap[i]] = pos[heap[j]]; pos[heap[j]] = t;
	};
	void push( int x ) {
		int i,j;
		if ( pos[x] < 0 ) { pos[heap[cnt]=x] = cnt; ++cnt; }
		for ( j = pos[x]; j > 0 && d[heap[i=(j-1)>>1]] > d[heap[j]]; bubble(i,j), j = i );
	}
	int pop() {
		int x = heap[0],i,j;
		if ( 0 != (cnt += (pos[x]=-1)) )
			pos[heap[0] = heap[cnt]] = 0;
		for ( j = 0; ; bubble(i,j) ) {
			i = j; j <<= 1; ++j;
			if ( j >= cnt ) break ;
			if ( j < cnt-1 && d[heap[j]] > d[heap[j+1]] ) ++j;
			if ( d[heap[i]] <= d[heap[j]] ) break ;
		}
		return x;
	}
	public static void main( String [] args ) throws Exception {
		new Main().go();
	};
	void addArcs( int x, int y, int c ) {
		int i = E++, j = E++;
		to[i] = y; next[i] = last[x]; last[x] = i; cost[i] = c;
		to[j] = x; next[j] = last[y]; last[y] = j; cost[j] = c;
	}
	void go() throws Exception {
		int i,j,k,l,t,x,y,u,v;
		while ( scan.hasNext() ) {
			n = scan.nextInt();
			m = scan.nextInt();
			for ( cnt = 0, E = 0, i = 0; i < n; ++i )
				for ( t = 0; t < 2; ++t ) {
					last[enc(i,t)] = -1;
					pos[enc(i,t)] = -1;
				}
			for ( l = 0; l < m; ++l ) {
				i = scan.nextInt()-1;
				j = scan.nextInt()-1;
				k = scan.nextInt();
				addArcs(i,j,k);
			}
			for ( i = 0; i < n; ++i )
				for ( t = 0; t < 2; ++t )
					d[enc(i,t)] = +oo;
			for ( d[u=enc(0,0)]=0, push(u); cnt>0;) 
				for ( u=pop(), t=(u&1), i=last[x=(u>>1)]; i>=0; i=next[i] )
					if ( d[v=enc(y=to[i],t^1)] > d[u]+cost[i] ) {
						d[v] = d[u]+cost[i];
						push(v);
					}
			System.out.println(d[u=enc(n-1,0)]<+oo?d[u]:-1);
		}
	};
};

