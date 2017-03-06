/*
 * 1352. Colored Cubes
 * TOPIC: brute force, complete enumeration, dihedral group, greedy, consensus string
 * status: Accepted
 */

/**
 * Created by sj on 23/01/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    private final static int N = 6;
    private final static long MOD = (1L<<31)-1L, MASK = (0xffffffff);
    enum Faces {
        FRONT, LEFT, UP, DOWN, RIGHT, BACK;
        static int n = values().length;
        public Faces next() {
            int i = this.ordinal();
            return values()[(i+1)%n];
        }
        public Faces prev() {
            int i = this.ordinal();
            return values()[(i+n-1)%n];
        }
    }
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    Scanner scan;
    int n;

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/1352/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/1352/src/out02.txt")));
        perms = new HashSet<>();
        /*
        perms.add(new Perm());
        perms.add(new Perm(2,1,5,0,4,3));
        perms.add(new Perm(1,5,2,3,0,4));
        Perm p;
        do {
            p = null;
            for ( Perm x: perms ) {
                for (Perm y : perms) {
                    Perm z = x.multiply(y);
                    if (perms.contains(z)) continue;
                    p = z;
                    break ;
                }
                if ( p != null ) break ;
            }
            if ( p != null ) perms.add(p);
        } while ( p != null);
        for ( Perm x: perms )
            System.out.println("perms.add(new Perm("+x.toString().replaceAll("[\\[\\]]","")+"));");
        */
        perms.add(new Perm(1, 3, 5, 0, 2, 4));
        perms.add(new Perm(2, 1, 5, 0, 4, 3));
        perms.add(new Perm(2, 0, 1, 4, 5, 3));
        perms.add(new Perm(4, 0, 2, 3, 5, 1));
        perms.add(new Perm(0, 4, 3, 2, 1, 5));
        perms.add(new Perm(4, 3, 0, 5, 2, 1));
        perms.add(new Perm(3, 5, 1, 4, 0, 2));
        perms.add(new Perm(3, 4, 5, 0, 1, 2));
        perms.add(new Perm(1, 0, 3, 2, 5, 4));
        perms.add(new Perm(3, 1, 0, 5, 4, 2));
        perms.add(new Perm(0, 2, 4, 1, 3, 5));
        perms.add(new Perm(4, 2, 5, 0, 3, 1));
        perms.add(new Perm(1, 5, 2, 3, 0, 4));
        perms.add(new Perm(3, 0, 4, 1, 5, 2));
        perms.add(new Perm(0, 3, 1, 4, 2, 5));
        perms.add(new Perm(4, 5, 3, 2, 0, 1));
        perms.add(new Perm(2, 5, 4, 1, 0, 3));
        perms.add(new Perm(5, 3, 4, 1, 2, 0));
        perms.add(new Perm(5, 1, 3, 2, 4, 0));
        perms.add(new Perm(0, 1, 2, 3, 4, 5));
        perms.add(new Perm(2, 4, 0, 5, 1, 3));
        perms.add(new Perm(5, 4, 2, 3, 1, 0));
        perms.add(new Perm(5, 2, 1, 4, 3, 0));
        perms.add(new Perm(1, 2, 0, 5, 3, 4));
        new Main().go();
    }

    static class Perm implements Comparable<Perm> {
        private int []x = {0,1,2,3,4,5};
        @Override
        public boolean equals( Object obj ) {
            if ( !(obj instanceof Perm) )
                return false ;
            Perm c = (Perm)obj;
            return Arrays.equals(this.x,c.x);
        }
        @Override
        public int hashCode() {
            long s = 0;
            for ( int i = 0; i < N; ++i ) {
                s <<= 1; s &= MASK;
                s += x[i]; s &= MASK;
            }
            return (int)s;
        }
        @Override
        public int compareTo( Perm p ) {
            for ( int i = 0; i < N; ++i )
                if ( x[i] != p.getX(i) )
                    return x[i]<p.getX(i)?-1:1;
            return 0;
        }
        Perm( int ... x ) {
            for ( int i = 0; i < N; ++i )
                this.x[i] = x[i];
        }
        Perm() {}
        public void setX( int i, int val ) {
            x[i] = val;
        }
        public int getX( int i ) { return x[i]; }
        Perm multiply( Perm other ) {
            Perm res = new Perm();
            for ( int i = 0; i < N; ++i )
                res.setX(i,this.getX(other.getX(i)));
            return res;
        }
        public boolean isSane() {
            int u = 0;
            for ( int i = 0; i < N; ++i )
                u |= (1<<x[i]);
            return u==(1<<N)-1;
        }
        public String toString() {
            return Arrays.toString(x);
        }
    }

    Map<String,Integer> color;
    static Set<Perm> perms;

    class Cube {
        private int []c = new int[N];
        public int getColor( Faces f ) {
            return c[f.ordinal()];
        }
        public int getColor( int i ) {
            return c[i];
        }
        public void setColor( Faces f, int cc ) {
            c[f.ordinal()] = cc;
        }
        public void setColor( int i, int cc ) {
            c[i] = cc;
        }
        Cube() {};
        Cube( int ... c ) {
            for ( int i = 0; i < N; ++i )
                this.c[i] = c[i];
        }
        public Cube rotate( final Perm p ) {
            int []e = new int[N], nc = new int[N];
            for ( int i = 0; i < N; ++i ) e[i] = c[i];
            for ( int i = 0; i < N; ++i )
                nc[p.getX(i)] = e[i];
            return new Cube(nc);
        }
        @Override
        public String toString() {
            return c.toString();
        }
        @Override
        public boolean equals( Object obj ) {
            if ( !(obj instanceof Cube) )
                return false ;
            Cube c = (Cube)obj;
            return Arrays.equals(this.c,c.c);
        }
        @Override
        public int hashCode() {
            long P = 37, s = 0;
            for ( int i = 0; i < N; ++i ) {
                s <<= 1; s &= MASK;
                s += c[i]; s &= MASK;
            }
            return (int)s;
        }
    }

    Cube []a = new Cube[4], b = new Cube[4];
    List<Set<Cube>> lst;

    int rec( int idx ) {
        int ans = (1<<29);
        if ( idx == n ) {
            ans = 0;
            for ( int i = 0; i < N; ++i ) {
                Map<Integer,Integer> m = new HashMap<>();
                for ( int j = 0; j < n; ++j )
                    if ( !m.containsKey(b[j].getColor(i)) )
                        m.put(b[j].getColor(i),1);
                    else m.put(b[j].getColor(i),m.get(b[j].getColor(i))+1);
                int majorityCnt = 0;
                for ( Map.Entry<Integer,Integer> entry: m.entrySet() )
                    if ( entry.getValue() > majorityCnt )
                        majorityCnt = entry.getValue();
                ans += n-majorityCnt;
            }
            return ans ;
        }
        assert idx < n;
        for ( Cube x: lst.get(idx) ) {
            b[idx] = x;
            ans = Math.min(ans,rec(idx+1));
        }
        return ans ;
    }

    void go() throws Exception {
        int i,j,k;
        String s;
        for ( ;(s = br.readLine()) != null && (n = Integer.parseInt(s)) != 0; ) {
            color = new HashMap<>();
            lst = new ArrayList<>();
            for ( i = 0; i < n; ++i ) {
                String []col = (s = br.readLine()).split("\\s");
                for ( String t: col )
                    if (!color.containsKey(t)) {
                        k = color.size();
                        color.put(t, k);
                    }
                a[i] = new Cube();
                lst.add(new HashSet<>());
                for ( j = 0; j < N; ++j )
                    a[i].setColor(j,color.get(col[j]));
                for ( Perm p: perms )
                    lst.get(i).add(a[i].rotate(p));
            }
            bw.write(rec(0)+"\n");
        }
        bw.flush();
    }
}
