/** @defgroup os_rpc Remote Procedure Calls
 *
 * @ingroup os
 *
 * This kernel implementation of RPC mechanism.
 */

/** @ingroup os_rpc
 * @{
 */
#pragma once

#include <stdint.h>

struct RPC_Service_t_;

typedef struct RPC_Service_t_ RPC_Service_t;

typedef int (*RPC_Method_t)(RPC_Service_t * service, unsigned arg0, unsigned arg1, unsigned arg2, unsigned arg3);

typedef RPC_Method_t * VTable_t ;

struct RPC_Service_t_ {
	VTable_t * vtable;
};

/** Kernel implementation of rpc_call syscall.
 *
 * This routine performs remote procedure call. It digs for 
 * 5th and 6th argument passed to @ref _rpc_call() on thread stack. Retrieves
 * address of called method from service VMT and synthesizes stack frame for
 * jumping into this method. Arguments used to call _rpc_call() are passed to
 * callee.
 */
int os_rpc_call(uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3);

/** Kernel implementation of rpc_return syscall.
 *
 * This routine unwinds stack frame used to call RPC method and passes return
 * value from RPC to the caller.
 */
int os_rpc_return(uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3);

/** @} */
