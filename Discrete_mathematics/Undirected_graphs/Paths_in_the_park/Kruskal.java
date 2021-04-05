import java.util.Scanner;

class Roads{
    int x, y, depth;
    double length;
    Roads parent;
    Roads u;
    Roads v;

    public Roads(int x, int y){
        this.x = x;
        this.y = y;
        this.depth = 0;
        parent = this;
    }
    public Roads(Roads x, Roads y, double length){
        u = x;
        v = y;
        this.length = length;
    }
}

public class Kruskal {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int numberOfDots = in.nextInt();

        Roads[] Graph = new Roads[numberOfDots];
        for (int i = 0; i < Graph.length; i++) {
            Graph[i] = new Roads(in.nextInt(), in.nextInt());
        }

        PriorityQueue links = new PriorityQueue(numberOfDots * (numberOfDots - 1) / 2);

        for (int i = 0; i < numberOfDots; i++) {
            for (int j = i + 1; j < numberOfDots; j++) {
                double length = Math.sqrt(Math.pow(Graph[j].x - Graph[i].x, 2) + Math.pow(Graph[j].y - Graph[i].y, 2));
                links.insert(new Roads(Graph[i] , Graph[j], length));
            }
        }

        System.out.printf("%.2f", MST_Kruskal(Graph, links));
    }

    public static double MST_Kruskal(Roads[] Graph, PriorityQueue links) {
        double answer = 0; int mintree = 0;
        while (mintree < Graph.length - 1){
            Roads t = links.extractMin();
            Roads p1 = find(t.u); Roads p2 = find(t.v);
            if(p1 != p2){
                mintree++;
                answer+= t.length;
                union(p1, p2);
            }
        }
        return answer;
    }

    public static Roads find(Roads x) {
        if (x.parent == x) return x;
        else return x.parent = find(x.parent);
    }

    public static void union(Roads x, Roads y) {
        if (x.depth < y.depth) {x.parent = y;}
        else {
            y.parent = x;
            if (y.depth == x.depth && x != y) {
                x.depth++;
            }
        }
    }
}

class PriorityQueue {
    int count;
    Roads[] heap;

    public PriorityQueue(int n) {
        count = 0;
        heap = new Roads[n];
    }

    public void insert(Roads v) {
        int i = this.count;
        this.heap[this.count++] = v;
        while (i > 0 && this.heap[(i - 1)/2].length > this.heap[i].length) {
            Swap((i - 1)/2, i);
            i = (i - 1)/2;
        }
    }

    public Roads extractMin() {
        Roads a = this.heap[0];
        this.count--;
        if (this.count > 0) {
            this.heap[0] = this.heap[this.count];
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
            if ((l < count) && (this.heap[i].length > this.heap[l].length))
                i = l;
            if ((r < count) && (this.heap[i].length > this.heap[r].length))
                i = r;
            if (i == j)
                break;
            Swap(i,j);
        }
    }
    public void Swap(int i, int j){
        Roads swap = this.heap[i];
        this.heap[i] = this.heap[j];
        this.heap[j] = swap;
    }
}
