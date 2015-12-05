       .text
.global caller
        .type   caller,@function
caller:
        # Your Code Goes Here
        #movq %rdi, %rax #place the value in the result register
        salq $1, %rdi #Shift left by 1 to yield x*2^1 == 2x
        decq %rdi #subtract 1
        pushq %rdi #push to stack to be an arg for quintuple
        call quintuple #call quintuple
        addq $3, %rax #Use the rax register that comes from quintuple to store the final result
        popq %rbx #pop out the arg for quintuple from the stack for memory cleanup, put it in an unused register
        # end of function
        ret
        
        .size   caller, .-caller
