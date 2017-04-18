public abstract class chessPiece{
	int boardSize = 0;
	char type = 'u';//stores piece type
	char shit = 'u';
	int X = 0;
	int Y = 0;
	abstract int[] attack(chessPiece piece);
}