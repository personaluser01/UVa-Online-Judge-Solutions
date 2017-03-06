/*
 * 257. Palinwords
 * TOPIC:
 * status:
 */
import java.io.*;
import java.util.*;

class Main {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	final int A = 26;
	String s,t;
	StringTokenizer st;
	char []c = new char[0x400];
	int cnt;
	boolean ispalin( int i, int j ) {
		int k,t;
		if ( j-i+1 < 3 ) return false;
		for ( k = i, t = j; k < t; ++k, --t )
			if ( c[k] != c[t] )
				return  false;
		return true;
	}
	boolean eq( int i, int j, int k, int t ) {
		if ( j-i != t-k )
			return false;
		for ( ;i <= j; ++i, ++k )
			if ( c[i] != c[k] )
				return false;
		return true;
	}
	Set<String> q;
	Cell root,sink;
	boolean [][]g;
	class Cell {
		int ch,id,IDX;
		Cell []son;
		Cell parent,link;
		Set<Integer> q;
		Cell ( int ch, Cell p, int id ) {
			this.ch = ch;
			this.son = new Cell[A];
			this.parent = p;
			q = new HashSet<Integer>();
			this.link = null;
			this.id = id;
			for ( int i = 0; i < A; ++i )
				this.son[i] = null;
		}
	}
	void push( String s, int idx ) {
		Cell x,y;
		int i,j,k,n;
		char []a = new char[n=s.length()];
		for ( i = 0; i < n; ++i ) a[i] = s.charAt(i);
		for ( x = root, i = 0; i < n; ++i, x = y ) 
			if ( (y=x.son[k=(int)(a[i]-'A')]) == null ) {
				x.son[k] = y = new Cell(k,x,cnt++);
			}
		x.q.add(idx);
		x.IDX = idx;
	}
	void sufLinks() {
		Queue<Cell> q = new LinkedList<Cell>();
		Cell x,y;
		int i,j,k;
		for ( i = 0; i < A; ++i )
			if ( root.son[i] != null )
				q.add(root.son[i]);
		for ( ;q.size() > 0; ) {
			for ( x = (Cell)q.poll(), i = 0; i < A; ++i ) 
				if ( x.son[i] != null )
					q.add(x.son[i]);
			//System.out.println(x.ch);
			for ( y = x.parent.link; y.son[x.ch] == null; y = y.link );
			x.link = y.son[x.ch];
			Iterator<Integer> it = x.link.q.iterator();
			//System.out.println(x.id+" "+x.link.id);
			for(;it.hasNext();x.q.add(k=it.next()));
		}
	}
	void traverse( String s, int idx ) {
		Cell x,y;
		int i,j,k,n;
		char []a = new char[n=s.length()];
		// System.out.println(s);
		for ( i = 0; i < n; ++i ) a[i] = s.charAt(i);
		for ( x = root, i = 0; i < n; ++i, x = y ) {
			if ( (y=x.son[k=(int)(a[i]-'A')])==null ) {
				assert 0 == 1;
			}
			for ( Iterator<Integer> it = y.q.iterator(); it.hasNext(); g[idx][it.next()] = true );
		}
	}
	boolean f( String s ) {
		int i,j,k,l,n = s.length(),m;
		String t;
		c = s.toCharArray();
		q = new TreeSet<String>();
		for ( i = 0; i < n; ++i ) {
			for ( k = i-1, l = i+1; k >= 0 && l < n && c[k]==c[l]; --k, ++l )
				if ( (l-k+1) >= 3 )
					q.add(s.substring(k,l+1));
			m = l-k+1-2;
			if ( m < 3 ) continue ;
			q.add(s.substring(k+1,l));
		}
		for ( i = 0; i < n; ++i ) {
			for ( k = i, l = i+1; k >= 0 && l < n && c[k] == c[l]; --k, ++l )
				if ( (l-k+1) >= 3 )
					q.add(s.substring(k,l+1));
			m = l-k+1-2;
			if ( m < 3 ) continue ;
			q.add(s.substring(k+1,l));
		}
		root = new Cell('$',null,-1);
		sink = new Cell('#',null,-2);
		for ( i = 0; i < A; sink.son[i++] = root );
		sink.parent = sink.link = sink;
		root.parent = root; 
		root.link = sink;
		Iterator<String> it = q.iterator();
		cnt = 0;
		for ( k = 0; it.hasNext(); push(it.next(),k++) );
		sufLinks();
		m = q.size();
		g = new boolean[m][m];
		for ( k = 0, it = q.iterator(); it.hasNext();)
			traverse(it.next(),k++);
		assert k == m;
		for ( i = 0; i < m; ++i )
			for ( j = i+1; j < m; ++j )
				if ( !g[i][j] && !g[j][i] )
					return true;
		return false;
	}
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		for ( ;(s = br.readLine()) != null; ) 
			for ( st = new StringTokenizer(s); st.hasMoreTokens(); ) 
				if ( f(t=st.nextToken()) )
					System.out.println(t);
	}
};

