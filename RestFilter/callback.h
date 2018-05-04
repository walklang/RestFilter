/////////////////////////////////////////////////////////////////////////////////////////// 
// 
// Copyright (c) 2018 The Authors of ANT(http:://ant.sh) . All Rights Reserved. 
// Use of this source code is governed by a BSD-style license that can be 
// found in the LICENSE file. 
// 
// Environment: kernel mode.
// 
// This file contains the callback routines definitions.
// 
/////////////////////////////////////////////////////////////////////////////////////////// 


#ifndef REST_FILTER_CALLBACK_INCLUDE_H_
#define REST_FILTER_CALLBACK_INCLUDE_H_

#include <fltKernel.h>
#include <ntdef.h>

// This is the context that can be placed per queue and would contain per queue information.
// TODO:






// REST Filter callback routines.
EXTERN_C_START

FLT_PREOP_CALLBACK_STATUS RestFilterPreOperation(_Inout_ PFLT_CALLBACK_DATA Data, _In_ PCFLT_RELATED_OBJECTS FltObjects, _Flt_CompletionContext_Outptr_ PVOID *CompletionContext);
FLT_POSTOP_CALLBACK_STATUS RestFilterPostOperation(_Inout_ PFLT_CALLBACK_DATA Data, _In_ PCFLT_RELATED_OBJECTS FltObjects, _In_opt_ PVOID CompletionContext, _In_ FLT_POST_OPERATION_FLAGS Flags);

FLT_PREOP_CALLBACK_STATUS RestFilterPreOperationNoPostOperation(_Inout_ PFLT_CALLBACK_DATA Data, _In_ PCFLT_RELATED_OBJECTS FltObjects, _Flt_CompletionContext_Outptr_ PVOID *CompletionContext);

BOOLEAN RestFilterDoRequestOperationStatus(_In_ PFLT_CALLBACK_DATA Data);

EXTERN_C_END

#endif  // !#define (REST_FILTER_CALLBACK_INCLUDE_H_ )