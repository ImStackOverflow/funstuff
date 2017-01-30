import java.io.*;
import java.util.Scanner;


class Node {
	Node before = new Node();
	Node after = new Node();
	chessPiece piece = new chessPiece();
	static int createNode(Node before, Node after){//creates node inbetween before and after
		Node create = new Node();//make sure can make new node
		create.before = before; //point to node before
		create.after = after; //point to node after
		before.after = create;//make post node point to new node
		after.before = create; //make previous node point to new node 
		return 1;//success!
	}
	static int deleteNode(Node delete){//deletes given node
		Node helper = delete.before;//set new node to previous one
		helper.after = delete.after;//point previous node to node after delete
		helper = delete.after;//set node to after delete
		helper.before = delete.before;//point post node to node before delete
		if (helper.before == delete.before){
			helper = delete.before;
			helper.after = delete.after
			if (helper.after == delete.after){
				return 1;//success!
			}
			else return 0;//not able to splice post node
		}
		else return -1;//not able to splice previous node
	}
}
class chessBoard extends Node{
	static int verify(Node node, int X, int Y){

	}	
	static int find(int X, int Y){
		//while 
	}
}

class chessPiece{
	int boardSize = 0;
	char color;//stores whether its white or black
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
		for (int j = 0; j<boardSize;j++){
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
	static int[] attack(chessPiece piece){
		int[] spots = new int[piece.boardSize*piece.boardSize];
		int i = 0;
		/* needs work


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
		*/
		

	}

}

class queen extends chessPiece{
	static int[] attack(chessPiece piece){
		int[] spots = new int[piece.boardSize*piece.boardSize];
		int i=0;
		int j;

		for (j=0; j<boardSize;j++){//up down left right
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
	}
}