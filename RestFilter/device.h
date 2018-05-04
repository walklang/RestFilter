/////////////////////////////////////////////////////////////////////////////////////////// 
// 
// Copyright (c) 2018 The Authors of ANT(http:://ant.sh) . All Rights Reserved. 
// Use of this source code is governed by a BSD-style license that can be 
// found in the LICENSE file.
// 
// Environment: kernel mode.
// 
// Abstract:
//   This file contains the device definitions.
// 
/////////////////////////////////////////////////////////////////////////////////////////// 


#ifndef REST_FILTER_DEVICE_INCLUDE_H_ 
#define REST_FILTER_DEVICE_INCLUDE_H_ 

#include <fltKernel.h>
#include <ntdef.h>
#include <ntifs.h>

// REST Filter setup and teardown routines.
EXTERN_C_START

NTSTATUS InstanceSetup(_In_ PCFLT_RELATED_OBJECTS FltObjects, _In_ FLT_INSTANCE_SETUP_FLAGS Flags, _In_ DEVICE_TYPE VolumeDeviceType, _In_ FLT_FILESYSTEM_TYPE VolumeFilesystemType);
NTSTATUS RestFilterInstanceQueryTeardown(_In_ PCFLT_RELATED_OBJECTS FltObjects, _In_ FLT_INSTANCE_QUERY_TEARDOWN_FLAGS Flags);

VOID RestFilterInstanceTeardownStart(_In_ PCFLT_RELATED_OBJECTS FltObjects, _In_ FLT_INSTANCE_TEARDOWN_FLAGS Flags);
VOID RestFilterInstanceTeardownComplete(_In_ PCFLT_RELATED_OBJECTS FltObjects, _In_ FLT_INSTANCE_TEARDOWN_FLAGS Flags);

EXTERN_C_END

#endif  // !#define (REST_FILTER_DEVICE_INCLUDE_H_ )