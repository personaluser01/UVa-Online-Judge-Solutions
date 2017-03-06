/*
 * 1513. Movie Collection
 * TOPIC: stacks, interval data, segment tree, interval tree, lazy propagation
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	java.io.Reader r = new InputStreamReader(System.in);
	private static final int N = (1<<17), Q = (N<<4);
	int n;
	int []pos = new int[Q];
	long[]tr = new long[Q], h = new long[Q];
	int rd() throws IOException {
		int n = 0,c;
		for (;(c=r.read())!=-1 && !('0'<=(char)c&&(char)c<='9'); );
		for ( n=c-'0'; (c=r.read())!=-1&&'0'<=(char)c&&(char)c<='9'; n=10*n+c-'0' );
		return n;
	}
	public static void main( String ... args ) throws Exception {
		new Main().go();
	}
	long buildTree( int v, int i, int j, int m ) {
		if ( i == j ) {
			tr[v] = (i>=m?1:0); h[v] = 0;
			return tr[v];
		}
		int k = (i+j)/2;
		h[v] = 0;
		return tr[v] = buildTree(2*v,i,k,m)+buildTree(2*v+1,k+1,j,m);
	}
	long query( int v, int i, int j, int qi, int qj ) {
		int k = (i+j)/2;
		if ( qi > qj || qi > j || qj < i ) return 0;
		if ( i < j && h[v] != 0 ) {
			assert (h[v]%(j-i+1)) == 0;
			h[2*v] += h[v]/(j-i+1)*(k-i+1);
			h[2*v+1] += h[v]/(j-i+1)*(j-k);
			h[v] = 0;
		}
		if ( h[v] != 0 ) { tr[v] += h[v]; h[v] = 0; }
		assert h[v] == 0: "This: "+h[v];
		if ( qi <= i && j <= qj ) 
			return tr[v];
		return query(2*v,i,k,qi,qj)+query(2*v+1,k+1,j,qi,qj);
	}
	void update( int v, int i, int j, int qi, int qj, int dv ) {
		int k = (i+j)/2;
		if ( qi > qj || qi > j || qj < i ) return ;
		if ( qi <= i && j <= qj ) {
			h[v] += dv*(j-i+1); 
			tr[v] += h[v]; h[v] = 0;
			return ;
		}
		update(2*v,i,k,qi,qj,dv); update(2*v+1,k+1,j,qi,qj,dv);
		tr[v] = tr[2*v]+tr[2*v+1];
	}
	void go() throws Exception {
		int i,j,k,qr,m,cur;
		for ( int ts = rd(); ts-->0;) {
			n = rd(); m = qr = rd();
			cur = m-1;
			buildTree(1,0,n+m-1,m);
			for ( i = m; i < m+n; pos[i-m] = i, ++i );
			for (;qr-->0;) {
				j = pos[i = rd()-1];
				k = (int)query(1,0,m+n-1,0,j-1);
				update(1,0,n+m-1,j,j,-1);
				assert query(1,0,m+n-1,j,j) == 0;
				bw.write(k+(qr==0?"\n":" "));
				pos[i] = cur--;
				assert query(1,0,m+n-1,pos[i],pos[i]) == 0;
				update(1,0,n+m-1,pos[i],pos[i],1);
				assert query(1,0,m+n-1,pos[i],pos[i]) == 1;
			}
			assert cur == -1;
		}
		bw.flush();
	}
}

