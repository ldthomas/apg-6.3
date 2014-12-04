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
#include "Generator.h"

void* vpErrorsCtor(void* vpMemCtx, void* vpAlertHandler){
	void* vpReturn = NULL;
	ERRORS_CTX* spCtx = NULL;
	while(APG_TRUE){
		if(!vpMemCtx){break;}

		// allocate & clear the data
		spCtx = (ERRORS_CTX*)vpMemAlloc(vpMemCtx, sizeof(ERRORS_CTX));
		if(!spCtx){break;}
		memset((void*)spCtx, 0, sizeof(ERRORS_CTX));
		spCtx->vpMemCtx = vpMemCtx;
		if(vpAlertHandler){spCtx->pfnAlertHandler = (PFN_ALERT)vpAlertHandler;}
		else{spCtx->pfnAlertHandler = vTerminalAlert;}

		// allocate a vector of error messages
		spCtx->vpVecMsgs = vpVecCtor(vpMemCtx, sizeof(char), 1000);
		if(!spCtx->vpVecMsgs){break;}
		spCtx->vpVecMsgIndex = vpVecCtor(vpMemCtx, sizeof(G_UINT), 100);
		if(!spCtx->vpVecMsgIndex){break;}

		// success
		vpReturn = (void*)spCtx;
		break;
	}
	if(!vpReturn){
		if(spCtx->vpVecMsgs){vVecDtor(spCtx->vpVecMsgs);}
		if(spCtx->vpVecMsgIndex){vVecDtor(spCtx->vpVecMsgIndex);}
		if(spCtx->vpMemCtx){vMemFree(vpMemCtx, spCtx->vpMemCtx);}
	}
  return vpReturn;
}

void  vErrorsDtor(void* vpErrorsCtx){
	ERRORS_CTX* spCtx = (ERRORS_CTX*)vpErrorsCtx;
	if(spCtx){
		void* vpMemCtx = spCtx->vpMemCtx;
		if(spCtx->vpVecMsgs){vVecDtor(spCtx->vpVecMsgs);}
		if(spCtx->vpVecMsgIndex){vVecDtor(spCtx->vpVecMsgIndex);}
		memset((void*)spCtx, 0, sizeof(ERRORS_CTX));
		vMemFree(vpMemCtx, spCtx->vpMemCtx);
	}
}

void	vErrorsReport(void* vpErrorsCtx, char* cpMsg){
	G_UINT uiLen, uiIndex;
	char  cNull = 0;
	void* vpTest;
	ERRORS_CTX* spCtx = (ERRORS_CTX*)vpErrorsCtx;
	while(APG_TRUE){
		if(!(spCtx && cpMsg)){break;}

		// push the message on the msg vector
		uiLen = strlen(cpMsg);
		if(!uiLen){break;}
		uiIndex = uiVecSize(spCtx->vpVecMsgs);
		vpTest = vpVecPushn(spCtx->vpVecMsgs, (void*)cpMsg, uiLen);
		if(!vpTest){break;}
		vpTest = vpVecPush(spCtx->vpVecMsgs, (void*)&cNull);
		if(!vpTest){break;}
		vpTest = vpVecPush(spCtx->vpVecMsgIndex, (void*)&uiIndex);
		if(!vpTest){break;}

		// success
		break;
	}
}

G_UINT uiErrorsCount(void* vpErrorsCtx){
	G_UINT uiRet = 0;
	ERRORS_CTX* spCtx = (ERRORS_CTX*)vpErrorsCtx;
	if(spCtx){uiRet = uiVecSize(spCtx->vpVecMsgIndex);}
	return uiRet;
}

char* cpErrorsIterInit(void* vpErrorsCtx){
	char* cpRet = NULL;
	G_UINT* uipIndex;
	ERRORS_CTX* spCtx = (ERRORS_CTX*)vpErrorsCtx;
	while(APG_TRUE){
		if(!spCtx){break;}
		spCtx->uiIterNext = APG_UNDEFINED;
		uipIndex = (G_UINT*)vpVecFront(spCtx->vpVecMsgIndex);
		if(!uipIndex){break;}
		cpRet = (char*)vpVecAt(spCtx->vpVecMsgs, *uipIndex);
		if(!cpRet){break;}
		spCtx->uiIterNext = 1;
		break;
	}
	return cpRet;
}

char* cpErrorsIterNext(void* vpErrorsCtx){
	char* cpRet = NULL;
	G_UINT* uipIndex;
	ERRORS_CTX* spCtx = (ERRORS_CTX*)vpErrorsCtx;
	while(APG_TRUE){
		if(!spCtx){break;}
		uipIndex = (G_UINT*)vpVecAt(spCtx->vpVecMsgIndex, spCtx->uiIterNext);
		if(!uipIndex){break;}
		cpRet = (char*)vpVecAt(spCtx->vpVecMsgs, *uipIndex);
		if(!cpRet){break;}
		spCtx->uiIterNext++;
		break;
	}
	return cpRet;
}
