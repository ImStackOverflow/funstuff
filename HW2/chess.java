import java.io.*;
import java.util.Scanner;


class Node {
	Node head;
	Node after;
	chessPiece piece;


	static Node createNode(Node before){//creates node returns created node
		Node create = new Node();//make sure can make new node
		if (before == null){//trying to make new head
			return null;//fail
		}
		create.head = before.head;//set head
		create.after = before.after; //point to node after
		before.after = create;//make post node point to new node
		return create;//success!
	}

	static Node deleteNode(Node delete){//deletes given node, returns node before
		Node helper = delete.head;//set new node to head
		if (delete == delete.head){//if trying to delete head
			while (helper != null){//go through whole linked list
				helper.head = delete.after;//set head to new head
				helper = helper.after;//go through list
			}
			helper = delete.after;
			delete.after = null;//free pointer
			return helper.head;//success return head
		}
		//not deleting head
		while (helper.after != delete){//get to node before delete
			helper = helper.after;
		}
		helper.after = delete.after;//point previous node to node after delete
			if (helper.after == delete.after){
				return helper;//success!
			}
			else return null;//not able to splice in node
	}
}
class chess extends Node{
	static Node createBoard(String firstL, Node helper) throws IOException{//returns linked list of board
		String[] data = firstL.split("");//split line into characters
		int length = data.length-1;//last place in array
		int i = 0;//start after board size
		while (i<=length){//for all data
			switch (data[++i].toUpperCase()) {//create chess piece type
				case "K":
					helper.piece = new King();
					break;

				case "Q":
					helper.piece = new queen();
					break;

				case "R":
					helper.piece = new Rook();
					break;

				case "B":
					helper.piece = new Bishop();
					break;

				case "N":
					helper.piece = new Knight();
					break;
			}
			if(data[i]==data[i].toUpperCase()){//check if black
				helper.piece.color = 'b';
			}
			else {//otherwise white
				helper.piece.color = 'c';	
			}
			helper.piece.X = data[++i].parseInt;//add x place 
			helper.piece.Y = data[++i].parseInt;//add y place
			helper.piece.boardSize = data[0];//add board size

			helper = createNode(helper);//make next node
		}
		return helper.head;
	}

	static Node find(int x, int y, Node helper){//takes in (x,y) returns found node
		while (helper != null){//till end of linked list
			if (x == helper.piece.X && y == helper.piece.Y){
				return helper;
			}
			helper=helper.after;
		}
		return null;
	}

	static boolean verify(Node lala){
		lala = lala.head;
		Node helper;
		while (lala.after != null){
			helper = lala.after;
			while (helper != null){
				if (lala.piece.X == helper.piece.X
				&& lala.piece.Y == helper.piece.Y){//x y cordinates match
					return false;//2 pieces in same place
			}
			helper=helper.after;
			}
			lala = lala.after;
		}
		return true;
	}

	static public void main(String[] args){
		Scanner in = new Scanner(new File(args[0]));

		Node poop = new Node();
		poop.head = poop;
		Knight ass = new Knight();
		for (int i = 0; i < 5; i++){
			poop = createNode(poop, ass);
		}
		Node helper = poop;
		poop = poop.head;
		while (poop != null){
			poop = deleteNode(poop);
			helper = poop;
			poop = poop.after;
		}
		helper = helper.head;
		while (helper != null){
			System.out.println(helper);
			helper = helper.after;
		}
		

	}
}

class chessPiece{
	int boardSize = 0;
	char color = 'u';//stores whether its white(w) or black(b)
	int X = 0;
	int Y = 0;
}

class Knight extends chessPiece {
	static int[] attack(chessPiece piece){//returns positions that piece can attack
		int[] spots = new int[piece.boardSize*piece.boardSize];
		int i = 0;
		if (piece.Y-2 >= 0){//down
			if(piece.X-1 >= 0){// left
			spots[i++] = piece.X-1;//store x place incriments i
			spots[i++] = piece.Y-2;//store y place increment i
		}
			if(piece.X+1 < piece.boardSize){//right
			spots[i++] = piece.X+1;//store x place incriments i
			spots[i++] = piece.Y-2;//store y place increment i
		}	
		}
		if (piece.Y+2 <= piece.boardSize){//up
			if(piece.X-1 >= 0){// left
			spots[i++] = piece.X-1;//store x place incriments i
			spots[i++] = piece.Y+2;//store y place increment i
		}
			if(piece.X+1 < piece.boardSize){//right
			spots[i++] = piece.X+1;//store x place incriments i
			spots[i++] = piece.Y+2;//store y place increment i
		}	
		}
		if (piece.X-2 >= 0){//left
			if(piece.Y-1 >= 0){// down
			spots[i++] = piece.X-2;//store x place incriments i
			spots[i++] = piece.Y-1;//store y place increment i
		}
			if(piece.Y+1 < piece.boardSize){//up
			spots[i++] = piece.X-2;//store x place incriments i
			spots[i++] = piece.Y+1;//store y place increment i
		}	
		}
		if (piece.X+2 <= piece.boardSize){//right
			if(piece.Y-1 >= 0){// down
			spots[i++] = piece.X+2;//store x place incriments i
			spots[i++] = piece.Y-1;//store y place increment i
		}
			if(piece.Y+1 < piece.boardSize){//up
			spots[i++] = piece.X+2;//store x place incriments i
			spots[i++] = piece.Y+1;//store y place increment i
		}	
		}
		return spots;
	}
}

class Rook extends chessPiece{
	static int[] attack(chessPiece piece){
		int[] spots = new int[piece.boardSize*piece.boardSize];
		int i = 0;
		for (int j = 0; j<piece.boardSize;j++){
			if(j == piece.Y){}//dont store current piece position in attack array
			else {
				spots[i++] = piece.X;//store up and down attack spaces
				spots[i++] = j;
			}
			
			if(j == piece.X){}//dont store current piece position in attack array
			else {
			spots[i++] = j;//store left and right attack spaces
			spots[i++] = piece.Y;
		}
		}
		return spots;
	}
}

class Bishop extends chessPiece{
	static int[] attack(chessPiece piece){
		int[] spots = new int[piece.boardSize*piece.boardSize];
		int j = 0;
		int i = 0;//position in output array
		while (piece.Y+j!=(piece.boardSize) && piece.X-j>=0){//down and left
			spots[i++] = piece.X-j;//store position
			spots[i++] = piece.Y+j;
			j++;
		}

		j=0;
		while (piece.Y-j>=0 && piece.X-j>=0){//up and left
			spots[i++] = piece.X-j;//store position
			spots[i++] = piece.Y-j;
			j++;
		}		
		
		j=0;
		while (piece.Y+j!=(piece.boardSize) && piece.X+j!=(piece.boardSize)){//down and right
			spots[i++] = piece.X+j;//store position
			spots[i++] = piece.Y+j;
			j++;
		}

		j=0;
		while (piece.Y-j >= 0 && piece.X+j <= piece.boardSize-1){//up and right
			spots[i++] = piece.X+j;//store position
			spots[i++] = piece.Y-j;		
			j++;
		}
		return spots;
	}
}

class King extends chessPiece{
	/* needs work
	static int[] attack(chessPiece piece){
		int[] spots = new int[piece.boardSize*piece.boardSize];
		int i = 0;
		


		if (piece.x >= 0){//if not at left edge of board
			//left
			spots[i++] = piece.Y;
			spots[i++] = piece.X-1;
			//upper left diagonal

			cant index upper left when at top of board
			need way to check this
			spots[i++] = piece.Y-1;
			spots[i++] = piece.X-1;
			//lower left diagonal
			spots[i++] = piece.Y+1;
			spots[i++] = piece.X-1;
		}

		if (piece.x < piece.boardSize){//piece not at right edge
			//right
			spots[i++] = piece.Y;
			spots[i++] = piece.X+1;
			//upper right diagonal
			spots[i++] = piece.Y-1;
			spots[i++] = piece.X+1;
			//lower right diagonal
			spots[i++] = piece.Y+1;
			spots[i++] = piece.X+1;		
		}
		
		if (piece.y >= 0){//not at top
			//up
			spots[i++] = piece.Y-1;
			spots[i++] = piece.X;
		}
		
		if (piece.y <= piece.boardSize){//not at bottom
			//down
			spots[i++] = piece.Y+1;
			spots[i++] = piece.X;
		}


	}
	*/

}

class queen extends chessPiece{
	static int[] attack(chessPiece piece){
		int[] spots = new int[piece.boardSize*piece.boardSize];
		int i=0;
		int j;

		for (j=0; j<piece.boardSize;j++){//up down left right
			if(j == piece.Y){}//dont store current piece position in attack array
			else {
				spots[i++] = piece.X;//store up and down attack spaces
				spots[i++] = j;
			}
			
			if(j == piece.X){}//dont store current piece position in attack array
			else {
			spots[i++] = j;//store left and right attack spaces
			spots[i++] = piece.Y;
		}
		}

		while (piece.Y+j!=(piece.boardSize) && piece.X-j>=0){//down and left
			spots[i++] = piece.X-j;//store position
			spots[i++] = piece.Y+j;
			j++;
		}

		j=0;
		while (piece.Y-j>=0 && piece.X-j>=0){//up and left
			spots[i++] = piece.X-j;//store position
			spots[i++] = piece.Y-j;
			j++;
		}		
		
		j=0;
		while (piece.Y+j!=(piece.boardSize) && piece.X+j!=(piece.boardSize)){//down and right
			spots[i++] = piece.X+j;//store position
			spots[i++] = piece.Y+j;
			j++;
		}

		j=0;
		while (piece.Y-j >= 0 && piece.X+j <= piece.boardSize-1){//up and right
			spots[i++] = piece.X+j;//store position
			spots[i++] = piece.Y-j;		
			j++;
		}
		return spots;
	}
}