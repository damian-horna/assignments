import java.util.ArrayList;
import java.util.Iterator;
import java.util.PriorityQueue;
import java.util.Stack;

public class AdjacencyMatrixGraph {

	private int[][] adjacencyMatrix;
	private int v;

	public AdjacencyMatrixGraph(int[][] tab, int n) {

		v = n;
		adjacencyMatrix = new int[v][v];

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				adjacencyMatrix[i][j] = tab[i][j];
	}

	public ArrayList<Integer> toposortBFS() {

		PriorityQueue<Integer> q = new PriorityQueue<Integer>();

		ArrayList<Integer> result = new ArrayList<Integer>();
		int[] inDegree = new int[v];
		boolean[] visited = new boolean[v];

		// creates table of in-degrees for all vertices
		for (int i = 0; i < v; i++)
			for (int j = 0; j < v; j++)
				if (adjacencyMatrix[i][j] == 1) inDegree[j]++;

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

			for (int j = 0; j < v; j++) {
				if (adjacencyMatrix[vertex][j] == 1 && visited[j] == false) {
					inDegree[j]--;
					if (inDegree[j] == 0) {
						q.add(j);
						visited[j] = true;
					}
				}
			}

		}
		// System.out.println(result);
		return result;
	}

	// A recursive function used by toposortDFS
	public void toposortDFSRec(int i, boolean visited[], Stack stack) {
		visited[i] = true;

		// Recur for all the vertices adjacent to current vertex

		for (int j = 0; j < v; j++)
			if (adjacencyMatrix[i][j] == 1 && visited[j] == false) toposortDFSRec(j, visited, stack);

		// push vertices with no way out as first - here the recursion stops
		stack.push(new Integer(i));
	}

	public void toposortDFS() {
		Stack stack = new Stack();
		boolean visited[] = new boolean[v]; // false by default

		// Call toposortDFSRec from all vertices one by one if they're not
		// visited yet
		for (int i = 0; i < v; i++)
			if (visited[i] == false) toposortDFSRec(i, visited, stack);

		// while (stack.empty() == false)
		// System.out.print(stack.pop() + " ");
	}

	public void display() {
		for (int i = 0; i < v; i++) {
			for (int j = 0; j < v; j++)
				System.out.print(adjacencyMatrix[i][j] + " ");
			System.out.println();
		}
	}
}
