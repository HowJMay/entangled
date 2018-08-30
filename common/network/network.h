/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/entangled
 *
 * Refer to the LICENSE file for licensing information
 */

#ifndef __COMMON_NETWORK_H__
#define __COMMON_NETWORK_H__

#define MAX_SCHEME_LENGTH 8
#define MAX_HOST_LENGTH 255

typedef enum protocol_type_e { PROTOCOL_TCP, PROTOCOL_UDP } protocol_type_t;
typedef enum ip_version_e { IPV4, IPV6 } ip_version_t;

#endif // __COMMON_NETWORK_H__
