  .text

  .global nop_slide
  .type   nop_slide, @function
nop_slide:
  pushq %rbp
  movq %rsp, %rbp
  rdtscp
  movl %eax, %ebx
  fnop
  fnop
  nop
  nop
  nop
  nop
  fnop
  nop
  nop
  fnop
  nop
  fnop
  fnop
  nop
  fnop
  fnop
  fnop
  rdtscp
  subl %ebx, %eax
  popq %rbp
  retq
