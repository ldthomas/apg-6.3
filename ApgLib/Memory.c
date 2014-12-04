/*******************************************************************************
  APG Version 6.3
  Copyright (C) 2005 - 2012 Lowell D. Thomas, all rights reserved

  author:  Lowell D. Thomas
  email:   lowell@coasttocoastresearch.com
  website: http://www.coasttocoastresearch.com

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see
  <http://www.gnu.org/licenses/old-licenses/gpl-2.0.html>
  or write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*******************************************************************************/
/** \file Memory.c \brief The Memory component API.

The Memory component is a simple, doubly-linked list of "cells".
A cell is simply a data struct of linked list pointers and memory allocation information.
*/

#include "Apg.h"
#include "Private.h"

/** \cond NOTENABLED */
#define MEM_ID_ALLOC    0
#define MEM_ID_REALLOC  1
#define MEM_ID_FREE     2
/** \endcond */
static void vMemStats(APG_MEM_STATS* spStats, apg_uint uiID, APG_MEM_CELL* spIn, APG_MEM_CELL* spOut);
static void vActivePush(APG_MEM_CTX* spCtx, APG_MEM_CELL* spCellIn);
static void vActivePop(APG_MEM_CTX* spCtx, APG_MEM_CELL* spCellIn);

//////////////////////////////////////////////////////////////////////////
// MEMORY MANAGEMENT COMPONENT FUNCTIONS
//   - Lowest-level APG component
//   - Does NO error reporting other than returning a NULL pointer
//     as an allocation failure indicator.
//   - always collects memory statistics in both debug and release modes
//////////////////////////////////////////////////////////////////////////

/** Constructs a Memory component using a user-defined memory allocator and de-allocator.
@param pfnAllocator pointer to a user-defined memory allocator
@param pfnDeAllocator pointer to a user-defined memory de-allocator
@return a Memory context handle (void pointer to an opaque data struct). NULL on failure.
*/
void*   vpMemCtorA(PFN_ALLOCATOR pfnAllocator, PFN_DEALLOCATOR pfnDeAllocator){
  void*           vpReturn = NULL;
  APG_MEM_CTX*    spCtx;
  if(pfnAllocator && pfnDeAllocator){
    spCtx = (APG_MEM_CTX*)pfnAllocator(sizeof(APG_MEM_CTX));
    if(spCtx){
      memset((void*)spCtx, 0, sizeof(APG_MEM_CTX));
      spCtx->pfnAllocator = pfnAllocator;
      spCtx->pfnDeAllocator = pfnDeAllocator;

      // success
      spCtx->vpValidate = (void*)spCtx;
      vpReturn = (void*)spCtx;
    }
  }
  return vpReturn;
}

/** Constructs a Memory component using malloc() as the memory allocator and free() as the de-allocator.
@return a Memory context handle (void pointer to an opaque data struct). NULL on failure.
*/
void* vpMemCtor(){return vpMemCtorA(malloc, free);}

//////////////////////////////////////////////////////////////////////////
// DESCRIPTION: memory component destructor
//
// FUNCTION: void vMemDtor
//
//      ARG: 1) void* vpCtx
//              : pointer to a memory context previously returned
//                from vpMemCtor() or vpMemCtorA()
//                NULL pointers are ignored, no action and no error
//
//   RETURN: void
//
//////////////////////////////////////////////////////////////////////////
/** Destroys a Memory component.
@param vpCtx a Memory context handle previously returned from vpMemCtor(), or vpMemCtorA(). NULL pointers are silently ignored.
@see vpMemCtor()
@see vpMemCtorA()
*/
void   vMemDtor(void* vpCtx){
  if(vpCtx){
    APG_MEM_CTX* spCtx = (APG_MEM_CTX*)vpCtx;
    if(spCtx->vpValidate == (void*)spCtx){
      PFN_DEALLOCATOR pfnDeAllocator = spCtx->pfnDeAllocator;
      vMemClear(vpCtx);
      memset(vpCtx, 0, sizeof(APG_MEM_CTX));
      pfnDeAllocator(vpCtx);
    }
  }
}

/** Validates a Memory context handle.
@param vpCtx a Memory context handle previously returned from vpMemCtor(), or vpMemCtorA().
@see vpMemCtor()
@see vpMemCtorA()
@return true if the handle is valid, false otherwise.
*/
apg_uint uiMemValidate(void* vpCtx){
  apg_uint uiRet = APG_FALSE;
  APG_MEM_CTX* spCtx = (APG_MEM_CTX*)vpCtx;
  if(vpCtx && spCtx->vpValidate == vpCtx){uiRet = APG_TRUE;}
  return uiRet;
}

/** Allocates memory.
@param vpCtx a Memory context handle previously returned from vpMemCtor(), or vpMemCtorA().
@param uiBytes the number of bytes of memory to allocate
@see vpMemCtor()
@see vpMemCtorA()
@see vMemFree()
@return a pointer to the allocated memory, NULL on allocation failure.
*/
void* vpMemAlloc(void* vpCtx, apg_uint uiBytes){
  void*         vpReturn = NULL;
  APG_MEM_CTX*  spCtx = (APG_MEM_CTX*)vpCtx;
  APG_MEM_CELL* spCell;
  if(spCtx && spCtx->vpValidate == (void*)spCtx){
    spCell = (APG_MEM_CELL*)spCtx->pfnAllocator(uiBytes + sizeof(APG_MEM_CELL));
    if(spCell){
      spCell->uiSize = uiBytes;

      // push it on the active list
      vActivePush(spCtx, spCell);
      vMemStats(&spCtx->sStats, MEM_ID_ALLOC, spCell, 0);

      // success
      vpReturn = (void*)(spCell + 1);
    }
  }
  return vpReturn;
}

/** De-allocates memory previously allocated with vpMemAlloc().
@param vpCtx a Memory context handle previously returned from vpMemCtor(), or vpMemCtorA(). NULL pointers are silently ignored.
@param vpData pointer to the memory allocation to free. If NULL, silently ignored.
@see vpMemCtor()
@see vpMemCtorA()
@see vpMemAlloc()
*/
void vMemFree(void* vpCtx, void* vpData){
  APG_MEM_CTX*  spCtx = (APG_MEM_CTX*)vpCtx;
  APG_MEM_CELL* spCell;
  if(vpData){
    if(spCtx && spCtx->vpValidate == (void*)spCtx){
      spCell = (APG_MEM_CELL*)vpData;
      --spCell;

      // pop from active list
      vMemStats(&spCtx->sStats, MEM_ID_FREE, spCell, 0);
      vActivePop(spCtx, spCell);
    }
  }
}

/** Re-allocates memory previously allocated with vpMemAlloc(). Can be used to up-size or down-size a memory allocation.
Any previous data in the memory allocation is copied to the re-allocation.
@param vpCtx a Memory context handle previously returned from vpMemCtor(), or vpMemCtorA().
@param vpData pointer to the memory to be re-allocated.
@param uiBytes number of re-allocated bytes of memory.
@see vpMemCtor()
@see vpMemCtorA()
@see vpMemAlloc()()
@return pointer to the re-allocated memory. NULL if re-allocation failed.
*/
void* vpMemRealloc(void* vpCtx, void* vpData, apg_uint uiBytes){
  void*         vpReturn = NULL;
  APG_MEM_CTX*  spCtx = (APG_MEM_CTX*)vpCtx;
  APG_MEM_CELL* spOldCell;
  APG_MEM_CELL* spNewCell;
  void*         vpDst;
  void*         vpSrc;
  apg_uint         uiCopy;

  if(vpData && uiBytes){
    if(spCtx && spCtx->vpValidate == (void*)spCtx){
      spOldCell = (APG_MEM_CELL*)vpData;
      --spOldCell;

      // get the new allocation
      spNewCell = (APG_MEM_CELL*)spCtx->pfnAllocator(uiBytes + sizeof(APG_MEM_CELL));
      if(spNewCell){
        spNewCell->spNext = spOldCell->spNext;
        spNewCell->spPrev = spOldCell->spPrev;
        spOldCell->spNext->spPrev = (struct APG_MEM_CELL_STRUCT*)spNewCell;
        spOldCell->spPrev->spNext = (struct APG_MEM_CELL_STRUCT*)spNewCell;
        spNewCell->uiSeq = spOldCell->uiSeq;
        spNewCell->uiSize = uiBytes;

        // copy the data from old allocation to new
        uiCopy = min(uiBytes, spOldCell->uiSize);
        vpDst = (void*)(spNewCell + 1);
        vpSrc = (void*)(spOldCell + 1);
        memcpy(vpDst, vpSrc, uiCopy);

        // free the old data
        vMemStats(&spCtx->sStats, MEM_ID_REALLOC, spOldCell, spNewCell);
        //APG_MEMSTATS(&spCtx->sStats, MEM_ID_REALLOC, spOldCell, spNewCell);
        spCtx->pfnDeAllocator((void*)spOldCell);
        vpReturn = (void*)(spNewCell + 1);
      }
    }
  }
  return vpReturn;
}

/** Returns a check point to the current state of the memory component. Can be used later to restore the current state.
@param vpCtx a Memory context handle previously returned from vpMemCtor(), or vpMemCtorA().
@see vpMemCtor()
@see vpMemCtorA()
@see vMemFreeToCheckPoint()
@return current state
*/
apg_uint uiMemCheckPoint(void* vpCtx){
  APG_MEM_CTX*  spCtx = (APG_MEM_CTX*)vpCtx;
  APG_MEM_CELL* spLast;
  apg_uint         uiChk = 0;
  if(spCtx && spCtx->vpValidate == (void*)spCtx){
    if(spCtx->spActiveList){
      spLast = (APG_MEM_CELL*)spCtx->spActiveList->spPrev;
      uiChk = spLast->uiSeq + 1;
    }
  }
  return uiChk;
}

/** Restores a previous state of the Memory component.
@param vpCtx a Memory context handle previously returned from vpMemCtor(), or vpMemCtorA(). NULL pointers are silently ignored.
@param uiChk the previous state to restore. Must be from a previous call to uiMemCheckPoint().
@see vpMemCtor()
@see vpMemCtorA()
@see uiMemCheckPoint()
*/
void vMemFreeToCheckPoint(void* vpCtx, apg_uint uiChk){
  APG_MEM_CTX*  spCtx = (APG_MEM_CTX*)vpCtx;
  APG_MEM_CELL* spLast;
  if(spCtx && spCtx->vpValidate == (void*)spCtx){
    // release all active blocks above the check point
    while(APG_TRUE){
      // break if list is empty
      if(spCtx->spActiveList == NULL){break;}

      // remove the last cell from the active list
      spLast = (APG_MEM_CELL*)spCtx->spActiveList->spPrev;

      // break if this cell is below check point
      if(spLast->uiSeq < uiChk){break;}

      // remove the cell from the active list
      vMemStats(&spCtx->sStats, MEM_ID_FREE, spLast, 0);
      vActivePop(spCtx, spLast);
    }
  }
}

/** Frees all memory allocations from this Memory component.
@param vpCtx a Memory context handle previously returned from vpMemCtor(), or vpMemCtorA(). NULL pointers are silently ignored.
@see vpMemCtor()
@see vpMemCtorA()
*/
void vMemClear(void* vpCtx){vMemFreeToCheckPoint(vpCtx, 0);}

/** Returns a copy of the Memory componenet's current statistics.
@param vpCtx a Memory context handle previously returned from vpMemCtor(), or vpMemCtorA().
@param spStats pointer to a user-supplied statistics buffer. May be NULL, in which case only the required size of the statistics buffer is returned.
@see vpMemCtor()
@see vpMemCtorA()
@see APG_MEM_STATS
@return the required size of the statistics buffer.
*/
apg_uint   uiMemStats(void* vpCtx, APG_MEM_STATS* spStats){
  apg_uint uiRet = 0;
  APG_MEM_CTX* spMemCtx = (APG_MEM_CTX*)vpCtx;
  if(vpCtx && uiMemValidate(vpCtx)){
    if(spStats){
      memcpy((void*)spStats, (void*)&spMemCtx->sStats, sizeof(APG_MEM_STATS));
    }
    uiRet = sizeof(APG_MEM_STATS);
  }
  return uiRet;
}

//////////////////////////////////////////////////////////////////////////
// STATIC HELPER FUNCTIONS
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// DESCRIPTION: Updates memory statistics.
//
// FUNCTION: static void vMemStats
//
//      ARG: 1) APG_MEM_STATS* spStats
//              : pointer to a statistics struct
//
//      ARG: 2) apg_uint uiID
//              : MEM_ID_ALLOC - update allocation stats on allocation
//              : MEM_ID_REALLOC - update reallocation stats
//              : MEM_ID_FREE - update allocation stats on deallocation
//
//      ARG: 3) APG_MEM_CELL* spIn
//              : pointer to the memory cell being re/de/allocated
//
//      ARG: 4) APG_MEM_CELL* spOut
//              : pointer to the new, reallocated memory cell
//
//   RETURN: void
//
//////////////////////////////////////////////////////////////////////////
static void vMemStats(APG_MEM_STATS* spStats, apg_uint uiID, APG_MEM_CELL* spIn, APG_MEM_CELL* spOut){
  switch(uiID)  {
  case MEM_ID_ALLOC:
    ++spStats->uiAllocations;
    ++spStats->uiCells;
    spStats->uiHeapBytes += spIn->uiSize + sizeof(APG_MEM_CELL);
    if(spStats->uiCells > spStats->uiMaxCells)
    {
      spStats->uiMaxCells = spStats->uiCells;
    }
    if(spStats->uiHeapBytes > spStats->uiMaxHeapBytes)
    {
      spStats->uiMaxHeapBytes = spStats->uiHeapBytes;
    }
    break;
  case MEM_ID_REALLOC:
    ++spStats->uiReAllocations;
    spStats->uiHeapBytes += spOut->uiSize - spIn->uiSize;
    if(spStats->uiHeapBytes > spStats->uiMaxHeapBytes){spStats->uiMaxHeapBytes = spStats->uiHeapBytes;}
    break;
  case MEM_ID_FREE:
    ++spStats->uiFrees;
    --spStats->uiCells;
    spStats->uiHeapBytes -= spIn->uiSize + sizeof(APG_MEM_CELL);
    break;
  }

}

//////////////////////////////////////////////////////////////////////////
// DESCRIPTION: push a new memory cell on the linked list
//
// FUNCTION: static void vActivePush
//
//      ARG: 1) APG_MEM_CTX* spCtx
//              : pointer to a memory context previously returned
//                from vpMemCtor() or vpMemCtorA()
//
//      ARG: 2) APG_MEM_CELL* spCellIn
//              : the new cell to be pushed
//
//   RETURN: void
//
//////////////////////////////////////////////////////////////////////////
static void vActivePush(APG_MEM_CTX* spCtx, APG_MEM_CELL* spCellIn){
  struct APG_MEM_CELL_STRUCT* spLast;
  struct APG_MEM_CELL_STRUCT* spFirst;
  struct APG_MEM_CELL_STRUCT* spCell = (struct APG_MEM_CELL_STRUCT*)spCellIn;

  // sequence number roll over is a fatal error
  // link the cell
  switch(spCtx->uiActiveCellCount){
  case 0:
    spCtx->spActiveList = spCell;
    spCell->spNext = spCell->spPrev = spCell;
    spCell->uiSeq = 0;
    break;
  case 1:
    spLast = spCtx->spActiveList;
    spLast->spNext = spLast->spPrev = spCell;
    spCell->spNext = spCell->spPrev = spLast;
    spCell->uiSeq = spLast->uiSeq + 1;
    break;
  default:
    spFirst = spCtx->spActiveList;
    spLast = spFirst->spPrev;
    spFirst->spPrev = spCell;
    spLast->spNext = spCell;
    spCell->spNext = spFirst;
    spCell->spPrev = spLast;
    spCell->uiSeq = spLast->uiSeq + 1;
    break;
  }

  ++spCtx->uiActiveCellCount;
}

//////////////////////////////////////////////////////////////////////////
// DESCRIPTION: removes (pops) a memory cell from the linked list
//
// FUNCTION: static void vActivePop
//
//      ARG: 1) APG_MEM_CTX* spCtx
//              : pointer to a memory context previously returned
//                from vpMemCtor() or vpMemCtorA()
//
//      ARG: 2) APG_MEM_CELL* spCellIn
//              : the memory cell to be removed (popped)
//
//   RETURN: void
//
//////////////////////////////////////////////////////////////////////////
static void vActivePop(APG_MEM_CTX* spCtx, APG_MEM_CELL* spCellIn){
  struct APG_MEM_CELL_STRUCT* spPrev;
  struct APG_MEM_CELL_STRUCT* spNext;
  struct APG_MEM_CELL_STRUCT* spCell = (struct APG_MEM_CELL_STRUCT*)spCellIn;

  if(spCtx->spActiveList == spCell){
    // update the pointer to the first cell
    if(spCtx->uiActiveCellCount == 1){
      spCtx->spActiveList = NULL;
    } else{spCtx->spActiveList = spCtx->spActiveList->spNext;}
  }

  // remove the cell from the active list
  spPrev = spCell->spPrev;
  spNext = spCell->spNext;
  spPrev->spNext = spCell->spNext;
  spNext->spPrev = spCell->spPrev;

  --spCtx->uiActiveCellCount;

  // free the data
  spCtx->pfnDeAllocator((void*)spCell);
}
