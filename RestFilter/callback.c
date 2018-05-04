////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2017 The Authors of ANT(http://ant.sh). All Rights Reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
////////////////////////////////////////////////////////////////////////////////

#include "callback.h"

#include <fltKernel.h>

#include "driver.h"
#include "utility.h"

#if defined(COMPILER_MSVC)
// We usually use the _CrtDumpMemoryLeaks() with the DEBUGER and CRT library to
// check a memory leak.
#if defined(_DEBUG) && _MSC_VER > 1000 // VC++ DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define  DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#if defined(DEBUG_NEW)
#define new DEBUG_NEW
#endif // DEBUG_NEW
#endif // VC++ DEBUG
#endif // defined(COMPILER_MSVC)


// Status Callback.
VOID RestFilterOperationStatusCallback(_In_ PCFLT_RELATED_OBJECTS FltObjects, _In_ PFLT_IO_PARAMETER_BLOCK ParameterSnapshot, _In_ NTSTATUS OperationStatus, _In_ PVOID RequesterContext);

/*++
Routine Description:
    This routine is a pre-operation dispatch routine for this miniFilter.
    This is non-pageable because it could be called on the paging path.
Arguments:
    Data - Pointer to the filter callbackData that is passed to us.
    FltObjects - Pointer to the FLT_RELATED_OBJECTS data structure containing
        opaque handles to this filter, instance, its associated volume and
        file object.
    CompletionContext - The context for the completion routine for this operation.
Return Value:
    The return value is the status of the operation.
--*/
FLT_PREOP_CALLBACK_STATUS RestFilterPreOperation(_Inout_ PFLT_CALLBACK_DATA Data, _In_ PCFLT_RELATED_OBJECTS FltObjects, _Flt_CompletionContext_Outptr_ PVOID *CompletionContext) {
    NTSTATUS status;

    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    PT_DBG_PRINT(PTDBG_TRACE_ROUTINES, ("RestFilter!RestFilterPreOperation: Entered\n"));


    //  See if this is an operation we would like the operation status
    //  for.  If so request it.
    //  NOTE: most filters do NOT need to do this.  You only need to make
    //        this call if, for example, you need to know if the oplock was
    //        actually granted.
    //
    if (RestFilterDoRequestOperationStatus(Data)) {
        status = FltRequestOperationStatusCallback(Data, RestFilterOperationStatusCallback, (PVOID)(++(rest.status_ctx)));
        if (!NT_SUCCESS(status)) {
            PT_DBG_PRINT(PTDBG_TRACE_OPERATION_STATUS, ("RestFilter!RestFilterPreOperation: FltRequestOperationStatusCallback Failed, status=%08x\n", status));
        }
    }

    // This template code does not do anything with the callbackData, but
    // rather returns FLT_PREOP_SUCCESS_WITH_CALLBACK.
    // This passes the request down to the next miniFilter in the chain.
    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

/*++
Routine Description:
    This routine is called when the given operation returns from the call
    to IoCallDriver.  This is useful for operations where STATUS_PENDING
    means the operation was successfully queued.  This is useful for OpLocks
    and directory change notification operations.

    This callback is called in the context of the originating thread and will
    never be called at DPC level.  The file object has been correctly
    referenced so that you can access it.  It will be automatically
    dereferenced upon return.

    This is non-pageable because it could be called on the paging path
Arguments:
    FltObjects - Pointer to the FLT_RELATED_OBJECTS data structure containing
        opaque handles to this filter, instance, its associated volume and
        file object.
    RequesterContext - The context for the completion routine for this operation.
    OperationStatus - 
Return Value:
    The return value is the status of the operation.
--*/

VOID RestFilterOperationStatusCallback( _In_ PCFLT_RELATED_OBJECTS FltObjects, _In_ PFLT_IO_PARAMETER_BLOCK ParameterSnapshot, _In_ NTSTATUS OperationStatus, _In_ PVOID RequesterContext) {
    UNREFERENCED_PARAMETER( FltObjects );

    PT_DBG_PRINT(PTDBG_TRACE_ROUTINES, ("RestFilter!RestFilterOperationStatusCallback: Entered\n"));
    PT_DBG_PRINT(PTDBG_TRACE_OPERATION_STATUS, ("RestFilter!RestFilterOperationStatusCallback: Status=%08x ctx=%p IrpMj=%02x.%02x \"%s\"\n",
        OperationStatus,
        RequesterContext,
        ParameterSnapshot->MajorFunction,
        ParameterSnapshot->MinorFunction,
        FltGetIrpName(ParameterSnapshot->MajorFunction)));
}

/*++
Routine Description:
    This routine is the post-operation completion routine for this
    miniFilter.

    This is non-pageable because it may be called at DPC level.

Arguments:
    Data - Pointer to the filter callbackData that is passed to us.

    FltObjects - Pointer to the FLT_RELATED_OBJECTS data structure containing
        opaque handles to this filter, instance, its associated volume and
        file object.
    CompletionContext - The completion context set in the pre-operation routine.
    Flags - Denotes whether the completion is successful or is being drained.
Return Value:
    The return value is the status of the operation.
--*/
FLT_POSTOP_CALLBACK_STATUS RestFilterPostOperation(_Inout_ PFLT_CALLBACK_DATA Data, _In_ PCFLT_RELATED_OBJECTS FltObjects, _In_opt_ PVOID CompletionContext, _In_ FLT_POST_OPERATION_FLAGS Flags) {
    UNREFERENCED_PARAMETER(Data);
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(CompletionContext);
    UNREFERENCED_PARAMETER(Flags);

    PT_DBG_PRINT(PTDBG_TRACE_ROUTINES, ("RestFilter!RestFilterPostOperation: Entered\n"));

    return FLT_POSTOP_FINISHED_PROCESSING;
}

/*++
Routine Description:
    This routine is a pre-operation dispatch routine for this miniFilter.
    This is non-pageable because it could be called on the paging path

Arguments:
    Data - Pointer to the filter callbackData that is passed to us.
    FltObjects - Pointer to the FLT_RELATED_OBJECTS data structure containing
        opaque handles to this filter, instance, its associated volume and
        file object.
    CompletionContext - The context for the completion routine for this
        operation.
Return Value:
    The return value is the status of the operation.
--*/
FLT_PREOP_CALLBACK_STATUS RestFilterPreOperationNoPostOperation(_Inout_ PFLT_CALLBACK_DATA Data, _In_ PCFLT_RELATED_OBJECTS FltObjects, _Flt_CompletionContext_Outptr_ PVOID *CompletionContext) {
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    PT_DBG_PRINT(PTDBG_TRACE_ROUTINES, ("RestFilter!RestFilterPreOperationNoPostOperation: Entered\n"));

    // This template code does not do anything with the callbackData, but
    // rather returns FLT_PREOP_SUCCESS_NO_CALLBACK.
    // This passes the request down to the next miniFilter in the chain.

    return FLT_PREOP_SUCCESS_NO_CALLBACK;
}

/*++
Routine Description:
    This identifies those operations we want the operation status for.  These
    are typically operations that return STATUS_PENDING as a normal completion
    status.
Arguments:

Return Value:
    TRUE - If we want the operation status
    FALSE - If we don't

--*/
BOOLEAN RestFilterDoRequestOperationStatus(_In_ PFLT_CALLBACK_DATA Data) {
    PFLT_IO_PARAMETER_BLOCK iopb = Data->Iopb;

    //  return boolean state based on which operations we are interested in
    return (BOOLEAN)

        //
        //  Check for oplock operations
        //

        (((iopb->MajorFunction == IRP_MJ_FILE_SYSTEM_CONTROL) &&
        ((iopb->Parameters.FileSystemControl.Common.FsControlCode == FSCTL_REQUEST_FILTER_OPLOCK) ||
            (iopb->Parameters.FileSystemControl.Common.FsControlCode == FSCTL_REQUEST_BATCH_OPLOCK) ||
            (iopb->Parameters.FileSystemControl.Common.FsControlCode == FSCTL_REQUEST_OPLOCK_LEVEL_1) ||
            (iopb->Parameters.FileSystemControl.Common.FsControlCode == FSCTL_REQUEST_OPLOCK_LEVEL_2)))

            ||

            //
            //    Check for directy change notification
            //

            ((iopb->MajorFunction == IRP_MJ_DIRECTORY_CONTROL) &&
            (iopb->MinorFunction == IRP_MN_NOTIFY_CHANGE_DIRECTORY))
            );
}
