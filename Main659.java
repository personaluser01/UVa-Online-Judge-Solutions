/*
 * 659. Reflections
 * TOPIC: ad hoc, computational geometry, recursion, vectors, rotations
 * status: Accepted
 */

/**
 * Created by sj on 12/01/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    final private static int N = 32;
    int n;
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    private final static double tol = 1e-9;

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/659/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/659/src/out02.txt")));
        new Main().go();
    }

    class Point {
        double x,y;
        Point( Scanner scan ) {
            this.x = scan.nextDouble();
            this.y = scan.nextDouble();
        }
        Point( double x, double y ) {
            this.x = x;
            this.y = y;
        }
        public double sqDistTo( Point other ) {
            return (this.x-other.x)*(this.x-other.x)+(this.y-other.y)*(this.y-other.y);
        }
        public Point subtract( Point other ) {
            return new Point(this.x-other.x,this.y-other.y);
        }
        public Point add( Point other ) {
            return new Point(this.x+other.x,this.y+other.y);
        }
        public double scalarMult( Point other ) {
            return this.x*other.x+this.y*other.y;
        }
        public Point mult( double t ) {
            return new Point(this.x*t,this.y*t);
        }
        public Point rotate( double t ) {
            double c = Math.cos(t), s = Math.sin(t);
            return new Point(this.x*c-this.y*s,this.x*s+this.y*c);
        }
        public boolean equals( Object other ) {
            if ( other == null ) return false ;
            if ( !(other instanceof Point) ) return false ;
            Point o = (Point)other;
            return Math.abs(x-o.x) < tol && Math.abs(y-o.y)<tol;
        }
    }

    double findAngle( Point a, Point b ) {
        double A = Math.sqrt(a.scalarMult(a)), B = Math.sqrt(b.scalarMult(b));
        double co = a.scalarMult(b)/A/B, si = (a.x*b.y-a.y*b.x)/A/B;
        if ( Math.abs(co-1.00) < tol )
            return 0.00;
        if ( co >= 0 && si >= 0 )
            return Math.acos(co);
        if ( co >= 0 && si <= 0 )
            return Math.asin(si);
        if ( co <= 0 && si >= 0 )
            return Math.acos(co);
        return -Math.PI+Math.acos(-co);
    }

    class Ray {
        Point o,m;
        Ray( Point o, Point m ) {
            this.o = o;
            this.m = m;
        }
    }

    class Sphere {
        Point c;
        double r;
        Sphere( Point c, double r ) {
            this.c = c;
            this.r = r;
        }
    }

    Sphere []e = new Sphere[N];

    void simulate( Ray v, List<Integer> lst, int curIdx ) {
        int i,j = -1,k;
        Point nextOrigin = null;
        double []t = new double[2];
        double tau;
        for ( i = 0; i < n; ++i ) {
            if ( i == curIdx ) continue ;
            Point a = v.m, b = v.o.subtract(e[i].c);
            double A = a.scalarMult(a), B = 2*a.scalarMult(b), C = b.scalarMult(b)-e[i].r*e[i].r;
            double det = B*B-4*A*C;
            if ( det < 0 ) continue ;
            List<Point> hits = new ArrayList<>();
            if ( Math.abs(det) < tol ) {
                tau = -B/2/A;
                if ( tau > 0 )
                    hits.add(v.o.add(v.m.mult(tau)));
            }
            else {
                t[0] = (-B-Math.sqrt(det))/2/A;
                t[1] = (-B+Math.sqrt(det))/2/A;
                if ( t[0] > 0 )
                    hits.add(v.o.add(v.m.mult(t[0])));
                if ( t[1] > 0 )
                    hits.add(v.o.add(v.m.mult(t[1])));
            }
            for ( Point p: hits )
                if ( !p.equals(v.o) )
                if ( nextOrigin == null || nextOrigin.sqDistTo(v.o) > p.sqDistTo(v.o) ) {
                    nextOrigin = p;
                    j = i;
                }
        }
        if ( nextOrigin == null )
            return ;
        lst.add(j);
        if ( lst.size() >= 11 ) return ;
        Point vec = nextOrigin.subtract(e[j].c), u = nextOrigin.subtract(v.o);
        Point rot = new Point(vec.y,-vec.x);
        double angle = findAngle(u,rot);
        rot = rot.rotate(angle);
        simulate(new Ray(nextOrigin,rot),lst,j);
    }

    void go() throws Exception {
        int i,j,k,t,cs = 0;
        Scanner scan;
        for ( String s; (s = br.readLine()) != null; ) {
            n = Integer.parseInt(s);
            if ( n == 0 ) break ;
            for ( i = 0; i < n; ++i ) {
                scan = new Scanner(s = br.readLine());
                j = scan.nextInt();
                k = scan.nextInt();
                t = scan.nextInt();
                e[i] = new Sphere(new Point((double)j,(double)k),(double)t);
            }
            scan = new Scanner(br.readLine());
            Point o = new Point(scan), m = new Point(scan);
            Ray cur = new Ray(o,m);
            List<Integer> res;
            simulate(cur,res = new ArrayList<>(),n);
            bw.write("Scene "+(++cs)+"\n");
            if ( res.size() >= 11 ) {
                for ( i = 0; i < 10; ++i )
                    bw.write((i==0?"":" ")+(res.get(i)+1));
                bw.write(" ...\n\n");
            }
            else {
                for ( i = 0; i < res.size(); ++i )
                    bw.write((i==0?"":" ")+(res.get(i)+1));
                bw.write((res.size()>0?" ":"")+"inf\n\n");
            }
        }
        bw.flush();
    }
}
