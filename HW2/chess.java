import java.io.*;
import java.util.*;


class Node {
	Node head;
	Node after = null;
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
	static Node clearList(Node clear){//clears list starting from top, returns last node
		clear = clear.head;
		while (clear.after != null){
			System.out.println("the head node is: "+clear.head.piece);
			clear = deleteNode(clear);
			
		}
		return clear;
	}
}
class chess extends Node{

	static public void main(String[] args) throws IOException{
		Scanner in = new Scanner(new File(args[0]));//in file
		PrintWriter out = new PrintWriter(new File(args[1]));//out file
		Node poop = new Node();//initiate linked list
		poop.head = poop;
		String[] find = new String[2];
		String input;
		int i = 0;
		while (in.hasNextLine()){
			System.out.println(i++);
			input = in.nextLine();//get board data line
			poop = clearList(poop);
			poop = createBoard(input, poop);//make linked list of pieces
/*
			
			System.out.println("the board is: "+verify(poop));
			poop = poop.head;
			while (poop!=null){
			System.out.print("Bsize: "+poop.piece.boardSize);
			System.out.print("  (x,y): "+(poop.piece.X)+","+(poop.piece.Y));
			System.out.println("  piece: "+poop.piece);
			poop = poop.after;
		}
		*/
			input = in.nextLine();//get square
			if (verify(poop)==true){//board is good
				find = input.split(" ");//parse second line and get piece at space
				poop = find(Integer.parseInt(find[0]),Integer.parseInt(find[1]),poop);
				if (poop != null){//found space
					out.print(poop.piece.type+" ");
				}
				else{
					out.print("- ");
				}
			}
			else {
				out.println("Invalid");
			}
			poop = poop.head;
			/*
			while (poop!=null){
				System.out.println(poop.piece);
				poop = poop.after;
			}
			*/
			poop=poop.head;
			while(poop.after!=null){
				poop=poop.after;
			}
			System.out.println("last node is: "+poop.piece);

		}
		in.close();
		out.close();
		/*
		int[] attacks = new int[poop.piece.boardSize*poop.piece.boardSize];

		Arrays.fill(attacks, -1);
		System.out.println(attacks[1]);
		poop = poop.head;
		Node helper = poop;
		System.out.println(poop.piece);
		queen queef = new queen();
		queef.boardSize=6;
		queef.X=3;
		queef.Y = 3;
		
		/*
		for(int i = 0; attacks[i]!= -1;){
			System.out.println(attacks[i++]+" "+attacks[i++]);
		}
		
	
		input = "8 q 4 3 k 4 4 r 8 2 r 8 8 b 1 1 K 4 8 N 7 7";
		poop = createBoard(input, poop);//make linked list of pieces
		Node helper = poop;
		int[] attacks = new int[poop.piece.boardSize*poop.piece.boardSize];
		System.out.print("Bsize: "+poop.piece.boardSize);
			System.out.print("  (x,y): "+(poop.piece.X)+","+(poop.piece.Y));
			System.out.println("  piece: "+poop.piece);	
		attacks = poop.piece.attack(poop.piece);//generate attack array
		for (i=0; i<attacks.length;){
			System.out.println("attacks: "+attacks[i++]+" "+attacks[i++]);
		}
		for (i = 0; attacks[i] != 0;){//all elements in attack array
			helper = find(attacks[i++],attacks[i++],poop);//search list for attack spaces
			 if(helper != null){//node at piece it can attack
			 	attacks[i] = 0;//exit loop
			 }
			 //if
		}
		/*
		poop = head;
		while (i<=2){
			System.out.println(i++);
			input = in.nextLine();//get board data line
			poop = createBoard(input, poop);//make linked list of pieces

			
			System.out.println("the board is: "+verify(poop));
			poop = poop.head;
			while (poop!=null){
			System.out.print("Bsize: "+poop.piece.boardSize);
			System.out.print("  (x,y): "+(poop.piece.X)+","+(poop.piece.Y));
			System.out.println("  piece: "+poop.piece);
			poop = poop.after;
		}
		}
		
		System.out.println("piece "+poop.piece.type+" at ("+poop.piece.X+","+poop.piece.Y+")"+
			" attacks "+helper.piece.type+" at ("+helper.piece.X+","+helper.piece.Y+")");
		*/	
			
	}





	static Node createBoard(String firstL, Node helper) throws IOException{//returns linked list of board
		String[] data = firstL.split(" ");//split line into characters
		int length = data.length-1;//last place in array
		/*for (int i = 0; i <= length; i++){
			System.out.print(data[i]);
		}*/
		int i = 0;//start after board size
		//System.out.println("lengnth is: "+length);
		while (i<length){//for all data
			
			//System.out.println("i is: "+i);
			switch (data[++i].toUpperCase()) {//create chess piece type

				case "K":
					helper.piece = new King();
					helper.piece.type = 'k';
					break;

				case "Q":
					helper.piece = new queen();
					helper.piece.type = 'q';
					break;

				case "R":
					helper.piece = new Rook();
					helper.piece.type = 'r';
					break;

				case "B":
					helper.piece = new Bishop();
					helper.piece.type = 'b';
					break;

				case "N":
					helper.piece = new Knight();
					helper.piece.type = 'n';
					break;
			}
			//System.out.println("i is: "+i+"piece type is: "+helper.piece.type);
			if(data[i]==data[i].toUpperCase()){//check if black
				helper.piece.type = Character.toUpperCase(helper.piece.type);
			}
			helper.piece.X = Integer.parseInt(data[++i]);//add x place 
			helper.piece.Y = Integer.parseInt(data[++i]);//add y place
			helper.piece.boardSize = Integer.parseInt(data[0]);//add board size
			if(i<length){
				helper=createNode(helper);
			}
		}
		return helper.head;
	}

	static Node find(int x, int y, Node helper){//takes in (x,y) returns found node
		helper=helper.head;//start at head
		while (helper != null){//till end of linked list
			if (x == helper.piece.X && y == helper.piece.Y){
				return helper;
			}
			helper=helper.after;
		}
		return null;//returns null if piece doesnt exist
	}

	static boolean verify(Node lala){//returns true if good
		int good;//check kings
		lala = lala.head;
		Node helper;
		while (lala.after != null){//make sure no duplicates, returns false if there is
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
		helper = lala.head;
		good = 0;
		while(helper != null){
			if(helper.piece.type == 'k'){//white king
				good++;
			}
			if(helper.piece.type == 'K'){//black king
				good++;
			}
			helper = helper.after;
		}
		if (good == 2) return true;//2 kings of each color
		else return false;//no 2 kings	
	}

	
}

class Knight extends chessPiece {
	int[] attack(chessPiece piece){//returns positions that piece can attack
		int[] spots = new int[piece.boardSize*piece.boardSize];
		int i = 0;
		if (piece.Y-2 > 0){//down
			if(piece.X-1 > 0){// left
			spots[i++] = piece.X-1;//store x place incriments i
			spots[i++] = piece.Y-2;//store y place increment i
		}
			if(piece.X+1 < piece.boardSize){//right
			spots[i++] = piece.X+1;//store x place incriments i
			spots[i++] = piece.Y-2;//store y place increment i
		}	
		}
		if (piece.Y+2 < piece.boardSize){//up
			if(piece.X-1 > 0){// left
			spots[i++] = piece.X-1;//store x place incriments i
			spots[i++] = piece.Y+2;//store y place increment i
		}
			if(piece.X+1 < piece.boardSize){//right
			spots[i++] = piece.X+1;//store x place incriments i
			spots[i++] = piece.Y+2;//store y place increment i
		}	
		}
		if (piece.X-2 > 0){//left
			if(piece.Y-1 > 0){// down
			spots[i++] = piece.X-2;//store x place incriments i
			spots[i++] = piece.Y-1;//store y place increment i
		}
			if(piece.Y+1 < piece.boardSize){//up
			spots[i++] = piece.X-2;//store x place incriments i
			spots[i++] = piece.Y+1;//store y place increment i
		}	
		}
		if (piece.X+2 < piece.boardSize){//right
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
	int[] attack(chessPiece piece){
		int[] spots = new int[piece.boardSize*piece.boardSize];
		int i = 0;
		for (int j = 1; j<piece.boardSize;j++){
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
	int[] attack(chessPiece piece){
		int[] spots = new int[piece.boardSize*piece.boardSize];
		int j = 1;
		int i = 0;//position in output array
		while (piece.Y+j<=(piece.boardSize) && piece.X-j>0){//up and left
			spots[i++] = piece.X-j;//store position
			spots[i++] = piece.Y+j;
			j++;
		}

		j=1;
		while (piece.Y-j>0 && piece.X-j>0){//down and left
			spots[i++] = piece.X-j;//store position
			spots[i++] = piece.Y-j;
			j++;
		}		
		
		j=1;
		while (piece.Y+j<=(piece.boardSize) && piece.X+j<=(piece.boardSize)){//up and right
			spots[i++] = piece.X+j;//store position
			spots[i++] = piece.Y+j;
			j++;
		}

		j=1;
		while (piece.Y-j > 0 && piece.X+j <= piece.boardSize){//down and right
			spots[i++] = piece.X+j;//store position
			spots[i++] = piece.Y-j;		
			j++;
		}
		return spots;
	}
}

class King extends chessPiece{
	int[] attack(chessPiece piece){
		int[] spots = new int[piece.boardSize*piece.boardSize];
		int i = 0;
		
		if (piece.X == 0){//if at left edge of board
			//right
			spots[i++] = piece.Y;
			spots[i++] = piece.X+1;
			if (piece.Y == 0){//at top
				//down
				spots[i++] = piece.Y-1;
				spots[i++] = piece.X;
				//lower right diagonal
				spots[i++] = piece.Y-1;
				spots[i++] = piece.X+1;	
		}
			else if (piece.Y == piece.boardSize){//at bottom
				//up
				spots[i++] = piece.Y+1;
				spots[i++] = piece.X;
				//upper right diagonal
				spots[i++] = piece.Y+1;
				spots[i++] = piece.X+1;
		}

			else{//can do all moves not at left
				//down
				spots[i++] = piece.Y-1;
				spots[i++] = piece.X;
				//lower right diagonal
				spots[i++] = piece.Y-1;
				spots[i++] = piece.X+1;	
				//up
				spots[i++] = piece.Y+1;
				spots[i++] = piece.X;
				//upper right diagonal
				spots[i++] = piece.Y+1;
				spots[i++] = piece.X+1;
			}
		}

	else if (piece.X == piece.boardSize){//piece at right edge
			//left
			spots[i++] = piece.Y;
			spots[i++] = piece.X-1;
			if (piece.Y == 0){//at top
				//down
				spots[i++] = piece.Y-1;
				spots[i++] = piece.X;
				//lower left diagonal
				spots[i++] = piece.Y-1;
				spots[i++] = piece.X-1;	
		}
			else if (piece.Y == piece.boardSize){//at bottom
			//up
			spots[i++] = piece.Y+1;
			spots[i++] = piece.X;
			//upper left diagonal
			spots[i++] = piece.Y+1;
			spots[i++] = piece.X-1;
		}
		else{
			//up
			spots[i++] = piece.Y+1;
			spots[i++] = piece.X;
			//upper left diagonal
			spots[i++] = piece.Y+1;
			spots[i++] = piece.X-1;
			//down
			spots[i++] = piece.Y-1;
			spots[i++] = piece.X;
			//lower left diagonal
			spots[i++] = piece.Y-1;
			spots[i++] = piece.X-1;	
		}
	}
	else if (piece.Y == piece.boardSize){//at top
			//down
			spots[i++] = piece.Y-1;
			spots[i++] = piece.X;
			if (piece.X == piece.boardSize){//piece at right edge
				//left
				spots[i++] = piece.Y;
				spots[i++] = piece.X-1;
				//lower left diagonal
				spots[i++] = piece.Y-1;
				spots[i++] = piece.X-1;	
			}
			else if (piece.X == 0){//if at left edge of board
				//right
				spots[i++] = piece.Y;
				spots[i++] = piece.X+1;
				//lower right diagonal
				spots[i++] = piece.Y-1;
				spots[i++] = piece.X+1;	
			}
			else {//can do all moves
					//left
				spots[i++] = piece.Y;
				spots[i++] = piece.X-1;
				//lower left diagonal
				spots[i++] = piece.Y-1;
				spots[i++] = piece.X-1;	
				//right
				spots[i++] = piece.Y;
				spots[i++] = piece.X+1;
				//lower right diagonal
				spots[i++] = piece.Y-1;
				spots[i++] = piece.X+1;	
			}
		}
		else if (piece.Y == 0){//at bottom
			//up
			spots[i++] = piece.Y+1;
			spots[i++] = piece.X;
			if (piece.X == piece.boardSize){//piece at right edge
				//left
				spots[i++] = piece.Y;
				spots[i++] = piece.X-1;
				//upper left diagonal
				spots[i++] = piece.Y+1;
				spots[i++] = piece.X-1;	
			}
			else if (piece.X == 0){//if at left edge of board
				//right
				spots[i++] = piece.Y;
				spots[i++] = piece.X+1;
				//upper right diagonal
				spots[i++] = piece.Y+1;
				spots[i++] = piece.X+1;	
			}
			else {//can do all moves
				//left
				spots[i++] = piece.Y;
				spots[i++] = piece.X-1;
				//upper left diagonal
				spots[i++] = piece.Y+1;
				spots[i++] = piece.X-1;	
				//right
				spots[i++] = piece.Y;
				spots[i++] = piece.X+1;
				//upper right diagonal
				spots[i++] = piece.Y+1;
				spots[i++] = piece.X+1;	
			}
		}
		else {//not at board edge
			//left
			spots[i++] = piece.Y;
			spots[i++] = piece.X-1;
			//upper left diagonal
			spots[i++] = piece.Y+1;
			spots[i++] = piece.X-1;	
			//right
			spots[i++] = piece.Y;
			spots[i++] = piece.X+1;
			//upper right diagonal
			spots[i++] = piece.Y+1;
			spots[i++] = piece.X+1;	
			//up
			spots[i++] = piece.Y+1;
			spots[i++] = piece.X;
			//down
			spots[i++] = piece.Y-1;
			spots[i++] = piece.X;
			//lower left diagonal
			spots[i++] = piece.Y-1;
			spots[i++] = piece.X-1;	
			//lower right diagonal
			spots[i++] = piece.Y-1;
			spots[i++] = piece.X+1;	

		}
		return spots;
	}
}

class queen extends chessPiece{
	int[] attack(chessPiece piece){
		int[] spots = new int[piece.boardSize*piece.boardSize];
		int i=0;
		int j;

		for (j=1; j<piece.boardSize;j++){//up down left right
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

		while (piece.Y+j<(piece.boardSize) && piece.X-j>0){//down and left
			spots[i++] = piece.X-j;//store position
			spots[i++] = piece.Y+j;
			j++;
		}

		j=1;
		while (piece.Y-j>0 && piece.X-j>0){//up and left
			spots[i++] = piece.X-j;//store position
			spots[i++] = piece.Y-j;
			j++;
		}		
		
		j=1;
		while (piece.Y+j<=(piece.boardSize) && piece.X+j<=(piece.boardSize)){//down and right
			spots[i++] = piece.X+j;//store position
			spots[i++] = piece.Y+j;
			j++;
		}

		j=1;
		while (piece.Y-j > 0 && piece.X+j <= piece.boardSize-1){//up and right
			spots[i++] = piece.X+j;//store position
			spots[i++] = piece.Y-j;		
			j++;
		}
		
		return spots;
	}
}