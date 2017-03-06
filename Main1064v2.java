/*
 * 1064. Network
 * TOPIC:
 * status:
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = 8, M = 0x400, oo = (1<<29);
	public static void main( String [] args ) throws Exception { new Main().go(); }
	int []sz = new int[N], which = new int[1<<N], c = new int[N], last = new int[N];
	int m,n,cs,ans,mask,bufsize,idx;
	class Packet implements Comparable<Packet> {
		int id,left,right;
		Packet( int id, int left, int right ) { this.id = id; this.left = left; this.right = right; }
		Packet merge(Packet other) {
			assert this.id == other.id;
			assert this.right+1 == other.left;
			return new Packet(this.id,this.left,other.right);
		}
		int size() { return this.right-this.left+1; }
		public int compareTo( Packet other ) {
			if ( this.id == other.id ) {
				if ( this.left == other.left ) {
					if ( this.right == other.right ) 
						return 0;
					return this.right < other.right?-1:1;
				}
				return this.left < other.left?-1:1;
			}
			return this.id < other.id?-1:1;
		}
	}

	Packet []p = new Packet[M];
	List<Packet> a;

	int B( int k ) { return (1<<k); }
	int L( int k ) { return ((k)&((~(k))+1)); }
	int MASK( int k ) { return B(k)-1; }
	int who( int u ) { return which[L(u)]; }

	void pushMerge( Packet e ) {
		Iterator<Packet> it,jt;
		boolean up;
		Packet x = null,y = null, z = null;
		for ( a.add(e), bufsize += e.size(), up = true; up; ) {
			for ( up = false, it = a.iterator(); it.hasNext() && !up; )
				for ( x = it.next(), jt = a.iterator(); jt.hasNext() && !up; ) 
					if ( x.right+1==(y=jt.next()).left && x.id==y.id )
						up = true;
			if ( up ) { a.remove(x); a.remove(y); a.add(z=x.merge(y)); }
		}
	}

	void traverse() {
		// System.out.println("[out] "+(c[idx-1]+1)+", bufsize "+bufsize);
		Iterator<Packet> it;
		Packet e;
		boolean up;
		//System.out.println("Has passed into out-area "+c[idx-1]+", bufsize = "+bufsize);
		for ( up = true; up; ) {
			for (up=false;idx<n&&a.contains(e=new Packet(c[idx],1,sz[c[idx]]));a.remove(e),bufsize-=e.size(),++idx);
			for ( it = a.iterator(); idx < n && it.hasNext(); ) 
				if ( (e = it.next()).id == c[idx] && e.left == last[c[idx]]+1 ) {
					last[c[idx]] = e.right;
					a.remove(e); bufsize -= e.size();
					up = true;
					break ;
				}
			if ( idx < n && last[c[idx]] == sz[c[idx]] ) { ++idx; up = true; }
		}
	}

	int f() {
		int i,j,k,w = -1;
		Iterator<Packet> it;
		Packet x = null;
		a = new ArrayList<Packet>();
		for ( i = 0; i < n; last[i++] = 0 );
		boolean up;
		/*
		for ( i = 0; i < n; ++i )
			System.out.print(c[i]+" ");
		System.out.println();
		*/
		for ( idx = 0, bufsize = 0, i = 0; i < m; ++i, w = Math.max(w,bufsize) ) 
			if ( p[i].id == c[idx] && p[i].left == last[c[idx]]+1 ) {
				if ( (last[c[idx]] = p[i].right) == sz[c[idx]] ) { ++idx; traverse(); }
				else for ( it = a.iterator(); it.hasNext(); ) {
					if ( (x=it.next()).id==c[idx] && x.left==last[c[idx]]+1 ) {
						a.remove(x); bufsize -= x.size();
						if ( (last[c[idx]] = x.right) == sz[c[idx]] ) { ++idx; traverse(); }
						break ;
					}
				}
			}
			else pushMerge(p[i]);
		/*
		for ( idx = 0, bufsize = 0, i = 0; i < m; ++i, w = Math.max(w,bufsize) )
			for ( pushMerge(p[i]), up = true; up; ) {
				for ( up = false, it = a.iterator(); it.hasNext() && !up; )
					if ( (x=it.next()).id == c[idx] && x.left == 1 ) 
						up = true;
				if ( up ) { a.remove(x); bufsize -= x.size(); }
				if ( up && x.right == sz[c[idx]] ) ++idx;
			}
			*/
		return w;
	}

	void rec( int k ) {
		int u,i;
		if ( k == n ) { 
			ans = Math.min(ans,f()); return ; 
		}
		for(u=((~mask)&MASK(n));u>0&&(i=who(u))>=0;mask|=B(i),c[k]=i,rec(k+1),mask&=~B(i),u&=~L(u));
	}

	void go() throws Exception {
		int i,j,k,l,t;
		for ( i = 0; i < N; which[B(i)] = i, ++i );
		for (;;) {
			n = scan.nextInt();
			m = scan.nextInt();
			if ( m == 0 && n == 0 ) break ;
			for ( i = 0; i < n; sz[i++] = scan.nextInt() );
			for ( i = 0; i < m; ++i ) {
				k = scan.nextInt()-1;
				j = scan.nextInt();
				t = scan.nextInt();
				p[i] = new Packet(k,j,t);
			}
			ans = +oo; rec(0);
			System.out.println("Case "+(++cs)+": "+ans+"\n");
		}
	}
};

