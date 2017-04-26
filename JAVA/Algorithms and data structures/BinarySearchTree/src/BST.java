import java.util.ArrayList;

public class BST
{
	private Node root = new Node(0);

	public Node getRoot()
	{
		return root;
	}

	public void setRoot(Node root)
	{
		this.root = root;
	}

	public BST(int[] array)
	{
		root.data = array[0];
		for (int i = 1; i < array.length; i++)
			insert(array[i]);
	}

	public boolean find(int elem)
	{
		Node current = root;
		while (current != null)
		{
			if (current.data == elem)
			{
				current = null;
				return true;
			}
			else
			{
				if (elem < current.data) current = current.left;
				else current = current.right;
			}
		}
		current = null;
		return false;
	}

	public void insert(int elem)
	{
		root = insertRec(root, elem);
	}

	public void delete(int elem)
	{
		setRoot(deleteRec(getRoot(), elem));
	}

	public void balanceAVL()
	{
		ArrayList<Integer> inOrder = new ArrayList<Integer>();

		readInOrder(root, inOrder);

		int len = inOrder.size();
		int[] arr = new int[len];

		for (int i = 0; i < len; i++)
			arr[i] = (int) inOrder.get(i);

		// arr is sorted(read inOrder)

		deleteTree(root);
		root = new Node(arr[arr.length / 2]);
		createAVL(arr, arr.length / 2, root, 0, arr.length - 1);
	}

	public void deleteTree(Node node)
	{
		postOrderDeletion(node);
		setRoot(null);
	}

	public void display(Node node, int level)
	{
		if (node != null)
		{
			display(node.right, level + 1);

			System.out.println();
			for (int i = 0; i < level; i++)
				System.out.print("     ");
			System.out.print(node.data);

			display(node.left, level + 1);
		}
	}

	public void readInOrder(Node node, ArrayList<Integer> arr)
	{
		if (node != null)
		{
			readInOrder(node.left, arr);
			arr.add(node.data);
			readInOrder(node.right, arr);
		}

	}

	public void readPreOrder(Node node, ArrayList<Integer> arr)
	{
		if (node != null)
		{
			arr.add(node.data);
			readPreOrder(node.left, arr);
			readPreOrder(node.right, arr);
		}
	}

	private Node insertRec(Node root, int elem)
	{

		if (root == null)
		{
			root = new Node(elem);
			return root;
		}

		if (elem < root.data) root.left = insertRec(root.left, elem);
		else if (elem > root.data) root.right = insertRec(root.right, elem);

		return root;
	}

	private Node deleteRec(Node root, int elem)
	{
		if (root == null) return root;

		if (elem < root.data) root.left = deleteRec(root.left, elem);
		else if (elem > root.data) root.right = deleteRec(root.right, elem);

		else
		{
			if (root.left == null) return root.right;
			else if (root.right == null) return root.left;

			root.data = minValue(root.right);

			root.right = deleteRec(root.right, root.data);
		}

		return root;
	}

	private int minValue(Node root)
	{
		int minv = root.data;
		while (root.left != null)
		{
			minv = root.left.data;
			root = root.left;
		}
		return minv;
	}

	/**
	 * this function creates AVL tree recursively from an sorted array
	 * 
	 * @param a
	 *            - sorted array
	 * @param len
	 *            - position when we've inserted the last element
	 * @param node
	 *            - last inserted element
	 * @param left
	 *            - left boundary
	 * @param right
	 *            -right boundary
	 */
	private void createAVL(int[] a, int len, Node node, int left, int right)
	{

		if ((len - (len - left + 1) / 2) >= left && len != left)
		{
			Node newNodeL = new Node(a[len - (len - left + 1) / 2]);
			node.left = newNodeL;
		}
		if ((len + (len - left + 1) / 2) <= right && len != right)
		{
			if (len == left && left == right - 1)
			{
				Node newNodeR = new Node(a[right]);
				node.right = newNodeR;
			}
			else
			{
				Node newNodeR = new Node(a[len + (len - left + 1) / 2]);
				node.right = newNodeR;
			}
		}
		if (len == left || len == right) return;
		createAVL(a, len - (len - left + 1) / 2, node.left, left, len - 1);
		createAVL(a, len + (len - left + 1) / 2, node.right, len + 1, right);
	}

	private void postOrderDeletion(Node node)
	{
		if (node != null)
		{
			postOrderDeletion(node.left);
			node.left = null;
			postOrderDeletion(node.right);
			node.right = null;
		}
	}
}
