/*
 * 570. Stats
 * TOPIC: formatting
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	static String header1 = "Player  Hit Pct    KPG      BPG      DPG\n";
	static String header2 = "-----------------------------------------\n";
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	Scanner scan = new Scanner(System.in);
	Game g;

		enum Outcomes {
			HIT("H"), KILL("K"), ERR("E"), BLOCK("B"), DIG("D"), GAMES("G");
			String name;
			Outcomes( String n ) {
				name = n;
			}
			static Outcomes find( String h ) {
				switch ( h ) {
					case "H": return HIT;
					case "K": return KILL;
					case "E": return ERR;
					case "B": return BLOCK;
					case "G": return GAMES;
					default: assert( "D".equals(h) );
							 return DIG;
				}
			}
		}

	class Game {
		private int cnt = 0;
		void inc() {
			++cnt;
		}
		private Set<Integer> players = new TreeSet<Integer>();
		private Map<Integer,Map<Outcomes,Integer>> m = new TreeMap<Integer,Map<Outcomes,Integer>>();
		void addPlayer( int x ) {
			if ( players.add(x) ) {
				Map<Outcomes,Integer> q;
				m.put(x,q = new HashMap<Outcomes,Integer>());
				for ( Outcomes o: Outcomes.values() )
					q.put(o,0);
			}
			addOutcome("G",x);
		}
		void addOutcome( String h, int x ) {
			int _cnt = m.get(x).get(Outcomes.find(h));
			m.get(x).put(Outcomes.find(h),_cnt+1);
		}
		void generateReport() throws Exception {
			double K = 0, E = 0, H = 0, B = 0, D = 0;
			bw.write(header1);
			bw.write(header2);
			for ( Integer x: players ) {
				double kills = m.get(x).get(Outcomes.KILL);
				double errs = m.get(x).get(Outcomes.ERR);
				double hits = m.get(x).get(Outcomes.HIT);
				double blocks = m.get(x).get(Outcomes.BLOCK);
				double digs = m.get(x).get(Outcomes.DIG);
				int _cnt = m.get(x).get(Outcomes.GAMES);
				if ( _cnt == 0 ) continue ;
				if ( kills == 0 && hits == 0 && errs == 0 )
					bw.write(String.format("%-8s%-+7.3f%8.3f%9.3f%9.3f\n",String.format("%02d",x),0.00,kills/_cnt,blocks/_cnt,digs/_cnt));
				else bw.write(String.format("%-8s%-+7.3f%8.3f%9.3f%9.3f\n",String.format("%02d",x),(kills-errs)/(kills+errs+hits),kills/_cnt,blocks/_cnt,digs/_cnt));
				K += kills; H += hits; E += errs; B += blocks; D += digs;
			}
			if ( K == 0 && H == 0 && E == 0 )
				bw.write(String.format("%-8s%-+7.3f%8.3f%9.3f%9.3f\n","team",0.00,K/cnt,B/cnt,D/cnt));
			else 
				bw.write(String.format("%-8s%-+7.3f%8.3f%9.3f%9.3f\n","team",(K-E)/(K+E+H),K/cnt,B/cnt,D/cnt));
			bw.write("\n");
		}
	}
	public static void main( String ... args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		int i,j,k;
		String s;
		while ( scan.hasNext() ) {
			switch ( (s = scan.next()).charAt(0) ) {
				case 'C': 
							if ( g == null ) g = new Game();
							for ( g.inc(), k = scan.nextInt(); k-- > 0; g.addPlayer(scan.nextInt()) );
							break ;
				case 'R': g.generateReport();
						  g = null;
						  break ;
				default:  
						  g.addOutcome(s,scan.nextInt());
						  break ;
			}
		}
		bw.flush();
	}
}


