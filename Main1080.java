/*
 * 1080. My Bad
 * TOPIC: topological sort, simulation, neat, iron logic
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	final int N = 0x80, ALWAYS_0 = 0, ALWAYS_1 = 1, INVERTER = 2;
	int ts = 0,m,n,gates,outputs,yes,cur,status;
	char[]typ = new char[N];
   	int	[]which = new int[1<<21];
	int [][][]adj = new int[2][N][N];
	int [][]inp = new int[N][2], deg = new int[2][N], ii = new int[512][N], o = new int[512][N];
	int []u = new int[N], tr = new int[N], seen = new int[N], v = new int[N], diagnosis = new int[N];
	Stack<Integer> S = new Stack<Integer>();
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	StringTokenizer st;
	void noFaults() { System.out.println("No faults detected"); }
	void cannotClassify() { System.out.println("Unable to totally classify the failure"); };
	void inverter( int i ) { System.out.println("Gate "+(i+1)+" is failing; output inverted"); };
	void stuckAt0( int i ) { System.out.println("Gate "+(i+1)+" is failing; output stuck at 0"); };
	void stuckAt1( int i ) { System.out.println("Gate "+(i+1)+" is failing; output stuck at 1"); };
	public static void main( String [] args ) throws Exception { new Main().go(); };
	int process( String s ) {
		if ( s.charAt(0)=='i' ) 
			return 0|((Integer.parseInt(s.substring(1))-1)<<1);
		else 
			return 1|((Integer.parseInt(s.substring(1))-1)<<1);
	};
	void add_arcs( int x, int y ) {
		adj[1][x][deg[1][x]++] = y;
		adj[0][y][deg[0][y]++] = x;
	};
	void dfs( int x, int t ) {
		int y,i;
		if ( seen[x] == yes ) return ;
		for ( seen[x] = yes, i = 0; i < deg[t][x]; ++i ) 
			if ( seen[y=adj[t][x][i]] != yes )
				dfs(y,t);
		S.push(x);
	};
	int op( char ch, int x, int y ) {
		switch ( ch ) {
			case 'a': return x&y;
			case 'o': return x|y;
			default: break;
		};
		return x^y;
	};
	void eval( int []val, int []out ) {
		int i,j,k,x,y;
		int []w = new int[N];
		for ( ++yes, i = 0; i < m; seen[x] = yes, ++i ) 
			if ( 0 == ((x=v[i])&1) ) 
				w[x] = val[x>>1];
			else {
				if ( typ[x>>1] == 'n' ) 
					w[x] = 1^w[adj[1][x][0]];
				else w[x] = op(typ[x>>1],w[adj[1][x][0]],w[adj[1][x][1]]);
				if ( cur == (x>>1) ) {
					if ( status == INVERTER ) 
						w[x] ^= 1;
					else if ( status == ALWAYS_0 )
						w[x] = 0;
					else if ( status == ALWAYS_1 )
						w[x] = 1;
				}
				for ( j = 0; j < deg[1][x]; ++j ) 
					if ( seen[adj[1][x][j]] != yes )
						x = 1/0;
			};
		for ( i = 0; i < outputs; ++i ) {
			if ( seen[u[i]] != yes ) x = 1/0;
			out[i] = w[u[i]];
		};
	};
	void go() throws Exception {
		String s;
		int i,j,k,t,observations,x,y,mask,U;
		boolean []incorrect = new boolean[N], is_inverter = new boolean[N];
		for ( i = 0; i < 21; ++i ) which[1<<i] = i;
		while ( (s = br.readLine()) != null ) {
			st = new StringTokenizer(s);
			n = Integer.parseInt(st.nextToken());
			gates = Integer.parseInt(st.nextToken());
			outputs = Integer.parseInt(st.nextToken());
			if ( n == 0 && gates == 0 && outputs == 0 )
				break ;
			System.out.print("Case "+(++ts)+": ");
			for ( t = 0; t <= 1; ++t )
				for ( i = 0; i < gates; ++i )
					deg[t][1|(i<<1)] = 0;
			for ( t = 0; t <= 1; ++t )
				for ( j = 0; j < n; ++j )
					deg[t][0|(j<<1)] = 0;
			for ( i = 0; i < gates; ++i ) {
				x = 1|(i<<1);
				st = new StringTokenizer(s = br.readLine());
				typ[i] = st.nextToken().charAt(0);
				if ( typ[i] == 'n' ) 
					add_arcs(x,inp[i][0] = process(st.nextToken()));
				else {
					add_arcs(x,inp[i][0] = process(st.nextToken()));
					add_arcs(x,inp[i][1] = process(st.nextToken()));
				}
			};
			for ( ++yes, i = 0; i < n; dfs(0|(i<<1),0), ++i );
			for ( j = 0; j < gates; dfs(1|(j<<1),0), ++j );
			for ( m = 0; !S.empty(); v[m++] = S.pop() );
			for ( st=new StringTokenizer(s=br.readLine()), i=0; i<outputs; u[i++]=1|((Integer.parseInt(st.nextToken())-1)<<1) );
			observations = Integer.parseInt(br.readLine());
			boolean ok = true ;
			for ( cur = -1, U = 0, k = 0; k < observations; ++k ) {
				st = new StringTokenizer(br.readLine());
				for ( i = 0; i < n; ++i )
					ii[k][i] = Integer.parseInt(st.nextToken());
				for ( j = 0; j < outputs; ++j )
					o[k][j] = Integer.parseInt(st.nextToken());
				for ( eval(ii[k],tr), i = 0; i < outputs && ok; ++i )
					if ( o[k][i] != tr[i] ) ok = false ;
			};
			if ( ok ) { noFaults(); continue ; }
			for ( cur = 0; cur < gates; ++cur ) {
				for ( diagnosis[cur]=-1, mask=0, status=ALWAYS_0; status<=INVERTER+1; ++status ) {
					for ( ok=true, k = 0; k < observations && ok; ++k ) 
						for ( eval(ii[k],tr), i = 0; i < outputs && ok; ++i )
							if ( tr[i] != o[k][i] ) ok = false ;
					if ( ok ) mask |= (1<<status);
				};
				if ( mask != 0 && 0 == (mask&(mask-1)) && 0 == (mask>>(INVERTER+1)) ) {
					diagnosis[cur] = which[mask];
					U|=(1<<cur);
				};
			};
			if ( U == 0 || 0 != (U&(U-1)) ) { cannotClassify(); continue ; };
			i = which[U];
			if ( diagnosis[i] == INVERTER ) inverter(i);
			else if ( diagnosis[i] == ALWAYS_0 ) stuckAt0(i);
			else stuckAt1(i);
		};
	};
};

