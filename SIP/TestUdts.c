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

#include "main.h"

static apg_achar g_acaBuffer[1024];
static void vPrintPhrase(apg_achar* acpPhrase, apg_uint uiPhraseLength){
	char caBuf[4096];
	if(uiPhraseLength > 4095){
		printf("vPrintPhrase: phrase length too long\n");
	} else{
		apg_uint i = 0;
		apg_uint j = 0;
		caBuf[j++] = '"';
		for(;i < uiPhraseLength; i++){
			if(acpPhrase[i] == (apg_achar)'\t'){caBuf[j++] = '\\';caBuf[j++] = 't';}
			else if(acpPhrase[i] == (apg_achar)'\r'){caBuf[j++] = '\\';caBuf[j++] = 'r';}
			else if(acpPhrase[i] == (apg_achar)'\n'){caBuf[j++] = '\\';caBuf[j++] = 'n';}
			else if(acpPhrase[i] < (apg_achar)32){j += sprintf(&caBuf[j], "\\x%02X", acpPhrase[i]);}
			else if(acpPhrase[i] > (apg_achar)126){j += sprintf(&caBuf[j], "\\x%02X", acpPhrase[i]);}
			else{caBuf[j++] = (apg_achar)acpPhrase[i];}
		}
		caBuf[j++] = '"';
		caBuf[j] = 0;
		printf("%s\n", caBuf);
	}
}

apg_uint uiTestHostname(){
	apg_uint uiRet = APG_TRUE;
	apg_achar* acpPhrase = &g_acaBuffer[0];
	apg_uint uiDomainLength;
	apg_uint uiTopLength;
	apg_uint uiTestLength;
	apg_uint i;
	char* cpTestPhrase;
	APG_CBDATA sData;
	char* cpaTests[] = {
			"x-x.y--y-y.x-x.",
			"1-x.1--1-y.xx.",
			"x-x.y--y-y.1x.",
			"x-.yy.xx.",
			"xx.yy..xx-",
			"xx.yy.x1",
			"x",
			"xx.-yy.xx.",
			"xx.yy.1x.",
			"xx.yy.zz  ",
			"xx.yy.zz"
	};
	apg_uint uiTestCount = sizeof(cpaTests)/sizeof(char*);

	// tests
	printf("\n");
	printf("uiTestHostname: \n");
	for(i = 0; i < uiTestCount; i++){
		char cSave;
		cpTestPhrase = cpaTests[i];
		uiTestLength = strlen(cpTestPhrase);
		vCharToAChar(acpPhrase, cpTestPhrase, uiTestLength);
		acpPhrase[uiTestLength] = (apg_achar)0;
		sData.acpSrc = acpPhrase;
		sData.uiSrcLen = uiTestLength;
		sData.uiPhraseOffset = 0;
		uiDomainLength = uiSIP_e_domainlabel(&sData);
		uiDomainLength = sData.uiPhraseLength;
		sData.uiPhraseOffset = uiDomainLength;
		uiTopLength = uiSIP_u_toplabel(&sData);
		uiTopLength = sData.uiPhraseLength;
		printf("\nuiTestHostname:  phrase[%2u]: \"%s\"\n", (apg_uint)i, acpPhrase);
		cSave = acpPhrase[uiDomainLength];
		acpPhrase[uiDomainLength] = 0;
		printf(  "uiTestHostname: domainlabel: \"%s\"\n", acpPhrase);
		acpPhrase[uiDomainLength] = cSave;
		if(uiTopLength == APG_UNDEFINED){
			printf(  "uiTestHostname:    toplabel: FAILED\n");
		} else{
			cSave = acpPhrase[uiDomainLength + uiTopLength];
			acpPhrase[uiDomainLength + uiTopLength] = 0;
			printf(  "uiTestHostname:    toplabel: \"%s\"\n", &acpPhrase[uiDomainLength]);
			acpPhrase[uiDomainLength + uiTopLength] = cSave;
		}
	}
	return uiRet;
}

apg_uint uiTestUnresereved(){
	apg_uint uiRet = APG_TRUE;
	apg_achar* acpPhrase = &g_acaBuffer[0];
	apg_uint uiTestLength;
	apg_uint i;
	apg_uint uiPhraseLength;
	char* cpTestPhrase;
	APG_CBDATA sData;
	char* cpaTests[] = {
			"aa",
			"Zx",
			"1",
			"-",
			"_",
			".",
			"!",
			"~",
			"*",
			"'",
			"(",
			")",
			"&",
			"Z"
	};
	apg_uint uiTestCount = sizeof(cpaTests)/sizeof(char*);

	// tests
	printf("\n");
	printf("uiTestUnresereved: \n");
	for(i = 0; i < uiTestCount; i++){
		char cSave;
		cpTestPhrase = cpaTests[i];
		uiTestLength = strlen(cpTestPhrase);
		vCharToAChar(acpPhrase, cpTestPhrase, uiTestLength);
		acpPhrase[uiTestLength] = (apg_achar)0;
		sData.acpSrc = acpPhrase;
		sData.uiSrcLen = uiTestLength;
		sData.uiPhraseOffset = 0;
		uiPhraseLength = uiSIP_u_unreserved(&sData);
		uiPhraseLength = sData.uiPhraseLength;
		printf("\nuiTestResereved:  phrase[%2u]: \"%s\"\n", (apg_uint)i, acpPhrase);
		if(uiPhraseLength == APG_UNDEFINED){
			printf(  "uiTestResereved:    FAILED\n");
		} else{
			cSave = acpPhrase[uiPhraseLength];
			acpPhrase[uiPhraseLength] = 0;
			printf(  "uiTestHostname:    unreserved: \"%s\"\n", &acpPhrase[0]);
			acpPhrase[uiPhraseLength] = cSave;
		}
	}
	return uiRet;
}

apg_uint uiTestToken(){
	apg_uint uiRet = APG_TRUE;
	apg_achar* acpPhrase = &g_acaBuffer[0];
	apg_uint uiTestLength;
	apg_uint i;
	apg_uint uiPhraseLength;
	char* cpTestPhrase;
	APG_CBDATA sData;
	char* cpaTests[] = {
			"-.!%&*_+`'~",
			"aa111",
			"ZxalAFKJHsdkjf03495832",
			"",
			"$-.!%*_+`'~",
			"-.!%*_+`'~",
			"Z"
	};
	apg_uint uiTestCount = sizeof(cpaTests)/sizeof(char*);

	// tests
	printf("\n");
	printf("uiTestToken: \n");
	for(i = 0; i < uiTestCount; i++){
		char cSave;
		cpTestPhrase = cpaTests[i];
		uiTestLength = strlen(cpTestPhrase);
		vCharToAChar(acpPhrase, cpTestPhrase, uiTestLength);
		acpPhrase[uiTestLength] = (apg_achar)0;
		sData.acpSrc = acpPhrase;
		sData.uiSrcLen = uiTestLength;
		sData.uiPhraseOffset = 0;
		uiPhraseLength = uiSIP_u_token(&sData);
		uiPhraseLength = sData.uiPhraseLength;
		printf("\nuiTestToken:  phrase[%2u]: \"%s\"\n", (apg_uint)i, acpPhrase);
		if(uiPhraseLength == APG_UNDEFINED){
			printf(  "uiTestToken:    FAILED\n");
		} else{
			cSave = acpPhrase[uiPhraseLength];
			acpPhrase[uiPhraseLength] = 0;
			printf(  "uiTestToken:    token: \"%s\"\n", &acpPhrase[0]);
			acpPhrase[uiPhraseLength] = cSave;
		}
	}
	return uiRet;
}

apg_uint uiTestScheme(){
	apg_uint uiRet = APG_TRUE;
	apg_achar* acpPhrase = &g_acaBuffer[0];
	apg_uint uiTestLength;
	apg_uint i;
	apg_uint uiPhraseLength;
	char* cpTestPhrase;
	APG_CBDATA sData;
	//scheme =  ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )
	char* cpaTests[] = {
			"ZxalAFKJHsdkjf03495832",
			"aa111",
			"P+-.amg",
			"+-.amg",
			"",
			"$-.!%*_+`'~",
			"abc2-.+`'~",
			"Z"
	};
	apg_uint uiTestCount = sizeof(cpaTests)/sizeof(char*);

	// tests
	printf("\n");
	printf("uiTestScheme: \n");
	for(i = 0; i < uiTestCount; i++){
		char cSave;
		cpTestPhrase = cpaTests[i];
		uiTestLength = strlen(cpTestPhrase);
		vCharToAChar(acpPhrase, cpTestPhrase, uiTestLength);
		acpPhrase[uiTestLength] = (apg_achar)0;
		sData.acpSrc = acpPhrase;
		sData.uiSrcLen = uiTestLength;
		sData.uiPhraseOffset = 0;
		uiPhraseLength = uiSIP_u_scheme(&sData);
		uiPhraseLength = sData.uiPhraseLength;
		printf("\n");
		printf("uiTestScheme:  phrase[%2u]: \"%s\"\n", (apg_uint)i, acpPhrase);
		if(uiPhraseLength == APG_UNDEFINED){
			printf(  "uiTestScheme:    FAILED\n");
		} else{
			cSave = acpPhrase[uiPhraseLength];
			acpPhrase[uiPhraseLength] = 0;
			printf(  "uiTestScheme:    scheme: \"%s\"\n", &acpPhrase[0]);
			acpPhrase[uiPhraseLength] = cSave;
		}
	}
	return uiRet;
}

apg_uint uiTestCallid(){
	apg_uint uiRet = APG_TRUE;
	apg_achar* acpPhrase = &g_acaBuffer[0];
	apg_uint uiTestLength;
	apg_uint i;
	apg_uint uiPhraseLength;
	char* cpTestPhrase;
	APG_CBDATA sData;
	char* cpaTests[] = {
			"a",
			"a@z",
			"azAZ09@a-.!%*_+'~()<>:\\\"/[]?{}",
			"1azAZ09@a-.!%*_+'~()<>:\\\"/[]?{}",
			"azAZ09@a-.!%*_+'~()$<>:\\\"/[]?{}",
			"<zAZ09>@a-.!%*_+'~()<>:\\\"/[]?{}",
			"&zAZ09>@a-.!%*_+'~()<>:\\\"/[]?{}",
			"@a-.!%*_+'~()<>:\\\"/[]?{}",
			"Z"
	};
	apg_uint uiTestCount = sizeof(cpaTests)/sizeof(char*);

	// tests
	printf("\n");
	printf("uiTestCallid: \n");
	for(i = 0; i < uiTestCount; i++){
		char cSave;
		cpTestPhrase = cpaTests[i];
		uiTestLength = strlen(cpTestPhrase);
		vCharToAChar(acpPhrase, cpTestPhrase, uiTestLength);
		acpPhrase[uiTestLength] = (apg_achar)0;
		sData.acpSrc = acpPhrase;
		sData.uiSrcLen = uiTestLength;
		sData.uiPhraseOffset = 0;
		uiPhraseLength = uiSIP_u_callid(&sData);
		uiPhraseLength = sData.uiPhraseLength;
		printf("\n");
		printf("uiTestCallid:  phrase[%2u]: \"%s\"\n", (apg_uint)i, acpPhrase);
		if(uiPhraseLength == APG_UNDEFINED){
			printf(  "uiTestCallid:    FAILED\n");
		} else{
			cSave = acpPhrase[uiPhraseLength];
			acpPhrase[uiPhraseLength] = 0;
			printf(  "uiTestCallid:    scheme: \"%s\"\n", &acpPhrase[0]);
			acpPhrase[uiPhraseLength] = cSave;
		}
	}
	return uiRet;
}

apg_uint uiTestRFC1035Domain(){
	apg_uint uiRet = APG_TRUE;
	apg_achar* acpPhrase = &g_acaBuffer[0];
	apg_uint uiTestLength;
	apg_uint i;
	apg_uint uiPhraseLength;
	char* cpTestPhrase;
	APG_CBDATA sData;
	char* cpaTests[] = {
			"a-.a1-1a--0z.z",
			"A",
			"a",
			"a.z",
			"a.a1-1a--0z",
			"a.a1-1a--0z.z",
			"a--z.a1-1a--0z.z",
			"a.-a1-1a--0z.z",
			"-a.a1-1a--0z.z",
			"a.a1-1a--0z-.z",
			"a.z.",
			"Z"
	};
	apg_uint uiTestCount = sizeof(cpaTests)/sizeof(char*);

	// tests
	printf("\n");
	printf("uiTestRFC1035Domain: \n");
	for(i = 0; i < uiTestCount; i++){
		char cSave;
		cpTestPhrase = cpaTests[i];
		uiTestLength = strlen(cpTestPhrase);
		vCharToAChar(acpPhrase, cpTestPhrase, uiTestLength);
		acpPhrase[uiTestLength] = (apg_achar)0;
		sData.acpSrc = acpPhrase;
		sData.uiSrcLen = uiTestLength;
		sData.uiPhraseOffset = 0;
		uiPhraseLength = uiSIP_u_rfc1035domain(&sData);
		uiPhraseLength = sData.uiPhraseLength;
		printf("\n");
		printf("uiTestRFC1035Domain:  phrase[%2u]: \"%s\"\n", (apg_uint)i, acpPhrase);
		if(uiPhraseLength == APG_UNDEFINED){
			printf(  "uiTestRFC1035Domain:    FAILED\n");
		} else{
			cSave = acpPhrase[uiPhraseLength];
			acpPhrase[uiPhraseLength] = 0;
			printf(  "uiTestRFC1035Domain:    scheme: \"%s\"\n", &acpPhrase[0]);
			acpPhrase[uiPhraseLength] = cSave;
		}
	}
	return uiRet;
}

apg_uint uiTestLws(){
	apg_uint uiRet = APG_TRUE;
	apg_achar* acpPhrase = &g_acaBuffer[0];
	apg_uint uiTestLength;
	apg_uint i;
	apg_uint uiPhraseLength;
	char* cpTestPhrase;
	APG_CBDATA sData;
	char* cpaTests[] = {
			" \r\na",
			"  \r\n",
			" \r\n ",
			"\r\na",
			" ",
			"   ",
			"\t  \t  \t",
			"\r\n ",
			"\r\n\t",
			"\r\n",
			"Z"
	};
	apg_uint uiTestCount = sizeof(cpaTests)/sizeof(char*);

	// tests
	printf("\n");
	printf("uiTestLws: \n");
	for(i = 0; i < uiTestCount; i++){
		char cSave;
		cpTestPhrase = cpaTests[i];
		uiTestLength = strlen(cpTestPhrase);
		vCharToAChar(acpPhrase, cpTestPhrase, uiTestLength);
		acpPhrase[uiTestLength] = (apg_achar)0;
		sData.acpSrc = acpPhrase;
		sData.uiSrcLen = uiTestLength;
		sData.uiPhraseOffset = 0;
		uiSIP_u_LWS(&sData);
		uiPhraseLength = sData.uiPhraseLength;
		printf("\n");
		printf("uiTestLws:  phrase[%2u]: ", (apg_uint)i);
		vPrintPhrase(acpPhrase, uiTestLength);
		if(uiPhraseLength == APG_UNDEFINED){
			printf(  "uiTestLws:    FAILED\n");
		} else{
			cSave = acpPhrase[uiPhraseLength];
			acpPhrase[uiPhraseLength] = 0;
			printf(  "uiTestLws:    scheme: ");
			vPrintPhrase(acpPhrase, uiPhraseLength);
			acpPhrase[uiPhraseLength] = cSave;
		}
	}
	return uiRet;
}

apg_uint uiTestHLetter(){
	apg_uint uiRet = APG_TRUE;
	apg_achar* acpPhrase = &g_acaBuffer[0];
	char* cpTestName = "uiTestHLetter";
	APG_CALLBACK pfnTest = uiSIP_u_Comma;
	apg_uint uiTestLength;
	apg_uint i;
	apg_uint uiPhraseLength;
	char* cpTestPhrase;
	APG_CBDATA sData;
	char* cpaTests[] = {
			",",
			" , ",
			"\t,\t",
			"\r\n ,",
			",\r\n ",
			"\r\n ,\r\n ",
			"\r\n\t,",
			",\r\n\t",
			"\r\n\t,\r\n\t",
			"\r\n,",
			",\r\n",
			","
	};
	apg_uint uiTestCount = sizeof(cpaTests)/sizeof(char*);

	// tests
	printf("\n");
	printf("%s: \n", cpTestName);
	for(i = 0; i < uiTestCount; i++){
		char cSave;
		cpTestPhrase = cpaTests[i];
		uiTestLength = strlen(cpTestPhrase);
		vCharToAChar(acpPhrase, cpTestPhrase, uiTestLength);
		acpPhrase[uiTestLength] = (apg_achar)0;
		sData.acpSrc = acpPhrase;
		sData.uiSrcLen = uiTestLength;
		sData.uiPhraseOffset = 0;
		pfnTest(&sData);
		uiPhraseLength = sData.uiPhraseLength;
		printf("\n");
		printf("%s:  phrase[%2u]: ", cpTestName, (apg_uint)i);
		vPrintPhrase(acpPhrase, uiTestLength);
		if(uiPhraseLength == APG_UNDEFINED){
			printf(  "%s:    FAILED\n", cpTestName);
		} else{
			cSave = acpPhrase[uiPhraseLength];
			acpPhrase[uiPhraseLength] = 0;
			printf(  "%s:    scheme: ", cpTestName);
			vPrintPhrase(acpPhrase, uiPhraseLength);
			acpPhrase[uiPhraseLength] = cSave;
		}
	}
	return uiRet;
}
apg_uint uiTestLeftRightLetter(){
	apg_uint uiRet = APG_TRUE;
	apg_achar* acpPhrase = &g_acaBuffer[0];
	char* cpTestName = "uiSIP_u_LDQuot";
	APG_CALLBACK pfnTest = uiSIP_u_LDQuot;
	apg_uint uiTestLength;
	apg_uint i;
	apg_uint uiPhraseLength;
	char* cpTestPhrase;
	APG_CBDATA sData;
	char* cpaTests[] = {
			"\"",
			" \"",
			"\t\"",
			"\r\n \"",
			"\" ",
			"\"\r\n ",
			"\""
	};
	apg_uint uiTestCount = sizeof(cpaTests)/sizeof(char*);

	// tests
	printf("\n");
	printf("%s: \n", cpTestName);
	for(i = 0; i < uiTestCount; i++){
		char cSave;
		cpTestPhrase = cpaTests[i];
		uiTestLength = strlen(cpTestPhrase);
		vCharToAChar(acpPhrase, cpTestPhrase, uiTestLength);
		acpPhrase[uiTestLength] = (apg_achar)0;
		sData.acpSrc = acpPhrase;
		sData.uiSrcLen = uiTestLength;
		sData.uiPhraseOffset = 0;
		pfnTest(&sData);
		uiPhraseLength = sData.uiPhraseLength;
		printf("\n");
		printf("%s:  phrase[%2u]: ", cpTestName, (apg_uint)i);
		vPrintPhrase(acpPhrase, uiTestLength);
		if(uiPhraseLength == APG_UNDEFINED){
			printf(  "%s:    FAILED\n", cpTestName);
		} else{
			cSave = acpPhrase[uiPhraseLength];
			acpPhrase[uiPhraseLength] = 0;
			printf(  "%s:    scheme: ", cpTestName);
			vPrintPhrase(acpPhrase, uiPhraseLength);
			acpPhrase[uiPhraseLength] = cSave;
		}
	}
	return uiRet;
}
apg_uint uiTestHColon(){
	apg_uint uiRet = APG_TRUE;
	apg_achar* acpPhrase = &g_acaBuffer[0];
	char* cpTestName = "uiTestHColon";
	APG_CALLBACK pfnTest = uiSIP_u_HColon;
	apg_uint uiTestLength;
	apg_uint i;
	apg_uint uiPhraseLength;
	char* cpTestPhrase;
	APG_CBDATA sData;
	char* cpaTests[] = {
			":",
			" : ",
			"\t:\t",
			"\r\n :",
			":\r\n ",
			"\r\n :\r\n ",
			"\r\n\t:",
			":\r\n\t",
			"\r\n\t:\r\n\t",
			"\r\n:",
			":\r\n",
			":"
	};
	apg_uint uiTestCount = sizeof(cpaTests)/sizeof(char*);

	// tests
	printf("\n");
	printf("%s: \n", cpTestName);
	for(i = 0; i < uiTestCount; i++){
		char cSave;
		cpTestPhrase = cpaTests[i];
		uiTestLength = strlen(cpTestPhrase);
		vCharToAChar(acpPhrase, cpTestPhrase, uiTestLength);
		acpPhrase[uiTestLength] = (apg_achar)0;
		sData.acpSrc = acpPhrase;
		sData.uiSrcLen = uiTestLength;
		sData.uiPhraseOffset = 0;
		pfnTest(&sData);
		uiPhraseLength = sData.uiPhraseLength;
		printf("\n");
		printf("%s:  phrase[%2u]: ", cpTestName, (apg_uint)i);
		vPrintPhrase(acpPhrase, uiTestLength);
		if(uiPhraseLength == APG_UNDEFINED){
			printf(  "%s:    FAILED\n", cpTestName);
		} else{
			cSave = acpPhrase[uiPhraseLength];
			acpPhrase[uiPhraseLength] = 0;
			printf(  "%s:    scheme: ", cpTestName);
			vPrintPhrase(acpPhrase, uiPhraseLength);
			acpPhrase[uiPhraseLength] = cSave;
		}
	}
	return uiRet;
}

apg_uint uiTestLHEX(){
	apg_uint uiRet = APG_TRUE;
	apg_achar* acpPhrase = &g_acaBuffer[0];
	char* cpTestName = "uiTestLHEX";
	APG_CALLBACK pfnTest = uiSIP_u_LHEX;
	apg_uint uiTestLength;
	apg_uint i;
	apg_uint uiPhraseLength;
	char* cpTestPhrase;
	APG_CBDATA sData;
	char* cpaTests[] = {
			"1",
			"0",
			"9",
			"a",
			"f",
			"z",
			"A",
			"F"
	};
	apg_uint uiTestCount = sizeof(cpaTests)/sizeof(char*);

	// tests
	printf("\n");
	printf("%s: \n", cpTestName);
	for(i = 0; i < uiTestCount; i++){
		char cSave;
		cpTestPhrase = cpaTests[i];
		uiTestLength = strlen(cpTestPhrase);
		vCharToAChar(acpPhrase, cpTestPhrase, uiTestLength);
		acpPhrase[uiTestLength] = (apg_achar)0;
		sData.acpSrc = acpPhrase;
		sData.uiSrcLen = uiTestLength;
		sData.uiPhraseOffset = 0;
		pfnTest(&sData);
		uiPhraseLength = sData.uiPhraseLength;
		printf("\n");
		printf("%s:  phrase[%2u]: ", cpTestName, (apg_uint)i);
		vPrintPhrase(acpPhrase, uiTestLength);
		if(uiPhraseLength == APG_UNDEFINED){
			printf(  "%s:    FAILED\n", cpTestName);
		} else{
			cSave = acpPhrase[uiPhraseLength];
			acpPhrase[uiPhraseLength] = 0;
			printf(  "%s:    scheme: ", cpTestName);
			vPrintPhrase(acpPhrase, uiPhraseLength);
			acpPhrase[uiPhraseLength] = cSave;
		}
	}
	return uiRet;
}

apg_uint uiTestNcValue(){
	apg_uint uiRet = APG_TRUE;
	apg_achar* acpPhrase = &g_acaBuffer[0];
	char* cpTestName = "uiTestNcValue";
	APG_CALLBACK pfnTest = uiSIP_u_nc_value;
	apg_uint uiTestLength;
	apg_uint i;
	apg_uint uiPhraseLength;
	char* cpTestPhrase;
	APG_CBDATA sData;
	char* cpaTests[] = {
			"01234567",
			"0123abcd",
			"abcdefef",
			"abcdEFEF",
			"abcd",
			"1234",
			"f"
	};
	apg_uint uiTestCount = sizeof(cpaTests)/sizeof(char*);

	// tests
	printf("\n");
	printf("%s: \n", cpTestName);
	for(i = 0; i < uiTestCount; i++){
		char cSave;
		cpTestPhrase = cpaTests[i];
		uiTestLength = strlen(cpTestPhrase);
		vCharToAChar(acpPhrase, cpTestPhrase, uiTestLength);
		acpPhrase[uiTestLength] = (apg_achar)0;
		sData.acpSrc = acpPhrase;
		sData.uiSrcLen = uiTestLength;
		sData.uiPhraseOffset = 0;
		pfnTest(&sData);
		uiPhraseLength = sData.uiPhraseLength;
		printf("\n");
		printf("%s:  phrase[%2u]: ", cpTestName, (apg_uint)i);
		vPrintPhrase(acpPhrase, uiTestLength);
		if(uiPhraseLength == APG_UNDEFINED){
			printf(  "%s:    FAILED\n", cpTestName);
		} else{
			cSave = acpPhrase[uiPhraseLength];
			acpPhrase[uiPhraseLength] = 0;
			printf(  "%s:    scheme: ", cpTestName);
			vPrintPhrase(acpPhrase, uiPhraseLength);
			acpPhrase[uiPhraseLength] = cSave;
		}
	}
	return uiRet;
}

apg_uint uiTestRequestDigest(){
	apg_uint uiRet = APG_TRUE;
	apg_achar* acpPhrase = &g_acaBuffer[0];
	char* cpTestName = "uiTestRequestDigest";
	APG_CALLBACK pfnTest = uiSIP_u_request_digest;
	apg_uint uiTestLength;
	apg_uint i;
	apg_uint uiPhraseLength;
	char* cpTestPhrase;
	APG_CBDATA sData;
	char* cpaTests[] = {
			"\"01234567abcdefef01234567abcdefef\"",
			"  \"01234567abcdefef01234567abcdefef\"  ",
			"  \r\n \"01234567abcdefef01234567abcdefef\"  \r\n ",
			"\r\n\"01234567abcdefef01234567abcdefef\"",
			"\"1234567abcdefef01234567abcdefef\"",
			"\"01234567abcdefef01234567abcdefef1\"",
			"f"
	};
	apg_uint uiTestCount = sizeof(cpaTests)/sizeof(char*);

	// tests
	printf("\n");
	printf("%s: \n", cpTestName);
	for(i = 0; i < uiTestCount; i++){
		char cSave;
		cpTestPhrase = cpaTests[i];
		uiTestLength = strlen(cpTestPhrase);
		vCharToAChar(acpPhrase, cpTestPhrase, uiTestLength);
		acpPhrase[uiTestLength] = (apg_achar)0;
		sData.acpSrc = acpPhrase;
		sData.uiSrcLen = uiTestLength;
		sData.uiPhraseOffset = 0;
		pfnTest(&sData);
		uiPhraseLength = sData.uiPhraseLength;
		printf("\n");
		printf("%s:  phrase[%2u]: ", cpTestName, (apg_uint)i);
		vPrintPhrase(acpPhrase, uiTestLength);
		if(uiPhraseLength == APG_UNDEFINED){
			printf(  "%s:    FAILED\n", cpTestName);
		} else{
			cSave = acpPhrase[uiPhraseLength];
			acpPhrase[uiPhraseLength] = 0;
			printf(  "%s:    scheme: ", cpTestName);
			vPrintPhrase(acpPhrase, uiPhraseLength);
			acpPhrase[uiPhraseLength] = cSave;
		}
	}
	return uiRet;
}

apg_uint uiTestMessageBody(){
	apg_uint uiRet = APG_TRUE;
	apg_achar* acpPhrase = &g_acaBuffer[0];
	char* cpTestName = "uiTestMessageBody";
	APG_CALLBACK pfnTest = uiSIP_e_MessageBody;
	apg_uint uiTestLength;
	apg_uint i;
	apg_uint uiPhraseLength;
	char* cpTestPhrase;
	APG_CBDATA sData;
	char* cpaTests[] = {
			"0123456789\x00\xFF",
			"\x02\x01\r\nabcdefef",
			"\x02\x01",
			"",
			"\xef"
	};
	apg_uint uiTestCount = sizeof(cpaTests)/sizeof(char*);

	// tests
	printf("\n");
	printf("%s: \n", cpTestName);
	for(i = 0; i < uiTestCount; i++){
		char cSave;
		cpTestPhrase = cpaTests[i];
		uiTestLength = strlen(cpTestPhrase);
		vCharToAChar(acpPhrase, cpTestPhrase, uiTestLength);
		acpPhrase[uiTestLength] = (apg_achar)0;
		sData.acpSrc = acpPhrase;
		sData.uiSrcLen = uiTestLength;
		sData.uiPhraseOffset = 0;
		pfnTest(&sData);
		uiPhraseLength = sData.uiPhraseLength;
		printf("\n");
		printf("%s:  phrase[%2u]: ", cpTestName, (apg_uint)i);
		vPrintPhrase(acpPhrase, uiTestLength);
		if(uiPhraseLength == APG_UNDEFINED){
			printf(  "%s:    FAILED\n", cpTestName);
		} else{
			cSave = acpPhrase[uiPhraseLength];
			acpPhrase[uiPhraseLength] = 0;
			printf(  "%s:    scheme: ", cpTestName);
			vPrintPhrase(acpPhrase, uiPhraseLength);
			acpPhrase[uiPhraseLength] = cSave;
		}
	}
	return uiRet;
}
