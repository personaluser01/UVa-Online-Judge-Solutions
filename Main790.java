/*
 * 790. Head Judge Headache
 * TOPIC: ad hoc, java collections
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	StringTokenizer st;
	public static void main( String [] args ) throws Exception { new Main().go(); }
	class Team implements Comparable<Team> {
		int solved, total_time, idx;
		Map<String,Integer> m;
		Map<String,Integer> st;
		Set<String> acc;
		List<Submission> q;
		Team( int idx ) {
			this.idx = idx;
			this.solved = this.total_time = 0;
			this.acc = new TreeSet<String>();
			this.m = new TreeMap<String,Integer>();
			this.st = new TreeMap<String,Integer>();
			this.q = new LinkedList<Submission>();
			for ( char c = 'A'; c <= 'Z'; ++c ) {
				String s;
				this.m.put(s = Character.toString(c),0);
				this.st.put(s,(1<<29));
			}
		}
		public int compareTo( Team other ) {
			if ( this.solved == other.solved ) {
				if ( this.total_time == other.total_time ) 
					return this.idx<other.idx?-1:1;
				return this.total_time<other.total_time?-1:1;
			}
			return this.solved>other.solved?-1:1;
		}
		void addSubmission( Submission y ) { this.q.add(y); }
		void Finalize() {
			for ( Iterator<Submission> it = this.q.iterator(); it.hasNext(); ) {
				Submission e = it.next();
				if ( !e.isAccepted ) continue ;
				if ( this.acc.contains(e.p) && this.st.get(e.p) <= e.timestamp )
					continue ;
				if ( this.acc.contains(e.p) && this.st.get(e.p) > e.timestamp ) {
					this.st.put(e.p,e.timestamp);
					continue ;
				}
				if ( !this.acc.contains(e.p) ) {
					this.acc.add(e.p);
					this.st.put(e.p,e.timestamp);
					++this.solved;
					continue ;
				}
			}
			for ( Iterator<Submission> it = this.q.iterator(); it.hasNext(); ) {
				Submission e = it.next();
				if ( e.isAccepted || !this.acc.contains(e.p) || this.st.get(e.p) < e.timestamp ) continue ;
				int k = this.m.get(e.p);
				this.m.put(e.p,k+1);
			}
			for ( Iterator<String> it = this.acc.iterator(); it.hasNext(); ) {
				String t = it.next();
				this.total_time += 20*this.m.get(t);
				this.total_time += this.st.get(t);
			}
		}
	};
	class Submission implements Comparable<Submission> {
		String p;
		int timestamp;
		boolean isAccepted;
		Submission( String p, int t, boolean f ) {
			this.p = p;
			this.timestamp = t;
			this.isAccepted = f;
		}
		public int compareTo( Submission other ) {
			if ( this.p.compareTo(other.p) != 0 )
				return this.p.compareTo(other.p);
			if ( this.timestamp == other.timestamp ) {
				if ( this.isAccepted && !other.isAccepted )
					return 1;
				if ( !this.isAccepted && other.isAccepted )
					return -1;
				return 0;
			}
			return this.timestamp<other.timestamp?-1:1;
		}
	}
	Team []t = new Team[0x20];
	int n;
	void go() throws Exception {
		int i,j,k,cs=0,maxi;
		String s;
		int ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
		for ( br.readLine(); ts-->0; ) {
			 if ( ++cs > 1 ) System.out.println("");
		Set<Integer> S = new TreeSet<Integer>();
		for ( n = 0; n < 32; t[n] = new Team(n), ++n );
		for ( maxi=-1; (s=br.readLine()) != null && !s.equals("");) {
			st = new StringTokenizer(s);
			S.add(i = Integer.parseInt(st.nextToken())-1);
			if ( i > maxi ) maxi = i;
			String p = st.nextToken(), tt = st.nextToken();
			String []a = tt.split(":");
			int tm = Integer.parseInt(a[0])*60+Integer.parseInt(a[1]);
			String status = st.nextToken();
			t[i].addSubmission(new Submission(p,tm,status.equals("Y")));
		}
		for ( i = 0; i <= maxi; t[i++].Finalize() );
		for ( j = 1; j == 1; )
			for ( i = j = 0; i < maxi; ++i )
				if ( t[i].compareTo(t[i+1]) > 0 ) {
					Team tmp = t[i];
					t[i] = t[i+1];
					t[i+1] = tmp;
					j = 1;
				}
		System.out.println("RANK TEAM PRO/SOLVED TIME");
		int rrun;
		for ( rrun = 0, j = 1, i = 0; i <= maxi; ++i ) {
			if ( i != 0 && (t[i-1].solved != t[i].solved || t[i-1].total_time != t[i].total_time) ) {
				j += rrun;
				rrun = 0;
			}
			System.out.printf("%4d %4d",j,t[i].idx+1,t[i].solved,t[i].total_time);
			++rrun;
			if ( t[i].solved > 0 )
				System.out.printf(" %4d %10d\n",t[i].solved,t[i].total_time);
			else System.out.println("");
		}
		}
	}
};

