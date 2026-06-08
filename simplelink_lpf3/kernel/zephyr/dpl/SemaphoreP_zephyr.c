/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/__assert.h>
#include <kernel/zephyr/dpl/dpl.h>
#include <ti/drivers/dpl/SemaphoreP.h>
#include <zephyr/tracing/tracking.h>

/*
 * Zephyr kernel object pools:
 *
 * This bit of code enables the simplelink host driver, which assumes dynamic
 * allocation of kernel objects (semaphores, mutexes, hwis), to be
 * more easily ported to Zephyr (which supports static allocation).
 *
 * It leverages the Zephyr memory slab, enabling us to define a semaphore
 * object pool for use by the SimpleLink host driver.
 */
#define DPL_MAX_SEMAPHORES 14 /* (user.h:MAX_CONCURRENT_ACTIONS+4) = 14 */
K_MEM_SLAB_DEFINE(sem_slab, sizeof(struct k_sem), DPL_MAX_SEMAPHORES, MEM_ALIGN);

static struct k_sem *dpl_sem_pool_alloc()
{
    struct k_sem *sem_ptr = NULL;

    if (k_mem_slab_alloc(&sem_slab, (void **)&sem_ptr, K_NO_WAIT) < 0)
    {
        /*
         * We assert, as this is a logic error, due to a change in #
         * of semaphores needed by the simplelink driver. In that case,
         * the sem pool must be increased programmatically to match.
         */
        __ASSERT(0, "Increase size of DPL semaphore pool");
    }
    return sem_ptr;
}

static SemaphoreP_Status dpl_sem_pool_free(struct k_sem *sem)
{
    k_mem_slab_free(&sem_slab, sem);

    return SemaphoreP_OK;
}

SemaphoreP_Handle SemaphoreP_create(unsigned int count, SemaphoreP_Params *params)
{
    unsigned int limit = UINT_MAX;
    struct k_sem *sem;

    if (params)
    {
        limit = (params->mode == SemaphoreP_Mode_BINARY) ? 1 : UINT_MAX;
    }

    sem = dpl_sem_pool_alloc();
    if (sem)
    {
        k_sem_init(sem, count, limit);
        return (SemaphoreP_Handle)sem;
    }
    return NULL;
}

SemaphoreP_Handle SemaphoreP_createBinary(unsigned int count)
{
    SemaphoreP_Params params;

    SemaphoreP_Params_init(&params);
    params.mode = SemaphoreP_Mode_BINARY;

    return (SemaphoreP_create(count, &params));
}

void SemaphoreP_delete(SemaphoreP_Handle handle)
{
    k_sem_reset((struct k_sem *)handle);

    (void)dpl_sem_pool_free((struct k_sem *)handle);
}

void SemaphoreP_Params_init(SemaphoreP_Params *params)
{
    params->mode     = SemaphoreP_Mode_COUNTING;
    params->callback = NULL;
}

/*
 * The SimpleLink driver calls this function with a timeout of 0 to "clear"
 * the SyncObject, rather than calling dpl_SyncObjClear() directly.
 * See: <simplelinksdk>/source/ti/drivers/net/wifi/source/driver.h
 *  #define SL_DRV_SYNC_OBJ_CLEAR(pObj)
 *	    (void)sl_SyncObjWait(pObj,SL_OS_NO_WAIT);
 *
 * So, we claim (via simplelink driver code inspection), that SyncObjWait
 * will *only* be called with timeout == 0 if the intention is to clear the
 * semaphore: in that case, we just call k_sem_reset.
 */
SemaphoreP_Status SemaphoreP_pend(SemaphoreP_Handle handle, uint32_t timeout)
{
    int retval;

    if (DPL_NO_WAIT == timeout)
    {
        k_sem_reset((struct k_sem *)handle);
        retval = SemaphoreP_OK;
    }
    else
    {
        retval = k_sem_take((struct k_sem *)handle, dpl_to_zephyr_timeout(timeout));
        __ASSERT_NO_MSG(retval != -EBUSY);
        retval = (retval >= 0) ? SemaphoreP_OK : SemaphoreP_TIMEOUT;
    }
    return retval;
}

void SemaphoreP_post(SemaphoreP_Handle handle)
{
    k_sem_give((struct k_sem *)handle);
}

SemaphoreP_Handle SemaphoreP_construct(SemaphoreP_Struct *handle, unsigned int count, SemaphoreP_Params *params)
{
    unsigned int limit = UINT_MAX;
    struct k_sem *sem;

    if (params)
    {
        limit = (params->mode == SemaphoreP_Mode_BINARY) ? 1 : UINT_MAX;
    }

    sem = (struct k_sem *)handle;
    if (sem)
    {
        k_sem_init(sem, count, limit);
    }

    return (SemaphoreP_Handle)sem;
}

SemaphoreP_Handle SemaphoreP_constructBinary(SemaphoreP_Struct *handle, unsigned int count)
{
    SemaphoreP_Params params;

    SemaphoreP_Params_init(&params);
    params.mode = SemaphoreP_Mode_BINARY;

    return (SemaphoreP_construct(handle, count, &params));
}

void SemaphoreP_destruct(SemaphoreP_Struct *semP)
{
    if (semP == NULL)
    {
      return;
    }

    struct k_sem *sem = (struct k_sem *)semP;

    #ifdef CONFIG_OBJ_CORE_SEM
        /* Verify if the semaphore exists */
        if (sem->obj_core.type != NULL)
        {
            /* Remove the obj_core.node from obj_type_sem.list */
            k_obj_core_unlink(K_OBJ_CORE(sem));
        }
    #endif

         #if defined(CONFIG_TRACING_OBJECT_TRACKING) && defined(CONFIG_TRACING_SEMAPHORE)
        {
            /* Disable interrupts to protect the list from modification done from another context by a function such as k_sem_init() */
            unsigned int key = irq_lock();
            struct k_sem *prev = NULL;
            struct k_sem *curr = _track_list_k_sem; /* curr starts in head of list */
 
            /* traverse the entire list (until tail) */
            while (curr != NULL)
            {
                /* When the semaphore is found */
                if (curr == sem)
                {
                    /* Then the semaphore is in the head, never updated. Move the global head pointer to the next address of the node */
                    if (prev == NULL)
                    {
                        /* Redirect the predecessor to the successor to erase node in between */
                        /* The head now points to the next sem track address */
                        _track_list_k_sem = SYS_PORT_TRACK_NEXT(sem);
                    }
                    else
                    /* The semaphore is somewhere in the middle or in the tail, so bypass prev over sem connecting prev to the next address of the node. */
                    /* prev points to curr/_track_list_k_sem therefore assigning _track_list_k_sem next addr (which has same k_sem struct) to sem->_obj_track_next. */
                    {
                        SYS_PORT_TRACK_NEXT(prev) = SYS_PORT_TRACK_NEXT(sem);
                    }
                    /* Set semaphore next pointer to NULL. */
                    SYS_PORT_TRACK_NEXT(sem) = NULL;
                    break;
                }
                /* Move the pointers one step forward searching for sem. */
                prev = curr;
                curr = SYS_PORT_TRACK_NEXT(curr);
            }
            /* Re-enable interrupts, when then list is consistent again */
            irq_unlock(key);
        }
        #endif

    k_sem_reset(sem);
}
