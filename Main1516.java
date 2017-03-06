/*
 * 1516. Smoking Gun
 * TOPIC: shortest paths, system of constraints, clrs, bellman-ford
 * status: surprisingly wa
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;
import java.text.*;

class Main {

	private final static int SH = 7, N = (1<<SH), MASK = (N-1), MAXE = (1<<14);
	private final static double oo = Double.MAX_VALUE-0x400, tol = 1e-9, eps = 1e-11;
	Pattern p = Pattern.compile("([A-Za-z]+)\\s+heard\\s+([A-Za-z]+)\\s+firing\\s+before\\s+([A-Za-z]+)");
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	Map<String,Integer> h;
	String []names = new String[N];
	double []xx = new double[N], yy = new double[N];
	int []x = new int[MAXE], y = new int[MAXE], parent = new int[N];
	double []cost = new double[MAXE], d = new double[N];
	double [][]w = new double[N][N];
	boolean []isMentioned = new boolean[N];
	int n,m,src,V,E;

	static double S( double x ) { return x*x; }

	public static void main( String ... args ) throws Exception {
		new Main().go();
	}

	boolean negCycleExists() {
		int i,j;
		boolean flag;
		for ( i = 0; i < V; d[i++] = +oo );
		for ( d[src] = 0.00, flag = true, j = 0; j < V && flag; ++j )
			for ( flag = false, i = 0; i < E; ++i )
				if ( d[x[i]] < +oo && d[y[i]] > d[x[i]]+cost[i] ) {
					d[y[i]] = d[x[i]]+cost[i];
					flag = true ;
					parent[y[i]] = i;
				}
		for ( i = 0; i < E; ++i )
			if ( d[x[i]] < +oo && d[y[i]] > d[x[i]]+cost[i] ) 
				return true ;
		return false ;
	}

	private class Pair {
		String name;
		double weight;
		Pair( String name, double weight ) {
			this.name = name;
			this.weight = weight;
		}
	}

	private class PairSrt implements Comparator<Pair> {
		public int compare( Pair a, Pair b ) {
			if ( Math.abs(a.weight-b.weight) < tol )
				return 0;
			return a.weight<b.weight?-1:1;
		}
	}

	void go() throws Exception {
		int i,j = 0,k = 0,l;
		boolean impossible = false, unknown;
		List<Pair> pairs;
		for ( int ts = Integer.parseInt(br.readLine()); ts-->0; ) {
			h = new HashMap<String,Integer>();
			Scanner scan = new Scanner(br.readLine());
			n = scan.nextInt();
			m = scan.nextInt();
			for ( i = 0; i < n; isMentioned[i++] = false );
			for ( i = 0; i < n; ++i ) {
				scan = new Scanner(br.readLine());
				h.put(names[i] = scan.next(),i);
				xx[i] = scan.nextDouble();
				yy[i] = scan.nextDouble();
			}
			for ( i = 0; i < n; ++i ) for ( j = i+1; j < n; ++j ) w[i][j] = w[j][i] = Math.sqrt(S(xx[i]-xx[j])+S(yy[i]-yy[j]));
			for ( l = 0; l < m; ++l ) {
				Matcher mt = p.matcher(br.readLine());
				if ( mt.find() ) {
					i = h.get(mt.group(1));
					y[l] = j = h.get(mt.group(2));
					x[l] = k = h.get(mt.group(3));
					isMentioned[j] = isMentioned[k] = true ;
					cost[l] = (w[i][k]-w[i][j])/340.00;
				}
				else {
					int trap = 1/0;
				}
			}
			for ( E = m, src = n, V = n+1, i = 0; i < n; ++i )
				if ( isMentioned[i] ) {
					x[E] = src; y[E] = i; cost[E++] = 0;
				}
			if ( negCycleExists() ) {
				bw.write("IMPOSSIBLE\n");
				continue ;
			}
			/*
			for ( impossible = false, i = 0; i < m && !impossible; ++i ) {
				assert d[y[i]]-d[x[i]] <= cost[i];
				if ( Math.abs(d[y[i]]-d[x[i]]-cost[i]) < tol ) 
					impossible = true ;
			}
			*/
			if ( impossible ) {
				bw.write("IMPOSSIBLE\n");
				continue ;
			}
			for ( unknown = false, i = 0; i < n && !unknown; ++i )
				for ( j = i+1; j < n && !unknown && isMentioned[i]; ++j )
					if ( isMentioned[j] && d[i] < +oo && d[j] < +oo && Math.abs(d[i]-d[j]) < tol ) 
						unknown = true ;
			if ( unknown ) {
				bw.write("UNKNOWN\n");
				continue ;
			}
			pairs = new ArrayList<>();
			for ( i = 0; i < n; ++i )
				if ( isMentioned[i] )
					pairs.add(new Pair(names[i],d[i]));
			Collections.sort(pairs,new PairSrt());
			for ( i = 0; i < pairs.size(); ++i ) 
				bw.write(pairs.get(i).name+(i==pairs.size()-1?"\n":" "));
			/*
			for ( i = 0; i < pairs.size(); ++i )
				bw.write(pairs.get(i).weight+(i==pairs.size()-1?"\n":" "));
			*/
		}
		bw.flush();
	}
};
