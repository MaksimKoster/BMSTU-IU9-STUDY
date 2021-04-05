import java.util.ArrayList;
import java.util.Scanner;

class Way {
    private int key, value;

    public Way(int key,int value) {
        this.key = key;
        this.value = value;
    }

    public int getKey(){ return key; }

    public int getValue(){ return value; }
}

class Graph {
    protected int index, key;
    protected int dist = Integer.MAX_VALUE;
    ArrayList<Way> a = new ArrayList<>();
    Graph parent = null;

    public Graph(int key) { this.key = key; }

    public int getDist() { return dist; }

    public int getKey() { return key; }

    public int getIndex() { return index; }

    public boolean relax(Graph v) {
        boolean changed;
        if (this.getDist() == Integer.MAX_VALUE)
            changed = false;
        else changed = (this.getDist() + v.getKey()) < v.getDist();
        if (changed) {
            v.dist = this.getDist() + v.getKey();
            v.parent = this;
        }
        return changed;
    }
}

class PriorityQueue {
    private int number_elem;
    Graph[] data;

    public int getNumber_elem(){ return  number_elem; }

    public PriorityQueue(int n) {
        data = new Graph[n];
        number_elem = 0;
    }

    public void swap(int i , int j, int variant){
        if (variant == 1) {
            Graph swap = data[i];
            data[i] = data[j];
            data[j] = swap;
            data[i].index = i;
            data[j].index = j;
        }
        if (variant == 0) {
            Graph swap = data[i];
            data[i] = data[j];
            data[j] = swap;
            data[j].index = j;
        }
    }

    public void heapify (Graph[] data, int pos, int nel) {
        int left, right, j;
        while(true) {
            left = 2*pos + 1;
            right = left + 1;
            j = pos;
            if ( (left < nel) && (data[pos].getDist() > data[left].getDist()) ) { pos = left; }
            if ( (right < nel) && (data[pos].getDist() > data[right].getDist()) ) { pos = right; }
            if (data[pos].getDist() == data[j].getDist()) { break; }
            swap(pos, j,  1);
        }
    }

    public void insert(Graph[] arr, int x) {
        int i = number_elem;
        number_elem++;
        data[i] = arr[x];
        while(i > 0 && (data[(i-1)/2].getDist() > data[i].getDist())) {
            swap((i-1)/2, i , 0);
            i = (i-1)/2;
        }
        data[i].index = i;
    }

    public Graph extractMin() {
        Graph min = data[0];
        number_elem--;
        if(number_elem > 0) {
            data[0] = data[number_elem];
            data[0].index = 0;
            heapify(data,0,number_elem);
        }
        return min;
    }

    public void increaseKey(Graph v, int k) {
        int i = v.getIndex();
        v.key = k;
        while(i > 0 && (data[(i-1)/2].getDist() > k)) {
            swap((i-1)/2, i , 0);
            i = (i-1)/2;
        }
        v.index = i;
    }

    public void fill(Graph[][] a, int k){
        a[0][0].dist = a[0][0].getKey();
        for(int i = 0; i < k;i++) {
            for (int j = 0; j < k; j++) {
                if(i + 1 < k) {
                    a[i][j].a.add(new Way(i+1,j));
                    a[i+1][j].a.add(new Way(i,j));
                }
                if(j + 1 < k) {
                    a[i][j].a.add(new Way(i,j+1));
                    a[i][j+1].a.add(new Way(i,j));
                }
                this.insert(a[i],j);
            }
        }
    }
}

public class MapRoute {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        Graph[][] a = new Graph[n][n];
        PriorityQueue queue = new PriorityQueue(n * n);

        for(int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = new Graph(in.nextInt());
            }
        }

        queue.fill(a, n);
        Dijkstra(a,queue);
        System.out.println(getAnswer(a, n));
    }

    public static void Dijkstra(Graph[][] a, PriorityQueue q) {
        while(q.getNumber_elem() > 0) {
            Graph u = q.extractMin();
            u.index = -1;
            for (Way way : u.a) {
                if (a[way.getKey()][way.getValue()].getIndex() != -1 && u.relax(a[way.getKey()][way.getValue()])) {
                    q.increaseKey(a[way.getKey()][way.getValue()], a[way.getKey()][way.getValue()].getDist());
                }
            }
        }
    }

    public static int getAnswer(Graph[][] a, int k){ return a[k-1][k-1].getDist(); }
}