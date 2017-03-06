/*
 * 12398. NumPuzz I
 * TOPIC: simulation, independence, modular arithmetic, congruences
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	Map<Cell,List<Cell>> map;

	enum Cell {
		A (0,0,'a'),
		B (0,1,'b'),
		C (0,2,'c'),
		D (1,0,'d'),
		E (1,1,'e'),
		F (1,2,'f'),
		G (2,0,'g'),
		H (2,1,'h'),
		I (2,2,'i');

		final int x,y;
		final char ch;

		Cell( int x, int y, char ch ) {
			this.x = x;
			this.y = y;
			this.ch = ch;
		}
		public String toString() { return ""+ch; }
		static Cell getInstance( char ch ) {
			return values()[(int)(ch-'a')];
		}
		static Cell getInstance( int x, int y ) {
			for ( Cell c: values() ) 
				if ( c.x == x && c.y == y )
					return c;
			return null;
		}
	};

	public static void main( String [] args ) throws Exception {
		new Main().go();
	}

	boolean vc( int x, int y ) { return 0<=x && x<=2 && 0<=y && y<=2; }
	int inv( int x ) { 
		return (10-(x%10))%10;
	}

	void go() throws Exception {
		String s;
		int i,j,k,ts = 0,di,dj;
		char ch;
		map = new TreeMap<Cell,List<Cell>>();
		for ( ch='a', i=0; i<3; ++i )
			for ( j=0; j<3; ++j, ++ch ) {
				map.put(Cell.getInstance(ch),new ArrayList<>());
				for ( di=-1; di<=1; ++di )
					for ( dj=-1; dj<=1; ++dj )
						if ( Math.abs(di)+Math.abs(dj) <= 1 && vc(i+di,j+dj) )
							map.get(Cell.getInstance(ch)).add(Cell.getInstance(i+di,j+dj));
			}
		while ( (s = br.readLine()) != null && !s.equals("#") ) {
			bw.write("Case #"+(++ts)+":\n");
			int [][]e = new int[3][3];
			for ( Character c: s.toCharArray() ) {
				Cell x = Cell.getInstance(c);
				for ( Cell y: map.get(x) ) 
					e[y.x][y.y] += 9;
			}
			for ( i = 0; i < 3; ++i ) {
				for ( j = 0; j < 2; ++j )
					bw.write(inv(e[i][j])+" ");
				bw.write(inv(e[i][j])+"\n");
			}
		}
		bw.flush();
	}
};


