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
#include "ApgUtilities.h"

/** \file timer.c \brief A timer component API.

A convenient timer API used for the timing studies in the APG examples.
Uses a "context handle" or pointer to an opaque data structure for data encapsulation.
*/
/** \cond NOSHOW */
typedef struct
{
  void*     vpMemCtx;
  apg_uint     uiStarted;
  double    dStartTime;
  double    dEndTime;
  double    dDuration; // milliseconds
  double    dClocksPerSec;
  void*     vpValidate;
} APG_TIMER;
/** \endcond */

/** Constructs a timer component.
@param vpMemCtx pointer to a Memory component
@see Memory.c
@see vpMemCtor()
@return a context handle
*/
void* vpTimerCtor(void* vpMemCtx)
{
  void* vpRet = NULL;
  APG_TIMER* spCtx = NULL;
  while(APG_TRUE)
  {

    if(!vpMemCtx){break;}
    if(!uiMemValidate(vpMemCtx)){break;}
    spCtx = (APG_TIMER*)vpMemAlloc(vpMemCtx, sizeof(APG_TIMER));
    if(!spCtx){break;}
    memset((void*)spCtx, 0, sizeof(APG_TIMER));
    spCtx->vpMemCtx = vpMemCtx;
    spCtx->dClocksPerSec = (double)CLOCKS_PER_SEC;
    spCtx->vpValidate = (void*)spCtx;
    vpRet = (void*)spCtx;
    break;
  }
  if(vpMemCtx)
  {
    if(!vpRet && spCtx){vMemFree(vpMemCtx, (void*)spCtx);}
  }
  return vpRet;
}

/** Destroys a timer component.
@param vpCtx context handle previously returned from vpTimerCtor()
@see vpTimerCtor()
*/
void vTimerDtor(void* vpCtx)
{
  APG_TIMER* spCtx = (APG_TIMER*)vpCtx;
  if(vpCtx && spCtx->vpValidate == vpCtx)
  {
    spCtx->vpValidate = NULL;
    vMemFree(spCtx->vpMemCtx, vpCtx);
  }
}

/** Start the timer.
@param vpCtx context handle previously returned from vpTimerCtor()
@see vpTimerCtor()
@see uiTimerStop()
@return the start time in internal clock units
*/
apg_uint uiTimerStart(void* vpCtx)
{
  apg_uint uiRet = APG_FALSE;
  APG_TIMER* spCtx = (APG_TIMER*)vpCtx;
  if(vpCtx && spCtx->vpValidate == vpCtx)
  {
    spCtx->dEndTime = 0.0;
    spCtx->dDuration = 0.0;
    spCtx->dStartTime = (double)clock();
    spCtx->uiStarted = APG_TRUE;
    uiRet = APG_TRUE;
  }
  return uiRet;
}

/** Stop the timer.
@param vpCtx context handle previously returned from vpTimerCtor()
@see vpTimerCtor()
@see uiTimerStart()
@return the stop time in internal clock units
*/
apg_uint uiTimerStop(void* vpCtx)
{
  apg_uint uiRet = APG_FALSE;
  APG_TIMER* spCtx = (APG_TIMER*)vpCtx;
  if(vpCtx && spCtx->vpValidate == vpCtx  && spCtx->uiStarted)
  {
    spCtx->dEndTime = (double)clock();
    spCtx->dDuration = (spCtx->dEndTime - spCtx->dStartTime) / spCtx->dClocksPerSec;
    uiRet = APG_TRUE;
  }
  return uiRet;
}

/** Convert any value into a rate (value/duration).

eg. If the parser parsed uiCharacters characters between the start and stop times,
uiTimerRates(vpCtx, &uiCharacters, 1, APG_TIMER_MILLISEC) would overrite uiCharacters with uiCharacters/duration in the specified units.
@param vpCtx context handle previously returned from vpTimerCtor()
@param dpRates an array of values to convert to rates
@param uiLen the number of values in the array.
@param dConversion a time units conversion factor. Use 1 for seconds, 1000 for milliseconds, etc.

The following #define macros are available:
<pre>
APG_TIMER_SEC      - return value in seconds
APG_TIMER_MILLISEC - return value in milliseconds
APG_TIMER_MICROSEC - return value in microseconds
</pre>
@see vpTimerCtor()
@see uiTimerStart()
@see uiTimerStop()
@return true on success, false if the context handle vpCtx is invalid or the duration of the timer is 0.0.<br>
The rates overwrite the original values in the dpRates array.
*/
apg_uint uiTimerRates(void* vpCtx, double* dpRates, apg_uint uiLen, double dConversion)
{
  apg_uint uiRet = APG_FALSE;
  APG_TIMER* spCtx = (APG_TIMER*)vpCtx;
  if(vpCtx && spCtx->vpValidate == vpCtx && spCtx->dDuration != 0.0)
  {
    while(uiLen--)
    {
      if(*dpRates != 0.0)
      {
        *dpRates = *dpRates/( dConversion * spCtx->dDuration);
      }
      dpRates++;
    }
    uiRet = APG_TRUE;
  }
  return uiRet;
}

/** Get the start time in specified units.
@param vpCtx context handle previously returned from vpTimerCtor()
@param dConversion a time units conversion factor. Use 1 for seconds, 1000 for milliseconds, etc.

The following #define macros are available:
<pre>
APG_TIMER_SEC      - return value in seconds
APG_TIMER_MILLISEC - return value in milliseconds
APG_TIMER_MICROSEC - return value in microseconds
</pre>
@see vpTimerCtor()
@see uiTimerStart()
@see uiTimerStop()
@return the start time in units specified by the dConversion parameter
*/
double dTimerStartTime(void* vpCtx, double dConversion)
{
  double dRet = 0.0;
  APG_TIMER* spCtx = (APG_TIMER*)vpCtx;
  if(vpCtx && spCtx->vpValidate == vpCtx)
  {
    dRet = dConversion * spCtx->dStartTime;
  }
  return dRet;
}

/** Get the stop time in specified units.
@param vpCtx context handle previously returned from vpTimerCtor()
@param dConversion a time units conversion factor. Use 1 for seconds, 1000 for milliseconds, etc.

The following #define macros are available:
<pre>
APG_TIMER_SEC      - return value in seconds
APG_TIMER_MILLISEC - return value in milliseconds
APG_TIMER_MICROSEC - return value in microseconds
</pre>
@see vpTimerCtor()
@see uiTimerStart()
@see uiTimerStop()
@return the stop time in units specified by the dConversion parameter
*/
double dTimerStopTime(void* vpCtx, double dConversion)
{
  double dRet = 0.0;
  APG_TIMER* spCtx = (APG_TIMER*)vpCtx;
  if(vpCtx && spCtx->vpValidate == vpCtx)
  {
    dRet = dConversion * spCtx->dEndTime;
  }
  return dRet;
}

/** The timed duration in specified units.
@param vpCtx context handle previously returned from vpTimerCtor()
@param dConversion a time units conversion factor. Use 1 for seconds, 1000 for milliseconds, etc.

The following #define macros are available:
<pre>
APG_TIMER_SEC      - return value in seconds
APG_TIMER_MILLISEC - return value in milliseconds
APG_TIMER_MICROSEC - return value in microseconds
</pre>
@see vpTimerCtor()
@see uiTimerStart()
@see uiTimerStop()
@return the timed duration in units specified by the dConversion parameter
*/
double dTimerDuration(void* vpCtx, double dConversion)
{
  double dRet = 0.0;
  APG_TIMER* spCtx = (APG_TIMER*)vpCtx;
  if(vpCtx && spCtx->vpValidate == vpCtx)
  {
    dRet = dConversion * spCtx->dDuration;
  }
  return dRet;
}
