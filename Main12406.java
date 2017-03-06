/*
 * 12406. Help Dexter
 * TOPIC: bfs
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception { new Main().go(); }
	int enc( int x, int y ) { return x|(y<<5); }
	final int Q = (1<<22);
	boolean []seen = new boolean[Q];
	int BIT( int k ) { return (1<<k); }
	int M( int k ) { return BIT(k)-1; }
	int [] p = new int[Q];
	Queue<Integer> q;
	String smol,larg;
	boolean []mov = new boolean[Q];
	String dump( int u ) {
		int k = u&M(5), r = u>>5;
		StringBuilder sb = new StringBuilder();
		if ( k == 1 ) {
			return mov[u]?"2":"1";
		}
		else {
			sb.append(dump(p[u]));
			if ( mov[u] ) sb.append("2");
			else sb.append("1");
			return sb.toString();
		}
	}
	void go() throws Exception {
		int i,j,k,l,t,ts = scan.nextInt(),cs=0,m,n,u,v,r,nr;
		for(;ts-->0;) {
			m = scan.nextInt();
			n = scan.nextInt();
			System.out.printf("Case %d: ",++cs);
			if ( m == 1 ) {
				if ( n == 1 ) {
					System.out.println("2");
					continue ;
				}
				assert n >= 2;
				System.out.println("impossible");
				continue ;
			}
			assert m >= 2;
			/*
			 * smallest
			 */
			q = new LinkedList<Integer>();
			for ( i = 0; i <= m; ++i )
				for ( j = 0; j < BIT(n); ++j )
					seen[enc(i,j)] = false;
			seen[u=enc(1,1&M(n))]=true; q.add(u); mov[u] = false;
			if ( !seen[v = enc(1,2&M(n))] ) {
				seen[v] = true;
				q.add(v);
				mov[v] = (2==2);
			}
			while ( !q.isEmpty() ) {
				u = q.poll();
				k = u&M(5);
				r = u>>5;
				if ( k >= m ) continue ;
				for ( t = 1; t <= 2; ++t ) 
					if ( !seen[v = enc(k+1,(r*10+t)&M(n))] ) {
						seen[v] = true; p[v] = u;
						q.add(v);
						mov[v] = (t==2);
					}
			}
			if ( !seen[v = enc(m,0)] ) {
				System.out.println("impossible");
				continue ;
			}
			smol = dump(v);

			/*
			 * largest
			 */
			q = new LinkedList<Integer>();
			for ( i = 0; i <= m; ++i )
				for ( j = 0; j < BIT(n); ++j )
					seen[enc(i,j)] = false;
			seen[u = enc(1,2&M(n))] = true; q.add(u); mov[u] = (2==2);
			if ( !seen[v = enc(1,1&M(n))] ) {
				seen[v] = true;
				q.add(v);
				mov[v] = (1==2);
			}
			while ( !q.isEmpty() ) {
				u = q.poll();
				k = u&M(5);
				r = u>>5;
				if ( k >= m ) continue ;
				for ( t = 2; t >= 1; --t ) 
					if ( !seen[v = enc(k+1,(r*10+t)&M(n))] ) {
						seen[v] = true; p[v] = u;
						q.add(v);
						mov[v] = (t==2);
					}
			}
			larg = dump(enc(m,0));
			if ( smol.equals(larg) )
				System.out.println(smol);
			else System.out.println(smol+" "+larg);
		}
	}
};

