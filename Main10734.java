/*
 * 10734. Triangle Partitioning
 * TOPIC: barycentric coordinates, normalization, bfs
 * status: Accepted
 */

/**
 * Created by sj on 27/02/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    private final static double tol = 1e-9;
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    Scanner scan = new Scanner(System.in);

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/10734/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/10734/src/out02.txt")));
        new Main().go();
    }

    class Triangle implements Comparable<Triangle> {
        double a,b;
        Triangle( double x, double y, double z ) {
            double t = x+y+z;
            x /= t; y /= t; z /= t;
            a = Math.max(x,Math.max(y,z));
            double c = Math.min(Math.min(x,y),z);
            b = x+y+z-a-c;
        }
        @Override
        public int compareTo( Triangle other ) {
            if ( Math.abs(a-other.a) < tol ) {
                if ( Math.abs(b-other.b) < tol )
                    return 0;
                return b<other.b?-1:1;
            }
            return a < other.a?-1:1;
        }
        List<Triangle> split() {
            List<Triangle> lst = new ArrayList<>();
            double c = 1-a-b, psi = Math.acos((b*b+c*c-a*a)/(2*b*c)), phi = Math.atan((c*Math.sin(psi))/(b+c*Math.cos(psi)));
            double m = (c*Math.sin(psi))/Math.sin(phi)/2;
            lst.add(new Triangle(b,m,a/2));
            lst.add(new Triangle(c,m,a/2));
            return lst;
        }
    }

    Set<Triangle> s = new TreeSet<>();

    void go() throws Exception {
        int i,j,k,cs = 0,ts = scan.nextInt();
        Triangle t;
        for (;ts-->0; ) {
            i = scan.nextInt();
            j = scan.nextInt();
            k = scan.nextInt();
            Queue<Triangle> q = new LinkedList<>();
            for ( s.clear(), q.add(t = new Triangle(i,j,k)), s.add(t); !q.isEmpty(); ) {
                t = q.poll();
                for ( Triangle x: t.split() )
                    if ( !s.contains(x) ) {
                        s.add(x);
                        q.add(x);
                    }
            }
            bw.write("Triangle "+(++cs)+": "+s.size()+"\n");
        }
        bw.flush();
    }
}
