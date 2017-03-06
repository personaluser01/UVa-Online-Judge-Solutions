/*
 * 10588. Queueing at the Doctors
 * TOPIC: simulation, queue
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {

	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	final static int N = 0x400;
	int m,n;

	Map<Integer,Queue<Integer>> mp;
	Map<Integer,PriorityQueue<Event>> q;

	int []charge;

	public static void main( String ... args ) throws Exception {
		new Main().go();
	}

	class Event implements Comparable<Event> {
		int client_id, arrival_time;
		int getId() { return client_id; }
		int getTime() { return arrival_time; }
		Event( int id, int t ) {
			client_id = id;
			arrival_time = t;
		}
		public int compareTo( Event other ) {
			if ( this.arrival_time == other.arrival_time ) 
				return this.client_id-other.client_id;
			return this.arrival_time<other.arrival_time?-1:1;
		}
	}

	boolean getRipeEvents( Queue<Integer> eq, int curTime ) {
		for ( Map.Entry<Integer,PriorityQueue<Event>> entry: q.entrySet() ) 
			if ( !(entry.getValue()).isEmpty() ) {
				// assert ( entry.getValue().peek().getTime() >= curTime );
				if ( entry.getValue().peek().getTime() <= curTime ) 
					eq.add(entry.getKey());
			}
		return !eq.isEmpty();
	}

	int getEarliest() {
		int ans = (1<<29);
		for ( Map.Entry<Integer,PriorityQueue<Event>> entry: q.entrySet() ) 
			if ( !(entry.getValue()).isEmpty() && entry.getValue().peek().getTime() < ans ) 
				ans = entry.getValue().peek().getTime();
		return ans;
	}

	int simulate() {
		int curTime = -1,i,j,k,ans = 0;
		Event e;
		Queue<Integer> eq = new LinkedList<Integer>();
		for (;getRipeEvents(eq,curTime=Math.max(getEarliest(),curTime+1));) 
			while ( !eq.isEmpty() ) {
				j = eq.poll();
				assert !q.get(j).isEmpty();
				e = q.get(j).poll();
				if ( 0 == --charge[j] )
					q.remove(j);
				i = e.getId();
				k = mp.get(i).poll();
				assert k == j;
				if ( !mp.get(i).isEmpty() ) {
					k = mp.get(i).peek();
					q.get(k).add(new Event(i,curTime+1));
				}
				else {
					mp.remove(i);
					if ( curTime+1 > ans )
						ans = curTime+1;
				}
			}
		return ans;
	}

	void go() throws Exception {
		int i,j,k,l,ts = Integer.parseInt(br.readLine()),t,cs = 0;
		String s;
		StringTokenizer st;
		Queue<Integer> lst;
		for(;ts-->0; bw.write(simulate()+"\n") ) {
			st = new StringTokenizer(s = br.readLine());
			n = Integer.parseInt(st.nextToken());
			m = Integer.parseInt(st.nextToken());
			mp = new HashMap<Integer,Queue<Integer>>();
			q = new HashMap<Integer,PriorityQueue<Event>>();
			charge = new int[m];
			for ( i = 0; i < m; q.put(i,new PriorityQueue<Event>()), ++i );
			for ( l = 0; l < n; ++l ) {
				st = new StringTokenizer(s = br.readLine());
				t = Integer.parseInt(st.nextToken());
				if ( 0 == (k = Integer.parseInt(st.nextToken())) )
					continue ;
				mp.put(l,lst = new LinkedList<Integer>());
				for ( j = 0; j < k; ++j ) {
					assert st.hasMoreTokens();
					lst.add(i = Integer.parseInt(st.nextToken())-1);
					++charge[i];
				}
				q.get(lst.peek()).add(new Event(l,t));
			}
		}
		bw.flush();
	}
}

