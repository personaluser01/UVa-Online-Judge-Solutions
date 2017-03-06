/*
 * 12100. Printer Queue
 * TOPIC: simulation, easy, queue
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	int m,n,N = 0x400,head,tail,sz,tick;
	int []cnt = new int[N],weight = new int[N],q = new int[N], t = new int[N];
	public static void main ( String [] args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		Scanner scan = new Scanner(System.in);
		int i,j,k,ts;
		for ( ts = scan.nextInt(); ts-- > 0; ) {
			n = scan.nextInt();
			m = scan.nextInt();
			for ( i = 0; i < N; cnt[i++] = 0 );
			for ( i = 0; i < n; ++i ) 
				++cnt[weight[i] = scan.nextInt()];
			head = tail = sz = 0;
			for ( i = 0; i < n; ++i ) {
				q[tail] = i; tail = (tail+1)&(N-1); ++sz;
			}
			for ( tick = 0; sz > 0; ) {
				i = q[head]; head = (head+1)&(N-1); --sz;
				for ( j = weight[i]+1; j <= 100; ++j )
					if ( cnt[j] > 0 ) break ;
				if ( j == 101 ) {
					t[i] = ++tick;
					--cnt[weight[i]];
					continue ;
				}
				q[tail] = i; tail = (tail+1)&(N-1); ++sz;
			}
			System.out.println(t[m]);
		}
	}
};

