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
/** \file Vector.c \brief The Vector component API.

A Vector component is a dynamically dimensioned array.
That is, the array will always grow large enough to accomodate newly added array elements.
If the initial memory allocation becomes insufficient, the memory is re-allocated (and relocated).
The memory size is never reduced.
That is, the number of allocated array elements is always large enough to accomodate the maximum
size of the component over its lifetime.

Warning: Because of dynamic data re-allocation,
pointers to elements returned from the various APG functions are only valid until
the next push or pop operation. Be careful to refresh pointers after any such operations.
@see vpVecPush()
@see vpVecPushn()
@see vpVecPop()
@see vpVecPopn()
@see vpVecPopTo()
*/

#include "Apg.h"
#include "Private.h"

//////////////////////////////////////////////////////////////////////////
// VECTOR COMPONENT FUNCTIONS
//////////////////////////////////////////////////////////////////////////
/** \cond NOTENABLED */
// private vector instance context
typedef struct
{
  void* vpMemCtx;         // context to the underlying memory component
  char* cpData;           // pointer to the vector's data buffer
  apg_uint uiElementSize;    // number of bytes in one element
  apg_uint uiReserved;       // number of elements that have been reserved on the buffer
  apg_uint uiUsed;           // number of the reserved elements that have been used
  apg_uint uiReallocations;  // statistics - number buffer reallocations done
  void* vpValidate;       // must be equal to the struct address
} APG_VECTOR_CTX;

typedef struct
{
  apg_uint uiElementSize;
  apg_uint uiElements;
  apg_uint uiValidator;
} APG_VECTOR_EXPORT_HDR;
/** \endcond */

static apg_uint uiGrow(APG_VECTOR_CTX*   spCtx, apg_uint uiElements);

/** The Vector comonent constructor.
@param vpMemCtx a Memory component context handle, previously returned from vpMemCtor().
@param uiElementSize size, in bytes, of each array element. If 0, uses the default element size APG_VEC_ELEMENT.
@param uiInitialAlloc number of elements to initially allocate. If 0, uses the default APG_VEC_ALLOC.
@see vpMemCtor()
@return a Vector component context handle (a void pointer to an opaque data struct.)
NULL on construction failure.
*/
void* vpVecCtor(void* vpMemCtx, apg_uint uiElementSize, apg_uint uiInitialAlloc)
{
  void*	vpReturn = NULL;
  APG_VECTOR_CTX* spCtx;
  while(APG_TRUE){
	  if(!vpMemCtx){break;}
	  if(!uiMemValidate(vpMemCtx)){break;}
	    if(uiElementSize == 0){uiElementSize = APG_VEC_ELEMENT;}
	    if(uiInitialAlloc == 0){uiInitialAlloc = APG_VEC_ALLOC;}

	    // allocate the vector context
	    spCtx = (APG_VECTOR_CTX*)vpMemAlloc(vpMemCtx, sizeof(APG_VECTOR_CTX));
	    if(!spCtx){break;}

	    // allocate the initial vector buffer
	    memset((void*)spCtx, 0, sizeof(*spCtx));
	    spCtx->vpMemCtx = vpMemCtx;
	    spCtx->cpData = (char*)vpMemAlloc(vpMemCtx, uiElementSize * uiInitialAlloc);
	    if(!spCtx->cpData)
	    {
	      // free the context and return failure
	      vMemFree(vpMemCtx, (void*)spCtx);
	      break;
	    }

	    // initialize the context
	    spCtx->vpMemCtx = vpMemCtx;
	    spCtx->uiElementSize = uiElementSize;
	    spCtx->uiReserved = uiInitialAlloc;

	    // success
	    spCtx->vpValidate = (void*)spCtx;
	    vpReturn = (void*)spCtx;
	  break;
  }
  return vpReturn;
}

/** The Vector component destructor. Frees all resouces allocated to this component.
@param vpCtx a Vector component handle previously returned from vpVecCtor(). NULL or invalid handles are silently ignored.
@see vpVecCtor()
*/
void  vVecDtor(void* vpCtx)
{
    APG_VECTOR_CTX* spCtx = (APG_VECTOR_CTX*)vpCtx;
  // no error and no action if vpCtx = NULL
  if(vpCtx && (spCtx->vpValidate == (void*)spCtx))
  {
    // delete the data buffer & context
    spCtx->vpValidate = NULL;
    vMemFree(spCtx->vpMemCtx, (void*)spCtx->cpData);
    vMemFree(spCtx->vpMemCtx, (void*)spCtx);
  }
  return;
}

/** Validates a Vector component handle.
@param vpCtx a Vector component handle previously returned from vpVecCtor(). NULL or invalid handles are silently ignored.
@see vpVecCtor()
@return true if the handle is valid, false otherwise.
*/
apg_uint uiVecValidate(void* vpCtx){
	APG_VECTOR_CTX* spCtx = (APG_VECTOR_CTX*)vpCtx;
	return (spCtx && spCtx->vpValidate == (void*)spCtx);
}

/** Gets the number of bytes of data in use.
@param vpCtx a Vector component handle previously returned from vpVecCtor(). NULL or invalid handles are silently ignored.
@see vpVecCtor()
@return the size in bytes of the data in use. May be smaller than the size of the allocation.
*/
apg_uint uiVecBytes(void* vpCtx)
{
  apg_uint uiRet = 0;
  APG_VECTOR_CTX* spCtx = (APG_VECTOR_CTX*)vpCtx;
  if(spCtx && spCtx->vpValidate == (void*)spCtx){
	  uiRet = spCtx->uiUsed * spCtx->uiElementSize;
  }
  return uiRet;
}

/** Gets the number of array elements in use.
@param vpCtx a Vector component handle previously returned from vpVecCtor(). NULL or invalid handles are silently ignored.
@see vpVecCtor()
@return the number of vector array elements in use. May be smaller than the number that have been allocated.
*/
apg_uint uiVecSize(void* vpCtx)
{
  apg_uint uiRet = 0;
  APG_VECTOR_CTX* spCtx = (APG_VECTOR_CTX*)vpCtx;
  if(spCtx && spCtx->vpValidate == (void*)spCtx){
	  uiRet = spCtx->uiUsed;
  }
  return uiRet;
}

/** Gets the size of a single element.

Note that:<br>
uiVecBytes() = uiVecElementSize() * uiVecSize().
@param vpCtx a Vector component handle previously returned from vpVecCtor(). NULL or invalid handles are silently ignored.
@see vpVecCtor()
@return the number of bytes in a single element.
*/
apg_uint uiVecElementSize(void* vpCtx)
{
  apg_uint uiRet = 0;
  APG_VECTOR_CTX* spCtx = (APG_VECTOR_CTX*)vpCtx;
  if(spCtx && spCtx->vpValidate == (void*)spCtx){
	  uiRet = spCtx->uiElementSize;
  }
  return uiRet;
}

/** Gets the number times the array memory has been reallocated.
@param vpCtx a Vector component handle previously returned from vpVecCtor().
@see vpVecCtor()
@return the number times the array memory has been reallocated.
*/
apg_uint uiVecReallocations(void* vpCtx)
{
  apg_uint uiRet = 0;
  APG_VECTOR_CTX* spCtx = (APG_VECTOR_CTX*)vpCtx;
  if(spCtx && spCtx->vpValidate == (void*)spCtx){
	  uiRet = spCtx->uiReallocations;
  }
  return uiRet;
}

/** Clears all used elements in a Vector component.

This simply resents the current element pointer to zero.
No data is actually deleted.
No memory is released or re-allocated.
@param vpCtx a Vector component handle previously returned from vpVecCtor(). NULL or invalid handles are silently ignored.
@see vpVecCtor()
*/
void  vVecClear(void* vpCtx)
{
    APG_VECTOR_CTX* spCtx = (APG_VECTOR_CTX*)vpCtx;
  if(vpCtx && (spCtx->vpValidate == (void*)spCtx))
  {
    spCtx->uiUsed = 0;
  }
  return;
}

/** Adds one element to the end of the array.
@param vpCtx a Vector component handle previously returned from vpVecCtor().
@param vpElement pointer to the element to add. If NULL, space for a new element is added but no data is copied to it.
@see vpVecCtor()
@see vpVecPushn()
@see vpVecPop()
@see vpVecPopn()
@see vpVecPopTo()
@return a pointer to the new element in the array. NULL on failure.
*/
void* vpVecPush(void* vpCtx, void* vpElement)
{
  void*       vpReturn = NULL;
  apg_uint       uiTest = APG_TRUE;
  APG_VECTOR_CTX* spCtx = (APG_VECTOR_CTX*)vpCtx;
  while(APG_TRUE){
	  if(!(spCtx && spCtx->vpValidate == (void*)spCtx)){break;}
	  if(spCtx->uiUsed >= spCtx->uiReserved)
	  {
	    uiTest = uiGrow(spCtx, 1);
	    if(!uiTest){break;}
	  }

	  vpReturn = (void*)(spCtx->cpData + (spCtx->uiUsed * spCtx->uiElementSize));
	  if(vpElement)
	  {
	    // copy new element to vector
	    memcpy(vpReturn, vpElement, spCtx->uiElementSize);
	  }

	  // success, return a pointer to the new element
	  ++spCtx->uiUsed;
	  break;
  }
  return vpReturn;
}

/** Adds one or more elements to the end of the array.
@param vpCtx a Vector component handle previously returned from vpVecCtor().
@param vpElement pointer to the first element to add. If NULL, space for the new elements is added but no data is copied to it.
@param uiCount the number of elements to add.
@see vpVecCtor()
@see vpVecPush()
@see vpVecPop()
@see vpVecPopn()
@see vpVecPopTo()
@return a pointer to the first new element in the array. NULL on failure.
*/
void* vpVecPushn(void* vpCtx, void* vpElement, apg_uint uiCount)
{
  void*       vpReturn = NULL;
  apg_uint       uiTest = APG_TRUE;
  APG_VECTOR_CTX* spCtx = (APG_VECTOR_CTX*)vpCtx;
  while(APG_TRUE){
	  if(!(spCtx && spCtx->vpValidate == (void*)spCtx)){break;}

	  if(uiCount)
	  {
	    // check allocation
	    if((spCtx->uiUsed + uiCount) > spCtx->uiReserved)
	    {
	      uiTest = uiGrow(spCtx, uiCount);
	      if(!uiTest){break;}
	    }

	    vpReturn = (void*)(spCtx->cpData + (spCtx->uiUsed * spCtx->uiElementSize));
	    if(vpElement)
	    {
	      // copy new elements to vector
	      memcpy(vpReturn, vpElement, uiCount * spCtx->uiElementSize);
	    }
	    spCtx->uiUsed += uiCount;
	  }
	  break;
  }
  return vpReturn;
}

/** Pops one element from the end of the array.
@param vpCtx a Vector component handle previously returned from vpVecCtor().
@see vpVecCtor()
@see vpVecPopn()
@see vpVecPopTo()
@see vpVecPush()
@see vpVecPushn()
@return a pointer to the popped element. NULL if the Vector is empty.
*/
void* vpVecPop(void* vpCtx)
{
  void*       vpReturn = NULL;
  APG_VECTOR_CTX* spCtx = (APG_VECTOR_CTX*)vpCtx;
  if(spCtx && spCtx->vpValidate == (void*)spCtx){
	  if(spCtx->uiUsed)
	  {
	    // pop one element
	    --spCtx->uiUsed;
	    vpReturn = (void*)(spCtx->cpData + (spCtx->uiUsed * spCtx->uiElementSize));
	  }
  }
  // return a pointer to the popped element
  return vpReturn;
}

/** Pops one or more elements from the end of the array.
@param vpCtx a Vector component handle previously returned from vpVecCtor().
@param uiCount the number of elements to pop.
@see vpVecCtor()
@see vpVecPop()
@see vpVecPopTo()
@see vpVecPush()
@see vpVecPushn()
@return a pointer to the first popped element. NULL if the Vector is empty.
*/
void* vpVecPopn(void* vpCtx, apg_uint uiCount)
{
  void*       vpReturn = NULL;
  APG_VECTOR_CTX* spCtx = (APG_VECTOR_CTX*)vpCtx;
  if(spCtx && spCtx->vpValidate == (void*)spCtx){
	  if(uiCount > 0){
		  if(spCtx->uiUsed > 0){
			  if(spCtx->uiUsed > uiCount)
			  {
			    // pop uiCount elements
			    spCtx->uiUsed -= uiCount;
			    vpReturn = (void*)(spCtx->cpData + (spCtx->uiUsed * spCtx->uiElementSize));
			  }
			  else
			  {
			    // pop all remaining elements
			    spCtx->uiUsed = 0;
			    vpReturn = spCtx->cpData;
			  }
		  }
	  }
  }
  return vpReturn;
}

/** Pops one or more elements from the end of the array.
@param vpCtx a Vector component handle previously returned from vpVecCtor().
@param uiIndex index of the first element to pop. Elements uiIndex and all higher indexed elements are popped.
@see vpVecCtor()
@see vpVecPop()
@see vpVecPopn()
@see vpVecPush()
@see vpVecPushn()
@return a pointer to the first popped element. NULL if the Vector is empty or if uiIndex is larger than the largest indexed element in the array.
*/
void* vpVecPopTo(void* vpCtx, apg_uint uiIndex)
{
  void*       vpReturn = NULL;
  APG_VECTOR_CTX* spCtx = (APG_VECTOR_CTX*)vpCtx;
  if(spCtx && spCtx->vpValidate == (void*)spCtx){
	  if(!(spCtx->uiUsed == 0 || uiIndex >= spCtx->uiUsed)){

		  // success
		  spCtx->uiUsed = uiIndex;
		  vpReturn = (void*)(spCtx->cpData + uiIndex);
	  }
  }
  return vpReturn;
}

/** Get a the first element in the array. The array is not altered.
@param vpCtx a Vector component handle previously returned from vpVecCtor().
@see vpVecCtor()
@return a pointer to the first element in the array. NULL if the array is empty.
*/
void* vpVecFront(void* vpCtx)
{
  void*       vpReturn = NULL;
  APG_VECTOR_CTX* spCtx = (APG_VECTOR_CTX*)vpCtx;
  if(spCtx && spCtx->vpValidate == (void*)spCtx){
	  if(spCtx->uiUsed)
	  {
	    vpReturn = (void*)spCtx->cpData;
	  }
  }
  return vpReturn;
}

/** Get a the last element in the array. The array is not altered.
@param vpCtx a Vector component handle previously returned from vpVecCtor().
@see vpVecCtor()
@return a pointer to the last element in the array. NULL if the array is empty.
*/
void* vpVecBack(void* vpCtx)
{
  void*       vpReturn = NULL;
  APG_VECTOR_CTX* spCtx = (APG_VECTOR_CTX*)vpCtx;
  if(spCtx && spCtx->vpValidate == (void*)spCtx){
	  if(spCtx->uiUsed)
	  {
	    vpReturn = (void*)(spCtx->cpData + (spCtx->uiUsed - 1) * spCtx->uiElementSize);
	  }
  }
  return vpReturn;
}

/** Get a the indexed element in the array. The array is not altered.
@param vpCtx a Vector component handle previously returned from vpVecCtor().
@param uiIndex the index of the element to get (0-based)
@see vpVecCtor()
@return a pointer to the indexed element in the array. NULL if the array is empty or the index is out of range.
*/
void* vpVecAt(void* vpCtx, apg_uint uiIndex)
{
  void*       vpReturn = NULL;
  APG_VECTOR_CTX* spCtx = (APG_VECTOR_CTX*)vpCtx;
  if(spCtx && spCtx->vpValidate == (void*)spCtx){
	  if(uiIndex < spCtx->uiUsed)
	  {
	    vpReturn = (void*)(spCtx->cpData + (uiIndex * spCtx->uiElementSize));
	  }
  }
  return vpReturn;
}

//////////////////////////////////////////////////////////////////////////
// DESCRIPTION: reallocate the buffer
//              - increase the buffer size to double the previous space plus
//                  specified number of elements
//              - copy existing data to the new buffer
//
// FUNCTION: static apg_uint uiGrow
//
//      ARG: 1) APG_VECTOR_CTX* spCtx
//              : pointer to a valid vector context previously returned
//                from vpVecCtor()
//
//      ARG: 2) apg_uint uiElements
//              : minimum number of elements to make additional room for
//
//   RETURN: true on success, false on failure
//
//////////////////////////////////////////////////////////////////////////
static apg_uint uiGrow(APG_VECTOR_CTX* spCtx, apg_uint uiElements)
{
  apg_uint uiReturn = APG_FALSE;
  void* vpNewData;
  apg_uint uiReserved;

  // allocate new space
  uiReserved = 2 * (spCtx->uiReserved + uiElements);
  vpNewData = vpMemRealloc(spCtx->vpMemCtx, (void*)spCtx->cpData, spCtx->uiElementSize * uiReserved);
  if(vpNewData){
	  // success
	  spCtx->cpData = (char*)vpNewData;
	  spCtx->uiReserved = uiReserved;
	  ++spCtx->uiReallocations;
	  uiReturn = APG_TRUE;
  }
  return uiReturn;
}
