/*
 * 1048. Low Cost Air Travel
 * TOPIC:
 * status:
 */
import java.io.*;
import java.util.*;

class Main {
	final int M = 0x100, L = 0x30;
	int V,E,C,nt;
	int []p = new int[L],len = new int[L],c = new int[L],deg = new int[M];
	int [][]idx = new int[L][M],fli = new int[L][L];
    int [][][]d = new int[M][L][L];
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception { new Main().go(); }
	class Flight {
		int x,y,ticket_id,w;
		Flight( int x, int y, int id, int w ) { this.x=x; this.y=y; this.ticket_id=id; this.w=w; }
	}
	Flight [][]adj = new Flight[M][M+M+M];
	TreeMap<Integer,Integer> m;
	int Ins( int x ) {
		if ( m.containsKey(x) )
			return m.get(x);
		m.put(x,V++);
		return V-1;
	}
	class Arr {
		int x,part_covered,ticket_id;
		Arr( int x, int pc, int id ) { this.x = x; this.part_covered = pc; this.ticket_id = id; }
	}
	Arr [][][]parent = new Arr[M][L][L];
	Queue<Arr> q = new LinkedList<Arr>();
	String ticketsUsed( int x, int pc, int ticket_id ) {
		if ( ticket_id == nt )
			return "";
		return ticketsUsed(parent[x][pc][ticket_id].x,parent[x][pc][ticket_id].part_covered,parent[x][pc][ticket_id].ticket_id)+" "+Integer.toString(ticket_id+1);
	}
	int bfs() {
		int x,y,i,j,k,w = (1<<29),l,pc,npc;
		for(x=0;x<V;++x)
			for ( i = 0; i <= nt; ++i )
				for ( k = 0; k <= C; ++k ) {
					parent[x][k][i] = null;
					d[x][k][i] = (1<<29);
				}
		for ( x = 0; x < V; ++x ) 
			if ( x == c[0] ) {
				d[x][1][nt] = 0;
				q.add(new Arr(x,1,nt));
			}
			else {
				d[x][0][nt] = 0;
				q.add(new Arr(x,0,nt));
			}
		for(;q.size()>0;) {
			Arr a = q.poll();
			x = a.x; pc = a.part_covered; j = a.ticket_id;
			if ( x == c[C-1] && pc == C ) {
				if ( d[x][pc][j] < w ) w = d[x][pc][j];
				continue ;
			}
			if ( pc == C || d[x][pc][j] >= w ) continue ;
			for ( i = 0; i < deg[x]; ++i ) {
				Flight f = adj[x][i];
				y = f.y;
				if ( idx[f.ticket_id][x] == 0 && d[y][npc=(y==c[pc]?pc+1:pc)][f.ticket_id] > d[x][pc][j] + f.w ) {
					d[y][npc][f.ticket_id] = d[x][pc][j]+f.w;
					parent[y][npc][f.ticket_id] = new Arr(x,pc,j);
					q.add(new Arr(y,npc,f.ticket_id));
				}
			}
			i = j;
			if ( j != nt ) {
				for ( l = idx[i][x]+1; l < len[i]; ++l ) {
					y = fli[i][l];
					if ( d[y][npc=(y==c[pc]?pc+1:pc)][j] > d[x][pc][j] ) {
						d[y][npc][j] = d[x][pc][j]; 
						parent[y][npc][j] = parent[x][pc][j];
						q.add(new Arr(y,npc,j));
					}
				}
			}
		}
		return w;
	}
	void go() throws Exception {
		int cs = 0,trip = 0,i,j,k,l,t,x,y,ni,cost,w;
		String path;
		while ( (nt=scan.nextInt())!=0 && (++cs)>0 ) {
			m = new TreeMap<Integer,Integer>(); V = 0;
			m.clear();
			for ( x = 0; x < M; deg[x++] = 0 );
			for ( i = 0; i < nt; ++i ) {
				p[i] = scan.nextInt();
				len[i] = scan.nextInt();
				for ( j = 0; j < len[i]; ++j ) {
					y = Ins(scan.nextInt());
					idx[i][fli[i][j] = y] = j;
				}
				for ( j = 0; j < len[i]; ++j ) 
					for ( k = j+1; k <= j+1; ++k )
						adj[fli[i][j]][deg[fli[i][j]]++] = new Flight(fli[i][j],fli[i][k],i,p[i]);
			}
			ni = scan.nextInt();
			for ( l = 0; l < ni; ++l ) {
				C = k = scan.nextInt();
				for ( t = 0; t < k; ++t )
					c[t] = Ins(scan.nextInt());
				cost = bfs();  path = "";
				if ( cost == (1<<29) ) continue ;
				w = (1<<29); j = -1;
				for ( j = i = 0; i < nt; ++i )
					if ( d[c[C-1]][C][i] < w ) 
						w = d[c[C-1]][C][j = i];
				if ( j == -1 ) continue ;
				path = ticketsUsed(c[C-1],C,j);
				System.out.printf("Case %d, Trip %d: Cost = ",cs,1+l);
				System.out.println(cost);
				System.out.printf("  Tickets used:");
				System.out.println(path);
			}
		}
	}
};


