import java.io.IOException;
import java.util.Arrays;

public class Main {
	public static void main(String[] args) throws IOException {
		
		InputGenerator generator = new InputGenerator();
		generator.generateInput("file1.txt",40,40);
		
		Knapsack knapsack = new Knapsack();
		knapsack.loadData("file1.txt");
		
		long div = 1000000000;
		
		long start = System.nanoTime();
		knapsack.dynamically();
		long stop = System.nanoTime();
		double wynik1 = (double) (stop - start) / div;
		
		start = System.nanoTime();
		knapsack.multithreadedBruteForce();
		stop = System.nanoTime();
		double wynik2 = (double) (stop - start) / div;
		
		start = System.nanoTime();
		knapsack.sequential("", 0, 0, 1);
		stop = System.nanoTime();
		double wynik3 = (double) (stop - start) / div;
		
		start = System.nanoTime();
		knapsack.typicalBruteForce();
		stop = System.nanoTime();
		double wynik4 = (double) (stop - start) / div;
		
		
		start = System.nanoTime();
		knapsack.multithreadedBruteForce2();
		stop = System.nanoTime();
		double wynik5 = (double) (stop - start) / div;
		
		
		System.out.println("Input:");
		knapsack.printInput();
		System.out.println("Dynamicznie: " + wynik1);
		knapsack.printDynamic();
		
		System.out.println("W¹tki: "+wynik2);
		knapsack.printBrute();
		
		System.out.println("bez w¹tków: "+wynik3);
		knapsack.printSeq();
		
		System.out.println("Typical brute force: " +wynik4);
		System.out.println(knapsack.typicalBruteForceResult);
		
		System.out.println("W¹tki 2: " + wynik5);
		System.out.println(knapsack.mBF2result);
		System.out.println(Arrays.toString(knapsack.mBF2items));
		
	}
}
