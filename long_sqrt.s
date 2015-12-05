       .text
.global long_sqrt 
        .type    long_sqrt,@function
long_sqrt:
        # Your Code Goes Here
        movq $1, %rax # t <- 1
        movq %rax, %rbx # Assign t to a temp value y to check for square
        imulq %rbx, %rbx # y <- y*y
        cmpq %rbx, %rdi # Check y^2:x
        jg .long_sqrt_loop # Jump to loop if y^2 < x, return otherwise
        ret
  	.long_sqrt_loop:
  		incq %rax #increment the number by one and preform similar checks as above
  		movq %rax, %rbx
  		imulq %rbx, %rbx
  		cmpq %rbx, %rdi
  		jg .long_sqrt_loop
  		jl .long_sqrt_come_back #Go to a decrementer if y^2 > x, as we want the number y just before that.
  		ret
  	.long_sqrt_come_back:
  		decq %rax #reduce the value x by 1 to get the correct value desired.
        # end of function
        ret
        
        .size    long_sqrt, .- long_sqrt
