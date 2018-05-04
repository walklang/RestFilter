////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2017 The Authors of ANT(http://ant.sh). All Rights Reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
////////////////////////////////////////////////////////////////////////////////

#include "device.h"

#include <fltKernel.h>
#include <dontuse.h>
#include <suppress.h>

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

// Assign text sections for each routine.
#ifdef ALLOC_PRAGMA
#pragma alloc_text(PAGE, InstanceSetup)
#pragma alloc_text(PAGE, RestFilterInstanceQueryTeardown)
#pragma alloc_text(PAGE, RestFilterInstanceTeardownStart)
#pragma alloc_text(PAGE, RestFilterInstanceTeardownComplete)
#endif

/*++
Routine Description:

    This routine is called whenever a new instance is created on a volume. This
    gives us a chance to decide if we need to attach to this volume or not.

    If this routine is not defined in the registration structure, automatic
    instances are always created.

Arguments:

    FltObjects - Pointer to the FLT_RELATED_OBJECTS data structure containing
        opaque handles to this filter, instance and its associated volume.

    Flags - Flags describing the reason for this attach request.

Return Value:

    STATUS_SUCCESS - attach
    STATUS_FLT_DO_NOT_ATTACH - do not attach

--*/
NTSTATUS InstanceSetup(_In_ PCFLT_RELATED_OBJECTS FltObjects, _In_ FLT_INSTANCE_SETUP_FLAGS Flags, _In_ DEVICE_TYPE VolumeDeviceType, _In_ FLT_FILESYSTEM_TYPE VolumeFilesystemType) {
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( Flags );
    UNREFERENCED_PARAMETER( VolumeDeviceType );
    UNREFERENCED_PARAMETER( VolumeFilesystemType );

    PAGED_CODE();

    PT_DBG_PRINT(PTDBG_TRACE_ROUTINES, ("RestFilter!RestFilterInstanceSetup: Entered\n"));

    return STATUS_SUCCESS;
}

/*++

Routine Description:
    This is called when an instance is being manually deleted by a
    call to FltDetachVolume or FilterDetach thereby giving us a
    chance to fail that detach request.
    If this routine is not defined in the registration structure, explicit
    detach requests via FltDetachVolume or FilterDetach will always be
    failed.
Arguments:
    FltObjects - Pointer to the FLT_RELATED_OBJECTS data structure containing opaque handles to this filter, instance and its associated volume.
    Flags - Indicating where this detach request came from.
Return Value:
    Returns the status of this operation.
--*/
NTSTATUS RestFilterInstanceQueryTeardown(_In_ PCFLT_RELATED_OBJECTS FltObjects, _In_ FLT_INSTANCE_QUERY_TEARDOWN_FLAGS Flags) {
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( Flags );

    PAGED_CODE();
    PT_DBG_PRINT(PTDBG_TRACE_ROUTINES, ("RestFilter!RestFilterInstanceQueryTeardown: Entered\n"));

    return STATUS_SUCCESS;
}

/*++

Routine Description:
    This routine is called at the start of instance teardown.
Arguments:
    FltObjects - Pointer to the FLT_RELATED_OBJECTS data structure containing
        opaque handles to this filter, instance and its associated volume.
    Flags - Reason why this instance is being deleted.
Return Value:
    None.
--*/
VOID RestFilterInstanceTeardownStart(_In_ PCFLT_RELATED_OBJECTS FltObjects, _In_ FLT_INSTANCE_TEARDOWN_FLAGS Flags) {
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( Flags );

    PAGED_CODE();
    PT_DBG_PRINT(PTDBG_TRACE_ROUTINES, ("RestFilter!RestFilterInstanceTeardownStart: Entered\n"));
}

/*++

Routine Description:
    This routine is called at the end of instance teardown.
Arguments:
    FltObjects - Pointer to the FLT_RELATED_OBJECTS data structure containing
        opaque handles to this filter, instance and its associated volume.
    Flags - Reason why this instance is being deleted.
Return Value:
    None.
--*/
VOID RestFilterInstanceTeardownComplete(_In_ PCFLT_RELATED_OBJECTS FltObjects, _In_ FLT_INSTANCE_TEARDOWN_FLAGS Flags) {
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( Flags );

    PAGED_CODE();
    PT_DBG_PRINT(PTDBG_TRACE_ROUTINES, ("RestFilter!RestFilterInstanceTeardownComplete: Entered\n"));
}
