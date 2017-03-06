/*
 * 330. Inventory Maintenance
 * TOPIC: ad hoc, pretty formatting
 * status: Accepted
 */
/**
 * Created by sj on 07/01/17.
 */
import java.io.*;
import java.util.*;

public class Main330 {

    public static void main( String ... args ) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/330/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/330/src/out02.txt")));
        new Main330().go();
    }
    private class Item implements Comparable<Item> {
        String name;
        double unitCost, sellingPrice;
        private Item( Scanner scan ) {
            name = scan.next();
            unitCost = scan.nextDouble();
            sellingPrice = scan.nextDouble();
        };
        private Item( String nm ) {
            name = nm;
        }
        @Override
        public int compareTo( Item other ) {
            return this.name.compareTo(other.name);
        }
    }

    Set<Item> goods;
    Map<Item,Integer> inventory;
    Map<Item,Double> items2prices,items2sell;
    double profit,losses,gains;

    void go() throws Exception {
        int i,j,k;
        Item x,y;
        String s,comm,nm;
        double totalValue,t;

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        goods = new TreeSet<>();
        inventory = new TreeMap<>();
        items2prices = new TreeMap<>();
        items2sell = new TreeMap<>();
        losses = gains = 0;
        profit = 0;
            while ( (s = br.readLine()) != null && !s.equals("*") ) {
                Scanner scan = new Scanner(s);
                comm = scan.next();
                switch (comm) {
                    case "new": x = new Item(scan);
                                goods.add(x);
                                items2prices.put(x,x.unitCost);
                                items2sell.put(x,x.sellingPrice);
                                inventory.put(x,0);
                                break;
                    case "delete": nm = scan.next();
                                x = new Item(nm);
                                if ( inventory.containsKey(x) )
                                    profit -= items2prices.get(x)*inventory.remove(x);
                                break;
                    case "buy": x = new Item(nm = scan.next());
                                k = scan.nextInt();
                                if ( inventory.containsKey(x) )
                                    inventory.put(x,inventory.get(x)+k);
                                else inventory.put(x,k);
                                break;
                    case "sell": nm = scan.next();
                                x = new Item(nm);
                                k = scan.nextInt();
                                assert inventory.containsKey(x) ;
                                assert inventory.get(x) >= k;
                                profit += (items2sell.get(x)-items2prices.get(x))*k;
                                inventory.put(x,inventory.get(x)-k);
                                break;
                    case "report":
                                totalValue = 0;
                                bw.write("                  INVENTORY REPORT\n");
                                bw.write("Item Name     Buy At      Sell At      On Hand        Value\n");
                                bw.write("---------     ------      -------      -------        -----\n");
                                for ( Map.Entry<Item,Integer> entry: inventory.entrySet() ) {
                                    x = entry.getKey();
                                    k = entry.getValue();
                                    totalValue += (t = items2prices.get(x)*k);
                                    bw.write(String.format("%-10s%10.2f%13.2f%13d%13.2f\n",x.name,items2prices.get(x),items2sell.get(x),k,t));
                                }
                                bw.write("------------------------\n");
                                bw.write(String.format("Total value of inventory%35.2f\n",totalValue));
                                bw.write(String.format("Profit since last report%35.2f\n\n",profit));
                                profit = 0;
                                break;
                    default:
                                assert false;
                }
            }
        bw.flush();
    }
}
