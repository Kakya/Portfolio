       .text
.global abundant
        .type   abundant,@function
abundant:
        # Your Code Goes Here
        movq $1, %rbx #Abundant calculation will go here, starts at 1, as 1 is always a divisor
        movq %rdi, %rcx #Move x to a temp register. This will be used to decrement the second counter which starts at the arg.
        movq $2, %rdx #Move 2 to a temp register, this will be used to increment up the first counter up to the arg.
        cmpq %rbx, %rdi
        jle .abundant_set_Res_great
    .abundant_loop:
      cmpq %rdx, %rdi #Check to see if you've reached the passed in arg, if so you're done and exit the loop
      je .abundant_check 
      movq %rdx, %r8 #Move the incrementer integer to a temp register for arithmetic
      imulq %rcx, %r8 #Multiply the two ints together
      cmpq %r8, %rdi  #Check to see if you get the number back. If so, you have divisors, go add them to the result
      je .abundant_add 
    .abundant_comp:
      cmpq %rdx, %rcx #Check the two divisors, if they are equal, no more arithmetic should be done on the first one
      jne .abundant_dec  #If not equal, keep decrementing from the value
      je .abundant_inc
    .abundant_add:
      addq %rdx, %rbx #Increment the result of divisors by the divisors found
      cmpq %rdx, %rcx #Run a check to ensure that squares aren't being added twice. (e.g. 2*2 = 4, should add only one 2)
      jne .abundant_dup #Jump either to adding the second divisors, if not a duplicate or back to the loop
      je .abundant_comp
    .abundant_dup:
      addq %rcx, %rbx #Add second divisor 
      jmp .abundant_comp
    .abundant_dec:
      decq %rcx #Decrement the second integer to check for divisors
      jmp .abundant_loop
    .abundant_inc:
      incq %rdx #Move up the first integer by one
      movq %rdi, %rcx #We have to refill the rcx register with the passed in value to check all numbers against the incremented int
      jmp .abundant_loop
    .abundant_check:
      cmpq %rbx, %rdi #Finally, check the result, if it is abundant go return 1, if not, 0
      jl .abundant_set_Res_less
      jge .abundant_set_Res_great
    .abundant_set_Res_less:
    	movq $1, %rax
    	ret
   	.abundant_set_Res_great:
   		movq $0, %rax
        # end of function
        ret
        
        .size   abundant, .-abundant
