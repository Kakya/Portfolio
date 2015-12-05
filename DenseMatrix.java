import java.util.Arrays;

public class DenseMatrix {
  private int numberOfRows;  //the number of dimensions of this multiarray, i.e., the value of 'n'
  private int numberOfColumns;
  private TwoDArray data;
  //Constructor for DenseMatrix that takes two arguments, initializes numberOfRows and numberOfColumns and initializes data.
  public DenseMatrix(int numberOfRows, int numberOfColumns){
	  //Checks to make sure numberOfRows and numberOfColumns > 0, otherwise throws an exception.
	  if(numberOfRows > 0 && numberOfColumns > 0){
		  this.numberOfRows= numberOfRows;
		  this.numberOfColumns  = numberOfColumns;
		  TwoDArray data = new TwoDArray(numberOfRows, numberOfColumns);
		  this.data = data;
	  }
	  else{
		  throw new IllegalArgumentException();
	  }
	  
  }
  //Second constructor, takes an array, y, as an extra argument to intialize the TwoDArray data with. 
  public DenseMatrix(int numberOfRows,int numberOfColumns,int y[][] ){
	  //Variable used to check all the lengths of the subarrays inside y.
	  int NumberOfMatches=0;
	  //This check for numberOfRows is sufficient, we will save initialization until we are sure all variables have passed the check, however.
	  //numberOfColumns requires another check further down in the constructor.
	  if(numberOfRows > 0 && numberOfColumns > 0 && y.length==numberOfRows){
		  for (int i=0; i<y.length; i++){
		  		//The if statement takes the array inside y being examined and ensures that the two variables, numberOfColumns and the array inside y are equivalent.
		  		if (y[i].length==(numberOfColumns)){
		  			//NumberOfMatches is used here to be incremented for every element i in y, if NumberOfMatches == y.length() then every element is valid, as NumberOfMatches increments for every element.
		  			NumberOfMatches++;
		  		}
		  		 else{
		  			  throw new IllegalArgumentException();
		  		  }
		  	}
		  	//Checks to see the number of elements that match is equivalent to the elements in y, if so then every element in y is equivalent to numberOfColumns and the check is passed.
		  	if(NumberOfMatches==(y.length)){
		  		//Once all checks are complete and have been passed, we can initialize all variables.
		  		this.numberOfColumns = numberOfColumns;
				this.numberOfRows=numberOfRows;
		  		TwoDArray data = new TwoDArray(numberOfRows, numberOfColumns, y);
				this.data = data;
		  	}
		  	 else{
				  throw new IllegalArgumentException();
			  }
	  }
	  else{
		  throw new IllegalArgumentException();
	  }
  }
  //Getter for the numberOfRows variable.
  public int getNumberOfRows () {
	  return numberOfRows;
  }
  //Getter for the numberOfColumns variable
  public int getNumberOfColumns () {
	  return numberOfColumns;
  }
  //Getter for NumberOfElements.
  public int getNumberOfElements (){
	  //calls the same method from the TwoDArray class and returns the result.
	  return data.getNumberOfElements();
  }    
  //Method to setElement, calls TwoDArray's setElement method.
  public void setElement(int row, int column, int value) {
	 //This runs through two checks each for variables row and column to ensure that they are valid arguments to the method, setElement. If they fail, an exception is thrown.
	 if(row >= 0 && row <= (getNumberOfRows()-1) && column>=0 && column <= (getNumberOfColumns()-1)){
		 //If the checks are passed, then the element is set using data's setElement method.
		 data.setElement(row, column, value); 
	 }
	 else{
		 throw new IndexOutOfBoundsException();
	 }
  }

  public int getElement(int row, int column) {
	  //Same checks for the arguments, row and column, that are used for the getIndex method; throws an exception if the checks fail.
	  if(row >= 0 && row <= (getNumberOfRows()-1) && column>=0 && column <= (getNumberOfColumns()-1)){
		  //We are returning the value of the element that the index in getIndex is pointing to, so the return statement references the data array.
		  return data.getElement(row,column);
	  }
	  else{
		  //Similar to getIndex, if the checks fail, throw an exception.
		  throw new IndexOutOfBoundsException();
	  }  
  }
  //A sum method, uses data's sum method to calculate the sum of the densematrix. 
  public int sum() {
	  return data.sum();
  }
  //Similar to the TwoDArray method, this method takes a dense-matrix and returns its transpose.
  public DenseMatrix transpose(){
	  //A newTwoDArray will be created from the transpose of data to access variables, numberOfRows and numberOfColumns
	  TwoDArray TransposedTwoDArray = data.transpose();
	  //A new array is created with the size figures being the transposed TwoDArray's values for rows and columns.
	  int[][] TransposedArray= new int[TransposedTwoDArray.getNumberOfRows()][TransposedTwoDArray.getNumberOfColumns()];
	  //This loop finds the elements in TransposedTwoDArray and sets the element at the same index value in TransposedArray as equal to it.
	  for(int TransposedArrayRowIndex =0; TransposedArrayRowIndex< TransposedArray.length; TransposedArrayRowIndex++){
		  //loops through the column index second to ensure that all elements in a row are added properly.
		 for(int TransposedArrayColumnIndex = 0; TransposedArrayColumnIndex < TransposedArray[TransposedArrayRowIndex].length; TransposedArrayColumnIndex++){
			 //Sets the value in TransposedArray equal to the value in TransposedTwoDArray.
			 TransposedArray[TransposedArrayRowIndex][TransposedArrayColumnIndex]=TransposedTwoDArray.getElement(TransposedArrayRowIndex, TransposedArrayColumnIndex);
		 }
	  }
	  //Initializes a new DenseMatrix with the transposed values for rows and columns and with the TransposedArray as the incoming array.
	  DenseMatrix TransposedDenseMatrix = new DenseMatrix(TransposedTwoDArray.getNumberOfRows(), TransposedTwoDArray.getNumberOfColumns(), TransposedArray);
	  //Returns the transposed Densematrix.
	  return TransposedDenseMatrix;
  }
  //Method to calculate the DOT sum of two matrices.
  public static int DOT(DenseMatrix D1, DenseMatrix D2, int D1row, int D2row) {
	//Initializes the DOTResult to be equal to zero, this will get modified as the method progresses.
	int DOTResult = 0;
	//First, a D1 and D2 go through a series of checks to ensure the inputs are valid, otherwise an exception is thrown.
	//The first check is to ensure that D1 and D2 have an equal number of columns.
	//The remaining checks are to ensure that D1row and D2row are valid arguments into D1 and D2.
	//An exception is thrown if either of these conditions fail.
	if(D1.getNumberOfColumns()==D2.getNumberOfColumns() && D1row<=D1.getNumberOfRows()-1 && D2row<=D2.getNumberOfRows()-1 && D1row >=0 && D2row >=0){
		//This for-loop runs through all the elements at D1row and D2row for D1 and D2, respectively.
		for(int ColumnIndex = 0; ColumnIndex<D1.getNumberOfColumns(); ColumnIndex++){
			//DOTResult is incremented with the value of D1's element multiplied by the value of D2's element.
			DOTResult += D1.getElement(D1row, ColumnIndex)*D2.getElement(D2row, ColumnIndex);
		}
		//return the DOT Result.
		return DOTResult;
	}
	//Exception thrown if a check fails.
	else{
			throw new IllegalArgumentException();
		}
  }  
  //Method for multiplying two matrices without using DOT sum.
  public DenseMatrix multiply(DenseMatrix second){
	  //Original check to ensure number of columns from the first matrix equal number of rows in the second matrix
	  if(this.getNumberOfColumns()==second.getNumberOfRows()){
		  //Initialize a new array that will store the results of the multiplication.
		  //Array will later be used to create a new dense-matrix.
		  //Multiplication result will be of format NxP from: First matrix == NxM and Second matrix == MxP.
		  int [][] MultiplicationResult = new int[this.getNumberOfRows()][second.getNumberOfColumns()];
		  //This nested for-loops will retrieve the row index of the first matrix, column index for the first and second matrices.
		  //The setup will allow for the ability to multiply two elements together as the first matrix requires both indices, but the second matrix will use the first matrix's column index for its row index.
		  for(int FirstMatrixRowIndex = 0; FirstMatrixRowIndex < this.getNumberOfRows(); FirstMatrixRowIndex++){
			  //loop through the second matrix's column index here.
			  for(int SecondMatrixColumnIndex = 0; SecondMatrixColumnIndex < second.getNumberOfColumns(); SecondMatrixColumnIndex++){
				  //initialize a variable to hold the value of the elements multiplied together.
				  //variable initialized within for-loop to ensure it is regularly reset back to zero and will not contain left overs.
				  int SumOfMultipliedElements = 0;
				  for(int FirstMatrixColumnIndex = 0; FirstMatrixColumnIndex < this.getNumberOfColumns(); FirstMatrixColumnIndex++){
					  //Multiplying the two elements to receive the value of the multiplied elements.
					  SumOfMultipliedElements += this.getElement(FirstMatrixRowIndex, FirstMatrixColumnIndex)* second.getElement(FirstMatrixColumnIndex, SecondMatrixColumnIndex);
				  }
				//the element in MultiplicationResult has its value set to the value of the multiplied elements.
				MultiplicationResult[FirstMatrixRowIndex][SecondMatrixColumnIndex]=SumOfMultipliedElements;  
			  }
		  }
		  //After the multiplication is done, return a new densematrix with the multiplied values.
		  return new DenseMatrix(this.getNumberOfRows(),second.getNumberOfColumns(),MultiplicationResult);
	  }
	  else{
		  throw new IllegalArgumentException();
	  }
  }
 //Similar to multiply method, but uses the transpose of the incoming argument and utilizes the DOT result to achive the result.
  public DenseMatrix multiplyTranspose(DenseMatrix B){
	  //Lines 169-170 are similar to lines 138 and 142 in multiply
	  if(this.getNumberOfColumns()==B.getNumberOfRows()){
		  int [][] MultiplicationResult = new int[this.getNumberOfRows()][B.getNumberOfColumns()];
		  //A new densematrix is created that will be used to multiply, from B's transpose() method.
		  DenseMatrix TransposedB = B.transpose();
		  //Similar for-loop setup to multiply, only without the first matrix column index, which is unnecessary, as the DOT result is being used and DOT does not need column index of the first matrix
		  for(int FirstMatrixRowIndex = 0; FirstMatrixRowIndex < this.getNumberOfRows(); FirstMatrixRowIndex++){
			  for(int SecondMatrixColumnIndex = 0; SecondMatrixColumnIndex < B.getNumberOfColumns(); SecondMatrixColumnIndex++){
				//The value of the element in Multiplication result is set to the DOT result of the first matrix and the transpose of the incoming matrix.
				MultiplicationResult[FirstMatrixRowIndex][SecondMatrixColumnIndex]=DOT(this, TransposedB, FirstMatrixRowIndex, SecondMatrixColumnIndex);  
			  }
		  }
		  //A new densematrix is returned using the multiplication results.
		  return new DenseMatrix(this.getNumberOfRows(),B.getNumberOfColumns(),MultiplicationResult);
	  }
	  //if checks fail, throw an exception.
	  else{
		  throw new IllegalArgumentException();
	  }
  }
  //Returns a string representation, using data's toString method.
  public String toString() {
	  return data.toString();
  }
  //Checks if the incoming object is equal to the DenseMatrix.
  public boolean equals(Object rhs) {
	  //Calls data's equals method to determine equality. 
	  //The variable, rhs, must be cast otherwise it will not run properly.
	  return data.equals(((DenseMatrix)rhs).getData());
  }
  //getter for data.
  public TwoDArray getData(){
	  return data;
  }
  public static void main(String args[]) {
	  	 DenseMatrix D1 = new DenseMatrix (3,2);  
	    D1.setElement (0,0, 1); 
	    D1.setElement (0,1, 2); 
	    D1.setElement (1,0, 3); 
	    D1.setElement (1,1, 4);  
	    D1.setElement (2,0, 5); 
	    D1.setElement (2,1, 6);   
	    System.out.println("D1(3,2) using toString():\n" + D1);
	 	 System.out.println();     
	    System.out.println("D1.sum(): "+D1.sum());
	 	 System.out.println();     
	    int[][] y ={
	      {1,2},
	      {3,4},
	      {5,6}
	    }; 
	    
		 DenseMatrix D2 = new DenseMatrix (3,2,y);
	    System.out.println("D2(3,2,y): using toString()\n" + D2);
	    System.out.println("D2.getNumberOfElements():"+D2.getNumberOfElements());
	    System.out.println("D2.getNumberOfRows():"+D2.getNumberOfRows());
	    System.out.println("D2.getNumberOfColumns():"+D2.getNumberOfColumns());  
	 	 System.out.println();  
	    System.out.println("D2's elements in row-major order using getElement():");
	    System.out.println(D2.getElement(0,0));
	    System.out.println(D2.getElement(0,1));  
	    System.out.println(D2.getElement(1,0));
	    System.out.println(D2.getElement(1,1)); 
	    System.out.println(D2.getElement(2,0));
	    System.out.println(D2.getElement(2,1)); 
		 System.out.println();    
		 
	    DenseMatrix D3=new DenseMatrix (2,3);
	    D3.setElement (0,0, 1); 
	    D3.setElement (0,1, 3); 
	    D3.setElement (0,2, 5); 
	    D3.setElement (1,0, 2);  
	    D3.setElement (1,1, 4); 
	    D3.setElement (1,2, 6); 
	    
	    System.out.println("Multiply");    
	    DenseMatrix P=D2.multiply(D3);
	    System.out.println("D2:\n"+D2);
	    System.out.println("D3:\n"+D3);
	    System.out.println("D2.multiply(D3):\n"+ D2.multiply(D3));
	  
	    System.out.println("D1.equals(D2):"+D1.equals(D2));
	    System.out.println("D2.equals(D3):"+D2.equals(D3));    
		 System.out.println();
		 
	    int[][] thirdArray={
	      {1,2},
	      {3,4}
	    };
	    int[][] fourthArray = { 
	      {1,3},
	      {2,4}
	    };
	    
	    DenseMatrix A=new DenseMatrix(2,2,thirdArray);
	    DenseMatrix B=new DenseMatrix(2,2,fourthArray);
	    System.out.println("A:\n"+A);
	    System.out.println("B:\n"+B);
	    System.out.println("A.multiply(B):\n"+A.multiply(B));
	    
	    System.out.println("Multiply with transpose:");
	    System.out.println("B.transpose():\n" + B.transpose());
	    System.out.println("DOT(A,B.transpose(),1,1):"+DenseMatrix.DOT(A,B.transpose(),1,1));
		 System.out.println();    
	    System.out.println("A.multiplyTranspose(B):\n"+A.multiplyTranspose(B));
	  }
	}
