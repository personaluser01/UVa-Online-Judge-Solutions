/*
 * 945. Loading a Cargo Ship
 * TOPIC: simulation, good interview question, OOP, priority queue
 * status: Accepted
 */

/**
 * Created by sj on 02/02/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/945/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/945/src/out02.txt")));
        new Main().go();
    }

    class Container implements Comparable<Container> {
        final int id, capacity;
        int currentLoad = 0;
        Deque<Integer> lst = new LinkedList<>();
        Container( int id, int cap ) {
            this.id = id;
            this.capacity = cap;
        }
        public boolean load( int cargoId, int weight ) {
            if ( weight+currentLoad > capacity )
                return false ;
            currentLoad += weight;
            lst.addLast(cargoId);
            return true ;
        }
        @Override
        public int compareTo( Container other ) {
            if ( lst.size() == other.lst.size() ) {
                if ( capacity-currentLoad == other.capacity-other.currentLoad ) {
                    if ( id == other.id ) return 0;
                    return id-other.id;
                }
                return -(capacity-currentLoad-(other.capacity-other.currentLoad));
            }
            return lst.size()-other.lst.size();
        }
    }

    int n,m;
    PriorityQueue<Container> pool = new PriorityQueue<>();
    int []weight = new int[0x400];

    void go() throws Exception {
        int i,j,k,ts = 0,unloadedWeight,unusedWeight,cargoWeight,h,t;
        boolean stop;
        Container []e;
        for ( String s; (s = br.readLine()) != null; ) {
            if ( ++ts > 1 ) bw.write("\n");
            e = new Container[n = Integer.parseInt(s)];
            for ( pool.clear(), i = 0; i < n; pool.add(e[i] = new Container(i,Integer.parseInt(br.readLine()))), ++i );
            unloadedWeight = cargoWeight = unusedWeight = 0; stop = false;
            for ( Container x: pool ) unusedWeight += x.capacity;
            for ( br.readLine(), m = Integer.parseInt(br.readLine()), i = 0; i < m; ++i ) {
                k = weight[i] = Integer.parseInt(br.readLine());
                if ( stop || pool.isEmpty() ) {
                    unloadedWeight += k;
                    continue ;
                }
                Container c = pool.poll();
                if ( !c.load(i,k) ) {
                    stop = true ;
                    unloadedWeight += k;
                    continue ;
                }
                cargoWeight += k;
                unusedWeight -= k;
                if ( c.capacity > c.currentLoad ) pool.add(c);
            }
            for ( k = 0, i = 0; i < n; ++i )
                k = Math.max(k,e[i].lst.size());
            for ( h = k, i = 0; i < k; ++i, --h, bw.write("\n") )
                for ( j = 0; j < n; ++j ) {
                    if ( j > 0 ) bw.write(" ");
                    if (e[j].lst.size() < h)
                        bw.write(":");
                    else {
                        t = e[j].lst.pollLast();
                        bw.write(weight[t] + "");
                    }
                }
            for ( i = 0; i < 2*n-1; ++i, bw.write("=") );
            bw.write("\n");
            for ( i = 0; i < n; ++i ) {
                if ( i > 0 ) bw.write(" ");
                bw.write((i+1)+"");
            }
            bw.write("\n\n");
            bw.write("cargo weight: "+cargoWeight+"\n");
            bw.write("unused weight: "+unusedWeight+"\n");
            bw.write("unloaded weight: "+unloadedWeight+"\n");
            if ( (br.readLine()) == null ) break ;
        }
        bw.flush();
    }
}
