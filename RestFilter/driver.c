////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2017 The Authors of ANT(http://ant.sh). All Rights Reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Abstract:
//   This file contains the driver entry points and callbacks.
////////////////////////////////////////////////////////////////////////////////

#include "driver.h"

#include <fltKernel.h>

#include "callback.h"
#include "device.h"
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
#pragma alloc_text(INIT, DriverEntry)
#pragma alloc_text(PAGE, RestFilterUnload)
#endif

REST_FILTER_DATA rest;

// operation registration
CONST FLT_OPERATION_REGISTRATION Callbacks[] = {
    { IRP_MJ_CREATE,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_CREATE_NAMED_PIPE,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_CLOSE,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_READ,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_WRITE,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_QUERY_INFORMATION,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_SET_INFORMATION,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_QUERY_EA,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_SET_EA,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_FLUSH_BUFFERS,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_QUERY_VOLUME_INFORMATION,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_SET_VOLUME_INFORMATION,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_DIRECTORY_CONTROL,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_FILE_SYSTEM_CONTROL,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_DEVICE_CONTROL,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_INTERNAL_DEVICE_CONTROL,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_SHUTDOWN,
      0,
      RestFilterPreOperationNoPostOperation,
      NULL },                               //post operations not supported

    { IRP_MJ_LOCK_CONTROL,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_CLEANUP,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_CREATE_MAILSLOT,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_QUERY_SECURITY,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_SET_SECURITY,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_QUERY_QUOTA,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_SET_QUOTA,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_PNP,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_ACQUIRE_FOR_SECTION_SYNCHRONIZATION,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_RELEASE_FOR_SECTION_SYNCHRONIZATION,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_ACQUIRE_FOR_MOD_WRITE,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_RELEASE_FOR_MOD_WRITE,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_ACQUIRE_FOR_CC_FLUSH,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_RELEASE_FOR_CC_FLUSH,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_FAST_IO_CHECK_IF_POSSIBLE,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_NETWORK_QUERY_OPEN,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_MDL_READ,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_MDL_READ_COMPLETE,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_PREPARE_MDL_WRITE,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_MDL_WRITE_COMPLETE,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_VOLUME_MOUNT,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_VOLUME_DISMOUNT,
      0,
      RestFilterPreOperation,
      RestFilterPostOperation },

    { IRP_MJ_OPERATION_END }
};


// This defines what we want to filter with FltMgr
CONST FLT_REGISTRATION FilterRegistration = {
    sizeof(FLT_REGISTRATION),           //  Size
    FLT_REGISTRATION_VERSION,           //  Version
    0,                                  //  Flags

    NULL,                               //  Context
    Callbacks,                          //  Operation callbacks

    RestFilterUnload,                   //  MiniFilterUnload

    InstanceSetup,                      //  InstanceSetup
    RestFilterInstanceQueryTeardown,    //  InstanceQueryTeardown
    RestFilterInstanceTeardownStart,    //  InstanceTeardownStart
    RestFilterInstanceTeardownComplete, //  InstanceTeardownComplete

    NULL,                               //  GenerateFileName
    NULL,                               //  GenerateDestinationFileName
    NULL                                //  NormalizeNameComponent
};


/*++
Routine Description:
    This is the initialization routine for this miniFilter driver.  This registers with FltMgr and initializes all global data structures.
Arguments:
    DriverObject - Pointer to driver object created by the system to represent this driver.
    RegistryPath - Unicode string identifying where the parameters for this driver are located in the registry.
Return Value:
    Routine can return non success error codes.
--*/
NTSTATUS DriverEntry (_In_ PDRIVER_OBJECT DriverObject,  _In_ PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER( RegistryPath );

    // Initialize global data structures.
    rest.driver = DriverObject;
    rest.status_ctx = 1;

    NTSTATUS status;
    PT_DBG_PRINT(PTDBG_TRACE_ROUTINES, ("RestFilter!DriverEntry: Entered\n") );


    //  Register with FltMgr to tell it our callback routines
    status = FltRegisterFilter(DriverObject, &FilterRegistration, &rest.filter);
    FLT_ASSERT( NT_SUCCESS( status ) );

    if (!NT_SUCCESS(status)) return status;

    // Start filtering i/o
    status = FltStartFiltering(rest.filter);
    if (!NT_SUCCESS( status )) {
        FltUnregisterFilter(rest.filter);
        return status;
    }

    return status;
}


/*++

Routine Description:
    This is the unload routine for this miniFilter driver. This is called
    when the minifilter is about to be unloaded. We can fail this unload
    request if this is not a mandatory unload indicated by the Flags
    parameter.
Arguments:
    Flags - Indicating if this is a mandatory unload.
Return Value:
    Returns STATUS_SUCCESS.
--*/
NTSTATUS RestFilterUnload (_In_ FLT_FILTER_UNLOAD_FLAGS Flags) {
    UNREFERENCED_PARAMETER(Flags);
    PAGED_CODE();
    PT_DBG_PRINT(PTDBG_TRACE_ROUTINES, ("RestFilter!RestFilterUnload: Entered\n"));
    FltUnregisterFilter(rest.filter);
    return STATUS_SUCCESS;
}
