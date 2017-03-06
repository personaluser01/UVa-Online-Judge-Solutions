/*
 * 10771. Barbarian tribes
 * TOPIC: invariants, neat
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Reader {
		static BufferedReader reader;
		static StringTokenizer st;

		static void init( InputStream input ) {
			reader = new BufferedReader(new InputStreamReader(input));
			st = new StringTokenizer("");
		}

		static String next() throws IOException {
			while ( !st.hasMoreTokens() ) 
				st = new StringTokenizer(reader.readLine());
			return st.nextToken();
		}

		static int nextInt() throws IOException {
			return Integer.parseInt(next());
		}
}


public class Main {
	Scanner scan = new Scanner(System.in);
	private final static int N = (1<<15);
	int n,K,cnt,m,remaining,GG,KK;
	int []t = new int[N], id = new int[N];

	
	enum Tribe { 
		G, K, NONE;
		public String toString() {
			switch( this ) {
				case G: return "Gared";
				case NONE: return "NONE";
				default: return "Keka";
			}
		};
	};

	Tribe []who = new Tribe[N];
	Queue<Tribe> q;

	int L( int x ) { return x&((~x)+1); }

	public static void main( String [] args ) throws Exception {
		new Main().go();
	}

	void update( int x, int dt ) {
		for(;x<K;t[x]+=dt,x+=L(x));
	}
	int prefix( int x ) {
		int s = 0;
		for(;x>0;s+=t[x],x&=~L(x));
		return s;
	}
	int segmentSum( int x, int y ) {
		return prefix(y)-prefix(Math.max(0,x-1));
	}
	int getKthOrderStatistic( int k ) {
		int low,high,mid,j = 0;
		/*
		for ( low = 0, high = n+m; low+1<high; )
			if ( prefix(mid=(low+high)/2) < k )
				low = mid;
			else high = mid;
		return high;
		*/
		for ( mid = 1; mid <= n+m; ++mid )
			if ( who[mid] != Tribe.NONE ) {
				if ( ++j == k )
					return mid;
			}
		return -1;
	}

	int exec( int kk ) {
		int i;
		Tribe x,y;

		i = getKthOrderStatistic(kk);
		q.add(who[i]);
		//update(i,-1);
		who[i] = Tribe.NONE;
		// System.out.println(who[i]+" "+id[i]);

		if ( q.size() == 2 ) {
			if ( (x=q.poll()) == (y=q.poll()) ) {
				who[i] = Tribe.G;
				id[i] = ++GG;
			}
			else {
				who[i] = Tribe.K;
				id[i] = ++GG;
			}
			//update(i,1);
			// System.out.println("Replaced by "+who[i]+" "+id[i]);
			assert q.size() == 0;
			return 0;
		}
		else {
			assert q.size() == 1;
			return 1;
		}
	}

	void go() throws Exception {
		int i,j,k,kk,offset;
		Reader.init(System.in);
		BufferedWriter br = new BufferedWriter(new OutputStreamWriter(System.out));
		boolean flag = false;
		for ( ;; ) {
			n = Reader.nextInt();
			m = Reader.nextInt();
			k = Reader.nextInt();
			if ( n == 0 && m == 0 && k == 0 ) break ;
			/*
			for ( K = 0; (1<<K) <= (n+m); ++K );
			for ( K = (1<<K), i = 0; i < K; t[i++] = 0 );
			*/
			for ( i = 1; i <= n; who[i++] = Tribe.G );
			for ( i = n+1; i <= n+m; who[i++] = Tribe.K );
			KK = GG = 0;
			for ( i = 1; i <= n; id[i++] = ++GG );
			for ( i = n+1; i <= n+m; id[i++] = ++GG );
			// for ( i = 1; i <= n+m; update(i++,1) );
			q = new LinkedList<Tribe>(); offset = 0; remaining = m+n;
			/*
			for ( ;; ) {
				kk = (offset+k)%remaining;
				if ( kk == 0 ) kk = remaining;
				remaining -= (j = exec(kk));
				offset = kk-j;
				if ( j == 0 && remaining == 1 ) break ;
			}
			*/
			br.write(((m&1)==1?Tribe.K:Tribe.G)+"\n");
			flag = true;
		}
		br.flush();
	}
}

