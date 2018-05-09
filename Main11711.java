/*
 * 11711. Turing
 * TOPIC: simulation
 * status: Accepted
 */
import java.io.*;
import java.util.*;

public class Main11711 {

	private static final int LIMIT= 10000, N= 1001, NONE= -1;
	private Scanner scan= new Scanner(System.in);

	public enum Verdicts {
		MLE("MLE"), TLE("TLE"), WA("WA"), AC("AC");
		private String name;
		private Verdicts( String name ) {
			this.name= name;
		}
		@Override
		public String toString() {
			return name;
		}
	};

	private class TuringMachine {
		private int[][] map, whatToWrite, whereToMove;
		private int []tape;
		public boolean isValidState() {
			int i,j,k= getState();
			for ( i= k; i < N; ++i )
				if ( tape[i] != 0 )
					return false ;
			return true ;
		}
		public int getState() {
			int x= 0;
			for ( int i= 0; i < N && tape[i] == 1; ++i, ++x ) ;
			return x;
		}
		public void setState( int x ) {
			Arrays.fill(tape,0);
			for ( int i= 0; i < x; tape[i++]= 1 ) ;
		}
		public TuringMachine() {
			map= new int[N][2];
			whatToWrite= new int[N][2];
			whereToMove= new int[N][2];
			for ( int x= 0; x < N; ++x )
				for ( int c= 0; c < 2; ++c )
					map[x][c]= NONE;
			tape= new int[N];
		}
		public int nextState( int x, int c ) {
			if ( x == NONE || map[x][c] == NONE )
				return NONE;
			return map[x][c];
		}
		public void addState( int x, int c, int y, int wr, char dir ) {
			if ( map[x][c] != NONE )
				return ;
			map[x][c]= y;
			whatToWrite[x][c]= wr;
			whereToMove[x][c]= dir=='L'?-1:1;
		}
		public Verdicts run( int x, int y ) {
			int q,head,it;
			for ( q= 0, head= 0, setState(x), it= 0; it < LIMIT; ++it ) {
				if ( map[q][tape[head]] == NONE ) {
					if ( isValidState() && getState() == y )
						return Verdicts.AC;
					return Verdicts.WA;
				}
				int nq= map[q][tape[head]], wr= whatToWrite[q][tape[head]], dir= whereToMove[q][tape[head]];
				tape[head]= wr; head+= dir;
				if ( head < 0 || head >= N-1 )
					return Verdicts.MLE;
				q= nq;
			}
			return Verdicts.TLE;
		}
	};

	public static void main( String [] args ) throws Exception {
		new Main11711().go();
	}

	private int m,n;
	TuringMachine T;

	void go() throws Exception {
		int i,j,k;
		while ( scan.hasNext() ) {
			n= scan.nextInt();
			m= scan.nextInt();
			if ( m == 0 && n == 0 )
				break ;
			T= new TuringMachine();
			for ( i= 0; i < n; ++i ) {
				int qprev= scan.nextInt(), cprev= scan.nextInt(), qnext= scan.nextInt(), cnext= scan.nextInt();
				String mov= scan.next();
				T.addState(qprev,cprev,qnext,cnext,mov.charAt(0));
			}
			for ( i= 0; i < m; ++i ) {
				int x= scan.nextInt(), y= scan.nextInt();
				System.out.println(T.run(x,y));
			}
		}
	}
};
