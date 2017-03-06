/*
 * 1048. Low Cost Air Travel
 * TOPIC: dijkstra, nontrivial search space
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = 0x100, M = 0x20, L = 0x20;
	int []len = new int[M], preis = new int[M], c = new int[M], deg = new int[N];
	int [][]fli = new int[M][M];
	int nt,n,V,C,ni;
	TreeMap<Integer,Integer> m;
	public static void main( String [] args ) throws Exception { new Main().go(); }
	class Arrival {
		int x,id,pos,pc;
		Arrival( int x, int id, int pos, int pc ) { this.x = x; this.id = id; this.pos = pos; this.pc = pc; }
	}
	class possibleFlight {
		int y,id;
		possibleFlight( int y, int id ) { this.y = y; this.id = id; }
	}
	int Ins( int x ) {
		if ( !m.containsKey(x) )
			m.put(x,V++);
		return m.get(x);
	}
	possibleFlight [][]adj = new possibleFlight[N][N+N];
	Queue<Arrival> q = new LinkedList<Arrival>();
	Arrival [][][][]parent = new Arrival[N][L][L][L/2];
	int [][][][]d = new int[N][L][L][L/2];
	int bfs() {
		int i,j,k,l,x,y,pc,npc,w = (1<<29);
		for ( x = 0; x < V; ++x )
			for ( i = 0; i <= nt; ++i )
				for ( l = 0; l <= C; ++l )
				for ( j = 0; j <= len[i]; ++j ) {
					d[x][i][j][l] = (1<<29);
					parent[x][i][j][l] = null;
				}
		for ( x = 0; x < V; ++x ) 
			if ( x == c[0] ) {
				q.add(new Arrival(x,nt,0,1));
				d[x][nt][0][1] = 0;
			}
			else {
				continue ;
				/*
				q.add(new Arrival(x,nt,0,0));
				d[x][nt][0][0] = 0;
				*/
			}
		while ( q.size() > 0 ) {
			Arrival a = q.poll();
			x = a.x; j = a.id; pc = a.pc;
			if ( pc == C ) 
				if ( w > d[x][j][a.pos][pc] )
					w = d[x][j][a.pos][pc];
			if ( w <= d[x][j][a.pos][pc] ) 
				continue ;
			for ( i = 0; i < deg[x]; ++i ) {
				possibleFlight f = adj[x][i];
				if ( d[y=f.y][f.id][1][npc=(f.y==c[pc]?pc+1:pc)] > d[x][j][a.pos][pc]+preis[f.id] ) {
					d[y][f.id][1][npc] = d[x][j][a.pos][pc]+preis[f.id];
					parent[y][f.id][1][npc] = new Arrival(a.x,a.id,a.pos,a.pc);
					q.add(new Arrival(y,f.id,1,npc));
				}
			}
			if ( a.pos+1 < len[j] ) {
				y = fli[j][a.pos+1];
				if ( d[y][j][a.pos+1][npc=(y==c[pc]?pc+1:pc)] > d[x][j][a.pos][pc] ) {
					d[y][j][a.pos+1][npc] = d[x][j][a.pos][pc];
					parent[y][j][a.pos+1][npc] = new Arrival(a.x,a.id,a.pos,a.pc);
					q.add(new Arrival(y,j,a.pos+1,npc));
				}
			}
		}
		return w;
	}
	String dump( Arrival a ) {
		if ( a == null || a.id == nt ) return "";
		if ( a.pos == 1 )
			return dump(parent[a.x][a.id][a.pos][a.pc])+" "+Integer.toString(a.id+1);
		else
			return dump(parent[a.x][a.id][a.pos][a.pc]);
	}
	void go() throws Exception {
		int i,j,k,l,x,y,cs = 0,w,cost,id,pos;
		String path;
		while ( (nt=scan.nextInt())!=0 && (++cs) >= 1 ) {
			m = new TreeMap<Integer,Integer>();
			m.clear(); V = 0;
			for ( i = 0; i < N; ++i ) deg[i] = 0;
			for ( len[nt] = i = 0; i < nt; ++i ) {
				preis[i] = scan.nextInt();
				len[i] = scan.nextInt();
				for ( j = 0; j < len[i]; ++j ) 
					fli[i][j] = Ins(scan.nextInt());
				x = fli[i][0]; y = fli[i][1];
				adj[x][deg[x]++] = new possibleFlight(y,i);
			}
			ni = scan.nextInt();
			for ( l = 0; l < ni; ++l ) {
				C = scan.nextInt();
				for ( j = 0; j < C; ++j ) 
					c[j] = Ins(scan.nextInt());
				w = bfs(); cost = (1<<29); path = ""; id = pos = 0;
				for ( i = 0; i <= nt; ++i )
					for ( j = 0; j <= len[i]; ++j )
						if ( cost > d[c[C-1]][i][j][C] ) 
							cost = d[c[C-1]][id = i][pos = j][C];
				path = dump(new Arrival(c[C-1],id,pos,C));
				System.out.printf("Case %d, Trip %d: Cost = ",cs,1+l);
				System.out.println(cost);
				System.out.printf("  Tickets used:");
				System.out.println(path);
			}
		}
	}
};
