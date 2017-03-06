/*
 * 1398. Meteor
 * TOPIC: event-driven-simulation, priority queue, sorting, intervals
 * status: Accepted
 */

/**
 * Created by sj on 23/01/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    int n;
    int W,H;
    static final int N = 100100;
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    InputStreamReader r = new InputStreamReader(System.in);
    int nextInt() throws Exception {
        int ch, n = 0,sign = 1;
        for (;(ch = r.read()) != -1 && !('0'<=((char)ch) && ((char)ch)<='9' || ((char)ch)=='-'); );
        if ( ((char)ch) == '-' )
            sign = -1;
        else n = ch-'0';
        for ( ;(ch = r.read()) != -1 && ('0'<=((char)ch) && ((char)ch<='9')); n = 10*n+ch-'0' );
        return sign*n;
    }
    final static double oo = (Double.MAX_VALUE-0x400), tol = 1e-7, eps = 0;

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/1398/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/1398/src/out02.txt")));
        new Main().go();
    }

    class Cell {
        int x,y;
        Cell() throws Exception {
            x = nextInt();
            y = nextInt();
        }
    }

    boolean inside( final Cell p, final Cell v, Pair t ) {
        return 0 <= p.x*t.y+v.x*t.x && p.x*t.y+v.x*t.x <= W*t.y && 0 <= p.y*t.y+v.y*t.x && p.y*t.y+v.y*t.x <= H*t.y;
    }
    boolean strictlyInside( final Cell p, final Cell v ) {
        return eps < p.x && p.x < W && eps < p.y && p.y < H;
    }

    boolean isParallel( final Cell p, final Cell v ) {
        return p.x == 0 && v.x == 0 || p.x == W && v.x == 0 || p.y == 0 && v.y == 0 || p.y == H && v.y == 0;
    }

    long gcd( long x, long y ) {
        if ( y == 0 ) return x;
        return gcd(y,x%y);
    }

    class Pair implements Comparable<Pair> {
        long x,y;
        Pair( long a, long b ) {
            long d = gcd(a,b);
            x = a/d;
            y = b/d;
            if ( y < 0 ) { x = -x; y = -y; }
        }
        @Override
        public int compareTo( Pair other ) {
            long lhs = x*other.y, rhs = y*other.x;
            if ( lhs == rhs ) return 0;
            return lhs < rhs?-1:1;
        }
        boolean isValid() { return this.y != 0; }
    }

    Pair ZERO = new Pair(0,1);

    Pair enteringTime( final Cell p, final Cell v ) {
        boolean flag = false ;
        Pair ans = new Pair(0,1),t;
        if ( strictlyInside(p,v) )
            return ZERO;
        if ( v.x != 0 ) {
            t = new Pair(-p.x,v.x);
            if ( t.compareTo(ZERO) >= 0 && inside(p, v, t) && (!flag || ans.compareTo(t) > 0 ) ) {
                ans = t;
                flag = true ;
            }
            t = new Pair(W-p.x, v.x);
            if ( t.compareTo(ZERO) >= 0 && inside(p, v, t) && (!flag || ans.compareTo(t) > 0) ) {
                ans = t;
                flag = true ;
            }
        }
        if ( v.y != 0 ) {
            t = new Pair(-p.y,v.y);
            if ( t.compareTo(ZERO) >= 0 && inside(p, v, t) && (!flag || ans.compareTo(t) > 0 ) ) {
                flag = true ;
                ans = t;
            }
            t = new Pair(H-p.y, v.y);
            if ( t.compareTo(ZERO) >= 0 && inside(p, v, t) && (!flag || ans.compareTo(t) > 0) ) {
                flag = true ;
                ans = t;
            }
        }
        if ( !flag ) ans.y = 0;
        return ans;
    }
    Pair leavingTime( final Cell p, final Cell v ) {
        boolean flag = false ;
        Pair ans = new Pair(0,1),t;
        if ( v.x != 0 ) {
            t = new Pair(-p.x,v.x);
            if ( t.compareTo(ZERO) >= 0 && inside(p, v,t) && (!flag || ans.compareTo(t) < 0 ) ) {
                ans = t;
                flag = true ;
            }
            t = new Pair(W-p.x, v.x);
            if ( t.compareTo(ZERO) >= 0 && inside(p, v,t) && (!flag || ans.compareTo(t) < 0) ) {
                ans = t;
                flag = true ;
            }
        }
        if ( v.y != 0 ) {
            t = new Pair(-p.y,v.y);
            if ( t.compareTo(ZERO) >= 0 && inside(p, v,t) && (!flag || ans.compareTo(t) < 0 ) ) {
                ans = t;
                flag = true ;
            }
            t = new Pair(H-p.y, v.y);
            if ( t.compareTo(ZERO) >= 0 && inside(p, v,t) && (!flag || ans.compareTo(t) < 0) ) {
                ans = t;
                flag = true ;
            }
        }
        if ( !flag ) ans.y = 0;
        return ans;
    }

    class Event implements Comparable<Event> {
        int id;
        boolean isOpening;
        Pair time;
        @Override
        public int compareTo( Event other ) {
            if ( time.compareTo(other.time) == 0 ) {
                if ( this.isOpening == other.isOpening )
                    return 0;
                return isOpening?1:-1;
            }
            return time.compareTo(other.time);
        }
        Event( Pair t, boolean flag, int id ) {
            isOpening = flag;
            time = t;
            this.id = id;
        }
    }

    PriorityQueue<Event> pq;
    int m;
    Pair []end = new Pair[N];

    void go() throws Exception {
        int i,ans,k;
        Cell p,v;
        for ( int ts = nextInt(); ts-->0; ) {
            W = nextInt();
            H = nextInt();
            n = nextInt();
            pq = new PriorityQueue<>();
            for ( k = m = 0, i = 0; i < n; ++i ) {
                p = new Cell();
                v = new Cell();
                if ( isParallel(p,v) ) continue ;
                Pair aa = enteringTime(p,v), bb = leavingTime(p,v);
                if ( aa.isValid() && aa.compareTo(bb) < 0 )  {
                    pq.add(new Event(aa,true,m++));
                    end[m-1] = bb;
                }
            }
            for ( ans = 0; !pq.isEmpty(); ) {
                Event e = pq.poll();
                if ( e.isOpening ) {
                    ++k;
                    pq.add(new Event(end[e.id],false,e.id));
                }
                else
                    ans = Math.max(ans,k--);
            }
            bw.write(ans+"\n");
        }
        bw.flush();
    }
}
