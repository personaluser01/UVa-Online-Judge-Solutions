/*
 * 240. Variable Radix Huffman Encoding
 * TOPIC: huffman encoding, priority queue
 * status: Accepted
 */

/**
 * Created by sj on 18/01/17.
 */

import java.io.*;
import java.util.*;

public class Main {

    final static double tol = 1e-10;
    final static char oo = (char)('Z'+1);
    int R,n;
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    double []freq = new double[0x400];

    public static void main(String... args) throws Exception {
        //System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/240/src/input.txt")));
        //System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/240/src/out02.txt")));
        new Main().go();
    }

    class Clade implements Comparable<Clade> {
        final double weight;
        final int ch;
        int addedAtStep;
        boolean isOriginal = false ;
        Map<Integer,String> m = new TreeMap<>();
        Clade( int ch, double weight ) {
            this.ch = ch;
            this.weight = weight;
            m.put(ch,"");
            addedAtStep = 0;
            isOriginal = true ;
        }
        Clade( final Set<Clade> s, int step ) {
            assert s.size() == R: s.size()+" vs "+R;
            double sumweight = 0;
            int repr = '\0';
            addedAtStep = step;
            for ( Iterator<Clade> it = s.iterator(); it.hasNext(); sumweight += it.next().weight );
            for ( Iterator<Clade> it = s.iterator(); it.hasNext(); ) {
                Clade c = it.next();
                if ( repr == '\0' || c.ch < repr ) repr = c.ch;
            }
            this.ch = repr;
            this.weight = sumweight;
            int dig = 0;
            for ( Iterator<Clade> it = s.iterator(); it.hasNext(); ) {
                String d = Integer.toString(dig++);
                Clade c = it.next();
                for ( Map.Entry<Integer,String> entry: c.m.entrySet() ) {
                    if ( entry.getKey().equals("") ) break ;
                    this.m.put(entry.getKey(), d + entry.getValue());
                }
            }
        }
        @Override
        public int compareTo( Clade other ) {
            if ( Math.abs(weight-other.weight) < tol ) {
                if ( isOriginal && !other.isOriginal )
                    return 1;
                if ( !isOriginal && other.isOriginal )
                    return -1;
                if ( !isOriginal && !other.isOriginal )
                    return addedAtStep-other.addedAtStep;
                if ( ch == other.ch )
                    return 0;
                return ch<other.ch?-1:1;
            }
            return weight < other.weight?-1:1;
        }
        public double avgLength() {
            double res = 0;
            for ( Map.Entry<Integer,String> entry: this.m.entrySet() )
                if ( entry.getKey() < n )
                    res += freq[entry.getKey()]*entry.getValue().length();
            return res;
        }
    }

    PriorityQueue<Clade> pq = new PriorityQueue<>();

    void go() throws Exception {
        int i,j,k,cs=0,K,t;
        Clade c;
        for ( String s; (s = br.readLine()) != null && !s.equals("0"); ) {
            Scanner scan = new Scanner(s);
            R = scan.nextInt();
            n = scan.nextInt();
            for ( k = 0, i = 0; i < n; ++i )
                k += (freq[i] = scan.nextInt());
            assert pq.isEmpty();
            K = (int)(Math.ceil((n-R+0.00)/(R-1))+tol);
            assert K*(R-1)+R < 0x400;
            for ( i = n; i < K*(R-1)+R; freq[i++] = 0 );
            for ( i = 0; i < n; ++i )
                pq.add(new Clade(i,freq[i] /= (k+0.00)));
            for ( t = n, i = n; i < K*(R-1)+R; ++i )
                pq.add(new Clade(t++,0.00));
            assert pq.size() == R+K*(R-1);
            t = 0;
            for ( Set<Clade> lst = new TreeSet<>(); pq.size() >= R; pq.add(new Clade(lst,++t)) )
                for (lst.clear(), i = 0; i < R; ++i, lst.add(pq.poll())) ;
            bw.write("Set "+(++cs)+"; average length "+String.format("%.2f\n",(c=pq.poll()).avgLength()));
            for ( Map.Entry<Integer,String> entry: c.m.entrySet() )
                if ( entry.getKey() < n )
                    bw.write("    "+((char)(entry.getKey()+'A'))+": "+entry.getValue()+"\n");
            bw.write("\n");
        }
        bw.flush();
    }
}
