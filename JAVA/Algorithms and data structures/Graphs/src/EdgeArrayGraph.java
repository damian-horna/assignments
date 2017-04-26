import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.Stack;

public class EdgeArrayGraph {

	private int[][] edgeArray;
	private int v;
	private int m;

	public EdgeArrayGraph(int[][] tab, int n, int em) {

		v = n;
		edgeArray = new int[em][2];
		int iter = 0;

		for (int i = 0; i < v; i++)
			for (int j = 0; j < v; j++)
				if (tab[i][j] == 1) {
					edgeArray[iter][0] = i;
					edgeArray[iter][1] = j;
					iter++;
				}
		m = em;
	}

	public ArrayList<Integer> toposortBFS() {

		PriorityQueue<Integer> q = new PriorityQueue<Integer>();

		ArrayList<Integer> result = new ArrayList<Integer>();
		int[] inDegree = new int[v];
		boolean[] visited = new boolean[v];

		// creates table of in-degrees for all vertices
		for (int i = 0; i < m; i++)
			inDegree[edgeArray[i][1]]++;

		// adds vertices with 0 in-degree to the queue
		for (int i = 0; i < v; i++)
			if (inDegree[i] == 0) {
				q.add(i);
				visited[i] = true;
			}

		// bfs - taking the first element with 0 in-degree in queue and deleting
		// the arcs
		while (q.size() > 0) {

			int vertex = q.poll();
			result.add(vertex);

			for (int j = 0; j < m; j++) {
				if (edgeArray[j][0] == vertex) {
					inDegree[edgeArray[j][1]]--;
					if (inDegree[edgeArray[j][1]] == 0) {
						q.add(j);
						visited[edgeArray[j][1]] = true;
					}
				}
			}

		}
		// System.out.println(result);
		return result;
	}

	// A recursive function used by toposortDFS
	public void toposortDFSRec(int x, boolean visited[], Stack stack) {
		visited[x] = true;

		// Recur for all the vertices adjacent to current vertex

		for (int j = 0; j < m; j++)
			if (edgeArray[j][0] == x && visited[edgeArray[j][1]] == false)
				toposortDFSRec(edgeArray[j][1], visited, stack);

		// push vertices with no way out as first - here the recursion stops
		stack.push(new Integer(x));
	}

	public void toposortDFS() {
		Stack stack = new Stack();
		// default value - false
		boolean visited[] = new boolean[v];

		// Call toposortDFSRec from all vertices one by one if they're not
		// visited yet
		for (int i = 0; i < m; i++)
			if (visited[edgeArray[i][0]] == false) toposortDFSRec(edgeArray[i][0], visited, stack);

		// while (stack.empty() == false)
		// System.out.print(stack.pop() + " ");
	}

	public void display() {
		for (int i = 0; i < m; i++)
			System.out.println(edgeArray[i][0] + " " + edgeArray[i][1]);
	}
}
