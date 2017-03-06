/*
 * 12150. Pole Position
 * TOPIC: ad hoc
 * status: Accepted
 */
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final static int N = 0x200*2;
	Map<Integer,Integer> m,im;
	int []p = new int[N], pos = new int[N];
	boolean []used = new boolean[N];
	int n;
	public static void main( String ... args ) throws Exception {
		new Main().go();
	}
	boolean arrange() {
		int i,j,k;
		for ( i = 0; i < n; ++i ) {
			k = i+p[i];
			if ( k < 0 || k >= n || used[k] ) return false ;
			used[pos[i] = k] = true ;
		}
		return true;
	}
	void go() throws Exception {
		int i,j,k;
		for ( ;(n=scan.nextInt())>0; ) {
			m = new TreeMap<Integer,Integer>();
			im = new TreeMap<Integer,Integer>();
			for ( i = 0; i < n; ++i ) {
				k = scan.nextInt();
				assert (!m.containsKey(k)) : "Key "+k+" is present";
				j = m.size();
				m.put(k,j++);
				im.put(j-1,k);
				used[j-1] = false;
				p[m.get(k)] = scan.nextInt();
			}
			if ( !arrange() ) {
				System.out.println("-1");
				continue ;
			}
			for ( i = 0; i < n; ++i ) {
				if ( i > 0 ) System.out.print(" ");
				for ( j = 0; j < n && pos[j] != i; ++j );
				System.out.print(im.get(j));
			}
			System.out.println();
		}
	}
}

