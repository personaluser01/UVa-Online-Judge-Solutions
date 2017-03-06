/*
 * 1556. Disk Tree
 * TOPIC: regex, dfs, graphs
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	class Dir implements Comparable<Dir> {
		String nm,fp;
		int level,idx,line_no;
		boolean visited;
		Dir() {};
		Set<Dir> adj;
		Dir( String nm, int level, int idx, String fp ) {
			this.nm = nm; this.level = level; this.fp = fp;
			this.adj = new TreeSet<Dir>();
			this.idx = idx; this.visited = false ;
		};
		public int compareTo( Dir other ) {
			if ( this.level == other.level ) {
				if ( 0 == this.nm.compareTo(other.nm) ) 
					return this.fp.compareTo(other.fp);
				return this.nm.compareTo(other.nm);
			}
			return this.level-other.level;
		};
		void addSon( Dir d ) {
			this.adj.add(d);
		};
	};
	final int N = (1<<20);
	int n,E,V,top,yes;
	int []to = new int[N], next = new int[N], last = new int[N], seen = new int[N], st = new int[N];
	Dir []u = new Dir[N];
	//Pattern dirname = Pattern.compile("([A-Z0-9!#\\$%&'\\(\\)\\-@\\^_`\\{\\}~]+)");
	Pattern dirname = Pattern.compile("([^\\s\\\\]+)");
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	void addArcs( int x, int y ) {
		int i = E++;
		to[i] = y; next[i] = last[x]; last[x] = i;
	}
	void dfs( Dir x ) {
		if ( x.visited ) return ;
		x.visited = true ;
		for ( Iterator<Dir> it = x.adj.iterator(); it.hasNext(); dfs(it.next()) );
		st[++top] = x.idx;
	}
	void f( Dir x, int SH, StringBuilder sb ) {
		if ( seen[x.idx] == yes ) return ;
		seen[x.idx] = yes;
		for ( int k = 0; k < SH; sb.append(" "), ++k );
		sb.append(x.nm+"\n");
		for ( Iterator<Dir> it = x.adj.iterator(); it.hasNext(); f(it.next(),SH+1,sb) );
	}
	void go() throws Exception {
		int i,j,k,ts,level;
		String s,t;
		Dir tmp;
		Map<Dir,Integer> m;
		for ( ;(s=br.readLine())!=null; br.readLine(), System.out.println("") ) {
			n = Integer.parseInt(s);
			m = new TreeMap<Dir,Integer>();
			for ( E = V = 0, i = 0; i < N; last[i++] = -1 );
			for (;n-->0;) {
				Matcher mt = dirname.matcher(s = new StringTokenizer(br.readLine()).nextToken());
				for ( level = 0, top = 0; mt.find(); st[++top] = m.get(tmp) ) 
					if ( !m.containsKey(tmp = new Dir(t=mt.group(1),top,0,s.substring(0,mt.start(1)))) ) {
						m.put(tmp,V++);
						u[tmp.idx = V-1] = tmp;
					}
				for ( i = 1; i <= top-1; addArcs(st[i],st[i+1]), u[st[i]].addSon(u[st[i+1]]), ++i );
			}
			top = 0;
			for ( Map.Entry<Dir,Integer> entry: m.entrySet() ) 
				if ( !entry.getKey().visited ) dfs(entry.getKey());
			Set<String> S = new TreeSet<String>();
			for ( ++yes; top > 0; )
				if ( seen[i=st[top--]]!=yes ) {
					StringBuilder sb = new StringBuilder();
					f(u[i],0,sb);
					S.add(sb.toString());
				}
			for ( Iterator<String> it = S.iterator(); it.hasNext(); System.out.print(it.next()) );
		}
	}
};

