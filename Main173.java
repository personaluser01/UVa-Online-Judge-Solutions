/*
 * 173. Network Wars
 * TOPIC: graph traversal
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	final int A = 26, NOBODY = -1, Paskill = 0, Lisper = 1;
	int enc( int x, int y ) { return (x&31)|((y&31)<<5); }
	boolean pTrapped,lTrapped,annil,lDestroyed;
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	Pattern p = Pattern.compile("([A-Z]):([A-Z]+)");
	Pattern r = Pattern.compile("\\.\\s*([A-Z])\\s+([A-Z])");
	int [][]g = new int[A][A];
	int []who = new int[A], tm = new int[A];
	public static void main( String [] args ) throws Exception { new Main().go(); }
	boolean eventOccurred() { return lDestroyed||pTrapped||lTrapped||annil; }
	void go() throws Exception {
		String s;
		int i,j,k,u,v,nx,ny,tick,pWhere,lWhere,whre,x,y,z;
		while ( !(s=br.readLine()).equals("#") ) {
			Matcher m = p.matcher(s);
			for ( i = 0; i < A; ++i )
				for ( j = 0; j < A; ++j )
					g[i][j] = 0;
			while ( m.find() ) {
				i = m.group(1).charAt(0)-'A';
				for ( char c: m.group(2).toCharArray() ) { j = c-'A'; g[i][j] = g[j][i] = 1; }
			}
			m = r.matcher(s);
			m.find();
			tick = 0;
			for ( i = 0; i < A; ++i ) { who[i] = NOBODY; tm[i] = tick = 0; }
			i = m.group(1).charAt(0)-'A';
			j = m.group(2).charAt(0)-'A';
			Queue<Integer> q = new LinkedList<Integer>();
			pTrapped = lTrapped = annil = lDestroyed = false;
			whre = lWhere = pWhere = 'A';
			for ( q.add(enc(i,j)), who[i] = Paskill, who[j] = Lisper; q.size() > 0 && !eventOccurred(); ) {
				u = q.poll(); x = (u&31); y = (u>>5); ++tick;
				if ( x == y ) { annil = true; whre = x; break ; }
				// System.out.println("This "+x+" and "+y);
				for ( nx = -1, i = 1; i < A && !eventOccurred(); ++i ) {
					if ( 0 == g[(i+x)%A][x] || who[z=(i+x)%A] == Paskill || who[z] == Lisper ) continue ;
					who[nx=z] = Paskill; tm[z] = tick;
					break ;
				}
				if ( nx == -1 && !eventOccurred() ) { pTrapped = true; pWhere = x; tm[nx = x] = tick; }
				for ( ny = -1, i = A-1; !lTrapped && !lDestroyed && !annil && i >= 1; --i ) {
					if ( 0==g[y][(i+y)%A] || who[z=(i+y)%A]==Lisper ) continue ;
					if ( who[z] == NOBODY ) {
						who[ny=z] = Lisper; tm[z] = tick;
						break ;
					}
					else if ( who[z] == Paskill ) {
						if ( tm[z] == tick ) {
							annil = true;
							whre = z;
						}
						else {
							assert tm[z] < tick;
							lDestroyed = true;
							lWhere = z;
						}
					}
				}
				if ( ny == -1 && !lTrapped && !lDestroyed && !annil ) { lTrapped = true; lWhere = y; }
				q.add(enc(nx,ny));
			}
			if ( !pTrapped && annil ) {
				System.out.println("Both annihilated in node "+(char)(whre+'A'));
				continue ;
			}
			if ( pTrapped && annil ) {
				System.out.print("Paskill trapped in node "+(char)(pWhere+'A'));
				System.out.println(" Both annihilated in node "+(char)(whre+'A'));
				continue ;
			}
			if ( pTrapped && lTrapped ) {
				System.out.print("Paskill trapped in node "+(char)(pWhere+'A'));
				System.out.println(" Lisper trapped in node "+(char)(lWhere+'A'));
			}
			else if ( pTrapped && lDestroyed ) {
				System.out.print("Paskill trapped in node "+(char)(pWhere+'A'));
				System.out.println(" Lisper destroyed in node "+(char)(lWhere+'A'));
			}
			else if ( pTrapped ) {
				System.out.println("Paskill trapped in node "+(char)(pWhere+'A'));
			}
			else if ( lTrapped ) {
				System.out.println("Lisper trapped in node "+(char)(lWhere+'A'));
			}
			else if ( lDestroyed ) {
				System.out.println("Lisper destroyed in node "+(char)(lWhere+'A'));
			}
		}
	}
};

