/*
 * 13017. Canvas Painting
 * TOPIC: Huffman coding, greedy, priority queue, heap
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = (1<<21);
	int n;
	long []s = new long[N];
	public static void main( String [] args ) throws Exception { new Main().go(); }
	public class Foo implements Comparator<Long> {
		public int compare( Long a, Long b ) {
			if ( a==b ) return 0;
			return a<b?-1:1;
		}
	}
	PriorityQueue<Long> pq;
	void go() throws Exception {
		long i,j,k,ts = scan.nextInt(),res;
		for (;ts-->0;System.out.println(res)) {
			n = scan.nextInt();
			pq = new PriorityQueue(n,new Foo());
			for ( i = 0; i < n; pq.add(s[(int)i++] = scan.nextInt()) );
			for(res=0;pq.size()>1;res+=(i+j),pq.add(i+j)) {
				i=pq.poll();
				j=pq.poll();
			}
		}
	}
};

