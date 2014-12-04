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

/** \file Files.c \brief A few commonly used functions for reading and writing files.
*/
//////////////////////////////////////////////////////////////////////////
// FILE HELPERS
//////////////////////////////////////////////////////////////////////////
/** Get the size of a file in bytes.

Useful when dynamically allocating a buffer for reading the entire file.
@param cpFileName the name of the file whose size to get
@see uiGetFile()
@return the file size on success, 0 if the file does not exist
*/
apg_uint uiGetFileSize(const char* cpFileName)
{
  FILE* spFile = NULL;
  int iTest;
  apg_uint uiReturn = 0;
  apg_uint uiLen;


  while(APG_TRUE)
  {
    spFile = fopen(cpFileName, "rb");
    if(!spFile){break;}
    iTest = fseek(spFile, 0, SEEK_END);
    if(iTest != 0){break;}
    uiLen = ftell(spFile);

    // success
    uiReturn = uiLen;
    break;
  }

  if(spFile){fclose(spFile);}
  return uiReturn;
}

/** Read an entire file into memory.
@param cpFileName the name of the file to get
@param vpBuffer pointer to the memory area to read the file into.
@see uiGetFileSize()
@return the file size on success, 0 if the file does not exist
*/
apg_uint uiGetFile(const char* cpFileName, void* vpBuffer)
{
  apg_uint uiSize;
  FILE* spFile = NULL;
  int iTest;
  apg_uint uiReturn = 0;
  apg_uint uiLen;



  while(APG_TRUE)
  {
    spFile = fopen(cpFileName, "rb");
    if(!spFile){break;}
    iTest = fseek(spFile, 0, SEEK_END);
    if(iTest != 0){break;}
    uiLen = ftell(spFile);
    iTest = fseek(spFile, 0, SEEK_SET);
    if(iTest != 0){break;}
    uiSize = fread(vpBuffer, 1, uiLen, spFile);
    if(uiSize != uiLen){break;}

    // success
    uiReturn = uiLen;
    break;
  }

  if(spFile){fclose(spFile);}
  return uiReturn;
}

/** Write data into a file. If the file already exists its data is overwritten.
@param cpFileName the name of the file to write
@param vpData pointer to the memory area to write.
@param uiDataLen the number of bytes of data to write
@return the number of bytes written. If not equal to uiDataLen an error occurred.
*/
apg_uint  uiWriteFile(const char* cpFileName, void* vpData, apg_uint uiDataLen)
{
  apg_uint uiReturn = 0;
  FILE* spFile = NULL;
  apg_uint uiBytesWritten = 0;


  while(APG_TRUE)
  {
    // validate
    if(!vpData){break;}
    if(uiDataLen ==0){break;}

    // open the file
    spFile = fopen(cpFileName, "wb");
    if(!spFile){break;}

    // write the data
    uiBytesWritten = fwrite(vpData, 1, uiDataLen, spFile);
    if(uiBytesWritten != uiDataLen){break;}

    // success
    uiReturn = uiDataLen;
    break;
  }

  if(spFile){fclose(spFile);}
  return uiReturn;
}

/** \cond NOSHOW */
void vJavaScriptApgBytes(FILE* in, FILE* out)
{
  int c;
  int count = 0;
  while(1)
  {
    c = getc(in);
    if(c == EOF){break;}
    fprintf(out, "0x%02X ", c);
    count++;
    if(count > 8)
    {
      fprintf(out, "\n");
      count = 0;
    }
  }
}
/** \endcond */

