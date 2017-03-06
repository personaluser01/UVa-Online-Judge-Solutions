/*
 * 660. Going on Circles on Alpha Centauri
 * TOPIC: ad hoc, simulation, even-driven-simulation, jobs-executors, neat
 * status: Accepted
 */

/**
 * Created by sj on 13/01/17.
 */

import java.io.*;
import java.text.NumberFormat;
import java.util.*;

public class Main {

    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static int ID;

    enum EventType {
        ROBOT_BECOMES_IDLE, REQUEST_ARRIVES;
    }

    class Event implements Comparable<Event> {
        EventType type;
        Marker obj;
        int time;
        Event( Marker obj, int time, EventType type ) {
            this.type = type;
            this.obj = obj;
            this.time = time;
        }
        public int compareTo( Event other ) {
            if ( this.time == other.time ) {
                if ( this.type == other.type )
                    return 0;
                return this.type == EventType.ROBOT_BECOMES_IDLE?-1:1;
            }
            return this.time-other.time;
        }
    }

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/660/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/660/src/out02.txt")));
        new Main().go();
    }

    interface Marker {};

    class Request implements Comparable<Request>, Marker {
        int arrivalTime,weight,portFrom,portTo,id;
        Request( int a, int b, int c, int d ) {
            arrivalTime = a;
            weight = d;
            portFrom = b;
            portTo = c;
            id = ID++;
        }
        public int compareTo( Request other ) {
            if ( arrivalTime == other.arrivalTime )
                return this.id-other.id;
            return arrivalTime-other.arrivalTime;
        }
        public String toString() { return "id = "+id+", load = "+weight+", arrivalTime = "+arrivalTime; }
    }

    int dist( int x, int y ) {
        if ( x > y )
            return n-x+y;
        return y-x;
    }

    class Robot implements Comparable<Robot>, Marker {
        final int id,load;
        int pos;
        Robot( int load, int id ) { this.load = load; pos = 0; this.id = id; }
        void setPos( int x ) { this.pos = x; }
        int getPos() { return pos; }
        public int compareTo( Robot other ) {
            if ( load == other.load )
                return this.id-other.id;
            return load-other.load;
        }
        public int carry( Request r, int curTime ) {
            int tm = dist(getPos(),r.portFrom)+5+dist(r.portFrom,r.portTo)+5;
            setPos(r.portTo);
            totalWorkingTime += tm;
            return curTime+tm;
        }
        public String toString() { return "id = "+id+", load = "+load+", pos = "+pos; }
    }

    Robot findExecutor( Request r ) {
        Set<Robot> s = pool.tailSet(new Robot(r.weight,-1),true);
        Robot best = null;
        for ( Iterator<Robot> it = s.iterator(); it.hasNext(); ) {
            Robot e = it.next();
            assert e.load >= r.weight;
            if (best==null||dist(best.getPos(),r.portFrom)>dist(e.getPos(),r.portFrom)||dist(best.getPos(),r.portFrom)==dist(e.getPos(),r.portFrom)&&best.id>e.id )
                best = e;
        }
        return best;
    }

    NavigableSet<Robot> pool;
    PriorityQueue<Event> pq;
    int m,n,numRequests,firstRequestTime,lastRequestSatisfied;
    double waitTime,avgUtilization,totalWorkingTime;

    void simulate() {
        Event e;
        Robot executor = null;
        int t,curTime = 0;
        List<Event> lst = new ArrayList<>();
        waitTime = 0;
        firstRequestTime = -1; lastRequestSatisfied = -1;
        totalWorkingTime = 0;
        firstRequestTime = ((Request)(pq.peek().obj)).arrivalTime;
        while ( !pq.isEmpty() ) {
            while ( !pq.isEmpty() && pq.peek().type==EventType.REQUEST_ARRIVES && (executor=findExecutor((Request)pq.peek().obj))==null )
                lst.add(pq.poll());
            assert !pq.isEmpty();
            e = pq.poll();
            pq.addAll(lst); lst.clear();
            if ( e.type == EventType.ROBOT_BECOMES_IDLE ) {
                assert curTime <= e.time;
                curTime = e.time;
                pool.add((Robot)e.obj);
                continue ;
            }
            assert executor != null;
            pool.remove(executor);
            t = executor.carry((Request)e.obj,curTime>e.time?curTime:e.time);
            pq.add(new Event(executor,t,EventType.ROBOT_BECOMES_IDLE));
            if ( lastRequestSatisfied == -1 || lastRequestSatisfied < t )
                lastRequestSatisfied = t;
            waitTime += (t-e.time);
        }
        waitTime /= numRequests;
        avgUtilization = totalWorkingTime/(lastRequestSatisfied-firstRequestTime)/m*100;
    }

    void go() throws Exception {
        int i,j,k,w,cs = 0;
        String s;
        NumberFormat nf = NumberFormat.getInstance();
        nf.setMinimumFractionDigits(3);
        nf.setMaximumFractionDigits(3);
        for ( ;(s = br.readLine()) != null; ) {
            Scanner scan = new Scanner(s);
            n = scan.nextInt();
            m = scan.nextInt();
            if ( m == 0 && n == 0 ) break ;
            ID = 0;
            bw.write("Simulation "+(++cs)+"\n");
            for ( pool = new TreeSet<>(), i = 0; i < m; pool.add(new Robot((new Scanner(br.readLine())).nextInt(),i++)) );
            assert pool.size() == m;
            pq = new PriorityQueue<>();
            int reqs = 0;
            for (;(s = br.readLine()) != null;) {
                scan = new Scanner(s);
                i = scan.nextInt();
                j = scan.nextInt()-1;
                k = scan.nextInt()-1;
                w = scan.nextInt();
                if ( i == -1 && j == -2 && k == -2 && w == -1 ) break ;
                ++reqs;
                Request rq = new Request(i,j,k,w);
                pq.add(new Event(rq,i,EventType.REQUEST_ARRIVES));
            }
            assert reqs == pq.size();
            numRequests = pq.size();
            simulate();
            bw.write("Average wait time   = "+nf.format(waitTime)+" minutes\n");
            bw.write("Average utilization = "+nf.format(avgUtilization)+" %\n\n");
        }
        bw.flush();
    }
}

