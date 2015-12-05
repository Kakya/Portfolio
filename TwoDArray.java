import java.util.Arrays;

public class TwoDArray {
  
  private int[] data;  //a 1D array of length rows x columns. Holds elements of 2D array in row-major order
  private int numberOfElements; //the number of data stored in this multiarray, i.e., the value of 'm'
  private int numberOfRows;  //the number of dimensions of this multiarray, i.e., the value of 'n'
  private int numberOfColumns;
  private int NumberOfMatches=0; //A number used in the TwoDArray functions to help check every array is equal to the length of numberOfColumns.
  private int[][] y;
  
  public TwoDArray (int numberOfRows, int numberOfColumns) {
	  //First save the number of rows and columns into their variables, while making sure that their values are greater than zero, otherwise we will raise an illegal argument exception.
	  //An If statement will check the validity of the two variables.
	  if (numberOfRows > 0 && numberOfColumns >0){
		  this.numberOfRows = numberOfRows;
		  this.numberOfColumns = numberOfColumns;
		  //Next we compute the number of elements. Inside the same "If" statement to keep the check for the values of number of rows and columns.
		  this.numberOfElements = numberOfRows*numberOfColumns;
		 //Done with the if statement, time to exit.
	  }
	  //In the "else" portion we will throw the Illegal Argument Exception necessary.
	  else{
		  throw new IllegalArgumentException("Either your row numbers or column numbers are less than zero, change them!"); 
	  }
	 //Now that we have our variables initialized, time to allocate the array "data" with the number of elements received from the above calculations.
	 int[] data = new int[numberOfElements];
	 for(int Element = 0; Element<data.length; Element++){
		 data[Element]=0;
	 }
	 this.data=data;
  }
  
  public TwoDArray(int numberOfRows,int numberOfColumns,int y[][] ){
	  this.y=y;
	//The checks made here are similar to the checks made in the method above this one but with two additional checks.
  	//The first additional check is to make sure that the length of the array "y" is equivalent to the variable numberOfRows.
    if (numberOfRows > 0 && numberOfColumns >0 && y.length==(numberOfRows)){
		  this.numberOfRows = numberOfRows;
    	//The second additional check is to make sure the length of every array inside the parent array, "y" is equivalent to the variable numberOfColumns.
    	//To begin this check, we start a for-loop at i=0, where i is a variable representing an array inside y.
    	//The loop ensure that i increments by one to ensure that the loop runs through all the arrays in y.
    	for (int i=0; i<y.length; i++){
    		//The if statement takes the array inside y being examined and ensures that the two variables, numberOfColumns and the array inside y are equivalent.
    		if (y[i].length==(numberOfColumns)){
    			//NumberOfMatches is used here to be incremented for every element i in y, if NumberOfMatches == y.length() then every element is valid, as NumberOfMatches increments for every element.
    			NumberOfMatches++;
    		}
    	}
    	//Checks to see the number of elements that match is equivalent to the elements in y and then computes numberOfElements.
    	if(NumberOfMatches==(y.length)){
    		this.numberOfElements = numberOfRows*numberOfColumns;
    		this.numberOfColumns = numberOfColumns;
    	}
    	//If the number of elements that match != the number of elements in y, throw an IllegalArgumentException.
    	else{
    		throw new IllegalArgumentException("Length of an array in y is not equal to numberofColumns.");
    	}
    }
    //If the original checks fail, throw an IllegalARgumentException
    else{
    	throw new IllegalArgumentException("The arguments passed in are invalid.");
    }
	//After all the checks have been passed, initialize data.
	int[] data = new int[numberOfElements];
    //Now that the array data is initialized, the elements need to be set similar to the elements in the sub-arrays of y.
    //Create a variable, l, that will be used to loop through the elements in data to allow modification of the elements from "null",
	//Which is the default given to the elements from the initialization of a new array, to the elements from the 2D Array, y.
    int ElementIndex=0;
    //The while loop keeps running so long as l is smaller than the length of data, to ensure that every element in data gets modified. 
	while(ElementIndex<data.length){
		//Next the variable "j" will point to the sub-arrays within y to begin filling data with the elements in the sub-arrays.
		for(int SubArrayIndex=0; SubArrayIndex<y.length; SubArrayIndex++){
			//The following loop will use the variable "k" to loop through the sub-arrays within y, denoted with y[SubArray], to find elements to fill data with.
			for(int SubArrayElementIndex=0; SubArrayElementIndex<y[SubArrayIndex].length; SubArrayElementIndex++){
				//Now we set the value in data, denoted with data[ElementIndex], to the value in the sub-array of y, denoted with y[SubArrayIndex][SubArrayElementIndex]
    			data[ElementIndex]=y[SubArrayIndex][SubArrayElementIndex];
    			//The variable denoting the element in data being modified is incremented at the end of the nested loops to allow for the element of data to change properly.
    			//The increment will occur here and allow the while loop at the beginning of the loop sequence to terminate. 
    			ElementIndex++;
				}
    		}
    	}
	this.data=data;
  }
  //Getter for the variable, numberOfRows.
  public int getNumberOfRows () {
	  return numberOfRows;
  }
  //getter for the variable, numberOfColumns.
  public int getNumberOfColumns () {
	  return numberOfColumns;
  }
  //getter for the variable, numberOfElements.
  public int getNumberOfElements (){
	  return numberOfElements;
  }
  //Purpose of the getIndex method is to take an index from a 2D Array and find the index of the element in the 1D Array, data.
  private int getIndex (int row, int column) {
	  //An if statement runs through checks to ensure that the two arguments passed through are valid, throws an exception otherwise.
	  if(row >= 0 && row <= (getNumberOfRows()-1) && column>=0 && column <= (getNumberOfColumns()-1)){
		  //An equation is needed to convert from the 2D indices, such as (2,1), to a 1D index, such as (5). 
		  //The equation used is: (Row * Number of Columns)+Column. 
		  //Initialize the variable "DataIndex" to be the result of the previous equation, making it house the result of getIndex.
		  int DataIndex=row*numberOfColumns+column;
		  //Now we just return the variable housing the index and the method is complete.
		  return DataIndex;
	  }
	  else{
		  //Throw this exception if the arguments passed into the method fail the checks in the if statement.
		  throw new IndexOutOfBoundsException();
	  }  
  }
  //Similar, conceptually, to the getIndex() method, but returns the element the index points to, rather than the index itself. 
  public int getElement (int row, int column) {
	  //Same checks for the arguments, row and column, that are used for the getIndex method; throws an exception if the checks fail.
	  if(row >= 0 && row <= (getNumberOfRows()-1) && column>=0 && column <= (getNumberOfColumns()-1)){
		  //Instead of rewriting the equation in getIndex, use the getIndex method to initialize the variable Index and give it the proper value.
		  int Index = getIndex(row, column);
		  //We are returning the value of the element that the index in getIndex is pointing to, so the return statement references the data array.
		  return data[Index];
	  }
	  else{
		  //Similar to getIndex, if the checks fail, throw an exception.
		  throw new IndexOutOfBoundsException();
	  }  
  }
  //Same method as getElement, only it sets the value retrieved by the index received from getIndex to the value passed into the method rather than returning the value.
  public void setElement (int row, int column, int value) {
	  if(row >= 0 && row <= (getNumberOfRows()-1) && column>=0 && column <= (getNumberOfColumns()-1)){
		   int SetIndex=getIndex(row, column);
		   data[SetIndex]=value;
	  }
	  else{
		  throw new IndexOutOfBoundsException();
	  }  
  }
 // The opposite of the getIndex Method, this will take a 1D index and return the 2D representation.
 private int[] getIndices (int index) {
	 //We need to initialize the array for the method, IndicesList, that will house the indices derived from the method.
	 int [] IndicesList= new int[data.length*2];
	 //Here is the beginning of two nested for loops that match the argument passed in, index, to the resulting 2D index.
	 //This is done by looping through the 2D Array passed into the method from the constructor.
	 for(int SubArrayIndex=0; SubArrayIndex<y.length; SubArrayIndex++){
			for(int SubArrayElementIndex=0; SubArrayElementIndex<y[SubArrayIndex].length; SubArrayElementIndex++){
				//This if statement is the critical statement in the method.
				//It runs the Indices, SubArrayIndex and SubArrayElementIndex, through the getIndex method to get what the index should be.
				//If the resulting index is equivalent to the argument passed in, it moves on and executes the inner statements.
				if(getIndex(SubArrayIndex, SubArrayElementIndex)==index){
					//The first element of IndicesList is set to the Index of the sub-array.
					//The second element of IndicesList is set to the element within the sub-array.
					IndicesList[0]=SubArrayIndex;
					IndicesList[1]=SubArrayElementIndex;
					}
			}
	 }
	 return IndicesList;
  }
  //Adds all the elements in the data array. 
  public int sum() {
	//Initializes the variable, sum, to zero.
  	int Sum = 0;
  	//Loops through the data array, adding the Elements within.
	for (int ElementIndex = 0; ElementIndex<data.length; ElementIndex++){
		Sum=Sum+data[ElementIndex];
	}
	return Sum;
  }
  //Returns a TwoDArray that is opposite of the TwoDArray passed in. 
  public TwoDArray transpose() {
	  //Initialize three variables that will be used to ensure the proper transposing of the TwoDArray.
	  //Switching the rows and columns necessary for transpose, thus "Row" in transpose is equivalent to the columns outside and "Column" is equivalent to rows.
	  int row = numberOfColumns;
	  int column = numberOfRows;
	  //A new 2D Array is also created to store the transposed array, temporarily.
	  int[][] TransposedArray = new int[row][column];
	  //Two nested for-loops are used to store values into Transposed Array. The first loops through the first dimension of TransposedArray, while the second loops through the second dimension.
	  for(int TransposedSubArrayIndex=0; TransposedSubArrayIndex<TransposedArray.length; TransposedSubArrayIndex++){
		  for(int TransposedSubArrayElementIndex=0; TransposedSubArrayElementIndex<TransposedArray[TransposedSubArrayIndex].length;TransposedSubArrayElementIndex++){
			  //Switches the order of the variables, TransposedSubArrayIndex and TransposedSubArrayElementIndex, between TransposedArray and y to assign transposed values.
			  TransposedArray[TransposedSubArrayIndex][TransposedSubArrayElementIndex]=y[TransposedSubArrayElementIndex][TransposedSubArrayIndex];
	  	}
  	}
	  //Use the created 2D Array as an argument passed into the TwoDArray constructor to create the TwoDArray object, Transposed.
	  TwoDArray Transposed = new TwoDArray(row,column,TransposedArray);
	  //return the desired TwoDArray object.
	  return Transposed;
  }
//This method returns the TwoDArray as a string. 
  public String toString() {
	  //Initialize the String, ArrayRepresentation, to an empty string.
	  String ArrayRepresentation = "";
	  //Initializes a variable used to in the while-loop to terminate if it is greater than or equal to data.length, to prevent exceptions.
	  int ElementIndex=0;
	  //Start the while loop that will change ArrayRepresentation to add every element in data to look like the original 2D array.
	  while(ElementIndex<data.length){
		  //The for-loop runs through and adds the element pointed to by ElementIndex for the number of columns there are.
		  //After the columns run out, the loop breaks and reinitializes after adding a newline outside the for-loop.
		  for(int ColumnNumber=0; ColumnNumber<numberOfColumns; ColumnNumber++){
			  //Adds elements to the, currently, empty string, ArrayRepresentation.
			  ArrayRepresentation += data[ElementIndex];
			  ArrayRepresentation +=" ";
			  //Increments ElementIndex to ensure that the method is not adding the same element over and over.
			  //Also ensures that the while loop will eventually terminate. 
			  ElementIndex++;
		  }
		  //Adds a newline between rows.
		  ArrayRepresentation += "\n";
	  }
	  return ArrayRepresentation;
  } 
  	//DOCUMENT!
    public boolean equals(Object rhs) {
    	boolean truth = true;
    	if(this.getNumberOfColumns()==(((TwoDArray)rhs).getNumberOfColumns())&&this.getNumberOfRows()==(((TwoDArray)rhs).getNumberOfRows())){
    		for(int ElementIndex=0; ElementIndex<this.getData().length; ElementIndex++){
    			if(this.getData()[ElementIndex] != ((TwoDArray)rhs).getData()[ElementIndex]){
    				truth= false;
   				}
   			}
    	}
    	else{
    		truth = false;
    	}
    	return truth;
	}
    public int[] getData(){
    	return data;
    }
    public static void main(String args[]) {
        
    	   TwoDArray D = new TwoDArray (3,2);  
    	    D.setElement (0,0, 1); 
    	    D.setElement (0,1, 2); 
    	    D.setElement (1,0, 3); 
    	    D.setElement (1,1, 4);  
    	    D.setElement (2,0, 5); 
    	    D.setElement (2,1, 6);  
    	    System.out.println("D(3,2) using toString():\n" + D);
    		 System.out.println(); 
    	    int[][] y ={
    	      {1,2},
    	      {3,4},
    	      {5,6}
    	    }; 
    		 D = new TwoDArray (3,2,y);
    	    System.out.println("D(3,2,y): using toString()\n" + D);
    		 System.out.println();    
    	    System.out.println("D.getNumberOfElements():"+D.getNumberOfElements());
    	    System.out.println("D.getNumberOfRows():"+D.getNumberOfRows());
    	    System.out.println("D.getNumberOfColumns():"+D.getNumberOfColumns());  
    		 System.out.println();    
    	    System.out.println("D's elements in row-major order using getElement():");
    	    System.out.println(D.getElement(0,0));
    	    System.out.println(D.getElement(0,1));  
    	    System.out.println(D.getElement(1,0));
    	    System.out.println(D.getElement(1,1)); 
    	    System.out.println(D.getElement(2,0));
    	    System.out.println(D.getElement(2,1)); 
    		 System.out.println();     
    	    System.out.println("Offsets of D's elements in row-major order:");
    	    System.out.println(D.getIndex(0,0));
    	    System.out.println(D.getIndex(0,1));
    	    System.out.println(D.getIndex(1,0));
    	    System.out.println(D.getIndex(1,1));
    	    System.out.println(D.getIndex(2,0));  
    	    System.out.println(D.getIndex(2,1));  
    		 System.out.println();     
    	    System.out.println("D.sum():"+ D.sum()); 
    		 System.out.println();     
    	    System.out.println("D's indices:");
    	    int[] indices = D.getIndices(0);
    	    System.out.println("D.getIndices(0):" + indices[0]+","+indices[1]);  
    	    indices = D.getIndices(1);
    	    System.out.println("D.getIndices(1):"+indices[0]+","+indices[1]);    
    	    indices = D.getIndices(2);
    	    System.out.println("D.getIndices(2):"+indices[0]+","+indices[1]);   
    	    indices = D.getIndices(3);  
    	    System.out.println("D.getIndices(3):"+indices[0]+","+indices[1]); 
    	    indices = D.getIndices(4);  
    	    System.out.println("D.getIndices(4):"+indices[0]+","+indices[1]);
    	    indices = D.getIndices(5);  
    	    System.out.println("D.getIndices(5):"+indices[0]+","+indices[1]);  
    		 System.out.println();     
    	    System.out.println("D.transpose():"+D.transpose());
    		 System.out.println(); 
    		 
    			int[][] z ={
    	      {6,5,4},
    	      {3,2,1}
    	    }; 
    		 TwoDArray E = new TwoDArray (2,3,z);
    	    System.out.println("E(2,3,z): using toString()\n" + E);
    		 System.out.println();    
    	    System.out.println("E.getNumberOfElements():"+E.getNumberOfElements());
    	    System.out.println("E.getNumberOfRows():"+E.getNumberOfRows());
    	    System.out.println("E.getNumberOfColumns():"+E.getNumberOfColumns());  
    		 System.out.println();    
    	    System.out.println("E's elements in row-major order using getElement():");
    	    System.out.println(E.getElement(0,0));
    	    System.out.println(E.getElement(0,1));  
    	    System.out.println(E.getElement(0,2));
    	    System.out.println(E.getElement(1,0)); 
    	    System.out.println(E.getElement(1,1));
    	    System.out.println(E.getElement(1,2)); 
    		 System.out.println();     
    	    System.out.println("Offsets of E's elements in row-major order:");
    	    System.out.println(E.getIndex(0,0));
    	    System.out.println(E.getIndex(0,1));
    	    System.out.println(E.getIndex(0,2));
    	    System.out.println(E.getIndex(1,0));
    	    System.out.println(E.getIndex(1,1));  
    	    System.out.println(E.getIndex(1,2));  
    		 System.out.println();     
    	    System.out.println("E.sum():"+ E.sum()); 
    		 System.out.println();     
    	    System.out.println("E's indices:");
    	    indices = E.getIndices(0);
    	    System.out.println("E.getIndices(0):" + indices[0]+","+indices[1]);  
    	    indices = E.getIndices(1);
    	    System.out.println("E.getIndices(1):"+indices[0]+","+indices[1]);    
    	    indices = E.getIndices(2);
    	    System.out.println("E.getIndices(2):"+indices[0]+","+indices[1]);   
    	    indices = E.getIndices(3);  
    	    System.out.println("E.getIndices(3):"+indices[0]+","+indices[1]); 
    	    indices = E.getIndices(4);  
    	    System.out.println("E.getIndices(4):"+indices[0]+","+indices[1]);
    	    indices = E.getIndices(5);  
    	    System.out.println("E.getIndices(5):"+indices[0]+","+indices[1]);  
    		 System.out.println();     
    	    System.out.println("E.transpose():"+E.transpose());
    		 System.out.println();
    	  }
    	} 