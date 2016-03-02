//
//  Java Network Workbench 2 (JNW2) Version 1
//  Copyright 2013/2014 Networking and Simulation Laboratory/George Mason University
//
//  This module is to be completed by the student. Its
//  purpose is to create the Cyclic Redundancy Check (CRC) 
//  16-bit Frame Check Sequence (FCS) for HDLC error checking. 
//
//  @version 1.2.1

package JNW2.message;

public class CrcFcs 
{
  /**
   * generates the 16-bit FCS
   * @param dataFrame
   * @return the 16-bit FCS for the dataFrame
   */
  public static BitSequence generateHdlcFcs(BitSequence dataFrame)
  {
    BitSequence fcs = new BitSequence(16);
    //
    // NW DLC CRC Algorithm
    // --------------------
    // establish an array FCS with 16 positions;
    // do for each data bit (but not for the start and end flags), 
    // scanning the frame from left to right,
    // { 
    //   make a copy of the high order FCS bit, call it "feedback";
    //   shift each FCS bit to the next higher FCS order bit;
    //   shift one data bit into the low-order bit of the FCS;
    //   as inputs to bits 0, 5 and 12 are shifted, 
    //     XOR them with the feedback bit;
    // }.
    //
    // NOTE:  throughout this program position 0 is treated as high-order
    // in character and bit strings for parity computation, etc.
    //
    //  student inserts CRC calculation here
    int feedback;
    if(fcs.getValue(0))
    {
        feedback = 1;
    }
    else
    {
        feedback = 0;
    }
    BitSequence temp = new BitSequence(dataFrame.size()-16);
    for(int i = 0; i < temp.size(); i++)
    {
        temp.setValue(i, dataFrame.getValue(i+8));
    }
    for(int k = 0; k<temp.size(); k++)
    {
        for(int j = 0; j<fcs.size(); j++)
        {
            fcs.setValue(j, fcs.getValue(j+1));
            if(j == fcs.size()-1)
            {
              fcs.setValue(j, temp.getValue(k));
            }           
            //perform xor operations
            if(j == 15 || j== 10 || j== 3)
            {
                int xorVal;
                if(fcs.getValue(j))
                {
                    xorVal = 1;
                }
                else
                {
                    xorVal = 0;
                }
                xorVal = xorVal^feedback;
                fcs.setValue(j, xorVal);
            }
        }
        if(fcs.getValue(0))
            {
                feedback = 1;
            }
            else
            {
                feedback = 0;
            }
        
    }
    
    return fcs;
    
  }// end generateHdlcFcs()
  
  /**
   * Returns true if the FCS is valid in bitFrame
   * @param dataFrame - the frame to be checked, which FCS at end
   * @return true if frame checks OK
   */
  public boolean checkFcs(BitSequence dataFrame)
  {
    // check whether the frame contains a compliant FCS
    BitSequence fcs = generateHdlcFcs(dataFrame);
    return fcs.equals(new BitSequence(16));
    
  }// end checkFcs()
  
  /**
   * reads a line from System.in
   * @return the line
   */
   public static String readStringFromStandardIn ( ) 
   {
     // read from the console  
     System.out.println ("\nEnter data:\n");
     String inputString = null ;
     try 
     {
       java.io.BufferedReader bufferedReader = 
         new java.io.BufferedReader ( 
           new java.io.InputStreamReader (
             System .in ) ) ;
       inputString = bufferedReader . readLine ( ) ;
     } 
     catch ( Exception e ) 
     {
       System.err.println ( "Error reading from console:" + e.getMessage());
     }
     return inputString ;      
   
   }// end ReadSingleLineFromStandardIO    
  
  /**
   * main() to enable testing generateHdlcFcs()
   * @param args - command line arguments; not used
   */
  public static void main(String[] args)
  {
    // obtain characters to test
    String dataString = readStringFromStandardIn();
    
    // make them into a BitSequence, leaving room for flags and FCS
    int bitSequenceLength = 8 * (dataString.length() + 4);
    BitSequence data = new BitSequence(bitSequenceLength);
    
    // insert the flags
    data.setOctet(0, (byte)0x7e);
    data.setOctet(bitSequenceLength-8, (byte)0x7e);
    // make bytes of the data and insert them in the data BitSequence
    byte[] dataBytes = dataString.getBytes();
    int dataLengthInBytes = dataBytes.length;
    for(int index = 0; index < dataLengthInBytes; ++index)
    {
         
      data.setOctet(8*(index+1), dataBytes[index]);
    }
    
    // generate an FCS and print it
    BitSequence fcs = generateHdlcFcs(data);
    System.out.println("Character input:" + dataString);
    System.out.println("BitSequence input ready for FCS calculation:" + data);
    System.out.println("FCS:" + fcs);
    
    // test by inserting the FCS back into the data and generating again
    int dataEndInBits = 8 * (dataLengthInBytes + 1);
    data.setValues(dataEndInBits, fcs);
    System.out.println("BitSequence input with FCS:" + data);
    BitSequence newFcs = generateHdlcFcs(data);
    System.out.println("FCS for that input:" + newFcs);
    System.out.println("If your FCS is correctly symmetric the above will be 00000000 00000000");
    System.out.println(
      "To make sure it also conforms to the standard, test using reference data such as the 123 string input");
      
  }// end main()

}// end class CrcFcs
