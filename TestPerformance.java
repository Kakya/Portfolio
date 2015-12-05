import java.util.Random;
public class TestPerformance { 
        static class ExecutionResults {
                int size;
                long multiplyTime;
                long multiplyTransposeTime; 
                public ExecutionResults(int size) {
                        this.size = size;
                }
        }        
        
        public static void main(String[] args) throws Exception {
                int choice = 3;
                if (args.length >0)
       				choice = Integer.parseInt(args[0]);      				
       
     				 // warm up the JVM
                for (int i = 0; i < 100; i++)
                   CheckPerformance(100,choice);
                   
                // print header
                 System.out.printf("%-15s %-20s %-20s  (millisec.) %n", 
                      "size",  "multiply Time", "multiplyTranspose Time");

                // perform the benchmarking
                displayResult(CheckPerformance(100,choice),choice);
                displayResult(CheckPerformance(200,choice),choice);
                displayResult(CheckPerformance(300,choice),choice);
                displayResult(CheckPerformance(400,choice),choice);
                displayResult(CheckPerformance(500,choice),choice);
                displayResult(CheckPerformance(600,choice),choice);
                displayResult(CheckPerformance(700,choice),choice);
                displayResult(CheckPerformance(800,choice),choice);
                displayResult(CheckPerformance(900,choice),choice);   
                displayResult(CheckPerformance(1000,choice),choice);   
                displayResult(CheckPerformance(2000,choice),choice);                 
        }
 
        private static void displayResult(ExecutionResults r, int choice) {
                
                long min = 1;
                if (choice == 3) {
                 min = Math.min(r.multiplyTime, r.multiplyTransposeTime);            
                
                 System.out.printf("%-15d %-10d (%-3.0f%%)    %-10d (%-3.0f%%)%n", 
                                r.size, 
                                r.multiplyTime,   (100 * (double) r.multiplyTime) / min,
                                r.multiplyTransposeTime, (100 * (double) r.multiplyTransposeTime) / min);                              
                }
                else if (choice == 1) {
                	System.out.printf("%-15d %-10d (100%%)%n", 
                                r.size, 
                                r.multiplyTime);                                              
                
                }
                else if (choice == 2) {                
                	  System.out.printf("%-15d                        %-10d (100%%)%n", 
                                r.size, 
                                r.multiplyTransposeTime);    
                }
        }
 
        private static ExecutionResults CheckPerformance(int size, int choice) {

                int[][] array = new int[size][size];
                Random random = new Random(123456789L);  
                for (int i = 0; i < size; i++){
                  for(int j=0;j<size;j++){
                        array[i][j] = random.nextInt();
                  }
                }
                DenseMatrix testing= new DenseMatrix(size,size,array);
                ExecutionResults result = new ExecutionResults(size);
   
     			 switch (choice) {
					case 1:
                 long before = System.nanoTime();
                 testing.multiply(testing);
                 result.multiplyTime = (System.nanoTime() - before) / 1000000;
                 break;
       			case 2:
                 before = System.nanoTime();
                 testing.multiplyTranspose(testing);
                 result.multiplyTransposeTime = (System.nanoTime() - before) / 1000000;
                 break;
            	case 3:
                 before = System.nanoTime();
                 DenseMatrix testing1= testing.multiply(testing);
                 result.multiplyTime = (System.nanoTime() - before) / 1000000;

                 before = System.nanoTime();
                 DenseMatrix testing2 = testing.multiplyTranspose(testing);
                 result.multiplyTransposeTime = (System.nanoTime() - before) / 1000000;    

					  if (choice == 3 && (!(testing1.equals(testing2))))
                        throw new RuntimeException("Matrix multiply results not equal.");                 
            }
                
                return result;
        }       
}
