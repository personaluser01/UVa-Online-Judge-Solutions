/*
 * 10120. Gift?!
 * status: Accepted
 * TOPIC: maths, induction, bfs
 */
import java.io.*;
import java.util.*;

class Main {
	public static void main( String[] args ) throws Exception {
		new Main().go();
	}
	class State {
		public int x,k;
		State( int x, int k ) { this.x = x; this.k = k; }
		State moveLeft() {
			return new State(this.x-2*this.k+1,this.k+1);
		}
		State moveRight() {
			return new State(this.x+2*this.k-1,this.k+1);
		}
	};
	Map<State,Integer> dist;
	void go() throws Exception {
		int i,j,k,n,m;
		String s;
		StringTokenizer st;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		while ( true ) {
			st = new StringTokenizer(br.readLine());
			n = Integer.parseInt(st.nextToken());
			m = Integer.parseInt(st.nextToken());
			if ( m == 0 && n == 0 ) break ;
			if ( n >= 49 ) {
				System.out.println("Let me try!");
				continue ;
			}
			dist = new HashMap<State,Integer>();
			Queue<State> q = new LinkedList<State>();
			dist.clear();
			State src = new State(0,1);
			dist.put(src,0);
			while ( !q.isEmpty() ) q.remove();
			q.add(src);
			boolean ok = false;
			while ( !q.isEmpty() ) {
				State x = q.remove();
				k = dist.get(x);
				if ( x.x == m ) { ok = true; break ; }
				State px = x.moveLeft();
				State nx = x.moveRight();
				if ( px.x > 0 && !dist.containsKey(px) ) {
					dist.put(px,k+1);
					q.add(px);
				}
				if ( nx.x < n+1 && !dist.containsKey(nx) ) {
					dist.put(nx,k+1);
					q.add(nx);
				}
			}
			if ( ok ) System.out.println("Let me try!");
			else System.out.println("Don't make fun of me!");
		}
	}
};

