        .text
.global quintuple
        .type   quintuple,@function
quintuple:
        # Your Code Goes Here
        #
        leaq (%rdi, %rdi, 4), %rax # res <- x+x*4 == x+4x == 5x
        # end of function
        ret
        
        .size   quintuple, .-quintuple
