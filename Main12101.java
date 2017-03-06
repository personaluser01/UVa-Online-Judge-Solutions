/*
 * 12101. Prime Path
 * TOPIC: bfs
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = (1<<16);
	boolean []isprime = new boolean[N];
	int []p,seen = new int[N],d = new int[N];
	int m,n,yes;
	public static void main( String [] args ) throws Exception {
		new Main().go();
	};
	void go() throws Exception {
		int i,j,k,ts = scan.nextInt(),src,dst,l,x,y;
		char tmp;
		for ( i = 3; i < N; isprime[i] = true, i += 2 );
		for ( isprime[2] = true, i = 3; i < N; i += 2 )
			for ( j = i+i; j < N && isprime[i]; isprime[j] = false, j += i );
		for ( i = 0; i < N; ++i )
			if ( isprime[i] ) ++m;
		p = new int[m];
		for ( k = 0, i = 0; i < N; ++i )
			if ( isprime[i] ) 
				p[k++] = i;
		assert m == k;
		for ( ;ts-->0; ) {
			src = scan.nextInt();
			dst = scan.nextInt();
			Queue<Integer> q = new LinkedList<Integer>();
			for ( seen[src] = ++yes, d[src] = 0, q.add(src); !q.isEmpty() && seen[dst] != yes; ) {
				x = q.poll();
				char []t = Integer.toString(x).toCharArray();
				for ( i = 0; i < 4; t[i++] = tmp ) 
					for ( tmp = t[i], j = 0; j < 10; ++j ) {
						if ( i == 0 && j == 0 ) continue ;
						for ( t[i] = (char)(j+'0'), y = 0, l = 0; l < 4; y = 10*y+((int)(t[l++]-'0')) );
						if ( isprime[y] && seen[y] != yes ) {
							seen[y] = yes; 
							q.add(y); 
							d[y] = d[x]+1;
						}
					}
			}
			System.out.println(d[dst]);
		};
	};
};

