/*
 * 10858. Unique Factorization
 * TOPIC: stacks, recursion
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	int top,N = 0x400,m;
	int []st = new int[N];
	public static void main( String [] args ) throws Exception { new Main().go(); }
	Queue<String> q;
	void f( int n, int L ) {
		if ( n == 1 ) {
			String s = new String("");
			if ( top == 1 ) return ;
			for ( int i = 1; i < top; ++i ) 
				s += Integer.toString(st[i])+" ";
			if ( top > 0 ) {
				s += Integer.toString(st[top]);
				q.add(s);
			}
			return ;
		}
		for ( int p = L; p <= n; ++p ) 
			if ( 0 == (n%p) ) {
				st[++top] = p;
				f(n/p,p);
				--top;
			}
	}
	void go() throws Exception {
		int n;
		while ( (n=scan.nextInt())!=0 ) {
			q = new LinkedList<String>();
			top = 0;
			f(n,2);
			System.out.println(q.size());
			while ( q.size() > 0 ) {
				String s = q.poll();
				System.out.println(s);
			}
		}
	}
};

