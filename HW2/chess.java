class Node {
	Node before = new Node;
	Node after = new Node;
	chessPiece piece = new chessPiece;
	static int createNode(Node before, Node after){//creates node inbetween before and after
		if (Node create = new Node){//make sure can make new node
			create.before = before; //point to node before
			create.after = after; //point to node after
			before.after = create;//make post node point to new node
			after.before = create; //make previous node point to new node 
			return 1;//success!
		} 
		else {
			return 0;
		}
		
	}
	static int deleteNode(Node delete){//deletes given node
		Node helper = delete.before;//set new node to previous one
		helper.after = delete.after;//point previous node to node after delete
		helper = delete.after;//set node to after delete
		helper.before = delete.before;//point post node to node before delete
		if (helper.before == delete.before){
			helper = delete.before;
			if (helper.after = delete.after){
				return 1;//success!
			}
			else return 0;//not able to splice post node
		}
		else return -1;//not able to splice previous node
	}
}
class chessBoard extends Node{
	static int verify(Node node, int row, int col){

	}
	static int find(int row, int col){
		while 
	}
}

class chessPiece{
	char color;//stores whether its white or black
	int row = 0;
	int col = 0;
	

}

class Rook extends chessPiece {
	static int is atta
}
class Knight extends chessPiece{

}
class Bishop extends chessPiece{

}
class King extends chessPiece{

}
class queen extends chessPiece{

}