import java.util.ArrayList;


public class AVL
{
	private NodeAVL root;

	public NodeAVL getRoot()
	{
		return root;
	}

	public void setRoot(NodeAVL root)
	{
		this.root = root;
	}

	public AVL(int[] a)
	{
		root = new NodeAVL(a[0]);
		for (int i = 1; i < a.length; i++)
			insert(a[i]);
		// createAVL(a, a.length / 2, root, 0, a.length - 1);
	}

	public boolean find(int elem)
	{
		NodeAVL current = root;
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
		setRoot(insertRec(this.getRoot(), elem));
	}

	public void delete(int elem)
	{
		setRoot(deleteNode(getRoot(), elem));
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
		root = new NodeAVL(arr[arr.length / 2]);
		createAVL(arr, arr.length / 2, root, 0, arr.length - 1);
	}

	public void deleteTree(NodeAVL node)
	{
		postOrderDeletion(node);
		setRoot(null);
	}

	public void display(NodeAVL node, int level)
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

	public void readInOrder(NodeAVL node, ArrayList<Integer> arr)
	{
		if (node != null)
		{
			readInOrder(node.left, arr);
			arr.add(node.data);
			readInOrder(node.right, arr);
		}

	}

	public void readPreOrder(NodeAVL node, ArrayList<Integer> arr)
	{
		if (node != null)
		{
			arr.add(node.data);
			readPreOrder(node.left, arr);
			readPreOrder(node.right, arr);
		}
	}

	private int height(NodeAVL N)
	{
		if (N == null) return 0;

		return N.height;
	}

	private int max(int a, int b)
	{
		return (a > b) ? a : b;
	}

	private NodeAVL rightRotate(NodeAVL y)
	{
		NodeAVL x = y.left;
		NodeAVL T2 = x.right;

		// Performing rotation
		x.right = y;
		y.left = T2;

		// Updating heights
		y.height = max(height(y.left), height(y.right)) + 1;
		x.height = max(height(x.left), height(x.right)) + 1;

		return x;
	}

	private NodeAVL leftRotate(NodeAVL x)
	{
		NodeAVL y = x.right;
		NodeAVL T2 = y.left;

		// Performing rotation
		y.left = x;
		x.right = T2;

		// Updating heights
		x.height = max(height(x.left), height(x.right)) + 1;
		y.height = max(height(y.left), height(y.right)) + 1;

		return y;
	}

	private int getBalance(NodeAVL N)
	{
		if (N == null) return 0;

		return height(N.left) - height(N.right);
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
	private void createAVL(int[] a, int len, NodeAVL node, int left, int right)
	{

		if ((len - (len - left + 1) / 2) >= left && len != left)
		{
			NodeAVL newNodeL = new NodeAVL(a[len - (len - left + 1) / 2]);
			node.left = newNodeL;
		}
		if ((len + (len - left + 1) / 2) <= right && len != right)
		{
			if (len == left && left == right - 1)
			{
				NodeAVL newNodeR = new NodeAVL(a[right]);
				node.right = newNodeR;
			}
			else
			{
				NodeAVL newNodeR = new NodeAVL(a[len + (len - left + 1) / 2]);
				node.right = newNodeR;
			}
		}
		if (len == left || len == right) return;
		createAVL(a, len - (len - left + 1) / 2, node.left, left, len - 1);
		createAVL(a, len + (len - left + 1) / 2, node.right, len + 1, right);
	}

	private NodeAVL insertRec(NodeAVL node, int elem)
	{

		if (node == null) return (new NodeAVL(elem));
		
		if (elem < node.data) node.left = insertRec(node.left, elem);
		else if (elem > node.data) node.right = insertRec(node.right, elem);
		else return node;

		node.height = 1 + max(height(node.left), height(node.right));

		int balance = getBalance(node);

		// Left Left
		if (balance > 1 && elem < node.left.data) return rightRotate(node);

		// Right Right
		if (balance < -1 && elem > node.right.data) return leftRotate(node);

		// Left Right
		if (balance > 1 && elem > node.left.data)
		{
			node.left = leftRotate(node.left);
			return rightRotate(node);
		}

		// Right Left
		if (balance < -1 && elem < node.right.data)
		{
			node.right = rightRotate(node.right);
			return leftRotate(node);
		}

		return node;
	}

	private NodeAVL deleteNode(NodeAVL root, int elem)
	{
		if (root == null) return root;

		if (elem < root.data) root.left = deleteNode(root.left, elem);

		else if (elem > root.data) root.right = deleteNode(root.right, elem);

		else
		{

			//only one child or no child
			if ((root.left == null) || (root.right == null))
			{
				NodeAVL temp = null;
				if (temp == root.left) temp = root.right;
				else temp = root.left;

				// No child
				if (temp == null)
				{
					temp = root;
					root = null;
				}
				else // One child
				root = temp;
			}
			else
			{

				//smallest in right subtree
				NodeAVL temp = minValueNode(root.right);

				// Copy the inorder successor's data to this node
				root.data = temp.data;

				// Delete the inorder successor
				root.right = deleteNode(root.right, temp.data);
			}
		}

		if (root == null) return root;

		root.height = max(height(root.left), height(root.right)) + 1;

		int balance = getBalance(root);

		// Left Left
		if (balance > 1 && getBalance(root.left) >= 0)
			return rightRotate(root);

		// Left Right
		if (balance > 1 && getBalance(root.left) < 0)
		{
			root.left = leftRotate(root.left);
			return rightRotate(root);
		}

		// Right Right
		if (balance < -1 && getBalance(root.right) <= 0)
			return leftRotate(root);

		// Right Left
		if (balance < -1 && getBalance(root.right) > 0)
		{
			root.right = rightRotate(root.right);
			return leftRotate(root);
		}

		return root;
	}
	private NodeAVL minValueNode(NodeAVL node)
	{
		NodeAVL current = node;

		while (current.left != null)
			current = current.left;

		return current;
	}

	private void postOrderDeletion(NodeAVL node)
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
