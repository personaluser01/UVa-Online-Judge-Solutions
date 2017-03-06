/*
 * 12207. This is Your Queue
 * TOPIC: priority queue with updates
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Map<Integer,Integer> m;
	Scanner scan = new Scanner(System.in);
	int n,cnt,N,V;
	int []heap,pos,d,aid = new int[1<<16];
	public static void main( String [] args ) throws Exception {
		new Main().go();
	};
	void bubble( int i, int j ) {
		int k;
		k = pos[heap[i]]; pos[heap[i]] = pos[heap[j]]; pos[heap[j]] = k;
		k = heap[i]; heap[i] = heap[j]; heap[j] = k;
	};
	void push( int x ) {
		int i,j;
		if ( pos[x] < 0 ) {
			pos[heap[cnt] = x] = cnt;
			++cnt;
		};
		for ( j = pos[x]; j > 0 && d[heap[i=(j-1)>>1]] > d[heap[j]]; bubble(i,j), j = i );
	};
	int pop() {
		int i,j,x = heap[0];
		assert cnt > 0;
		if ( (cnt+=(pos[x]=-1)) > 0 ) 
			pos[heap[0]=heap[cnt]]=0;
		for ( j=0;;bubble(i,j) ) {
			i=j; j<<=1; ++j;
			if ( j >= cnt ) break ;
			if ( j < cnt-1 && d[heap[j+1]] < d[heap[j]] ) ++j;
			if ( d[heap[i]] <= d[heap[j]] ) break ;
		};
		return x;
	};
	int peek() { return heap[0]; };
	int ins( int x ) {
		if ( m.containsKey(x) )
			return m.get(x);
		m.put(x,V++);
		aid[V-1] = x;
		return V-1;
	};
	class Request {
		boolean change;
		int x;
		Request( boolean f, int X ) { change = f; x = X; };
		Request() { change = false; };
	};
	Request []r = new Request[0x400];
	void go() throws Exception {
		int i,j,k,qr,cs = 0,t,L;
		for(;;) {
			n = scan.nextInt();
			qr = scan.nextInt();
			if ( n == 0 && qr == 0 ) break ;
			m = new TreeMap<Integer,Integer>();
			N = (qr<<1)+0x400; V = 0;
			heap = new int[N];
			pos = new int[N];
			d = new int[N];
			cnt = 0;
			System.out.println("Case "+(++cs)+":");
			int []p = new int[qr+qr];
			for ( t = 0, i = 0; i < qr && i < n; ins(p[t++] = ++i) );
			for ( i = 0; i < qr; ++i ) {
				String tmp = scan.next();
				if ( tmp.equals("N") ) {
					r[i] = new Request(false,0);
					continue ;
				}
				assert tmp.equals("E");
				r[i] = new Request(true,k=scan.nextInt());
				ins(p[t++] = k);
			};
			for ( k = t; t < qr+qr; p[t++] = 1000000001 );
			Arrays.sort(p);
			L = qr+qr+0x400;
			for ( i = 0; i < V; pos[i++] = -1 );
			for ( i = 0; i < k; ++i ) {
				j = m.get(p[i]); d[j] = p[i];
				push(j);
			}
			for ( int l = 0; l < qr; ++l ) {
				assert r[l] != null;
				if ( !r[l].change ) {
					System.out.println(aid[i = pop()]);
					d[i] = L++;
					push(i);
					continue ;
				};
				d[i=m.get(r[l].x)] = d[peek()]-1;
				push(i);
			};
		};
	};
};

