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
#include "Apg.h"
#include "WideGrammar.h"

// NOTE 1: Generator's ApgLib version number = "6.3"

// NOTE 2: The Parser's alphabet character (apg_achar) must be large enough to accommodate the grammar's largest character.
//         Grammar's largest alphabet character = 4294967295
//         Parser's sizeof(apg_achar) must be  >= 4
//         Grammar's largest integer(*)         = 4294967295
//         Parser's sizeof(apg_uint) must be   >= 4
//
//    (*): sizeof(apg_uint) <= 2 should be used with caution and only for extemely small parsers.
//         The largest integer refers only to the grammar's data. Other Parser integer's may,
//         and likely will, have larger requirements. Parser may fail unpredictably.

static unsigned long int ulData[478] = {
    4, 4, 3824, 0, -1, -1, 20, 4, 321, 135, 456, 22, 24, 14, 38, 10, 0, 0, 118, 29, 
    54, 46, 51, 0, 3, 4, 5, 6, 2, 7, 9, 10, 14, 15, 19, 20, 26, 27, 8, 353, 14, 4, 14, 
    0, 0, 8, 10, 451, 13, 19, 13, 1, 8, 4, 11, 491, 10, 33, 10, 2, 12, 1, 13, 523, 16, 
    44, 16, 3, 13, 4, 14, 569, 13, 61, 13, 4, 17, 1, 16, 601, 16, 75, 16, 5, 18, 4, 
    17, 647, 13, 92, 13, 6, 22, 1, 19, 679, 13, 106, 13, 7, 23, 2, 20, 710, 10, 120, 
    10, 8, 25, 3, 22, 751, 3, 131, 3, 9, 28, 1, 30, 8, 372, 77, 1, 1, -1, 41, 8, 375, 
    73, 4, 2, 0, 40, 8, 376, 67, 0, 4, 0, 10, 8, 376, 13, -1, 1, 0, 10, 8, 392, 16, 
    -1, 3, 0, 10, 8, 411, 16, -1, 5, 0, 10, 8, 430, 13, -1, 7, 0, 10, 8, 445, 3, -1, 
    9, 0, 41, 10, 470, 20, 6, 2, 0, 70, 10, 470, 7, 0, 5, 0, 30, 10, 478, 12, 11, 1, 
    -1, 10, 10, 480, 10, -1, 2, 0, 90, 11, 510, 11, 880, 1023, 0, 41, 13, 542, 26, 8, 
    2, 0, 70, 13, 542, 10, 5, 8, 0, 30, 13, 553, 15, 16, 1, -1, 10, 13, 555, 13, -1, 
    4, 0, 90, 14, 588, 11, 1024, 1279, 0, 41, 16, 620, 26, 10, 2, 0, 70, 16, 620, 10, 
    13, 8, 0, 30, 16, 631, 15, 21, 1, -1, 10, 16, 633, 13, -1, 6, 0, 90, 17, 666, 11, 
    5024, 5119, 0, 30, 19, 698, 11, 24, 0, -1, 10, 19, 699, 10, -1, 8, 0, 40, 20, 729, 
    20, 12, 2, 0, 90, 20, 729, 12, 11, -1, 0, 90, 20, 744, 5, 0, 9, 0, 80, 22, 770, 
    3, 21, 1, 0, 54, 46, 51, 0, 85, 84, 70, 51, 50, 45, 101, 120, 97, 109, 112, 108, 
    101, 115, 0, 103, 114, 101, 101, 107, 45, 101, 120, 97, 109, 112, 108, 101, 0, 103, 
    114, 101, 101, 107, 45, 99, 104, 97, 114, 0, 99, 121, 114, 105, 108, 108, 105, 99, 
    45, 101, 120, 97, 109, 112, 108, 101, 0, 99, 121, 114, 105, 108, 108, 105, 99, 45, 
    99, 104, 97, 114, 0, 99, 104, 101, 114, 111, 107, 101, 101, 45, 101, 120, 97, 109, 
    112, 108, 101, 0, 99, 104, 101, 114, 111, 107, 101, 101, 45, 99, 104, 97, 114, 0, 
    101, 114, 114, 111, 114, 45, 101, 120, 97, 109, 112, 108, 101, 0, 101, 114, 114, 
    111, 114, 45, 99, 104, 97, 114, 0, 101, 110, 100, 0, 71, 114, 101, 101, 107, 67, 
    121, 114, 105, 108, 108, 105, 99, 67, 104, 101, 114, 111, 107, 101, 101, 10
};

// Parser initialization data
void* vpParserInit_WideGrammar = (void*)&ulData[0];
