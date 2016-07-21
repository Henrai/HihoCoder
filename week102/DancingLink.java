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
    public boolean compare(Node n1, Node n2) {
        return (n1.x == n2.x && n1.y == n2.y);
    }
    Node head;
    Node[] columHead;
    Node[] node;
    int[][] id;
    int [][] matrix;
    int [] cnt;
    int mincnt, cntnum;
    int[][] ans;
    public DancingLink() {
        head = null;
        mincnt = -1;
        cntnum = -1;
        ans = new int[10][10];
    }
    public void set(int i, int j, int k) {
        int id = (i - 1) * 9 + j;
        int pid = (id - 1) * 9 + k;
        matrix[pid][(i - 1)*9 + k] = 1;
        matrix[pid][81 + (j-1)*9 + k] = 1;
        int t = ((i - 1) / 3 * 3 + (j - 1) / 3) + 1;
        matrix[pid][162 + (t - 1) * 9 + k] = 1;
        matrix[pid][243 + id] = 1;
    }
    public void create(int[][] board) {
        matrix = new int [750][330];
        for(int i = 1; i <= 9; i++)
            for(int j = 1; j <= 9; j++) {
                if(board[i][j] == 0) {
                    for(int k = 1; k <= 9; k++)
                        set(i, j, k);
                }
                else
                    set(i, j, board[i][j]);
            }
    }
    Node findMinCnt() {
        Node ans = null, p = head.right;
        int min = 214748364;
        int i = 0;
        while(p != head) {
            if(cnt[p.y] < min) {
                min = cnt[p.y];
                ans = p;
            }
            p = p.right;
        }
        return ans;
    }
    public void build() {
        int n = 729;
        int m = 324;
    	head = new Node(0, 0);
    	columHead = new Node[m+1];
    	node = new Node[n*m + 1];
    	id = new int[n+1][m+1];
    	cnt = new int[1000];
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
    	int count = 0;
    	for(int i = 1; i <= n; i++)
    		for(int j = 1; j <= m; j++) {
    			if(matrix[i][j] == 1) {
    				count++;
    				id[i][j] = count;
    				node[count] = new Node(i,j);	
    			}
    		}
    	//up to down
    	for(int j = 1; j <= m; j++) {
    		pre = columHead[j];
    		for(int i = 1; i<= n; i++) {
    			if(matrix[i][j] == 1) {
                    cnt[j]++;
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
    			cnt[p3.y]--;
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
                cnt[p3.y]++;
    			p3 = p3.right;
    		}
    		p2 = p2.down;
    	}
    }
    
    public boolean dance(int depth) {
    	Node p = findMinCnt();
        if(head.right == head)
            return true;
    	if(compare(p, head) )
    		return true;
    	Node p2 = p.down;
    	if(compare(p2, p))
    		return false;
    	remove(p.y);
    	while(!compare(p2, p)) {
    		ans[(p2.x -1) / 81 + 1][((p2.x - 1) / 9) % 9 + 1] = (p2.x - 1) % 9 + 1;
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
    		int[][] board = new int[10][10];
    		for(int i = 1; i <= 9; i++)
    			for(int j = 1; j <= 9; j++)
    				board[i][j] = in.nextInt();
    		dlk.create(board);
            dlk.build();
    		dlk.dance(0);
          	for (int i = 1; i <= 9; i++) {
                for (int j = 1; j <= 9; j++) {
                    System.out.print(dlk.ans[i][j]);
                    System.out.print(" ");
                }
                System.out.println();
      		}
    		t--;
    	}
    }
}
