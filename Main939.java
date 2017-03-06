/*
 * 939. Genes
 * TOPIC: topological sorting, dag, tree, lazy dp
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = (1<<12);
	Scanner scan = new Scanner(System.in);
	int n,V,E;
	int []s,last,to,next;
	Map<String,Integer> g = new TreeMap<String,Integer>();
	public static void main( String [] args ) throws Exception { new Main().go(); };
	boolean []processed,is_dominant,is_recessive;
	int calc( int x ) {
		int a=-1,b=-1;
		if ( processed[x] ) return s[x];
		for ( int i = last[x]; i >= 0; i = next[i] ) {
			int y = to[i];
			calc(y);
			if ( a == -1 ) a = y;
			else b = y;
		}
		if ( (is_dominant[a]&&is_dominant[b]) || (is_dominant[a]&&is_recessive[b]) || (is_recessive[a]&&is_dominant[b]) )
			is_dominant[x] = true;
		else if ( is_recessive[a]&&is_recessive[b] || is_dominant[a] || is_dominant[b] )
			is_recessive[x] = true;
		processed[x] = true ;
		return s[x];
	};
	void go() throws Exception {
		Map<String,Integer> m;
		int i,j,k,t,l;
		g.put("non-existent",0);
		g.put("recessive",1);
		g.put("dominant",2);
		while ( scan.hasNext() ) {
			n = scan.nextInt(); V = E = 0;
			m = new TreeMap<String,Integer>();
			processed = new boolean[n+1];
			is_dominant = new boolean[n+1];
			is_recessive = new boolean[n+1];
			s = new int[n+1];
			last = new int[n+1];
			to = new int[N+N];
			next = new int[N+N];
			for ( i = 0; i < n; last[i++] = -1 );
			for ( i = 0; i < n; ++i ) {
				String a = scan.next(), b = scan.next();
				if ( !m.containsKey(a) ) m.put(a,V++);
				j = m.get(a);
				if ( !b.equals("non-existent") && !b.equals("recessive") && !b.equals("dominant") ) {
					if ( !m.containsKey(b) ) m.put(b,V++);
					k = m.get(b);
					t = E++;
					to[t] = j; next[t] = last[k]; last[k] = t;
				}
				else {
					k = g.get(b);
					processed[j] = true ;
					s[j] |= k;
					if ( k == 1 )
						is_recessive[j] = true ;
					else if ( k == 2 )
						is_dominant[j] = true ;
				}
			}
			for ( i = 0; i < V; ++i )
				if ( !processed[i] ) calc(i);
			for ( Map.Entry<String,Integer> entry: m.entrySet() ) {
				System.out.print(entry.getKey()+" ");
				i = entry.getValue();
				if ( !is_recessive[i] && !is_dominant[i] )
					System.out.println("non-existent");
				else if ( is_recessive[i] )
					System.out.println("recessive");
				else System.out.println("dominant");
			}
		}
	};
};

