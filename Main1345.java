/*
 * 1345. Jamie's Contact Groups
 * TOPIC: maxflow, binary search
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {

	private static int N = 2*0x400, MAXE = (1<<21), oo = (1<<29);
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	Map<String,Integer> names;
	Map<Integer,List<Integer>> lst;
	Scanner scan;
	int []last,next,to,cap,flow,visited,seen,d,c;
	int indeed,yes,E,V,src,sink;
	Queue<Integer> q = new LinkedList<Integer>();

	void addArcs( int x, int y, int cp ) {
		int i = E++, j = E++;
		to[i] = y; next[i] = last[x]; last[x] = i; cap[i] = cp; flow[i] = 0;
		to[j] = x; next[j] = last[y]; last[y] = j; cap[j] = 0; flow[j] = 0;
	}


	{
		last = new int[N];
		next = new int[MAXE];
		to = new int[MAXE];
		cap = new int[MAXE];
		flow = new int[MAXE];
		visited = new int[N];
		seen = new int[N];
		d = new int[N];
	}

	int m,n;

	public static void main( String ... args ) throws Exception {
		new Main().go();
	}

	void go() throws Exception {
		String s;
		int i,j,k,l,low,high,mid;
		while ( (s = br.readLine()) != null ) {
			scan = new Scanner(s);
			n = scan.nextInt();
			m = scan.nextInt();
			if ( m == 0 && n == 0 ) 
				break ;
			names = new HashMap<String,Integer>();
			lst = new HashMap<Integer,List<Integer>>();
			List<Integer> ll;
			for ( l = 0; l < n; ++l ) {
				scan = new Scanner(s = br.readLine());
				lst.put(l,ll = new ArrayList<Integer>());
				for ( names.put(scan.next(),l); scan.hasNext(); ll.add(scan.nextInt()) );
			}
			V = m+n+2; E = 0; src = V-2; sink = V-1; indeed = yes = 0;
			for ( i = 0; i < V; visited[i] = seen[i] = 0, last[i++] = -1 );
			for ( i = 0; i < n; ++i ) {
				for ( Integer t: lst.get(i) )
					addArcs(i,t+n,1);
				addArcs(src,i,1);
			}
			for ( j = 0; j < m; ++j )
				addArcs(j+n,sink,+oo);

			for ( low = 0, high = +oo; low+1 < high; ) {
				mid = (low+high)/2;
				if ( new MaxFlow(mid).maxflow() < n )
					low = mid;
				else high = mid;
			}
			bw.write(high+"\n");
		}
		bw.flush();
	}

	class MaxFlow {
		private int maxCacpacity;

		MaxFlow( int cc ) {
			int i,j,k,x,y;
			maxCacpacity = cc;
			for ( i = 0; i < E; i += 2 ) {
				flow[i] = flow[i^1] = 0;
				x = to[i^1]; y = to[i];
				if ( y == sink && n <= x && x < m+n ) {
					cap[i] = maxCacpacity; 
					cap[i^1] = 0;
				}
				else { cap[i] = 1; cap[i^1] = 0; }
			}
		}

		int capacity( int i ) {
			return cap[i];
		}

		boolean bfs() {
			int x,y,i,j,k;
			for ( visited[sink] = ++indeed, q.add(sink); !q.isEmpty(); )
				for ( i = last[x = q.poll()]; i >= 0; i = next[i] )
					if ( visited[y=to[i]] != indeed || d[y] > d[x]+1 )
						if ( capacity(i^1) > flow[i^1] ) {
							visited[y] = indeed; d[y] = d[x]+1;
							q.add(y);
						}
			return visited[src] == indeed;
		}

		int dfs( int x, int df ) {
			int dt,i,y;
			if ( x == sink )
				return df;
			if ( seen[x] == yes ) return 0;
			for ( seen[x] = yes, i = last[x]; i >= 0; i = next[i] )
				if ( capacity(i) > flow[i] && visited[y = to[i]] == indeed && d[y]+1 == d[x] )
					if ( (dt = dfs(y,Math.min(capacity(i)-flow[i],df))) > 0 ) {
						flow[i] += dt;
						flow[i^1] -= dt;
						return dt;
					}
			return 0;
		}

		int maxflow() {
			int tot = 0,t;
			for ( ;bfs(); )
				for (;++yes > 0 && (t = dfs(src,+oo))>0; tot += t );
			return tot;
		}
	}
}

