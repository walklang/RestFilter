/////////////////////////////////////////////////////////////////////////////////////////// 
// 
// Copyright (c) 2018 The Authors of ANT(http:://ant.sh) . All Rights Reserved. 
// Use of this source code is governed by a BSD-style license that can be 
// found in the LICENSE file. 
// 
// Environment: user and kernel mode.
//
// This module contains the common declarations shared by driver and user applications.
// 
/////////////////////////////////////////////////////////////////////////////////////////// 


#ifndef REST_FILTER_TYPES_INCLUDE_H_ 
#define REST_FILTER_TYPES_INCLUDE_H_ 

#include <guiddef.h>

// Define an Interface GUID so that apps can find the device and talk to it.
// {a3ad6e86-5e31-4213-b75a-ce1b764c01e4} 
DEFINE_GUID (GUID_DEVINTERFACE_RestFilter, 
    0xa3ad6e86, 0x5e31, 0x4213, 0xb7, 0x5a, 0xce, 0x1b, 0x76, 0x4c, 0x01, 0xe4);



#endif  // !#define (REST_FILTER_TYPES_INCLUDE_H_ )