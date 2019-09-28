section .rodata
double db "%lf", 10, 0

section .bss
x resq 1
tmp resq 1

section .data
const1 dq 1.000000
const2 dq 2.000000
const3 dq 3.000000
const06 dq 0.600000
const0 dq 0.000000
constn1 dq -1.000000

section .text

global _f1
_f1:
push ebp
mov ebp, esp
   fld qword[const06]
   fld qword[ebp + 8]
   fmulp
   fld qword[const3]
   faddp
mov esp, ebp
pop ebp
ret

global _f2
_f2:
push ebp
mov ebp, esp
    fld qword[ebp + 8]
    fld qword[const2]
    fsubp
    fst qword[tmp]
    fld qword[tmp]
    fmulp
    fld qword[tmp]
    fmulp
    fst qword[tmp]
    fld qword[const1]
    fsubp
    
mov esp, ebp
pop ebp
ret

global _f3
_f3:
push ebp
mov ebp, esp 

    fld qword[const3]
    fld qword[ebp + 8]
    fdivp 
    
mov esp, ebp
pop ebp
ret   
  