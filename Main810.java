/*
 * 810. A Dicey Problem
 * TOPIC: bfs, simulation, die
 * status: Accepted
 */

/**
 * Created by sj on 31/01/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    int m,n;

    enum Perm {
        RIGHT(new int[]{0,5,2,4,1,3}),LEFT(new int[]{0,4,2,5,3,1}),BACK(new int[]{4,1,5,3,2,0}),FORTH(new int[]{5,1,4,3,0,2});
        int []x;
        Perm( int []x ) { this.x = x; }
    }

    class Die implements Comparable<Die> {
        int []faceval = new int[]{5,4,2,3,6,1};
        public int onTop() { return faceval[5]; }
        public int facingSouth() { return faceval[0]; }
        Die rotate( Perm p ) {
            Die d = new Die();
            for ( int i = 0; i < 6; ++i )
                d.faceval[i] = faceval[i];
            d.tip(p);
            return d;
        }
        void tip( Perm p ) {
            int []t = new int[6];
            for ( int i = 0; i < 6; ++i )
                t[i] = faceval[p.x[i]];
            for ( int i = 0; i < 6; ++i )
                faceval[i] = t[i];
        }
        @Override
        public int compareTo( Die other ) {
            if ( faceval[0] == other.faceval[0] )
                return faceval[5]-other.faceval[5];
            return faceval[0]-other.faceval[0];
        }
        @Override
        public boolean equals( Object obj ) {
            if ( !(obj instanceof Die) ) return false ;
            Die d = (Die)obj;
            for ( int i = 0; i < 6; ++i )
                if ( faceval[i] != d.faceval[i] )
                    return false ;
            return true ;
        }
        @Override
        public int hashCode() {
            int h = 0;
            for ( int i = 0; i < 6; ++i ) {
                h += (faceval[i] << i);
                h &= 1023;
            }
            return h&1023;
        }
    }

    int []dx = {0,1,0,-1}, dy = {1,0,-1,0};
    boolean vc( int x, int y ) { return  0<=x&&x<m && 0<=y&&y<n; }

    class State {
        Die d;
        int x,y,dist = 0;
        State parent = null;
        State( int x, int y, Die d ) {
            this.x = x;
            this.y = y;
            this.d = d;
        }
        boolean samePosition( State s ) {
            return x == s.x && y == s.y;
        }
        State tip( int dir ) {
            Die e;
            if ( !vc(x+dx[dir],y+dy[dir]) ) return null;
            switch ( dir ) {
                case 0: e = d.rotate(Perm.RIGHT); return new State(x+dx[dir],y+dy[dir],e);
                case 1: e = d.rotate(Perm.FORTH); return new State(x+dx[dir],y+dy[dir],e);
                case 2: e = d.rotate(Perm.LEFT); return new State(x+dx[dir],y+dy[dir],e);
                default: e = d.rotate(Perm.BACK); return new State(x+dx[dir],y+dy[dir],e);
            }
        }
        @Override
        public boolean equals( Object obj ) {
            if ( !(obj instanceof State) )
                return false ;
            State s = (State)obj;
            return samePosition(s) && s.d.equals(this.d);
        }
        @Override
        public int hashCode() {
            return (((x+y)&1023)+d.hashCode())&1023;
        }
    }

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/810/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/810/src/out02.txt")));
        new Main().go();
    }

    int [][]g = new int[16][16];
    Set<Die> dies = new TreeSet<>();

    void precalc() {
        Queue<Die> q = new LinkedList<>();
        Die x,y = new Die();
        for ( dies.add(y), q.add(y); !q.isEmpty(); ) {
            x = q.poll();
            for ( Perm p: Perm.values() ) {
                y = x.rotate(p);
                if ( !dies.contains(y) ) {
                    dies.add(y);
                    q.add(y);
                }
            }
        }
    }

    boolean admissible( State s, int dir ) {
        assert s != null;
        int x = s.x+dx[dir], y = s.y+dy[dir];
        return vc(x,y) && (g[x][y] == s.d.onTop() || g[x][y] == -1);
    }

    int sx,sy;

    List<String> lst = new ArrayList<>();
    void dump( State s ) {
        if ( s.dist > 0 )
            dump(s.parent);
        lst.add(String.format("(%d,%d)",s.x+1,s.y+1));
    }

    void go() throws Exception {
        int i,j,k,facingSouth, onTop;
        precalc();
        for ( String buff,s; (buff = br.readLine()) != null && !buff.equals("END"); ) {
            bw.write(buff+"\n");
            Scanner scan = new Scanner(br.readLine());
            m = scan.nextInt();
            n = scan.nextInt();
            sx = scan.nextInt()-1;
            sy = scan.nextInt()-1;
            onTop = scan.nextInt();
            facingSouth = scan.nextInt();
            for ( i = 0; i < m; ++i ) {
                scan = new Scanner(br.readLine());
                for (j = 0; j < n; ++j)
                    g[i][j] = scan.nextInt();
            }

            Die src = null;
            for ( Die d: dies )
                if ( d.onTop() == onTop && d.facingSouth() == facingSouth ) {
                    src = d;
                    break ;
                }
            assert src != null;
            State x = new State(sx,sy,src),y,source = x;
            Queue<State> q = new LinkedList<>();
            Set<State> seen = new HashSet<>();
            for ( i = 0; i < 4; ++i )
                if ( admissible(x,i) && (y = x.tip(i)) != null ) {
                    y.dist = x.dist+1;
                    y.parent = x;
                    seen.add(y);
                    q.add(y);
                }
            State soln = null;
            for ( ;!q.isEmpty(); ) {
                x = q.poll();
                assert x != null;
                if ( x.samePosition(source) ) {
                    soln = x;
                    break ;
                }
                for ( i = 0; i < 4; ++i)
                    if (admissible(x, i) && (y = x.tip(i)) != null && !seen.contains(y)) {
                        y.dist = x.dist+1;
                        y.parent = x;
                        q.add(y);
                        seen.add(y);
                    }
            }
            if ( soln == null ) {
                bw.write("  No Solution Possible\n");
                continue ;
            }
            lst.clear();
            dump(x);
            for ( i = 0; i < lst.size(); i = j ) {
                bw.write("  ");
                for ( k = 0, j = i; k < 9 && j < lst.size(); ++k, ++j ) {
                    bw.write(lst.get(j));
                    if ( j < lst.size()-1 ) bw.write(",");
                }
                bw.write("\n");
            }
        }
        bw.flush();
    }
}

