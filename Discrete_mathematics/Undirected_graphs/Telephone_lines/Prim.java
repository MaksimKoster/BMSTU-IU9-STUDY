import java.util.ArrayList;
import java.util.Scanner;

class Graph {
    ArrayList<Graph> list = new ArrayList<>();
    int index = -1, key = -1, value; Graph link;

    public Graph(int value, Graph link) {
        this.link = link;
        this.value = value;
    }
    public Graph(){}
}

public class Prim {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n, m;
        n = in.nextInt();
        m = in.nextInt();
        Graph[] Graph = new Graph[n];

        for(int i = 0; i < n; i++) {
            Graph[i] = new Graph();
        }

        for(int i = 0; i < m; i++) {
            int u = in.nextInt();
            int v = in.nextInt();
            int len = in.nextInt();
            Graph[v].list.add(new Graph(len, Graph[u]));
            Graph[u].list.add(new Graph(len, Graph[v]));
        }
        System.out.println(MST_Prim(Graph));
    }

    public static int MST_Prim(Graph[] Graph) {
        int answer = 0;
        PriorityQueue Que = new PriorityQueue(Graph.length);
        Graph v = Graph[0];
        while (true) {
            v.index = -2;
            for(int i = 0; i < v.list.size(); i++) {
                Graph u = v.list.get(i).link;
                if (u.index == -1) {
                    u.key = v.list.get(i).value;
                    Que.insert(u);
                }
                else if (u.index != -2 && v.list.get(i).value < u.key) {
                    Que.decreaseKey(u, v.list.get(i).value);
                }
            }
            if (Que.empty()) {break;}
            v = Que.extractMin();
            answer += v.key;
        }
        return answer;
    }
}

class PriorityQueue {
    int count;
    Graph[] heap;

    public PriorityQueue(int n) {
        count = 0;
        heap = new Graph[n];
    }

    public void insert(Graph v) {
        int i = this.count;
        this.heap[this.count++] = v;
        while (i > 0 && this.heap[(i - 1)/2].key > this.heap[i].key) {
            Swap((i - 1)/2, i);
            this.heap[i].index = i;
            i = (i - 1)/2;
        }
        this.heap[i].index = i;
    }

    public Graph extractMin() {
        Graph a = this.heap[0];
        this.count--;
        if (this.count > 0) {
            this.heap[0] = this.heap[this.count];
            this.heap[0].index = 0;
            SortHeap(this.count);
        }
        return a;
    }

    public void SortHeap(int count) {
        int l, r, j, i = 0;
        for(;;) {
            l = i * 2 + 1;
            r = l + 1;
            j = i;
            if ((l < count) && (this.heap[i].key > this.heap[l].key))
                i = l;
            if ((r < count) && (this.heap[i].key > this.heap[r].key))
                i = r;
            if (i == j)
                break;
            Swap(i,j);
            this.heap[i].index = i;
            this.heap[j].index = j;
        }
    }

    public void decreaseKey(Graph v, int k) {
        int i = v.index;
        v.key = k;
        while (i > 0 && this.heap[(i - 1)/2].key > k) {
            Swap((i - 1)/2, i);
            this.heap[i].index = i;
            i = (i - 1)/2;
        }
        v.index = i;
    }

    public boolean empty() {
        return (this.count == 0);
    }
    public void Swap(int i, int j){
        Graph swap = this.heap[i];
        this.heap[i] = this.heap[j];
        this.heap[j] = swap;
    }
}