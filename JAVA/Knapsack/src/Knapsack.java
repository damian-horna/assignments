import java.io.File;
import java.lang.Math;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Knapsack {

	private int capacity;
	private int numOfItems;
	private int[][] valuesAndWeights;
	private int[][] dynamicSolution;
	ArrayList<Integer> res = new ArrayList<Integer>();

	public void loadData(String filename) throws FileNotFoundException {

		File file = new File(filename);
		Scanner sc = new Scanner(file);

		capacity = sc.nextInt();
		numOfItems = sc.nextInt();

		valuesAndWeights = new int[numOfItems + 1][2];
		valuesAndWeights[0][0] = valuesAndWeights[0][1] = 0;

		for (int i = 1; i < numOfItems + 1; i++) {
			valuesAndWeights[i][0] = sc.nextInt();
			valuesAndWeights[i][1] = sc.nextInt();
		}

		sc.close();
	}

	public void printInput() {
		System.out.println(capacity);
		System.out.println(numOfItems);
		for (int i = 1; i < numOfItems + 1; i++) {
			System.out.println(valuesAndWeights[i][0] + " " + valuesAndWeights[i][1]);
		}
	}

	public int dynamically() {

		dynamicSolution = new int[numOfItems + 1][capacity + 1];

		for (int i = 0; i <= capacity; i++)
			dynamicSolution[0][i] = 0;

		for (int i = 1; i <= numOfItems; i++)
			for (int j = 0; j <= capacity; j++) {
				if (valuesAndWeights[i][1] <= j) dynamicSolution[i][j] = max(dynamicSolution[i - 1][j],
						valuesAndWeights[i][0] + dynamicSolution[i - 1][j - valuesAndWeights[i][1]]);
				else dynamicSolution[i][j] = dynamicSolution[i - 1][j];
			}

		return dynamicSolution[numOfItems][capacity];
	}

	public void printDynamic() {
		// for (int i = 0; i <= numOfItems; i++) {
		// for (int j = 0; j <= capacity; j++) {
		// System.out.print(dynamicSolution[i][j] + " ");
		// }
		// System.out.println();
		// }
		System.out.println(dynamicSolution[numOfItems][capacity]);
		System.out.println(printDynamicSet(numOfItems, capacity));
	}

	private ArrayList<Integer> printDynamicSet(int i, int j) {
		if (i == 0) return res;
		else {
			if (dynamicSolution[i][j] != dynamicSolution[i - 1][j]) {
				res.add(i);
				return printDynamicSet(i - 1, j - valuesAndWeights[i][1]);
			} else return printDynamicSet(i - 1, j);
		}
	}

	private int max(int i, int j) {
		return (i > j) ? i : j;
	}

	// ---------------------------------------------------------------------

	private int bruteResult;
	private String bruteZerosAndOnes;

	private int seq;

	public void store(int x, String y) {
		if (x > bruteResult) {
			bruteResult = x;
			bruteZerosAndOnes = y;
		}
	}

	public void computeBestPossibility(String res, int wt, int val, int item) {
		if (val > bruteResult && wt <= capacity) store(val, res);
		if (item > numOfItems) return;
		if (wt > capacity) return;
		computeBestPossibility(res + "1", wt + valuesAndWeights[item][1], val + valuesAndWeights[item][0], item + 1);
		computeBestPossibility(res + "0", wt, val, item + 1);
	}

	public void sequential(String res, int wt, int val, int item) {
		if (val > seq && wt <= capacity) seq = val;
		if (item > numOfItems) return;
		if (wt > capacity) return;
		sequential(res + "1", wt + valuesAndWeights[item][1], val + valuesAndWeights[item][0], item + 1);
		sequential(res + "0", wt, val, item + 1);
	}

	public int multithreadedBruteForce() {

		Thread t1 = new Thread(new Runnable() {

			String t1res = "";
			int t1wt, t1val;

			@Override
			public void run() {

				t1res = "11";
				t1wt = valuesAndWeights[1][1] + valuesAndWeights[2][1];
				t1val = valuesAndWeights[1][0] + valuesAndWeights[2][0];

				if (t1wt < capacity) computeBestPossibility(t1res, t1wt, t1val, 3);
			}

		});

		Thread t2 = new Thread(new Runnable() {

			String t2res = "";
			int t2wt, t2val;

			@Override
			public void run() {

				t2res = "10";
				t2wt = valuesAndWeights[1][1];
				t2val = valuesAndWeights[1][0];

				if(t2wt<capacity)computeBestPossibility(t2res, t2wt, t2val, 3);
			}

		});

		Thread t3 = new Thread(new Runnable() {

			String t3res = "";
			int t3wt, t3val;

			@Override
			public void run() {

				t3res = "01";
				t3wt = valuesAndWeights[2][1];
				t3val = valuesAndWeights[2][0];

				if(t3wt<capacity)computeBestPossibility(t3res, t3wt, t3val, 3);
			}

		});

		Thread t4 = new Thread(new Runnable() {

			String t4res = "";
			int t4wt, t4val;

			@Override
			public void run() {

				t4res = "00";
				t4wt = 0;
				t4val = 0;
				computeBestPossibility(t4res, t4wt, t4val, 3);
			}

		});

		t1.start();
		t2.start();
		t3.start();
		t4.start();

		try {
			t1.join();
			t2.join();
			t3.join();
			t4.join();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		return bruteResult;
	}

	public void printBrute() {
		System.out.println(bruteResult);
		System.out.println(bruteZerosAndOnes);
	}

	public void printSeq() {
		System.out.println(seq);
	}
	
	int typicalBruteForceResult;
	
	public int typicalBruteForce(){
		int[] A = new int[numOfItems+1];
		double n=Math.pow(2, (double)numOfItems);
		int bnd = (int)n;
		int j, tempWeight=0, tempValue=0,bestWeight=0;
		for(int i=1;i<=bnd;i++){
			j=numOfItems;
			tempWeight=0;
			tempValue=0;
			while(A[j]!=0 && j>0){
				A[j]=0;
				j--;
			}
			A[j]=1;
			for(int k=1;k<=numOfItems;k++){
				if(A[k]==1){
					tempWeight+=valuesAndWeights[k][1];
					tempValue+=valuesAndWeights[k][0];
				}
			}
			if((tempValue>typicalBruteForceResult)&&(tempWeight<=capacity)){
				typicalBruteForceResult=tempValue;
				bestWeight=tempWeight;
			}
		}
				
		return typicalBruteForceResult;
	}
	
	
	
//--------------------------------------------------------------------------
	int mBF2result=0;
	int[] mBF2items = new int[numOfItems+1];
	
	public  void storeResult(int[] pom, int res ){
		if (res>mBF2result){
			mBF2result=res;
			mBF2items=pom;
		}
	}
	
	public int multithreadedBruteForce2(){
		
		Thread t1 = new Thread(new Runnable() {

			@Override
			public void run() {
				int bestYet=0;
				int[] A = new int[numOfItems+1];
				int[] pom = new int[numOfItems+1];
				double n=Math.pow(2, (double)numOfItems);
				int bnd = (int)n;
				int j, tempWeight=0, tempValue=0,bestWeight=0;
				for(int i=1;i<bnd/4;i++){
					j=numOfItems;
					tempWeight=0;
					tempValue=0;
					while(A[j]!=0 && j>0){
						A[j]=0;
						j--;
					}
					A[j]=1;
					for(int k=1;k<=numOfItems;k++){
						if(A[k]==1){
							tempWeight+=valuesAndWeights[k][1];
							tempValue+=valuesAndWeights[k][0];
						}
					}
					if((tempValue>bestYet)&&(tempWeight<=capacity)){
						bestYet=tempValue;
						bestWeight=tempWeight;
						System.arraycopy( A, 0, pom, 0, A.length );
					}
				}
				storeResult(pom, bestYet);
			}

		});
		Thread t2 = new Thread(new Runnable() {

			@Override
			public void run() {
				int bestYet=0;
				int[] A = new int[numOfItems+1];
				int[] pom = new int[numOfItems+1];
				A[0]=0;
				A[1]=0;
				A[2]=0;
				for(int i=3;i<=numOfItems;i++){
					A[i]=1;
				}
				double n=Math.pow(2, (double)numOfItems);
				int bnd = (int)n;
				int j, tempWeight=0, tempValue=0,bestWeight=0;
				for(int i=bnd/4;i<bnd/2;i++){
					j=numOfItems;
					tempWeight=0;
					tempValue=0;
					while(A[j]!=0 && j>0){
						A[j]=0;
						j--;
					}
					A[j]=1;
					for(int k=1;k<=numOfItems;k++){
						if(A[k]==1){
							tempWeight+=valuesAndWeights[k][1];
							tempValue+=valuesAndWeights[k][0];
						}
					}
					if((tempValue>bestYet)&&(tempWeight<=capacity)){
						bestYet=tempValue;
						bestWeight=tempWeight;
						System.arraycopy( A, 0, pom, 0, A.length );
					}
				}
				storeResult(pom, bestYet);
			}

		});
		Thread t3 = new Thread(new Runnable() {

			@Override
			public void run() {
				int bestYet=0;
				int[] A = new int[numOfItems+1];
				int[] pom = new int[numOfItems+1];
				A[0]=0;
				A[1]=0;
				for(int i=2;i<=numOfItems;i++){
					A[i]=1;
				}
				double n=Math.pow(2, (double)numOfItems);
				int bnd = (int)n;
				int j, tempWeight=0, tempValue=0,bestWeight=0;
				for(int i=bnd/2;i<(3*bnd)/4;i++){
					j=numOfItems;
					tempWeight=0;
					tempValue=0;
					while(A[j]!=0 && j>0){
						A[j]=0;
						j--;
					}
					A[j]=1;
					for(int k=1;k<=numOfItems;k++){
						if(A[k]==1){
							tempWeight+=valuesAndWeights[k][1];
							tempValue+=valuesAndWeights[k][0];
						}
					}
					if((tempValue>bestYet)&&(tempWeight<=capacity)){
						bestYet=tempValue;
						bestWeight=tempWeight;
						System.arraycopy( A, 0, pom, 0, A.length );
					}
				}
				storeResult(pom, bestYet);
			}

		});
		Thread t4 = new Thread(new Runnable() {

			@Override
			public void run() {
				int bestYet=0;
				int[] A = new int[numOfItems+1];
				int[] pom = new int[numOfItems+1];
				A[0]=0;
				A[1]=1;
				A[2]=0;
				for(int i=3;i<=numOfItems;i++){
					A[i]=1;
				}
				double n=Math.pow(2, (double)numOfItems);
				int bnd = (int)n;
				int j, tempWeight=0, tempValue=0,bestWeight=0;
				for(int i=(3*bnd)/4;i<=bnd;i++){
					j=numOfItems;
					tempWeight=0;
					tempValue=0;
					while(A[j]!=0 && j>0){
						A[j]=0;
						j--;
					}
					A[j]=1;
					for(int k=1;k<=numOfItems;k++){
						if(A[k]==1){
							tempWeight+=valuesAndWeights[k][1];
							tempValue+=valuesAndWeights[k][0];
						}
					}
					if((tempValue>bestYet)&&(tempWeight<=capacity)){
						bestYet=tempValue;
						bestWeight=tempWeight;
						System.arraycopy( A, 0, pom, 0, A.length );
					}
				}
				storeResult(pom, bestYet);
			}

		});
		
		t1.start();
		t2.start();
		t3.start();
		t4.start();

		try {
			t1.join();
			t2.join();
			t3.join();
			t4.join();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return mBF2result;
	}
}



