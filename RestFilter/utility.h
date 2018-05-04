/////////////////////////////////////////////////////////////////////////////////////////// 
// 
// Copyright (c) 2018 The Authors of ANT(http:://ant.sh) . All Rights Reserved. 
// Use of this source code is governed by a BSD-style license that can be 
// found in the LICENSE file. 
// 
/////////////////////////////////////////////////////////////////////////////////////////// 


#ifndef REST_FILTER_TRACE_INCLUDE_H_ 
#define REST_FILTER_TRACE_INCLUDE_H_ 

#include <minwindef.h>

#ifdef DEBUG
ULONG gTrackFlags = 0;
#else
static ULONG gTrackFlags = 1;
#endif


#define PTDBG_TRACE_ROUTINES            0x00000001
#define PTDBG_TRACE_OPERATION_STATUS    0x00000002

#define PT_DBG_PRINT( _dbgLevel, _string )          \
    (FlagOn(gTrackFlags,(_dbgLevel)) ?              \
        DbgPrint _string :                          \
        ((int)0))




#endif  // !#define (REST_FILTER_TRACE_INCLUDE_H_ )