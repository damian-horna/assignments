import java.util.ArrayList;
import java.util.Scanner;

public class BinarySearchTree
{

	private static Scanner scanner;

	public static void main(String[] args)
	{

		System.out.print("How many elements: ");
		scanner = new Scanner(System.in);
		int howMany = scanner.nextInt();
		ArrayList<Integer> reading = new ArrayList<Integer>();
		int[] a = Generator.generateUniqueRandomArray(howMany);

		int[] aSorted = new int[howMany];
		for (int i = 0; i < howMany; i++)
			aSorted[i] = i + 1;

		BST BSTree = new BST(a);
		BST degeneratedBST = new BST(aSorted);
		AVL AVLTree = new AVL(aSorted);

		for (int i = 0; i < howMany; i++)
			System.out.print(" " + a[i]);

		System.out.println("\nAVL: ");
		AVLTree.display(AVLTree.getRoot(), 1);
		System.out.println("\nDegenerated BST: ");
		degeneratedBST.display(degeneratedBST.getRoot(), 1);
		System.out.println("\nBST: ");
		BSTree.display(BSTree.getRoot(), 1);

		int action = 0;
		int elem;
		while (action != 10)
		{
			System.out.println("\nACTIONS:");
			System.out.println("1. Find");
			System.out.println("2. Insert");
			System.out.println("3. Delete");
			System.out.println("4. Balance an AVL");
			System.out.println("10. Exit");
			System.out.println("Your choice: ");
			action = scanner.nextInt();
			switch (action)
			{
			case 1:
				System.out.println("What to find: ");
				elem = scanner.nextInt();
				if (BSTree.find(elem)) System.out.println("BST: Element "
						+ elem + " found.");
				else System.out.println("BST: Not found.");

				if (degeneratedBST.find(elem)) System.out
						.println("Degenerated: Element " + elem + " found.");
				else System.out.println("Degenerated: Not found.");

				if (AVLTree.find(elem)) System.out.println("AVL: Element "
						+ elem + " found.");
				else System.out.println("AVL: Not found.");

				break;
			case 2:
				System.out.println("What to insert: ");
				elem = scanner.nextInt();
				BSTree.insert(elem);
				degeneratedBST.insert(elem);
				AVLTree.insert(elem);

				System.out.println("\nAVL: ");
				AVLTree.display(AVLTree.getRoot(), 1);
				System.out.println("\nDegenerated BST: ");
				degeneratedBST.display(degeneratedBST.getRoot(), 1);
				System.out.println("\nBST: ");
				BSTree.display(BSTree.getRoot(), 1);

				break;
			case 3:
				System.out.println("What to delete: ");
				elem = scanner.nextInt();
				BSTree.delete(elem);
				degeneratedBST.delete(elem);
				AVLTree.delete(elem);

				System.out.println("\nAVL: ");
				AVLTree.display(AVLTree.getRoot(), 1);
				System.out.println("\nDegenerated BST: ");
				degeneratedBST.display(degeneratedBST.getRoot(), 1);
				System.out.println("\nBST: ");
				BSTree.display(BSTree.getRoot(), 1);
				break;
			case 4:
				BSTree.balanceAVL();
				System.out.println("\nBST---> Balanced AVL: ");
				BSTree.display(BSTree.getRoot(), 1);
				break;

			}

		}

	}
}

