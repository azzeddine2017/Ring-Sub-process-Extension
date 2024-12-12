#ifndef ring_subprocess_h
#define ring_subprocess_h

#include "ring.h"

// التعريفات الأساسية
RING_API void ringlib_init(RingState *pRingState);

// هياكل البيانات
typedef struct SubProcess {
    HANDLE hProcess;
    FILE *pipeHandle;
    String *output;
    DWORD processId;
} SubProcess;

// دوال الواجهة
RING_API void ring_vm_subprocess_init(void *pPointer);
RING_API void ring_vm_subprocess_create(void *pPointer);
RING_API void ring_vm_subprocess_execute(void *pPointer);
RING_API void ring_vm_subprocess_wait(void *pPointer);
RING_API void ring_vm_subprocess_getoutput(void *pPointer);
RING_API void ring_vm_subprocess_terminate(void *pPointer);

#endif
