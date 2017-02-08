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
		if (clear.after != null){
			clearList(clear.after);
		}
		if (clear != clear.head) deleteNode(clear); //delete up to head
		return clear;//return head
	}
}