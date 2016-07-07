.text
.globl _SystemCallHandle

_SystemCallHandle:
//    push %eax
//added by Ryo
    push %gs 
    push %ebp
    push %edi
    push %esi
    push %edx
    push %ecx
    push %ebx

    cmpl $318, %eax
    jae  systemcall_fail
    call *SystemCallsTable(, %eax, 4)
systemcall_fail:
    pop %ebx
    pop %ecx
    pop %edx
    pop %esi
    pop %edi
    pop %ebp
//added by Ryo	
    pop %gs
//    pop %ebx
    ret
