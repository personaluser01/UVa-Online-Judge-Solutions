/*
 * 1346. Songs
 * TOPIC: greedy
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	int n;
	Song []s;
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	class Song implements Comparable<Song> {
		int id,len;
		double freq;
		Song() {};
		Song( int id, int len, double freq ) {
			this.id = id; this.len = len; this.freq = freq;
		}
		public int compareTo( Song other ) {
			//if ( this.freq > other.freq ) return -1;
			//if ( this.freq < other.freq ) return 1;
			double r = other.freq*this.len-other.len*this.freq;
			if ( Math.abs(r) < 1e-9 )
				return 0;
			return r<0?-1:1;
		};
	}
	void go() throws Exception {
		int i,j,k,l,t;
		double g;
		while ( scan.hasNext() ) {
			n = scan.nextInt();
			s = new Song[n];
			for ( i = 0; i < n; ++i ) {
				j = scan.nextInt();
				k = scan.nextInt();
				g = scan.nextDouble();
				s[i] = new Song(j,k,g);
			}
			Arrays.sort(s);
			i = scan.nextInt();
			System.out.println(s[i-1].id);
		}
	}
};

