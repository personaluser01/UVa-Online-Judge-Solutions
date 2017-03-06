/*
 * 13079. On the Beach
 * TOPIC: segments, intervals, sweepline, priority queue
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	class Segment implements Comparable<Segment> {
		int x,y;
		Segment( int x, int y ) { this.x = x; this.y = y; };
		public int compareTo( Segment other ) {
			if ( this.x == other.x )
				return this.y-other.y;
			return this.x-other.x;
		};
	};
	Segment []s;
	int n;
	public static void main( String [] args ) throws Exception {
		new Main().go();
	};
	class Event implements Comparable<Event> {
		Segment parent;
		boolean isOpening;
		Event() { parent = null; isOpening = false; };
		Event( Segment s, boolean f ) {
			this.parent = s;
			this.isOpening = f;
		};
		int getWeight() {
			if ( this.isOpening ) return parent.x;
			return parent.y;
		};
		public int compareTo( Event other ) {
			if ( this.getWeight() == other.getWeight() ) {
				if ( this.isOpening == other.isOpening )
					return 0;
				if ( this.isOpening ) 
					return -1;
				return 1;
			}
			return this.getWeight()-other.getWeight();
		};
	};
	PriorityQueue<Event> pq;
	void go() throws Exception {
		int i,j,k,ans,lastStab;
		for(;scan.hasNext(); System.out.println(ans) ) {
			n = scan.nextInt();
			if ( n == 0 ) break ;
			s = new Segment[n];
			for ( i = 0; i < n; ++i ) {
				j = scan.nextInt();
				k = scan.nextInt();
				s[i] = new Segment(j,k);
			}
			pq = new PriorityQueue<Event>();
			for ( i = 0; i < n; ++i )
				pq.add(new Event(s[i],false));
			for ( lastStab=-(int)((1L<<30)-5), ans = 0; !pq.isEmpty(); ) {
				Event e = pq.poll();
				if ( e.isOpening ) {
					pq.add(new Event(e.parent,true));
					continue ;
				}
				if ( e.parent.x >= lastStab ) {
					++ans; lastStab = e.parent.y;
				}
			}
		}
	};
};

