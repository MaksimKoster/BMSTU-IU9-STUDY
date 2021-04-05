import java.util.ArrayList;
import java.util.Scanner;

public class DelGraph {

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        long number = in.nextLong();

        ArrayList<Long> all = new ArrayList<>();
        dividers(all,number,1,number);
        printGraph(all);
    }

    public static void printGraph(ArrayList<Long> all){
        printTops(all);
        makeGraph(all,all.size() - 1);
        printEnd();
    };

    public static void printEnd(){ System.out.println("}");}

    public static void dividers(ArrayList<Long> a,long b ,long c, long d) {
        a.add(c);
        if (c != d) {
            c++;
            for (; c <= (long) Math.sqrt(b) && b % c != 0; c++) ;
            if (c <= (long) Math.sqrt(b))
                dividers(a, b, c, b / c);
            a.add(d);
        }
    }

    public static boolean prime(double n){
            for (long i = 2; i <= Math.sqrt(n); i++) {
                if (n % i == 0) return false;
            }
            return true;
    }

    public static boolean checkDiv(ArrayList<Long> a, int size, int i){
        if(a.get(size) % a.get(i) == 0){ return true; }
        return false;
    }

    public static void printTops(ArrayList<Long> a) {
        System.out.println("graph {");
        for (int i = a.size() - 1; i > -1; i--) {
            System.out.println("\t" + a.get(i));
        }
    }

    public static void makeGraph(ArrayList<Long> a, int size){
        if (size == 0){
            return;
        }
        for(int i = size - 1; i > - 1; i--){
            if( prime((a.get(size) / a.get(i))) && (checkDiv(a, size,i)) ){
                System.out.println("\t" + a.get(size) + " -- " + a.get(i) + "");
            }
        }
        makeGraph(a, size - 1);
    }

}
