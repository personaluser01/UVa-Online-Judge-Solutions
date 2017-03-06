/*
 * 801. Flight Planning
 * TOPIC: dijkstra
 * status:
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final double tol = 1e-9;
	final int VCRUISE = 400, AOPT = 30000, GPHOPT = 200, GPHEXTRA = 10, CLIMBCOST = 50, K = 10;
	int n;
	int [][]wind = new int[K][2];
	int []len = new int[K];
	public static void main( String [] args ) throws Exception { new Main().go(); };
	double getWind( int x, int k ) {
		return wind[k][0]+(wind[k][1]-wind[k][0])*(x-20000)/20000.00;
	};
	Map<State,Double> d;
	class State implements Comparable<State> {
		int k,h;
		State() {};
		State( int k, int h ) { this.k = k; this.h = h; };
		public int compareTo( State other ) {
			double diff = d.get(this)-d.get(other);
			if ( Math.abs(diff) < tol )
				return 0;
			return diff<0?-1:1;
		};
	};
	PriorityQueue<State> pq;
	void dijkstra() {
		State src,dst;
		double cost,velocity,w;
		pq = new PriorityQueue<State>();
		src = new State(0,0);
		dst = new State(n-1,0);
		d = new TreeMap<State,Double>();
		d.put(src,0.00);
		pq.add(src);
		while ( pq.size() > 0 ) {
			State t = pq.poll();
			if ( t.k == n-1 ) {
				continue ;
			}
			w = d.get(t);
			for ( int newheight = 20000; newheight <= 40000; newheight += 1000 ) {
				int dh = newheight-t.h;
				if ( dh > 0 )
					cost += CLIMBCOST*(dh/1000.00);
				else cost = 0;
				dh = Math.abs(AOPT-newheight)/1000;
				velocity = VCRUISE+getWind(newheight,t.k);
				cost += (len[t.k]/velocity)*(dh*GPHEXTRA+GPHOPT);
				State nt = new State(newheight,t.k+1);
				if ( !d.containsKey(nt) || d.get(nt) > cost+w ) {
					d.put(nt,cost+w);
					q.add(nt);
				}
			}
		};
	};
	void go() throws Exception {
		int i,j,k,cs = 0,ts = scan.nextInt();
		for (;ts-->0;) {
			n = scan.nextInt();
			for ( i = 0; i < n; ++i ) {
				len[i] = scan.nextInt();
				wind[i][0] = scan.nextInt();
				wind[i][1] = scan.nextInt();
			}
		}
	};
};

