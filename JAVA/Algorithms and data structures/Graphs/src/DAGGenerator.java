import java.util.Random;

public class DAGGenerator {
	public static int[][] generateDAG(int n, int m) {
		int[][] adjacencyMatrixy = new int[n][n];

		Random random = new Random();

		while (true)
			for (int i = 0; i < n - 1; i++) {
				int j = random.nextInt(n - i - 1) + i + 1; // proper boundaries

				if (adjacencyMatrixy[i][j] == 0) {
					adjacencyMatrixy[i][j] = 1;
					m--;
					if (m == 0) return adjacencyMatrixy;
				}
			}
	}
}
