class Node
{
    private String word;
    private int freq, length;

   	
    public Node(String input)
    {
        this.word = input;
        this.freq = 1;
        this.length = input.length();
    }

    public Node addOne(){
    		this.freq++;
    		return this;
    }
    public int getFreq(){
    	return this.freq;
    }
    public int getLength(){
    	return this.length;
    }
    public String getWord(){
    	return this.word;
    }
}