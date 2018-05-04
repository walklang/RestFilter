/////////////////////////////////////////////////////////////////////////////////////////// 
// 
// Copyright (c) 2018 The Authors of ANT(http:://ant.sh) . All Rights Reserved. 
// Use of this source code is governed by a BSD-style license that can be 
// found in the LICENSE file. 
// 
// Environment: kernel mode.
// 
// This file contains the driver definitions.
// 
/////////////////////////////////////////////////////////////////////////////////////////// 


#ifndef REST_FILTER_DRIVER_INCLUDE_H_ 
#define REST_FILTER_DRIVER_INCLUDE_H_ 

#include <fltKernel.h>
#include <dontuse.h>
#include <suppress.h>

#pragma prefast(disable:__WARNING_ENCODE_MEMBER_FUNCTION_POINTER, "Not valid for kernel mode drivers")

// Global variables
typedef struct __REST_FILTER_DATA {
    PDRIVER_OBJECT  driver;     // The object that identifies this driver.
    PFLT_FILTER     filter;     // The filter that results from a call to.

    ULONG_PTR       status_ctx; // Operation Status Ctx. 

} REST_FILTER_DATA, *PREST_FILTER_DATA;

extern REST_FILTER_DATA rest;




// REST Filter initialization and unload routines.
EXTERN_C_START

DRIVER_INITIALIZE DriverEntry;

NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath);
NTSTATUS RestFilterUnload(_In_ FLT_FILTER_UNLOAD_FLAGS Flags);

EXTERN_C_END

#endif  // !#define (REST_FILTER_DRIVER_INCLUDE_H_ )