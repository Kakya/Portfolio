#include <stdio.h>
#include "log.h" 

/* Enumerated type for events to log:
 *     ILLEGAL:  input virtual address out of range
 *     FROM_PT:  computed physical address using the page table
 *     FROM_TLB:  computed physical address from the tlb
 *     PAGE_FAULT:  physical address could not be determined  */

FILE *log_file = NULL;
//This struct will hold the data from the page table for the physical addresses
typedef struct Address
{
	//It's data types are as follows
	//Integer for holding the validity bit, either 1 or 0
	int validityBit;
	//The actual physical address stored in that entry
	int physicalAddress;
	//The index of the address in the page table
	int pTableIndex;
	//A next field to allow addresses to point to each other
	struct Address *next;
} Address, *Address_Ptr;
typedef struct TLB
{
	int TLBT;
	int TLBI;
	int PA;
	struct TLB *next;
} TLB, *TLB_ptr;
void start_logging() {
/* TODO:  modify the log file name to contain your userid rather than mine: */
  log_file = fopen("Zamzami_lab3.log","w");
}

void stop_logging() {
    fclose(log_file);
}


void log_it(log_type entry, int va, int pa) {
/* param1:  event type
 * param2:  virtual address
 * param3:  physical address (ignored if ILLEGAL or PAGE_FAULT event)
 */
   switch(entry) {
      case ILLEGAL:  fprintf(log_file,"Illegal address: 0x%x\n",va); break;
      case FROM_PT:  fprintf(log_file,"Page table maps 0x%x to 0x%x\n",va,pa); break;
      case FROM_TLB:  fprintf(log_file,"TLB maps 0x%x to 0x%x\n",va,pa); break;
      case PAGE_FAULT:  fprintf(log_file,"Page fault: 0x%x\n",va); break;
   }

}
int main(int argc, char *argv[])
{
	if(argc == 2)
	{
		start_logging();
		//Open pagetable
		FILE *pageTable; 
		pageTable = fopen(argv[1], "r");
		//Check if we opened a valid pagetable.
		if(!pageTable)
		{
			printf("That's an invalid page table\n");
			return 1;
		}
		else
		{
			//Create the linked list that will hold the data for each address
			int ctr = 0;
			Address_Ptr firstAddr = (Address_Ptr)malloc(sizeof(Address));
			firstAddr -> next = NULL;
			while(!feof(pageTable))
			{
				//Loop through the addresses until you find one without a next address.
				//This address is empty
				Address_Ptr temp = firstAddr;
				while(temp->next)
				{
					temp = temp -> next;
				}
				//Create a new address to append to the end of the linked list
				Address_Ptr newAddress = (Address_Ptr)malloc(sizeof(Address));
				//Assign it a number, this will be it's index into page table, used for lookup later.
				temp -> pTableIndex = ctr;
				temp -> next = newAddress;
				//Read from the pagetable what we need to know, primarily whether the address is valid
				//And what is the physical address.
				fscanf(pageTable, "%d %d", &(temp -> validityBit), &(temp -> physicalAddress));
				//Increment our counter by one to keep track of index into the page table
				ctr++;
			}
			//Close table after done reading it.
			fclose(pageTable);
			//Create the TLB to be an eight element Linked-List.
			TLB_ptr tlb = (TLB_ptr)malloc(sizeof(TLB));
			TLB_ptr filler = tlb;
			int tlbCtr = 0;
			//Fill the TLB with nodes that have index from 0-7.
			while(filler && tlbCtr < 8)
			{
				//The Linked-List will not be incremented any further after this.
				filler -> TLBI = tlbCtr;
				filler -> next = (TLB_ptr)malloc(sizeof(TLB));
				filler = filler -> next;
				tlbCtr++;
			}

			//Start the process of finding physical addresses
			//This loop will run until terminated by the user
			while(1)
			{
				//Place the virtual address into an integer
				printf("Enter a virtual address or -1 to exit: ");
				int vA;
				fscanf(stdin,"%d", &vA);
				if(vA == -1)
				{
					//Kill the program at -1
					printf("Thank you, come again\n");
					stop_logging();
					return;
				}
				//Check for addresses that are greater than 17 bits in length.
				if(vA > 131072)
				{
					printf("Illegal virtual address at 0x%X \n", vA);
					log_it(ILLEGAL,vA, 0);
				}
				else
				{
					int found = 0;
					//Here is all the magic with bitwise operators. 
					printf("Virtual address: 0x%X\n", vA);
					//Shift the virtual address 10 spots to clear out the VPO
					int lookUp = vA >> 10;
					//Mask the remaining VPN to clear out any leading 1's from the shifting.
					//Now we have the 7-bit VPN to search our page-table with.
					lookUp = lookUp & 127;
					//Search the TLB for the address, first.
					TLB_ptr tlbLookUp = tlb;
					//Search the TLB first to find the address
					while(tlbLookUp && !found)
					{
						//Check if the TLBT and the TLBI together are equal to the lookup VPN
						if(((tlbLookUp->TLBT << 3) | (tlbLookUp -> TLBI)) == lookUp)
						{
							//If so, print out the physical address at that TLB
							printf("physicalAddress from TLB: 0x%X\n", tlbLookUp -> PA);
							found = 1;
							//Log the result.
							log_it(FROM_TLB, vA, tlbLookUp -> PA);
						}
						tlbLookUp = tlbLookUp -> next; 
					}
					//Search the linked-list of addresses to find our address.
					Address_Ptr temp = firstAddr;
					while(temp && !found)
					{
						//If our index of the address is equal to our look up int, we have found our address.
						if(temp -> pTableIndex == lookUp)
						{
							//Only keep going if the validityBit is not 0, otherwise we have a page fault.
							if(temp -> validityBit)
							{
								//Shift the physical address to make room for the VPO
								int printOut = (temp -> physicalAddress) << 10;
								//Or the address with the virtual address masked to remove the VPN.
								printOut = printOut | (vA & 1023);
								//Print out the physical address in hex.
								printf("Physical address from pageTable: 0x%X\n", printOut);
								found = 1;
								//Having found the physical address, PPN + PPO, from the pagetable, time to update the TLB
								TLB_ptr tlbLookUp = tlb;
								while(tlbLookUp)
								{
									//Find the TLBI that corresponds to the last 3-bits of the VPN
									if(tlbLookUp -> TLBI == (lookUp & 7))
									{
										//Update the TLBT and the Physical address held at that location.
										tlbLookUp -> TLBT = ((lookUp >> 3) & 15);
										//The physical address stored in the TLB will be the PPN + PPO, for ease of extraction later.
										tlbLookUp -> PA = printOut;
									}
									tlbLookUp = tlbLookUp -> next;
								}
								log_it(FROM_PT, vA, printOut);		
							}
							else
							{
								printf("page fault \n");
								log_it(PAGE_FAULT, vA, 0);
								found = 1;
							}
						}
						//Move along the linked-list.
						temp = temp -> next;
					}
				}
			}
		}
	}
}