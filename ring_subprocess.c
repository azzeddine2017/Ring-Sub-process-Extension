#include "ring_subprocess.h"
#include <windows.h>
#include <stdio.h>

RING_API void ringlib_init(RingState *pRingState)
{
    ring_vm_funcregister("subprocess_init", ring_vm_subprocess_init);
    ring_vm_funcregister("subprocess_create", ring_vm_subprocess_create);
    ring_vm_funcregister("subprocess_execute", ring_vm_subprocess_execute);
    ring_vm_funcregister("subprocess_wait", ring_vm_subprocess_wait);
    ring_vm_funcregister("subprocess_getoutput", ring_vm_subprocess_getoutput);
    ring_vm_funcregister("subprocess_terminate", ring_vm_subprocess_terminate);
}

RING_API void ring_vm_subprocess_init(void *pPointer)
{
    SubProcess *pSubProcess = (SubProcess *)malloc(sizeof(SubProcess));
    if (pSubProcess == NULL) {
        RING_API_ERROR(RING_OOM);
        return;
    }
    pSubProcess->hProcess = NULL;
    pSubProcess->pipeHandle = NULL;
    pSubProcess->output = NULL;
    pSubProcess->processId = 0;
    RING_API_RETCPOINTER(pSubProcess, "SubProcess");
}

RING_API void ring_vm_subprocess_create(void *pPointer)
{
    if (RING_API_PARACOUNT != 2) {
        RING_API_ERROR(RING_API_MISS2PARA);
        return;
    }
    if (!RING_API_ISPOINTER(1) || !RING_API_ISSTRING(2)) {
        RING_API_ERROR(RING_API_BADPARATYPE);
        return;
    }

    SubProcess *pSubProcess = (SubProcess *)RING_API_GETCPOINTER(1, "SubProcess");
    const char *command = RING_API_GETSTRING(2);

    FILE *pipe = _popen(command, "r");
    if (pipe == NULL) {
        RING_API_ERROR("Failed to create process");
        return;
    }

    pSubProcess->pipeHandle = pipe;
    RING_API_RETNUMBER(1);
}

RING_API void ring_vm_subprocess_execute(void *pPointer)
{
    if (RING_API_PARACOUNT != 2) {
        RING_API_ERROR(RING_API_MISS2PARA);
        return;
    }
    if (!RING_API_ISPOINTER(1) || !RING_API_ISSTRING(2)) {
        RING_API_ERROR(RING_API_BADPARATYPE);
        return;
    }

    SubProcess *pSubProcess = (SubProcess *)RING_API_GETCPOINTER(1, "SubProcess");
    const char *command = RING_API_GETSTRING(2);

    FILE *pipe = _popen(command, "r");
    if (pipe == NULL) {
        RING_API_ERROR("Failed to execute process");
        return;
    }

    pSubProcess->pipeHandle = pipe;
    RING_API_RETNUMBER(1);
}

RING_API void ring_vm_subprocess_wait(void *pPointer)
{
    if (RING_API_PARACOUNT != 1) {
        RING_API_ERROR(RING_API_MISS1PARA);
        return;
    }
    if (!RING_API_ISPOINTER(1)) {
        RING_API_ERROR(RING_API_BADPARATYPE);
        return;
    }

    SubProcess *pSubProcess = (SubProcess *)RING_API_GETCPOINTER(1, "SubProcess");
    if (pSubProcess->pipeHandle != NULL) {
        char buffer[4096];
        String *pString = ring_string_new("");

        while (fgets(buffer, sizeof(buffer)-1, pSubProcess->pipeHandle) != NULL) {
            ring_string_add(pString, buffer);
        }

        if (pSubProcess->output != NULL) {
            ring_string_delete(pSubProcess->output);
        }
        pSubProcess->output = pString;

        _pclose(pSubProcess->pipeHandle);
        pSubProcess->pipeHandle = NULL;
        RING_API_RETNUMBER(1);
    }
    RING_API_RETNUMBER(0);
}

RING_API void ring_vm_subprocess_getoutput(void *pPointer)
{
    if (RING_API_PARACOUNT != 1) {
        RING_API_ERROR(RING_API_MISS1PARA);
        return;
    }
    if (!RING_API_ISPOINTER(1)) {
        RING_API_ERROR(RING_API_BADPARATYPE);
        return;
    }

    SubProcess *pSubProcess = (SubProcess *)RING_API_GETCPOINTER(1, "SubProcess");
    if (pSubProcess->output != NULL) {
        RING_API_RETSTRING2(ring_string_get(pSubProcess->output), ring_string_size(pSubProcess->output));
    } else {
        RING_API_RETSTRING("");
    }
}

RING_API void ring_vm_subprocess_terminate(void *pPointer)
{
    if (RING_API_PARACOUNT != 1) {
        RING_API_ERROR(RING_API_MISS1PARA);
        return;
    }
    if (!RING_API_ISPOINTER(1)) {
        RING_API_ERROR(RING_API_BADPARATYPE);
        return;
    }

    SubProcess *pSubProcess = (SubProcess *)RING_API_GETCPOINTER(1, "SubProcess");
    if (pSubProcess->pipeHandle != NULL) {
        _pclose(pSubProcess->pipeHandle);
    }
    if (pSubProcess->output != NULL) {
        ring_string_delete(pSubProcess->output);
    }
    free(pSubProcess);
    RING_API_RETNUMBER(1);
}
