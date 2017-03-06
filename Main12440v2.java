/*
 * 12440. Save The Trees
 * TOPIC: priority queue, DP
 * status: Accepted
 * NOTES: idea borrowed
 */
import java.io.*;
import java.util.*;
import java.text.*;

class Main {
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	Scanner scan = new Scanner(System.in);
	private final static int N = (1<<17), MAXT = N, oo = (1<<29);
	int n,cnt;
	int []x = new int[N], h = new int[N], last = new int[N], lastSeen = new int[MAXT], d = new int[N], heap = new int[N<<1], pos = new int[N], z = new int[N], next = new int[N], dins = new int[N];
	int rd() {
		return scan.nextInt();
	}
	public static void main( String ... args ) throws Exception {
		new Main().go();
	}
	void computeLast() {
		int i;
		for ( int t = 0; t < MAXT; lastSeen[t++] = n+1 );
		for ( last[n+1] = n, i = n; i >= 1; --i ) {
			last[i] = Math.min(last[i+1],lastSeen[x[i]]-1);
			lastSeen[x[i]] = i;
		}
	}
	void bubble( int i, int j ) {
		assert i != j;
		int k;
		//System.out.println("Came with "+pos[heap[i]]+" "+heap[i]+" and "+pos[heap[j]]+" "+heap[j]);
		k = heap[i]; heap[i] = heap[j]; heap[j] = k;
		k = pos[heap[i]]; pos[heap[i]] = pos[heap[j]]; pos[heap[j]] = k;
		//System.out.println("Gone with "+pos[heap[i]]+" "+heap[i]+" and "+pos[heap[j]]+" "+heap[j]);
	}

	int peek() {
		// assert cnt >= 1;
		return heap[0];
	}

	void push( int x ) {
		int i,j;
		assert cnt >= 0;
		//System.out.println("Aha "+x);
		if ( pos[x] < 0 ) {
			pos[heap[cnt] = x] = cnt;
			//System.out.println("New arrival of "+x+" to "+pos[x]);
			++cnt;
		}
		else {
			assert cnt >= 1: x+" "+pos[x]+" "+cnt;
		}
		for ( j = pos[x]; j >= 1 && d[heap[i=(j-1)>>1]] > d[heap[j]]; bubble(i,j), j = i );
		// System.out.println("After pushing "+x+", cnt is "+cnt+", and new position is "+pos[x]);
		assert cnt >= 1;
	}

	int pop() {
		int i,j,x = heap[0];
		assert pos[x] >= 0;
		pos[x] = -1;
		cnt = cnt-1;
		if ( cnt >= 1 ) 
			pos[heap[0]=heap[cnt]] = 0;
		assert cnt >= 0;
		for ( j = 0; ; ) {
			i = j; j <<= 1; ++j;
			if ( j >= cnt ) break ;
			if ( j < cnt-1 && d[heap[j]] > d[heap[j+1]] ) ++j;
			if ( d[heap[i]] <= d[heap[j]] ) break ;
			bubble(i,j);
		}
		assert pos[x] == -1;
		// System.out.println("Retrieving "+x+", remaining "+cnt+" "+peek());
		return x;
	}

	void trap( boolean f ) {
		assert( f );
	}

	class Pair<T extends Comparable<T>,V extends Comparable<V>> implements Comparable<Pair<T,V>> {
		T t;
		V v;
		Pair( T t, V v ) {
			this.t = t;
			this.v = v;
		}
		public int compareTo( Pair<T,V> other ) {
			if ( this.t.compareTo(other.t) == 0 )
				return -this.v.compareTo(other.v);
			return other.t.compareTo(this.t);
		}
	}

	Deque<Integer> q = new LinkedList<>();
	PriorityQueue<Pair<Integer,Integer>> cua, alt;

	int solve() {
		int i,j,k,t;
		for ( computeLast(), cnt = 0, k = 0; k <= n+1; pos[k++] = -1 );
		for ( next[n] = n+1, i = n-1; i >= 1; --i ) {
			if ( h[i+1] > h[i] ) next[i] = i+1;
			else {
				for ( j = next[i+1]; j <= n && j <= last[i]+1 && h[j] <= h[i]; j = next[j] );
				if ( j <= n && j <= last[i]+1 && h[j] > h[i] )
					next[i] = j;
				else next[i] = last[i]+1;
			}
		}
		for ( i = 0; i <= n+1; z[i++] = 0 );
		for ( ;!q.isEmpty(); q.poll() );
		cua = new PriorityQueue<Pair<Integer,Integer>>();
		alt = new PriorityQueue<Pair<Integer,Integer>>();
		for ( z[n+1] = 0, i = n; i >= 1; --i ) {
			int height = h[i]; j = last[i];
			while ( !q.isEmpty() ) {
				int p = q.poll();
				if ( p > j ) break ;
				if ( dins[p] <= height && h[p] <= height ) dins[p] = -1;
				else {
					dins[p] = height;
					cua.add(new Pair<Integer,Integer>(-height-z[p],p));
					q.addFirst(p);
					break ;
				}
			}
			alt.add(new Pair<Integer,Integer>(height,i));
			while ( !alt.isEmpty() && j < alt.peek().v ) alt.poll();
			int hmax = alt.peek().t;
			z[i] = hmax + z[j+1];

			while ( !cua.isEmpty() ) {
				int x = -cua.peek().t;
				int p = cua.peek().v;
				if ( j < p || x != dins[p]+z[p] ) cua.poll();
				else break ;
			}
			if ( !cua.isEmpty() ) z[i] = Math.min(z[i],-cua.peek().t);
			dins[i] = 0;
			cua.add(new Pair<Integer,Integer>(-z[i],i));
			q.addFirst(i);
		}
		return z[1];
	}

	void go() throws Exception {
		int i,j,k;
		for ( int cs = 0, ts = rd(); ts-->0; ) {
			n = rd(); 
			for ( i = 1; i <= n; x[i] = rd(), h[i] = rd(), ++i );
			bw.write("Case "+(++cs)+": "+solve()+"\n");
		}
		bw.flush();
	}
}

