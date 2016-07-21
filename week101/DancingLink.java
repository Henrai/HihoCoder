import java.util.*;

class DancingLink {
	class Node {
		Node left,right,up,down;
		int x,y;
		Node(int x, int y)
		{
			this.x = x;
			this.y = y;
			this.left = this;
    		this.right = this;
    		this.up = this;
    		this.down = this;
		}
	}
    
    Node head;
    Node[] columHead;
    Node[] node;
    int[][] id;
    static int[] ans = new int[101];
    public DancingLink() {
        head = null;
    }
    
    public void build(int n, int m, int[][] matrix) {
    	head = new Node(0, 0);
    	columHead = new Node[m+1];
    	node = new Node[n*m + 1];
    	id = new int[n+1][m+1];
    	Node pre = head;
    	for(int i = 1; i <= m; i++) {
    		Node p = new Node(0, i);
    		columHead[i] = p;
    		p.right = pre.right;
    		p.left  = pre;
    		pre.right.left = p;
    		pre.right = p;
    		pre = p;
    	}
    	int cnt = 0;
    	for(int i = 1; i <= n; i++)
    		for(int j = 1; j <= m; j++) {
    			if(matrix[i][j] == 1) {
    				cnt++;
    				id[i][j] = cnt;
    				node[cnt] = new Node(i,j);	
    			}
    		}
    	//up to down
    	for(int j = 1; j <= m; j++) {
    		pre = columHead[j];
    		for(int i = 1; i<= n; i++) {
    			if(matrix[i][j] == 1) {
    				Node p = node[id[i][j]];
    				p.down = pre.down;
    				p.up = pre;
    				pre.down.up = p;
    				pre.down = p;
    				pre = p;
    			}

    		}
    	}
    	for(int i = 1; i <= n; i++) {
    		pre = null;
    		for(int j = 1; j <= m; j++) {
    			if(matrix[i][j] == 1) {
    				if(pre == null)
    					pre = node[id[i][j]];
    				else {
    					Node p = node[id[i][j]];
    					p.right = pre.right;
    					p.left = pre;
    					pre.right.left = p;
    					pre.right = p;
    					pre = p;
    				}
    			}
    		}
    	}
    }

    public void remove(int col) {
    	Node p = columHead[col];
    	p.right.left = p.left;
    	p.left.right = p.right;
    	Node p2 = p.down;
    	while(!compare(p2, p)) {
    		Node p3 = p2.right;
    		while(!compare(p3, p2)) {
    			p3.down.up = p3.up;
    			p3.up.down = p3.down;
    			p3 = p3.right;
    		}
    		p2 = p2.down;
    	}
    }
    public void resume(int col) {
    	Node p = columHead[col];
    	p.right.left = p;
    	p.left.right = p;
    	Node p2 = p.down;
    	while(!compare(p2, p)) {
    		Node p3 = p2.right;
    		while(!compare(p3, p2)) {
    			p3.down.up = p3;
    			p3.up.down  = p3;
    			p3 = p3.right;
    		}
    		p2 = p2.down;
    	}
    }
    public boolean compare(Node n1, Node n2) {
    	return (n1.x == n2.x && n1.y == n2.y);
    }
    public boolean dance(int depth) {
    	Node p = head.right;
    	if(compare(p, head) )
    		return true;
    	Node p2 = p.down;
    	if(compare(p2, p))
    		return false;
    	remove(p.y);
    	while(!compare(p2, p)) {
    		ans[depth] = p2.x;
    		Node p3 = p2.right;
    		while(!compare(p3, p2)) {
    			remove(p3.y);
    			p3 = p3.right;
    		}
    		if(dance(depth + 1)) {
    			return true;
    		}
    		p3 = p2.left;
    		while(!compare(p3, p2)) {
    			resume(p3.y);
    			p3 = p3.left;
    		}
    		p2 = p2.down;
    	}
    	resume(p.y);
    	return false;
    }

    public static void main(String args[])
    {
    	Scanner in = new Scanner(System.in);
    	int t = in.nextInt();
    	while(t != 0){
    		int n,m;
    		DancingLink dlk = new DancingLink();
    		n = in.nextInt();
    		m = in.nextInt(); 
    		int[][] matrix = new int[n+1][m+1];
    		for(int i = 1; i <= n; i++)
    			for(int j = 1; j <= m; j++)
    				matrix[i][j] = in.nextInt();
    		dlk.build(n, m, matrix);
    		if(dlk.dance(0))
        	{
    			System.out.println("Yes");
          		// for (int i=0; i < ans.length; i++) {
            // 		if (ans[i] == 0) break;
            // 		System.out.println(ans[i]);
          		// }
        	}
    		else 
    			System.out.println("No");
    		t--;
    	}
    }
}
