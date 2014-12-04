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
#ifndef MEGACO_H
#define MEGACO_H
using namespace std;

/*********************************************************
 * NOTE: DO NOT MODIFY THE CONTENTS OF THIS FILE       ***
 *       CHANGES WILL BE LOST ON REGENERATION          ***
 ********************************************************/
class MEGACO{
	private:
	PFN_ALERT m_pfnAlertHandler;

	public:
	static void* m_vpParserInit;
	enum{
        RULEID_ACTIONREPLY = 27, // actionReply
        RULEID_ACTIONREPLYLIST = 26, // actionReplyList
        RULEID_ACTIONREQUEST = 14, // actionRequest
        RULEID_ADDTOKEN = 241, // AddToken
        RULEID_ALPHA = 227, // ALPHA
        RULEID_ALTERNATIVEVALUE = 80, // alternativeValue
        RULEID_AMMPARAMETER = 32, // ammParameter
        RULEID_AMMREQUEST = 31, // ammRequest
        RULEID_AMMSREPLY = 33, // ammsReply
        RULEID_ANDAUDITSELECTTOKEN = 242, // AndAUDITSelectToken
        RULEID_AUDITCAPTOKEN = 244, // AuditCapToken
        RULEID_AUDITDESCRIPTOR = 42, // auditDescriptor
        RULEID_AUDITITEM = 154, // auditItem
        RULEID_AUDITOTHER = 37, // auditOther
        RULEID_AUDITREPLY = 36, // auditReply
        RULEID_AUDITREQUEST = 35, // auditRequest
        RULEID_AUDITRETURNITEM = 41, // auditReturnItem
        RULEID_AUDITRETURNPARAMETER = 40, // auditReturnParameter
        RULEID_AUDITSELECTLOGIC = 21, // auditSelectLogic
        RULEID_AUDITTOKEN = 243, // AuditToken
        RULEID_AUDITVALUETOKEN = 245, // AuditValueToken
        RULEID_AUTHDATA = 4, // AuthData
        RULEID_AUTHENTICATIONHEADER = 1, // authenticationHeader
        RULEID_AUTHTOKEN = 246, // AuthToken
        RULEID_BOTHTOKEN = 247, // BothToken
        RULEID_BOTHWAYTOKEN = 248, // BothwayToken
        RULEID_BRIEFTOKEN = 249, // BriefToken
        RULEID_BUFFERTOKEN = 250, // BufferToken
        RULEID_COLON = 221, // COLON
        RULEID_COMMA = 224, // COMMA
        RULEID_COMMANDREPLY = 28, // commandReply
        RULEID_COMMANDREPLYLIST = 29, // commandReplyList
        RULEID_COMMANDREPLYS = 30, // commandReplys
        RULEID_COMMANDREQUEST = 24, // commandRequest
        RULEID_COMMANDREQUESTLIST = 23, // commandRequestList
        RULEID_COMMENT = 239, // COMMENT
        RULEID_CONTEXTATTRDESCRIPTOR = 209, // contextAttrDescriptor
        RULEID_CONTEXTATTRTOKEN = 253, // ContextAttrToken
        RULEID_CONTEXTAUDIT = 18, // contextAudit
        RULEID_CONTEXTAUDITPROPERTIES = 19, // contextAuditProperties
        RULEID_CONTEXTAUDITSELECTOR = 20, // contextAuditSelector
        RULEID_CONTEXTAUDITTOKEN = 252, // ContextAuditToken
        RULEID_CONTEXTID = 53, // ContextID
        RULEID_CONTEXTIDLIST = 210, // contextIdList
        RULEID_CONTEXTLISTTOKEN = 254, // ContextListToken
        RULEID_CONTEXTPROPERTIES = 16, // contextProperties
        RULEID_CONTEXTPROPERTY = 17, // contextProperty
        RULEID_CONTEXTREQUEST = 15, // contextRequest
        RULEID_CONTEXTTERMINATIONAUDIT = 39, // contextTerminationAudit
        RULEID_CR = 233, // CR
        RULEID_CTXTOKEN = 251, // CtxToken
        RULEID_DATE = 197, // Date
        RULEID_DELAYTOKEN = 258, // DelayToken
        RULEID_DEVICENAME = 52, // deviceName
        RULEID_DIGIT = 228, // DIGIT
        RULEID_DIGITLETTER = 152, // digitLetter
        RULEID_DIGITMAP = 146, // digitMap
        RULEID_DIGITMAPDESCRIPTOR = 142, // digitMapDescriptor
        RULEID_DIGITMAPLETTER = 153, // digitMapLetter
        RULEID_DIGITMAPNAME = 143, // digitMapName
        RULEID_DIGITMAPRANGE = 151, // digitMapRange
        RULEID_DIGITMAPTOKEN = 255, // DigitMapToken
        RULEID_DIGITMAPVALUE = 144, // digitMapValue
        RULEID_DIGITPOSITION = 150, // digitPosition
        RULEID_DIGITSTRING = 148, // digitString
        RULEID_DIGITSTRINGELEMENT = 149, // digitStringElement
        RULEID_DIGITSTRINGLIST = 147, // digitStringList
        RULEID_DIRECTION = 131, // direction
        RULEID_DIRECTIONTOKEN = 256, // DirectionToken
        RULEID_DISCONNECTEDTOKEN = 257, // DisconnectedToken
        RULEID_DOMAINADDRESS = 54, // domainAddress
        RULEID_DOMAINNAME = 51, // domainName
        RULEID_DOT = 225, // DOT
        RULEID_DQUOTE = 229, // DQUOTE
        RULEID_DURATIONTOKEN = 259, // DurationToken
        RULEID_EMBEDFIRST = 108, // embedFirst
        RULEID_EMBEDNOSIG = 107, // embedNoSig
        RULEID_EMBEDSIG = 111, // embedSig
        RULEID_EMBEDTOKEN = 260, // EmbedToken
        RULEID_EMBEDWITHSIG = 106, // embedWithSig
        RULEID_EMERGENCYOFFTOKEN = 262, // EmergencyOffToken
        RULEID_EMERGENCYTOKEN = 261, // EmergencyToken
        RULEID_EMERGENCYVALUE = 208, // emergencyValue
        RULEID_EMERGENCYVALUETOKEN = 263, // EmergencyValueToken
        RULEID_EOL = 236, // EOL
        RULEID_EQUAL = 220, // EQUAL
        RULEID_ERRORCODE = 48, // ErrorCode
        RULEID_ERRORDESCRIPTOR = 47, // errorDescriptor
        RULEID_ERRORTOKEN = 264, // ErrorToken
        RULEID_EVENTBUFFERCONTROL = 89, // eventBufferControl
        RULEID_EVENTBUFFERCONTROLVALUE = 90, // eventBufferControlValue
        RULEID_EVENTBUFFERDESCRIPTOR = 86, // eventBufferDescriptor
        RULEID_EVENTBUFFERTOKEN = 265, // EventBufferToken
        RULEID_EVENTDM = 115, // eventDM
        RULEID_EVENTOTHER = 113, // eventOther
        RULEID_EVENTPARAMETER = 105, // eventParameter
        RULEID_EVENTPARAMETERNAME = 114, // eventParameterName
        RULEID_EVENTSDESCRIPTOR = 101, // eventsDescriptor
        RULEID_EVENTSPEC = 87, // eventSpec
        RULEID_EVENTSPECPARAMETER = 88, // eventSpecParameter
        RULEID_EVENTSTOKEN = 266, // EventsToken
        RULEID_EVENTSTREAM = 112, // eventStream
        RULEID_EXTENSION = 192, // extension
        RULEID_EXTENSIONPARAMETER = 211, // extensionParameter
        RULEID_EXTERNALTOKEN = 267, // ExternalToken
        RULEID_FAILOVERTOKEN = 268, // FailoverToken
        RULEID_FORCEDTOKEN = 269, // ForcedToken
        RULEID_GRACEFULTOKEN = 270, // GracefulToken
        RULEID_H221TOKEN = 271, // H221Token
        RULEID_H223TOKEN = 272, // H223Token
        RULEID_H226TOKEN = 273, // H226Token
        RULEID_HANDOFFTOKEN = 274, // HandOffToken
        RULEID_HEX4 = 60, // hex4
        RULEID_HEXDIG = 230, // HEXDIG
        RULEID_HEXPART = 58, // hexpart
        RULEID_HEXSEQ = 59, // hexseq
        RULEID_HTAB = 232, // HTAB
        RULEID_IEPSTOKEN = 275, // IEPSToken
        RULEID_IEPSVALUE = 207, // iepsValue
        RULEID_IMMACKREQUIREDTOKEN = 276, // ImmAckRequiredToken
        RULEID_INACTIVETOKEN = 277, // InactiveToken
        RULEID_INDAUDAUDITRETURNPARAMETER = 156, // indAudauditReturnParameter
        RULEID_INDAUDCONTEXTATTRDESCRIPTOR = 22, // indAudcontextAttrDescriptor
        RULEID_INDAUDDIGITMAPDESCRIPTOR = 178, // indAuddigitMapDescriptor
        RULEID_INDAUDEVENTBUFFERDESCRIPTOR = 167, // indAudeventBufferDescriptor
        RULEID_INDAUDEVENTSDESCRIPTOR = 170, // indAudeventsDescriptor
        RULEID_INDAUDEVENTSPEC = 168, // indAudeventSpec
        RULEID_INDAUDEVENTSPECPARAMETER = 169, // indAudeventSpecParameter
        RULEID_INDAUDLOCALCONTROLDESCRIPTOR = 163, // indAudlocalControlDescriptor
        RULEID_INDAUDLOCALDESCRIPTOR = 161, // indAudlocalDescriptor
        RULEID_INDAUDLOCALPARM = 164, // indAudlocalParm
        RULEID_INDAUDMEDIADESCRIPTOR = 157, // indAudmediaDescriptor
        RULEID_INDAUDMEDIAPARM = 158, // indAudmediaParm
        RULEID_INDAUDPACKAGESDESCRIPTOR = 180, // indAudpackagesDescriptor
        RULEID_INDAUDREMOTEDESCRIPTOR = 160, // indAudremoteDescriptor
        RULEID_INDAUDREQUESTEDEVENT = 171, // indAudrequestedEvent
        RULEID_INDAUDSIGNALLIST = 176, // indAudsignalList
        RULEID_INDAUDSIGNALLISTPARM = 177, // indAudsignalListParm
        RULEID_INDAUDSIGNALPARM = 173, // indAudsignalParm
        RULEID_INDAUDSIGNALREQUEST = 174, // indAudsignalRequest
        RULEID_INDAUDSIGNALREQUESTPARM = 175, // indAudsignalRequestParm
        RULEID_INDAUDSIGNALSDESCRIPTOR = 172, // indAudsignalsDescriptor
        RULEID_INDAUDSTATISTICSDESCRIPTOR = 179, // indAudstatisticsDescriptor
        RULEID_INDAUDSTREAMDESCRIPTOR = 162, // indAudstreamDescriptor
        RULEID_INDAUDSTREAMPARM = 159, // indAudstreamParm
        RULEID_INDAUDTERMINATIONAUDIT = 155, // indAudterminationAudit
        RULEID_INDAUDTERMINATIONSTATEDESCRIPTOR = 165, // indAudterminationStateDescriptor
        RULEID_INDAUDTERMINATIONSTATEPARM = 166, // indAudterminationStateParm
        RULEID_INEQUAL = 81, // INEQUAL
        RULEID_INSVCTOKEN = 281, // InSvcToken
        RULEID_INTERNALTOKEN = 278, // InternalToken
        RULEID_INTERRUPTBYEVENTTOKEN = 282, // InterruptByEventToken
        RULEID_INTERRUPTBYNEWSIGNALSDESCRTOKEN = 283, // InterruptByNewSignalsDescrToken
        RULEID_INTSIGDELAYTOKEN = 279, // IntsigDelayToken
        RULEID_IPV4ADDRESS = 56, // IPv4address
        RULEID_IPV6ADDRESS = 55, // IPv6address
        RULEID_ISOLATETOKEN = 280, // IsolateToken
        RULEID_ITEMID = 100, // ItemID
        RULEID_ITERATIONTOKEN = 284, // IterationToken
        RULEID_KEEPACTIVETOKEN = 285, // KeepActiveToken
        RULEID_LBRKT = 222, // LBRKT
        RULEID_LF = 234, // LF
        RULEID_LOCALCONTROLDESCRIPTOR = 72, // localControlDescriptor
        RULEID_LOCALCONTROLTOKEN = 287, // LocalControlToken
        RULEID_LOCALDESCRIPTOR = 84, // localDescriptor
        RULEID_LOCALPARM = 73, // localParm
        RULEID_LOCALTOKEN = 286, // LocalToken
        RULEID_LOCKSTEPTOKEN = 288, // LockStepToken
        RULEID_LOOPBACKTOKEN = 289, // LoopbackToken
        RULEID_LSBRKT = 82, // LSBRKT
        RULEID_LWSP = 235, // LWSP
        RULEID_MEDIADESCRIPTOR = 68, // mediaDescriptor
        RULEID_MEDIAPARM = 69, // mediaParm
        RULEID_MEDIATOKEN = 290, // MediaToken
        RULEID_MEGACOMESSAGE = 0, // megacoMessage
        RULEID_MEGACOPTOKEN = 291, // MegacopToken
        RULEID_MESSAGE = 5, // Message
        RULEID_MESSAGEBODY = 6, // messageBody
        RULEID_MESSAGESEGMENTTOKEN = 292, // MessageSegmentToken
        RULEID_METHODTOKEN = 293, // MethodToken
        RULEID_MGCIDTOKEN = 294, // MgcIdToken
        RULEID_MID = 50, // mId
        RULEID_MODEMDESCRIPTOR = 140, // modemDescriptor
        RULEID_MODEMTOKEN = 297, // ModemToken
        RULEID_MODEMTYPE = 141, // modemType
        RULEID_MODETOKEN = 295, // ModeToken
        RULEID_MODIFYTOKEN = 296, // ModifyToken
        RULEID_MOVETOKEN = 298, // MoveToken
        RULEID_MTPADDRESS = 62, // mtpAddress
        RULEID_MTPTOKEN = 299, // MTPToken
        RULEID_MUXDESCRIPTOR = 95, // muxDescriptor
        RULEID_MUXTOKEN = 300, // MuxToken
        RULEID_MUXTYPE = 96, // MuxType
        RULEID_NAME = 217, // NAME
        RULEID_NEVERNOTIFYTOKEN = 301, // NeverNotifyToken
        RULEID_NONESCAPECHAR = 213, // nonEscapeChar
        RULEID_NOTIFICATIONREASON = 135, // notificationReason
        RULEID_NOTIFYBEHAVIOUR = 104, // notifyBehaviour
        RULEID_NOTIFYCOMPLETION = 134, // notifyCompletion
        RULEID_NOTIFYCOMPLETIONTOKEN = 303, // NotifyCompletionToken
        RULEID_NOTIFYIMMEDIATETOKEN = 304, // NotifyImmediateToken
        RULEID_NOTIFYREGULATED = 103, // notifyRegulated
        RULEID_NOTIFYREGULATEDTOKEN = 305, // NotifyRegulatedToken
        RULEID_NOTIFYREPLY = 44, // notifyReply
        RULEID_NOTIFYREQUEST = 43, // notifyRequest
        RULEID_NOTIFYTOKEN = 302, // NotifyToken
        RULEID_NX64KTOKEN = 306, // Nx64kToken
        RULEID_OBSERVEDEVENT = 137, // observedEvent
        RULEID_OBSERVEDEVENTPARAMETER = 138, // observedEventParameter
        RULEID_OBSERVEDEVENTSDESCRIPTOR = 136, // observedEventsDescriptor
        RULEID_OBSERVEDEVENTSTOKEN = 307, // ObservedEventsToken
        RULEID_OCTETSTRING = 212, // octetString
        RULEID_ONEWAYBOTHTOKEN = 309, // OnewayBothToken
        RULEID_ONEWAYEXTERNALTOKEN = 310, // OnewayExternalToken
        RULEID_ONEWAYTOKEN = 308, // OnewayToken
        RULEID_ONOFFTOKEN = 311, // OnOffToken
        RULEID_ORAUDITSELECTTOKEN = 312, // OrAUDITselectToken
        RULEID_OTHERREASONTOKEN = 313, // OtherReasonToken
        RULEID_OUTOFSVCTOKEN = 314, // OutOfSvcToken
        RULEID_PACKAGENAME = 99, // PackageName
        RULEID_PACKAGESDESCRIPTOR = 193, // packagesDescriptor
        RULEID_PACKAGESITEM = 195, // packagesItem
        RULEID_PACKAGESTOKEN = 315, // PackagesToken
        RULEID_PARMVALUE = 79, // parmValue
        RULEID_PATHDOMAINNAME = 66, // pathDomainName
        RULEID_PATHNAME = 65, // pathNAME
        RULEID_PENDINGTOKEN = 316, // PendingToken
        RULEID_PKGDNAME = 98, // pkgdName
        RULEID_PORTNUMBER = 61, // portNumber
        RULEID_PRIORITY = 206, // priority
        RULEID_PRIORITYTOKEN = 317, // PriorityToken
        RULEID_PROFILETOKEN = 318, // ProfileToken
        RULEID_PROPERTYPARM = 78, // propertyParm
        RULEID_QUOTEDSTRING = 214, // quotedString
        RULEID_RBRKT = 223, // RBRKT
        RULEID_REASONTOKEN = 319, // ReasonToken
        RULEID_RECVONLYTOKEN = 320, // RecvonlyToken
        RULEID_REMOTEDESCRIPTOR = 85, // remoteDescriptor
        RULEID_REMOTETOKEN = 324, // RemoteToken
        RULEID_REPLYTOKEN = 321, // ReplyToken
        RULEID_REQUESTEDEVENT = 102, // requestedEvent
        RULEID_REQUESTID = 139, // RequestID
        RULEID_REQUESTIDTOKEN = 325, // RequestIDToken
        RULEID_RESERVEDGROUPMODE = 75, // reservedGroupMode
        RULEID_RESERVEDGROUPTOKEN = 326, // ReservedGroupToken
        RULEID_RESERVEDVALUEMODE = 74, // reservedValueMode
        RULEID_RESERVEDVALUETOKEN = 327, // ReservedValueToken
        RULEID_RESETEVENTSDESCRIPTORTOKEN = 322, // ResetEventsDescriptorToken
        RULEID_RESPONSEACKTOKEN = 348, // ResponseAckToken
        RULEID_RESTARTTOKEN = 323, // RestartToken
        RULEID_RESTCHAR = 240, // RestChar
        RULEID_RSBRKT = 83, // RSBRKT
        RULEID_SAFECHAR = 219, // SafeChar
        RULEID_SECONDEVENTPARAMETER = 110, // secondEventParameter
        RULEID_SECONDREQUESTEDEVENT = 109, // secondRequestedEvent
        RULEID_SECURITYPARMINDEX = 2, // SecurityParmIndex
        RULEID_SEGMENTATIONCOMPLETETOKEN = 328, // SegmentationCompleteToken
        RULEID_SEGMENTNUMBER = 25, // segmentNumber
        RULEID_SEGMENTREPLY = 12, // segmentReply
        RULEID_SENDONLYTOKEN = 329, // SendonlyToken
        RULEID_SENDRECVTOKEN = 330, // SendrecvToken
        RULEID_SEP = 238, // SEP
        RULEID_SEQUENCENUM = 3, // SequenceNum
        RULEID_SERVCHGREPLYPARM = 184, // servChgReplyParm
        RULEID_SERVICECHANGEADDRESS = 188, // serviceChangeAddress
        RULEID_SERVICECHANGEADDRESSTOKEN = 335, // ServiceChangeAddressToken
        RULEID_SERVICECHANGEDELAY = 187, // serviceChangeDelay
        RULEID_SERVICECHANGEDESCRIPTOR = 181, // serviceChangeDescriptor
        RULEID_SERVICECHANGEINCOMPLETETOKEN = 333, // ServiceChangeIncompleteToken
        RULEID_SERVICECHANGEMETHOD = 185, // serviceChangeMethod
        RULEID_SERVICECHANGEMGCID = 189, // serviceChangeMgcId
        RULEID_SERVICECHANGEPARM = 182, // serviceChangeParm
        RULEID_SERVICECHANGEPROFILE = 190, // serviceChangeProfile
        RULEID_SERVICECHANGEREASON = 186, // serviceChangeReason
        RULEID_SERVICECHANGEREPLY = 46, // serviceChangeReply
        RULEID_SERVICECHANGEREPLYDESCRIPTOR = 183, // serviceChangeReplyDescriptor
        RULEID_SERVICECHANGEREQUEST = 45, // serviceChangeRequest
        RULEID_SERVICECHANGETOKEN = 334, // ServiceChangeToken
        RULEID_SERVICECHANGEVERSION = 191, // serviceChangeVersion
        RULEID_SERVICESTATES = 93, // serviceStates
        RULEID_SERVICESTATESTOKEN = 332, // ServiceStatesToken
        RULEID_SERVICESTATESVALUE = 94, // serviceStatesValue
        RULEID_SERVICESTOKEN = 331, // ServicesToken
        RULEID_SIGDIRECTION = 130, // sigDirection
        RULEID_SIGDURATION = 129, // sigDuration
        RULEID_SIGINTSIGDELAY = 133, // sigIntsigDelay
        RULEID_SIGNALLIST = 119, // signalList
        RULEID_SIGNALLISTID = 120, // signalListId
        RULEID_SIGNALLISTPARM = 121, // signalListParm
        RULEID_SIGNALLISTTOKEN = 336, // SignalListToken
        RULEID_SIGNALNAME = 122, // signalName
        RULEID_SIGNALPARM = 117, // signalParm
        RULEID_SIGNALREQUEST = 118, // signalRequest
        RULEID_SIGNALSDESCRIPTOR = 116, // signalsDescriptor
        RULEID_SIGNALSTOKEN = 337, // SignalsToken
        RULEID_SIGNALTYPE = 128, // signalType
        RULEID_SIGNALTYPETOKEN = 338, // SignalTypeToken
        RULEID_SIGOTHER = 125, // sigOther
        RULEID_SIGPARAMETER = 123, // sigParameter
        RULEID_SIGPARAMETERNAME = 126, // sigParameterName
        RULEID_SIGREQUESTID = 132, // sigRequestID
        RULEID_SIGSIGNALTYPE = 127, // sigSignalType
        RULEID_SIGSTREAM = 124, // sigStream
        RULEID_SLASH = 226, // SLASH
        RULEID_SP = 231, // SP
        RULEID_STATISTICSDESCRIPTOR = 199, // statisticsDescriptor
        RULEID_STATISTICSPARAMETER = 200, // statisticsParameter
        RULEID_STATSTOKEN = 339, // StatsToken
        RULEID_STREAMDESCRIPTOR = 71, // streamDescriptor
        RULEID_STREAMID = 97, // StreamID
        RULEID_STREAMMODE = 76, // streamMode
        RULEID_STREAMMODES = 77, // streamModes
        RULEID_STREAMPARM = 70, // streamParm
        RULEID_STREAMTOKEN = 340, // StreamToken
        RULEID_SUBTRACTREQUEST = 34, // subtractRequest
        RULEID_SUBTRACTTOKEN = 341, // SubtractToken
        RULEID_SYNCHISDNTOKEN = 342, // SynchISDNToken
        RULEID_TERMIDLIST = 63, // termIDList
        RULEID_TERMINATIONA = 203, // terminationA
        RULEID_TERMINATIONAUDIT = 38, // terminationAudit
        RULEID_TERMINATIONB = 204, // terminationB
        RULEID_TERMINATIONID = 67, // TerminationID
        RULEID_TERMINATIONIDLIST = 64, // terminationIDList
        RULEID_TERMINATIONSTATEDESCRIPTOR = 91, // terminationStateDescriptor
        RULEID_TERMINATIONSTATEPARM = 92, // terminationStateParm
        RULEID_TERMINATIONSTATETOKEN = 343, // TerminationStateToken
        RULEID_TESTTOKEN = 344, // TestToken
        RULEID_TIME = 198, // Time
        RULEID_TIMEOUTTOKEN = 345, // TimeOutToken
        RULEID_TIMER = 145, // Timer
        RULEID_TIMESTAMP = 196, // TimeStamp
        RULEID_TOPOLOGYDESCRIPTOR = 201, // topologyDescriptor
        RULEID_TOPOLOGYDIRECTION = 205, // topologyDirection
        RULEID_TOPOLOGYTOKEN = 346, // TopologyToken
        RULEID_TOPOLOGYTRIPLE = 202, // topologyTriple
        RULEID_TRANSACTIONACK = 13, // transactionAck
        RULEID_TRANSACTIONID = 49, // TransactionID
        RULEID_TRANSACTIONLIST = 7, // transactionList
        RULEID_TRANSACTIONPENDING = 10, // transactionPending
        RULEID_TRANSACTIONREPLY = 9, // transactionReply
        RULEID_TRANSACTIONREQUEST = 8, // transactionRequest
        RULEID_TRANSACTIONRESPONSEACK = 11, // transactionResponseAck
        RULEID_TRANSTOKEN = 347, // TransToken
        RULEID_UINT16 = 215, // UINT16
        RULEID_UINT32 = 216, // UINT32
        RULEID_V18TOKEN = 349, // V18Token
        RULEID_V22BISTOKEN = 351, // V22bisToken
        RULEID_V22TOKEN = 350, // V22Token
        RULEID_V32BISTOKEN = 353, // V32bisToken
        RULEID_V32TOKEN = 352, // V32Token
        RULEID_V34TOKEN = 354, // V34Token
        RULEID_V4HEX = 57, // V4hex
        RULEID_V76TOKEN = 355, // V76Token
        RULEID_V90TOKEN = 356, // V90Token
        RULEID_V91TOKEN = 357, // V91Token
        RULEID_VALUE = 218, // VALUE
        RULEID_VERSION = 194, // Version
        RULEID_VERSIONTOKEN = 358, // VersionToken
        RULEID_WSP = 237, // WSP
        RULEID_COUNT = 359
	} RULEIDS;

	//UDT IDs
	enum{
        UDTID_COUNT = 0
	} UDTIDS;

	// CLASS FUNCTIONS
	MEGACO();
	MEGACO(PFN_ALERT pfnAlertHandler);
	~MEGACO();
	void* vpGetParserCtx(){return m_vpParserCtx;}

	// parser syntax analysis
	void 		vDefineSyntaxCallbacks(APG_CALLBACK* sppRuleCallbacks, APG_CALLBACK* sppUdtCallbacks);
	apg_uint	uiSyntaxCallbacks(APG_CALLBACK* spRuleCallbacks, APG_CALLBACK* spUdtCallbacks);
	apg_uint	uiSyntaxAnalysis(apg_uint uiStartRule, apg_achar* acpSrc, apg_uint uiSrcLen, void* vpData = NULL);
	apg_uint	uiState(APG_PARSER_STATE* spState);

	// parser semantic analysis
	void		vDefineAstNodes(apg_uint* uipRules, apg_uint* uipUdts);
	void		vDefineAstCallbacks(APG_CALLBACK* ppfnRuleCallbacks, APG_CALLBACK* ppfnUdtCallbacks);
	void		vAstInitNodes(apg_uint* uipRules, apg_uint* uipUdts);
	void		vAstInitCallbacks(APG_CALLBACK* ppfnRuleCallbacks, APG_CALLBACK* ppfnUdtCallbacks);
	apg_uint	uiAstTranslate(APG_CALLBACK* ppfnRuleCallbacks, APG_CALLBACK* ppfnUdtCallbacks, void* vpData = NULL);

	// parser statistics
	apg_uint 	uiStatsEnable(apg_uint uiEnable = APG_TRUE);
	apg_uint	uiStatsGet(APG_PARSER_STATS* spStats, apg_uint* uipBufferSize);

	// parser trace configuration
	apg_uint	uiTraceEnable(apg_uint uiEnable = APG_TRUE);
	void		vTraceOp(apg_uint uiOpId, apg_uint uiEnable = APG_TRUE);
	void		vTraceRule(apg_uint uiIndex, apg_uint uiEnable = APG_TRUE);
	void		vTraceUdt(apg_uint uiIndex, apg_uint uiEnable = APG_TRUE);
	void		vTraceRange(apg_uint uiBegin = 0, apg_uint uiCount = APG_INFINITE);

	public:
	void* m_vpParserCtx;
	APG_PARSER_STATS* m_spStats;
	APG_PARSER_STATE m_sState;

	// SYNTAX CALL BACK FUNCTIONS
   static apg_uint uiSyn_actionReply(APG_CBDATA* spData);
   static apg_uint uiSyn_actionReplyList(APG_CBDATA* spData);
   static apg_uint uiSyn_actionRequest(APG_CBDATA* spData);
   static apg_uint uiSyn_AddToken(APG_CBDATA* spData);
   static apg_uint uiSyn_ALPHA(APG_CBDATA* spData);
   static apg_uint uiSyn_alternativeValue(APG_CBDATA* spData);
   static apg_uint uiSyn_ammParameter(APG_CBDATA* spData);
   static apg_uint uiSyn_ammRequest(APG_CBDATA* spData);
   static apg_uint uiSyn_ammsReply(APG_CBDATA* spData);
   static apg_uint uiSyn_AndAUDITSelectToken(APG_CBDATA* spData);
   static apg_uint uiSyn_AuditCapToken(APG_CBDATA* spData);
   static apg_uint uiSyn_auditDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_auditItem(APG_CBDATA* spData);
   static apg_uint uiSyn_auditOther(APG_CBDATA* spData);
   static apg_uint uiSyn_auditReply(APG_CBDATA* spData);
   static apg_uint uiSyn_auditRequest(APG_CBDATA* spData);
   static apg_uint uiSyn_auditReturnItem(APG_CBDATA* spData);
   static apg_uint uiSyn_auditReturnParameter(APG_CBDATA* spData);
   static apg_uint uiSyn_auditSelectLogic(APG_CBDATA* spData);
   static apg_uint uiSyn_AuditToken(APG_CBDATA* spData);
   static apg_uint uiSyn_AuditValueToken(APG_CBDATA* spData);
   static apg_uint uiSyn_AuthData(APG_CBDATA* spData);
   static apg_uint uiSyn_authenticationHeader(APG_CBDATA* spData);
   static apg_uint uiSyn_AuthToken(APG_CBDATA* spData);
   static apg_uint uiSyn_BothToken(APG_CBDATA* spData);
   static apg_uint uiSyn_BothwayToken(APG_CBDATA* spData);
   static apg_uint uiSyn_BriefToken(APG_CBDATA* spData);
   static apg_uint uiSyn_BufferToken(APG_CBDATA* spData);
   static apg_uint uiSyn_COLON(APG_CBDATA* spData);
   static apg_uint uiSyn_COMMA(APG_CBDATA* spData);
   static apg_uint uiSyn_commandReply(APG_CBDATA* spData);
   static apg_uint uiSyn_commandReplyList(APG_CBDATA* spData);
   static apg_uint uiSyn_commandReplys(APG_CBDATA* spData);
   static apg_uint uiSyn_commandRequest(APG_CBDATA* spData);
   static apg_uint uiSyn_commandRequestList(APG_CBDATA* spData);
   static apg_uint uiSyn_COMMENT(APG_CBDATA* spData);
   static apg_uint uiSyn_contextAttrDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_ContextAttrToken(APG_CBDATA* spData);
   static apg_uint uiSyn_contextAudit(APG_CBDATA* spData);
   static apg_uint uiSyn_contextAuditProperties(APG_CBDATA* spData);
   static apg_uint uiSyn_contextAuditSelector(APG_CBDATA* spData);
   static apg_uint uiSyn_ContextAuditToken(APG_CBDATA* spData);
   static apg_uint uiSyn_ContextID(APG_CBDATA* spData);
   static apg_uint uiSyn_contextIdList(APG_CBDATA* spData);
   static apg_uint uiSyn_ContextListToken(APG_CBDATA* spData);
   static apg_uint uiSyn_contextProperties(APG_CBDATA* spData);
   static apg_uint uiSyn_contextProperty(APG_CBDATA* spData);
   static apg_uint uiSyn_contextRequest(APG_CBDATA* spData);
   static apg_uint uiSyn_contextTerminationAudit(APG_CBDATA* spData);
   static apg_uint uiSyn_CR(APG_CBDATA* spData);
   static apg_uint uiSyn_CtxToken(APG_CBDATA* spData);
   static apg_uint uiSyn_Date(APG_CBDATA* spData);
   static apg_uint uiSyn_DelayToken(APG_CBDATA* spData);
   static apg_uint uiSyn_deviceName(APG_CBDATA* spData);
   static apg_uint uiSyn_DIGIT(APG_CBDATA* spData);
   static apg_uint uiSyn_digitLetter(APG_CBDATA* spData);
   static apg_uint uiSyn_digitMap(APG_CBDATA* spData);
   static apg_uint uiSyn_digitMapDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_digitMapLetter(APG_CBDATA* spData);
   static apg_uint uiSyn_digitMapName(APG_CBDATA* spData);
   static apg_uint uiSyn_digitMapRange(APG_CBDATA* spData);
   static apg_uint uiSyn_DigitMapToken(APG_CBDATA* spData);
   static apg_uint uiSyn_digitMapValue(APG_CBDATA* spData);
   static apg_uint uiSyn_digitPosition(APG_CBDATA* spData);
   static apg_uint uiSyn_digitString(APG_CBDATA* spData);
   static apg_uint uiSyn_digitStringElement(APG_CBDATA* spData);
   static apg_uint uiSyn_digitStringList(APG_CBDATA* spData);
   static apg_uint uiSyn_direction(APG_CBDATA* spData);
   static apg_uint uiSyn_DirectionToken(APG_CBDATA* spData);
   static apg_uint uiSyn_DisconnectedToken(APG_CBDATA* spData);
   static apg_uint uiSyn_domainAddress(APG_CBDATA* spData);
   static apg_uint uiSyn_domainName(APG_CBDATA* spData);
   static apg_uint uiSyn_DOT(APG_CBDATA* spData);
   static apg_uint uiSyn_DQUOTE(APG_CBDATA* spData);
   static apg_uint uiSyn_DurationToken(APG_CBDATA* spData);
   static apg_uint uiSyn_embedFirst(APG_CBDATA* spData);
   static apg_uint uiSyn_embedNoSig(APG_CBDATA* spData);
   static apg_uint uiSyn_embedSig(APG_CBDATA* spData);
   static apg_uint uiSyn_EmbedToken(APG_CBDATA* spData);
   static apg_uint uiSyn_embedWithSig(APG_CBDATA* spData);
   static apg_uint uiSyn_EmergencyOffToken(APG_CBDATA* spData);
   static apg_uint uiSyn_EmergencyToken(APG_CBDATA* spData);
   static apg_uint uiSyn_emergencyValue(APG_CBDATA* spData);
   static apg_uint uiSyn_EmergencyValueToken(APG_CBDATA* spData);
   static apg_uint uiSyn_EOL(APG_CBDATA* spData);
   static apg_uint uiSyn_EQUAL(APG_CBDATA* spData);
   static apg_uint uiSyn_ErrorCode(APG_CBDATA* spData);
   static apg_uint uiSyn_errorDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_ErrorToken(APG_CBDATA* spData);
   static apg_uint uiSyn_eventBufferControl(APG_CBDATA* spData);
   static apg_uint uiSyn_eventBufferControlValue(APG_CBDATA* spData);
   static apg_uint uiSyn_eventBufferDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_EventBufferToken(APG_CBDATA* spData);
   static apg_uint uiSyn_eventDM(APG_CBDATA* spData);
   static apg_uint uiSyn_eventOther(APG_CBDATA* spData);
   static apg_uint uiSyn_eventParameter(APG_CBDATA* spData);
   static apg_uint uiSyn_eventParameterName(APG_CBDATA* spData);
   static apg_uint uiSyn_eventsDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_eventSpec(APG_CBDATA* spData);
   static apg_uint uiSyn_eventSpecParameter(APG_CBDATA* spData);
   static apg_uint uiSyn_EventsToken(APG_CBDATA* spData);
   static apg_uint uiSyn_eventStream(APG_CBDATA* spData);
   static apg_uint uiSyn_extension(APG_CBDATA* spData);
   static apg_uint uiSyn_extensionParameter(APG_CBDATA* spData);
   static apg_uint uiSyn_ExternalToken(APG_CBDATA* spData);
   static apg_uint uiSyn_FailoverToken(APG_CBDATA* spData);
   static apg_uint uiSyn_ForcedToken(APG_CBDATA* spData);
   static apg_uint uiSyn_GracefulToken(APG_CBDATA* spData);
   static apg_uint uiSyn_H221Token(APG_CBDATA* spData);
   static apg_uint uiSyn_H223Token(APG_CBDATA* spData);
   static apg_uint uiSyn_H226Token(APG_CBDATA* spData);
   static apg_uint uiSyn_HandOffToken(APG_CBDATA* spData);
   static apg_uint uiSyn_hex4(APG_CBDATA* spData);
   static apg_uint uiSyn_HEXDIG(APG_CBDATA* spData);
   static apg_uint uiSyn_hexpart(APG_CBDATA* spData);
   static apg_uint uiSyn_hexseq(APG_CBDATA* spData);
   static apg_uint uiSyn_HTAB(APG_CBDATA* spData);
   static apg_uint uiSyn_IEPSToken(APG_CBDATA* spData);
   static apg_uint uiSyn_iepsValue(APG_CBDATA* spData);
   static apg_uint uiSyn_ImmAckRequiredToken(APG_CBDATA* spData);
   static apg_uint uiSyn_InactiveToken(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudauditReturnParameter(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudcontextAttrDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_indAuddigitMapDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudeventBufferDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudeventsDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudeventSpec(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudeventSpecParameter(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudlocalControlDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudlocalDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudlocalParm(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudmediaDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudmediaParm(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudpackagesDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudremoteDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudrequestedEvent(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudsignalList(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudsignalListParm(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudsignalParm(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudsignalRequest(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudsignalRequestParm(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudsignalsDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudstatisticsDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudstreamDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudstreamParm(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudterminationAudit(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudterminationStateDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_indAudterminationStateParm(APG_CBDATA* spData);
   static apg_uint uiSyn_INEQUAL(APG_CBDATA* spData);
   static apg_uint uiSyn_InSvcToken(APG_CBDATA* spData);
   static apg_uint uiSyn_InternalToken(APG_CBDATA* spData);
   static apg_uint uiSyn_InterruptByEventToken(APG_CBDATA* spData);
   static apg_uint uiSyn_InterruptByNewSignalsDescrToken(APG_CBDATA* spData);
   static apg_uint uiSyn_IntsigDelayToken(APG_CBDATA* spData);
   static apg_uint uiSyn_IPv4address(APG_CBDATA* spData);
   static apg_uint uiSyn_IPv6address(APG_CBDATA* spData);
   static apg_uint uiSyn_IsolateToken(APG_CBDATA* spData);
   static apg_uint uiSyn_ItemID(APG_CBDATA* spData);
   static apg_uint uiSyn_IterationToken(APG_CBDATA* spData);
   static apg_uint uiSyn_KeepActiveToken(APG_CBDATA* spData);
   static apg_uint uiSyn_LBRKT(APG_CBDATA* spData);
   static apg_uint uiSyn_LF(APG_CBDATA* spData);
   static apg_uint uiSyn_localControlDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_LocalControlToken(APG_CBDATA* spData);
   static apg_uint uiSyn_localDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_localParm(APG_CBDATA* spData);
   static apg_uint uiSyn_LocalToken(APG_CBDATA* spData);
   static apg_uint uiSyn_LockStepToken(APG_CBDATA* spData);
   static apg_uint uiSyn_LoopbackToken(APG_CBDATA* spData);
   static apg_uint uiSyn_LSBRKT(APG_CBDATA* spData);
   static apg_uint uiSyn_LWSP(APG_CBDATA* spData);
   static apg_uint uiSyn_mediaDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_mediaParm(APG_CBDATA* spData);
   static apg_uint uiSyn_MediaToken(APG_CBDATA* spData);
   static apg_uint uiSyn_megacoMessage(APG_CBDATA* spData);
   static apg_uint uiSyn_MegacopToken(APG_CBDATA* spData);
   static apg_uint uiSyn_Message(APG_CBDATA* spData);
   static apg_uint uiSyn_messageBody(APG_CBDATA* spData);
   static apg_uint uiSyn_MessageSegmentToken(APG_CBDATA* spData);
   static apg_uint uiSyn_MethodToken(APG_CBDATA* spData);
   static apg_uint uiSyn_MgcIdToken(APG_CBDATA* spData);
   static apg_uint uiSyn_mId(APG_CBDATA* spData);
   static apg_uint uiSyn_modemDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_ModemToken(APG_CBDATA* spData);
   static apg_uint uiSyn_modemType(APG_CBDATA* spData);
   static apg_uint uiSyn_ModeToken(APG_CBDATA* spData);
   static apg_uint uiSyn_ModifyToken(APG_CBDATA* spData);
   static apg_uint uiSyn_MoveToken(APG_CBDATA* spData);
   static apg_uint uiSyn_mtpAddress(APG_CBDATA* spData);
   static apg_uint uiSyn_MTPToken(APG_CBDATA* spData);
   static apg_uint uiSyn_muxDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_MuxToken(APG_CBDATA* spData);
   static apg_uint uiSyn_MuxType(APG_CBDATA* spData);
   static apg_uint uiSyn_NAME(APG_CBDATA* spData);
   static apg_uint uiSyn_NeverNotifyToken(APG_CBDATA* spData);
   static apg_uint uiSyn_nonEscapeChar(APG_CBDATA* spData);
   static apg_uint uiSyn_notificationReason(APG_CBDATA* spData);
   static apg_uint uiSyn_notifyBehaviour(APG_CBDATA* spData);
   static apg_uint uiSyn_notifyCompletion(APG_CBDATA* spData);
   static apg_uint uiSyn_NotifyCompletionToken(APG_CBDATA* spData);
   static apg_uint uiSyn_NotifyImmediateToken(APG_CBDATA* spData);
   static apg_uint uiSyn_notifyRegulated(APG_CBDATA* spData);
   static apg_uint uiSyn_NotifyRegulatedToken(APG_CBDATA* spData);
   static apg_uint uiSyn_notifyReply(APG_CBDATA* spData);
   static apg_uint uiSyn_notifyRequest(APG_CBDATA* spData);
   static apg_uint uiSyn_NotifyToken(APG_CBDATA* spData);
   static apg_uint uiSyn_Nx64kToken(APG_CBDATA* spData);
   static apg_uint uiSyn_observedEvent(APG_CBDATA* spData);
   static apg_uint uiSyn_observedEventParameter(APG_CBDATA* spData);
   static apg_uint uiSyn_observedEventsDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_ObservedEventsToken(APG_CBDATA* spData);
   static apg_uint uiSyn_octetString(APG_CBDATA* spData);
   static apg_uint uiSyn_OnewayBothToken(APG_CBDATA* spData);
   static apg_uint uiSyn_OnewayExternalToken(APG_CBDATA* spData);
   static apg_uint uiSyn_OnewayToken(APG_CBDATA* spData);
   static apg_uint uiSyn_OnOffToken(APG_CBDATA* spData);
   static apg_uint uiSyn_OrAUDITselectToken(APG_CBDATA* spData);
   static apg_uint uiSyn_OtherReasonToken(APG_CBDATA* spData);
   static apg_uint uiSyn_OutOfSvcToken(APG_CBDATA* spData);
   static apg_uint uiSyn_PackageName(APG_CBDATA* spData);
   static apg_uint uiSyn_packagesDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_packagesItem(APG_CBDATA* spData);
   static apg_uint uiSyn_PackagesToken(APG_CBDATA* spData);
   static apg_uint uiSyn_parmValue(APG_CBDATA* spData);
   static apg_uint uiSyn_pathDomainName(APG_CBDATA* spData);
   static apg_uint uiSyn_pathNAME(APG_CBDATA* spData);
   static apg_uint uiSyn_PendingToken(APG_CBDATA* spData);
   static apg_uint uiSyn_pkgdName(APG_CBDATA* spData);
   static apg_uint uiSyn_portNumber(APG_CBDATA* spData);
   static apg_uint uiSyn_priority(APG_CBDATA* spData);
   static apg_uint uiSyn_PriorityToken(APG_CBDATA* spData);
   static apg_uint uiSyn_ProfileToken(APG_CBDATA* spData);
   static apg_uint uiSyn_propertyParm(APG_CBDATA* spData);
   static apg_uint uiSyn_quotedString(APG_CBDATA* spData);
   static apg_uint uiSyn_RBRKT(APG_CBDATA* spData);
   static apg_uint uiSyn_ReasonToken(APG_CBDATA* spData);
   static apg_uint uiSyn_RecvonlyToken(APG_CBDATA* spData);
   static apg_uint uiSyn_remoteDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_RemoteToken(APG_CBDATA* spData);
   static apg_uint uiSyn_ReplyToken(APG_CBDATA* spData);
   static apg_uint uiSyn_requestedEvent(APG_CBDATA* spData);
   static apg_uint uiSyn_RequestID(APG_CBDATA* spData);
   static apg_uint uiSyn_RequestIDToken(APG_CBDATA* spData);
   static apg_uint uiSyn_reservedGroupMode(APG_CBDATA* spData);
   static apg_uint uiSyn_ReservedGroupToken(APG_CBDATA* spData);
   static apg_uint uiSyn_reservedValueMode(APG_CBDATA* spData);
   static apg_uint uiSyn_ReservedValueToken(APG_CBDATA* spData);
   static apg_uint uiSyn_ResetEventsDescriptorToken(APG_CBDATA* spData);
   static apg_uint uiSyn_ResponseAckToken(APG_CBDATA* spData);
   static apg_uint uiSyn_RestartToken(APG_CBDATA* spData);
   static apg_uint uiSyn_RestChar(APG_CBDATA* spData);
   static apg_uint uiSyn_RSBRKT(APG_CBDATA* spData);
   static apg_uint uiSyn_SafeChar(APG_CBDATA* spData);
   static apg_uint uiSyn_secondEventParameter(APG_CBDATA* spData);
   static apg_uint uiSyn_secondRequestedEvent(APG_CBDATA* spData);
   static apg_uint uiSyn_SecurityParmIndex(APG_CBDATA* spData);
   static apg_uint uiSyn_SegmentationCompleteToken(APG_CBDATA* spData);
   static apg_uint uiSyn_segmentNumber(APG_CBDATA* spData);
   static apg_uint uiSyn_segmentReply(APG_CBDATA* spData);
   static apg_uint uiSyn_SendonlyToken(APG_CBDATA* spData);
   static apg_uint uiSyn_SendrecvToken(APG_CBDATA* spData);
   static apg_uint uiSyn_SEP(APG_CBDATA* spData);
   static apg_uint uiSyn_SequenceNum(APG_CBDATA* spData);
   static apg_uint uiSyn_servChgReplyParm(APG_CBDATA* spData);
   static apg_uint uiSyn_serviceChangeAddress(APG_CBDATA* spData);
   static apg_uint uiSyn_ServiceChangeAddressToken(APG_CBDATA* spData);
   static apg_uint uiSyn_serviceChangeDelay(APG_CBDATA* spData);
   static apg_uint uiSyn_serviceChangeDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_ServiceChangeIncompleteToken(APG_CBDATA* spData);
   static apg_uint uiSyn_serviceChangeMethod(APG_CBDATA* spData);
   static apg_uint uiSyn_serviceChangeMgcId(APG_CBDATA* spData);
   static apg_uint uiSyn_serviceChangeParm(APG_CBDATA* spData);
   static apg_uint uiSyn_serviceChangeProfile(APG_CBDATA* spData);
   static apg_uint uiSyn_serviceChangeReason(APG_CBDATA* spData);
   static apg_uint uiSyn_serviceChangeReply(APG_CBDATA* spData);
   static apg_uint uiSyn_serviceChangeReplyDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_serviceChangeRequest(APG_CBDATA* spData);
   static apg_uint uiSyn_ServiceChangeToken(APG_CBDATA* spData);
   static apg_uint uiSyn_serviceChangeVersion(APG_CBDATA* spData);
   static apg_uint uiSyn_serviceStates(APG_CBDATA* spData);
   static apg_uint uiSyn_ServiceStatesToken(APG_CBDATA* spData);
   static apg_uint uiSyn_serviceStatesValue(APG_CBDATA* spData);
   static apg_uint uiSyn_ServicesToken(APG_CBDATA* spData);
   static apg_uint uiSyn_sigDirection(APG_CBDATA* spData);
   static apg_uint uiSyn_sigDuration(APG_CBDATA* spData);
   static apg_uint uiSyn_sigIntsigDelay(APG_CBDATA* spData);
   static apg_uint uiSyn_signalList(APG_CBDATA* spData);
   static apg_uint uiSyn_signalListId(APG_CBDATA* spData);
   static apg_uint uiSyn_signalListParm(APG_CBDATA* spData);
   static apg_uint uiSyn_SignalListToken(APG_CBDATA* spData);
   static apg_uint uiSyn_signalName(APG_CBDATA* spData);
   static apg_uint uiSyn_signalParm(APG_CBDATA* spData);
   static apg_uint uiSyn_signalRequest(APG_CBDATA* spData);
   static apg_uint uiSyn_signalsDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_SignalsToken(APG_CBDATA* spData);
   static apg_uint uiSyn_signalType(APG_CBDATA* spData);
   static apg_uint uiSyn_SignalTypeToken(APG_CBDATA* spData);
   static apg_uint uiSyn_sigOther(APG_CBDATA* spData);
   static apg_uint uiSyn_sigParameter(APG_CBDATA* spData);
   static apg_uint uiSyn_sigParameterName(APG_CBDATA* spData);
   static apg_uint uiSyn_sigRequestID(APG_CBDATA* spData);
   static apg_uint uiSyn_sigSignalType(APG_CBDATA* spData);
   static apg_uint uiSyn_sigStream(APG_CBDATA* spData);
   static apg_uint uiSyn_SLASH(APG_CBDATA* spData);
   static apg_uint uiSyn_SP(APG_CBDATA* spData);
   static apg_uint uiSyn_statisticsDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_statisticsParameter(APG_CBDATA* spData);
   static apg_uint uiSyn_StatsToken(APG_CBDATA* spData);
   static apg_uint uiSyn_streamDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_StreamID(APG_CBDATA* spData);
   static apg_uint uiSyn_streamMode(APG_CBDATA* spData);
   static apg_uint uiSyn_streamModes(APG_CBDATA* spData);
   static apg_uint uiSyn_streamParm(APG_CBDATA* spData);
   static apg_uint uiSyn_StreamToken(APG_CBDATA* spData);
   static apg_uint uiSyn_subtractRequest(APG_CBDATA* spData);
   static apg_uint uiSyn_SubtractToken(APG_CBDATA* spData);
   static apg_uint uiSyn_SynchISDNToken(APG_CBDATA* spData);
   static apg_uint uiSyn_termIDList(APG_CBDATA* spData);
   static apg_uint uiSyn_terminationA(APG_CBDATA* spData);
   static apg_uint uiSyn_terminationAudit(APG_CBDATA* spData);
   static apg_uint uiSyn_terminationB(APG_CBDATA* spData);
   static apg_uint uiSyn_TerminationID(APG_CBDATA* spData);
   static apg_uint uiSyn_terminationIDList(APG_CBDATA* spData);
   static apg_uint uiSyn_terminationStateDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_terminationStateParm(APG_CBDATA* spData);
   static apg_uint uiSyn_TerminationStateToken(APG_CBDATA* spData);
   static apg_uint uiSyn_TestToken(APG_CBDATA* spData);
   static apg_uint uiSyn_Time(APG_CBDATA* spData);
   static apg_uint uiSyn_TimeOutToken(APG_CBDATA* spData);
   static apg_uint uiSyn_Timer(APG_CBDATA* spData);
   static apg_uint uiSyn_TimeStamp(APG_CBDATA* spData);
   static apg_uint uiSyn_topologyDescriptor(APG_CBDATA* spData);
   static apg_uint uiSyn_topologyDirection(APG_CBDATA* spData);
   static apg_uint uiSyn_TopologyToken(APG_CBDATA* spData);
   static apg_uint uiSyn_topologyTriple(APG_CBDATA* spData);
   static apg_uint uiSyn_transactionAck(APG_CBDATA* spData);
   static apg_uint uiSyn_TransactionID(APG_CBDATA* spData);
   static apg_uint uiSyn_transactionList(APG_CBDATA* spData);
   static apg_uint uiSyn_transactionPending(APG_CBDATA* spData);
   static apg_uint uiSyn_transactionReply(APG_CBDATA* spData);
   static apg_uint uiSyn_transactionRequest(APG_CBDATA* spData);
   static apg_uint uiSyn_transactionResponseAck(APG_CBDATA* spData);
   static apg_uint uiSyn_TransToken(APG_CBDATA* spData);
   static apg_uint uiSyn_UINT16(APG_CBDATA* spData);
   static apg_uint uiSyn_UINT32(APG_CBDATA* spData);
   static apg_uint uiSyn_V18Token(APG_CBDATA* spData);
   static apg_uint uiSyn_V22bisToken(APG_CBDATA* spData);
   static apg_uint uiSyn_V22Token(APG_CBDATA* spData);
   static apg_uint uiSyn_V32bisToken(APG_CBDATA* spData);
   static apg_uint uiSyn_V32Token(APG_CBDATA* spData);
   static apg_uint uiSyn_V34Token(APG_CBDATA* spData);
   static apg_uint uiSyn_V4hex(APG_CBDATA* spData);
   static apg_uint uiSyn_V76Token(APG_CBDATA* spData);
   static apg_uint uiSyn_V90Token(APG_CBDATA* spData);
   static apg_uint uiSyn_V91Token(APG_CBDATA* spData);
   static apg_uint uiSyn_VALUE(APG_CBDATA* spData);
   static apg_uint uiSyn_Version(APG_CBDATA* spData);
   static apg_uint uiSyn_VersionToken(APG_CBDATA* spData);
   static apg_uint uiSyn_WSP(APG_CBDATA* spData);

	// AST CALL BACK FUNCTIONS
   static apg_uint uiAst_actionReply(APG_CBDATA* spData);
   static apg_uint uiAst_actionReplyList(APG_CBDATA* spData);
   static apg_uint uiAst_actionRequest(APG_CBDATA* spData);
   static apg_uint uiAst_AddToken(APG_CBDATA* spData);
   static apg_uint uiAst_ALPHA(APG_CBDATA* spData);
   static apg_uint uiAst_alternativeValue(APG_CBDATA* spData);
   static apg_uint uiAst_ammParameter(APG_CBDATA* spData);
   static apg_uint uiAst_ammRequest(APG_CBDATA* spData);
   static apg_uint uiAst_ammsReply(APG_CBDATA* spData);
   static apg_uint uiAst_AndAUDITSelectToken(APG_CBDATA* spData);
   static apg_uint uiAst_AuditCapToken(APG_CBDATA* spData);
   static apg_uint uiAst_auditDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_auditItem(APG_CBDATA* spData);
   static apg_uint uiAst_auditOther(APG_CBDATA* spData);
   static apg_uint uiAst_auditReply(APG_CBDATA* spData);
   static apg_uint uiAst_auditRequest(APG_CBDATA* spData);
   static apg_uint uiAst_auditReturnItem(APG_CBDATA* spData);
   static apg_uint uiAst_auditReturnParameter(APG_CBDATA* spData);
   static apg_uint uiAst_auditSelectLogic(APG_CBDATA* spData);
   static apg_uint uiAst_AuditToken(APG_CBDATA* spData);
   static apg_uint uiAst_AuditValueToken(APG_CBDATA* spData);
   static apg_uint uiAst_AuthData(APG_CBDATA* spData);
   static apg_uint uiAst_authenticationHeader(APG_CBDATA* spData);
   static apg_uint uiAst_AuthToken(APG_CBDATA* spData);
   static apg_uint uiAst_BothToken(APG_CBDATA* spData);
   static apg_uint uiAst_BothwayToken(APG_CBDATA* spData);
   static apg_uint uiAst_BriefToken(APG_CBDATA* spData);
   static apg_uint uiAst_BufferToken(APG_CBDATA* spData);
   static apg_uint uiAst_COLON(APG_CBDATA* spData);
   static apg_uint uiAst_COMMA(APG_CBDATA* spData);
   static apg_uint uiAst_commandReply(APG_CBDATA* spData);
   static apg_uint uiAst_commandReplyList(APG_CBDATA* spData);
   static apg_uint uiAst_commandReplys(APG_CBDATA* spData);
   static apg_uint uiAst_commandRequest(APG_CBDATA* spData);
   static apg_uint uiAst_commandRequestList(APG_CBDATA* spData);
   static apg_uint uiAst_COMMENT(APG_CBDATA* spData);
   static apg_uint uiAst_contextAttrDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_ContextAttrToken(APG_CBDATA* spData);
   static apg_uint uiAst_contextAudit(APG_CBDATA* spData);
   static apg_uint uiAst_contextAuditProperties(APG_CBDATA* spData);
   static apg_uint uiAst_contextAuditSelector(APG_CBDATA* spData);
   static apg_uint uiAst_ContextAuditToken(APG_CBDATA* spData);
   static apg_uint uiAst_ContextID(APG_CBDATA* spData);
   static apg_uint uiAst_contextIdList(APG_CBDATA* spData);
   static apg_uint uiAst_ContextListToken(APG_CBDATA* spData);
   static apg_uint uiAst_contextProperties(APG_CBDATA* spData);
   static apg_uint uiAst_contextProperty(APG_CBDATA* spData);
   static apg_uint uiAst_contextRequest(APG_CBDATA* spData);
   static apg_uint uiAst_contextTerminationAudit(APG_CBDATA* spData);
   static apg_uint uiAst_CR(APG_CBDATA* spData);
   static apg_uint uiAst_CtxToken(APG_CBDATA* spData);
   static apg_uint uiAst_Date(APG_CBDATA* spData);
   static apg_uint uiAst_DelayToken(APG_CBDATA* spData);
   static apg_uint uiAst_deviceName(APG_CBDATA* spData);
   static apg_uint uiAst_DIGIT(APG_CBDATA* spData);
   static apg_uint uiAst_digitLetter(APG_CBDATA* spData);
   static apg_uint uiAst_digitMap(APG_CBDATA* spData);
   static apg_uint uiAst_digitMapDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_digitMapLetter(APG_CBDATA* spData);
   static apg_uint uiAst_digitMapName(APG_CBDATA* spData);
   static apg_uint uiAst_digitMapRange(APG_CBDATA* spData);
   static apg_uint uiAst_DigitMapToken(APG_CBDATA* spData);
   static apg_uint uiAst_digitMapValue(APG_CBDATA* spData);
   static apg_uint uiAst_digitPosition(APG_CBDATA* spData);
   static apg_uint uiAst_digitString(APG_CBDATA* spData);
   static apg_uint uiAst_digitStringElement(APG_CBDATA* spData);
   static apg_uint uiAst_digitStringList(APG_CBDATA* spData);
   static apg_uint uiAst_direction(APG_CBDATA* spData);
   static apg_uint uiAst_DirectionToken(APG_CBDATA* spData);
   static apg_uint uiAst_DisconnectedToken(APG_CBDATA* spData);
   static apg_uint uiAst_domainAddress(APG_CBDATA* spData);
   static apg_uint uiAst_domainName(APG_CBDATA* spData);
   static apg_uint uiAst_DOT(APG_CBDATA* spData);
   static apg_uint uiAst_DQUOTE(APG_CBDATA* spData);
   static apg_uint uiAst_DurationToken(APG_CBDATA* spData);
   static apg_uint uiAst_embedFirst(APG_CBDATA* spData);
   static apg_uint uiAst_embedNoSig(APG_CBDATA* spData);
   static apg_uint uiAst_embedSig(APG_CBDATA* spData);
   static apg_uint uiAst_EmbedToken(APG_CBDATA* spData);
   static apg_uint uiAst_embedWithSig(APG_CBDATA* spData);
   static apg_uint uiAst_EmergencyOffToken(APG_CBDATA* spData);
   static apg_uint uiAst_EmergencyToken(APG_CBDATA* spData);
   static apg_uint uiAst_emergencyValue(APG_CBDATA* spData);
   static apg_uint uiAst_EmergencyValueToken(APG_CBDATA* spData);
   static apg_uint uiAst_EOL(APG_CBDATA* spData);
   static apg_uint uiAst_EQUAL(APG_CBDATA* spData);
   static apg_uint uiAst_ErrorCode(APG_CBDATA* spData);
   static apg_uint uiAst_errorDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_ErrorToken(APG_CBDATA* spData);
   static apg_uint uiAst_eventBufferControl(APG_CBDATA* spData);
   static apg_uint uiAst_eventBufferControlValue(APG_CBDATA* spData);
   static apg_uint uiAst_eventBufferDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_EventBufferToken(APG_CBDATA* spData);
   static apg_uint uiAst_eventDM(APG_CBDATA* spData);
   static apg_uint uiAst_eventOther(APG_CBDATA* spData);
   static apg_uint uiAst_eventParameter(APG_CBDATA* spData);
   static apg_uint uiAst_eventParameterName(APG_CBDATA* spData);
   static apg_uint uiAst_eventsDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_eventSpec(APG_CBDATA* spData);
   static apg_uint uiAst_eventSpecParameter(APG_CBDATA* spData);
   static apg_uint uiAst_EventsToken(APG_CBDATA* spData);
   static apg_uint uiAst_eventStream(APG_CBDATA* spData);
   static apg_uint uiAst_extension(APG_CBDATA* spData);
   static apg_uint uiAst_extensionParameter(APG_CBDATA* spData);
   static apg_uint uiAst_ExternalToken(APG_CBDATA* spData);
   static apg_uint uiAst_FailoverToken(APG_CBDATA* spData);
   static apg_uint uiAst_ForcedToken(APG_CBDATA* spData);
   static apg_uint uiAst_GracefulToken(APG_CBDATA* spData);
   static apg_uint uiAst_H221Token(APG_CBDATA* spData);
   static apg_uint uiAst_H223Token(APG_CBDATA* spData);
   static apg_uint uiAst_H226Token(APG_CBDATA* spData);
   static apg_uint uiAst_HandOffToken(APG_CBDATA* spData);
   static apg_uint uiAst_hex4(APG_CBDATA* spData);
   static apg_uint uiAst_HEXDIG(APG_CBDATA* spData);
   static apg_uint uiAst_hexpart(APG_CBDATA* spData);
   static apg_uint uiAst_hexseq(APG_CBDATA* spData);
   static apg_uint uiAst_HTAB(APG_CBDATA* spData);
   static apg_uint uiAst_IEPSToken(APG_CBDATA* spData);
   static apg_uint uiAst_iepsValue(APG_CBDATA* spData);
   static apg_uint uiAst_ImmAckRequiredToken(APG_CBDATA* spData);
   static apg_uint uiAst_InactiveToken(APG_CBDATA* spData);
   static apg_uint uiAst_indAudauditReturnParameter(APG_CBDATA* spData);
   static apg_uint uiAst_indAudcontextAttrDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_indAuddigitMapDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_indAudeventBufferDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_indAudeventsDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_indAudeventSpec(APG_CBDATA* spData);
   static apg_uint uiAst_indAudeventSpecParameter(APG_CBDATA* spData);
   static apg_uint uiAst_indAudlocalControlDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_indAudlocalDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_indAudlocalParm(APG_CBDATA* spData);
   static apg_uint uiAst_indAudmediaDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_indAudmediaParm(APG_CBDATA* spData);
   static apg_uint uiAst_indAudpackagesDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_indAudremoteDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_indAudrequestedEvent(APG_CBDATA* spData);
   static apg_uint uiAst_indAudsignalList(APG_CBDATA* spData);
   static apg_uint uiAst_indAudsignalListParm(APG_CBDATA* spData);
   static apg_uint uiAst_indAudsignalParm(APG_CBDATA* spData);
   static apg_uint uiAst_indAudsignalRequest(APG_CBDATA* spData);
   static apg_uint uiAst_indAudsignalRequestParm(APG_CBDATA* spData);
   static apg_uint uiAst_indAudsignalsDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_indAudstatisticsDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_indAudstreamDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_indAudstreamParm(APG_CBDATA* spData);
   static apg_uint uiAst_indAudterminationAudit(APG_CBDATA* spData);
   static apg_uint uiAst_indAudterminationStateDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_indAudterminationStateParm(APG_CBDATA* spData);
   static apg_uint uiAst_INEQUAL(APG_CBDATA* spData);
   static apg_uint uiAst_InSvcToken(APG_CBDATA* spData);
   static apg_uint uiAst_InternalToken(APG_CBDATA* spData);
   static apg_uint uiAst_InterruptByEventToken(APG_CBDATA* spData);
   static apg_uint uiAst_InterruptByNewSignalsDescrToken(APG_CBDATA* spData);
   static apg_uint uiAst_IntsigDelayToken(APG_CBDATA* spData);
   static apg_uint uiAst_IPv4address(APG_CBDATA* spData);
   static apg_uint uiAst_IPv6address(APG_CBDATA* spData);
   static apg_uint uiAst_IsolateToken(APG_CBDATA* spData);
   static apg_uint uiAst_ItemID(APG_CBDATA* spData);
   static apg_uint uiAst_IterationToken(APG_CBDATA* spData);
   static apg_uint uiAst_KeepActiveToken(APG_CBDATA* spData);
   static apg_uint uiAst_LBRKT(APG_CBDATA* spData);
   static apg_uint uiAst_LF(APG_CBDATA* spData);
   static apg_uint uiAst_localControlDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_LocalControlToken(APG_CBDATA* spData);
   static apg_uint uiAst_localDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_localParm(APG_CBDATA* spData);
   static apg_uint uiAst_LocalToken(APG_CBDATA* spData);
   static apg_uint uiAst_LockStepToken(APG_CBDATA* spData);
   static apg_uint uiAst_LoopbackToken(APG_CBDATA* spData);
   static apg_uint uiAst_LSBRKT(APG_CBDATA* spData);
   static apg_uint uiAst_LWSP(APG_CBDATA* spData);
   static apg_uint uiAst_mediaDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_mediaParm(APG_CBDATA* spData);
   static apg_uint uiAst_MediaToken(APG_CBDATA* spData);
   static apg_uint uiAst_megacoMessage(APG_CBDATA* spData);
   static apg_uint uiAst_MegacopToken(APG_CBDATA* spData);
   static apg_uint uiAst_Message(APG_CBDATA* spData);
   static apg_uint uiAst_messageBody(APG_CBDATA* spData);
   static apg_uint uiAst_MessageSegmentToken(APG_CBDATA* spData);
   static apg_uint uiAst_MethodToken(APG_CBDATA* spData);
   static apg_uint uiAst_MgcIdToken(APG_CBDATA* spData);
   static apg_uint uiAst_mId(APG_CBDATA* spData);
   static apg_uint uiAst_modemDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_ModemToken(APG_CBDATA* spData);
   static apg_uint uiAst_modemType(APG_CBDATA* spData);
   static apg_uint uiAst_ModeToken(APG_CBDATA* spData);
   static apg_uint uiAst_ModifyToken(APG_CBDATA* spData);
   static apg_uint uiAst_MoveToken(APG_CBDATA* spData);
   static apg_uint uiAst_mtpAddress(APG_CBDATA* spData);
   static apg_uint uiAst_MTPToken(APG_CBDATA* spData);
   static apg_uint uiAst_muxDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_MuxToken(APG_CBDATA* spData);
   static apg_uint uiAst_MuxType(APG_CBDATA* spData);
   static apg_uint uiAst_NAME(APG_CBDATA* spData);
   static apg_uint uiAst_NeverNotifyToken(APG_CBDATA* spData);
   static apg_uint uiAst_nonEscapeChar(APG_CBDATA* spData);
   static apg_uint uiAst_notificationReason(APG_CBDATA* spData);
   static apg_uint uiAst_notifyBehaviour(APG_CBDATA* spData);
   static apg_uint uiAst_notifyCompletion(APG_CBDATA* spData);
   static apg_uint uiAst_NotifyCompletionToken(APG_CBDATA* spData);
   static apg_uint uiAst_NotifyImmediateToken(APG_CBDATA* spData);
   static apg_uint uiAst_notifyRegulated(APG_CBDATA* spData);
   static apg_uint uiAst_NotifyRegulatedToken(APG_CBDATA* spData);
   static apg_uint uiAst_notifyReply(APG_CBDATA* spData);
   static apg_uint uiAst_notifyRequest(APG_CBDATA* spData);
   static apg_uint uiAst_NotifyToken(APG_CBDATA* spData);
   static apg_uint uiAst_Nx64kToken(APG_CBDATA* spData);
   static apg_uint uiAst_observedEvent(APG_CBDATA* spData);
   static apg_uint uiAst_observedEventParameter(APG_CBDATA* spData);
   static apg_uint uiAst_observedEventsDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_ObservedEventsToken(APG_CBDATA* spData);
   static apg_uint uiAst_octetString(APG_CBDATA* spData);
   static apg_uint uiAst_OnewayBothToken(APG_CBDATA* spData);
   static apg_uint uiAst_OnewayExternalToken(APG_CBDATA* spData);
   static apg_uint uiAst_OnewayToken(APG_CBDATA* spData);
   static apg_uint uiAst_OnOffToken(APG_CBDATA* spData);
   static apg_uint uiAst_OrAUDITselectToken(APG_CBDATA* spData);
   static apg_uint uiAst_OtherReasonToken(APG_CBDATA* spData);
   static apg_uint uiAst_OutOfSvcToken(APG_CBDATA* spData);
   static apg_uint uiAst_PackageName(APG_CBDATA* spData);
   static apg_uint uiAst_packagesDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_packagesItem(APG_CBDATA* spData);
   static apg_uint uiAst_PackagesToken(APG_CBDATA* spData);
   static apg_uint uiAst_parmValue(APG_CBDATA* spData);
   static apg_uint uiAst_pathDomainName(APG_CBDATA* spData);
   static apg_uint uiAst_pathNAME(APG_CBDATA* spData);
   static apg_uint uiAst_PendingToken(APG_CBDATA* spData);
   static apg_uint uiAst_pkgdName(APG_CBDATA* spData);
   static apg_uint uiAst_portNumber(APG_CBDATA* spData);
   static apg_uint uiAst_priority(APG_CBDATA* spData);
   static apg_uint uiAst_PriorityToken(APG_CBDATA* spData);
   static apg_uint uiAst_ProfileToken(APG_CBDATA* spData);
   static apg_uint uiAst_propertyParm(APG_CBDATA* spData);
   static apg_uint uiAst_quotedString(APG_CBDATA* spData);
   static apg_uint uiAst_RBRKT(APG_CBDATA* spData);
   static apg_uint uiAst_ReasonToken(APG_CBDATA* spData);
   static apg_uint uiAst_RecvonlyToken(APG_CBDATA* spData);
   static apg_uint uiAst_remoteDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_RemoteToken(APG_CBDATA* spData);
   static apg_uint uiAst_ReplyToken(APG_CBDATA* spData);
   static apg_uint uiAst_requestedEvent(APG_CBDATA* spData);
   static apg_uint uiAst_RequestID(APG_CBDATA* spData);
   static apg_uint uiAst_RequestIDToken(APG_CBDATA* spData);
   static apg_uint uiAst_reservedGroupMode(APG_CBDATA* spData);
   static apg_uint uiAst_ReservedGroupToken(APG_CBDATA* spData);
   static apg_uint uiAst_reservedValueMode(APG_CBDATA* spData);
   static apg_uint uiAst_ReservedValueToken(APG_CBDATA* spData);
   static apg_uint uiAst_ResetEventsDescriptorToken(APG_CBDATA* spData);
   static apg_uint uiAst_ResponseAckToken(APG_CBDATA* spData);
   static apg_uint uiAst_RestartToken(APG_CBDATA* spData);
   static apg_uint uiAst_RestChar(APG_CBDATA* spData);
   static apg_uint uiAst_RSBRKT(APG_CBDATA* spData);
   static apg_uint uiAst_SafeChar(APG_CBDATA* spData);
   static apg_uint uiAst_secondEventParameter(APG_CBDATA* spData);
   static apg_uint uiAst_secondRequestedEvent(APG_CBDATA* spData);
   static apg_uint uiAst_SecurityParmIndex(APG_CBDATA* spData);
   static apg_uint uiAst_SegmentationCompleteToken(APG_CBDATA* spData);
   static apg_uint uiAst_segmentNumber(APG_CBDATA* spData);
   static apg_uint uiAst_segmentReply(APG_CBDATA* spData);
   static apg_uint uiAst_SendonlyToken(APG_CBDATA* spData);
   static apg_uint uiAst_SendrecvToken(APG_CBDATA* spData);
   static apg_uint uiAst_SEP(APG_CBDATA* spData);
   static apg_uint uiAst_SequenceNum(APG_CBDATA* spData);
   static apg_uint uiAst_servChgReplyParm(APG_CBDATA* spData);
   static apg_uint uiAst_serviceChangeAddress(APG_CBDATA* spData);
   static apg_uint uiAst_ServiceChangeAddressToken(APG_CBDATA* spData);
   static apg_uint uiAst_serviceChangeDelay(APG_CBDATA* spData);
   static apg_uint uiAst_serviceChangeDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_ServiceChangeIncompleteToken(APG_CBDATA* spData);
   static apg_uint uiAst_serviceChangeMethod(APG_CBDATA* spData);
   static apg_uint uiAst_serviceChangeMgcId(APG_CBDATA* spData);
   static apg_uint uiAst_serviceChangeParm(APG_CBDATA* spData);
   static apg_uint uiAst_serviceChangeProfile(APG_CBDATA* spData);
   static apg_uint uiAst_serviceChangeReason(APG_CBDATA* spData);
   static apg_uint uiAst_serviceChangeReply(APG_CBDATA* spData);
   static apg_uint uiAst_serviceChangeReplyDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_serviceChangeRequest(APG_CBDATA* spData);
   static apg_uint uiAst_ServiceChangeToken(APG_CBDATA* spData);
   static apg_uint uiAst_serviceChangeVersion(APG_CBDATA* spData);
   static apg_uint uiAst_serviceStates(APG_CBDATA* spData);
   static apg_uint uiAst_ServiceStatesToken(APG_CBDATA* spData);
   static apg_uint uiAst_serviceStatesValue(APG_CBDATA* spData);
   static apg_uint uiAst_ServicesToken(APG_CBDATA* spData);
   static apg_uint uiAst_sigDirection(APG_CBDATA* spData);
   static apg_uint uiAst_sigDuration(APG_CBDATA* spData);
   static apg_uint uiAst_sigIntsigDelay(APG_CBDATA* spData);
   static apg_uint uiAst_signalList(APG_CBDATA* spData);
   static apg_uint uiAst_signalListId(APG_CBDATA* spData);
   static apg_uint uiAst_signalListParm(APG_CBDATA* spData);
   static apg_uint uiAst_SignalListToken(APG_CBDATA* spData);
   static apg_uint uiAst_signalName(APG_CBDATA* spData);
   static apg_uint uiAst_signalParm(APG_CBDATA* spData);
   static apg_uint uiAst_signalRequest(APG_CBDATA* spData);
   static apg_uint uiAst_signalsDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_SignalsToken(APG_CBDATA* spData);
   static apg_uint uiAst_signalType(APG_CBDATA* spData);
   static apg_uint uiAst_SignalTypeToken(APG_CBDATA* spData);
   static apg_uint uiAst_sigOther(APG_CBDATA* spData);
   static apg_uint uiAst_sigParameter(APG_CBDATA* spData);
   static apg_uint uiAst_sigParameterName(APG_CBDATA* spData);
   static apg_uint uiAst_sigRequestID(APG_CBDATA* spData);
   static apg_uint uiAst_sigSignalType(APG_CBDATA* spData);
   static apg_uint uiAst_sigStream(APG_CBDATA* spData);
   static apg_uint uiAst_SLASH(APG_CBDATA* spData);
   static apg_uint uiAst_SP(APG_CBDATA* spData);
   static apg_uint uiAst_statisticsDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_statisticsParameter(APG_CBDATA* spData);
   static apg_uint uiAst_StatsToken(APG_CBDATA* spData);
   static apg_uint uiAst_streamDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_StreamID(APG_CBDATA* spData);
   static apg_uint uiAst_streamMode(APG_CBDATA* spData);
   static apg_uint uiAst_streamModes(APG_CBDATA* spData);
   static apg_uint uiAst_streamParm(APG_CBDATA* spData);
   static apg_uint uiAst_StreamToken(APG_CBDATA* spData);
   static apg_uint uiAst_subtractRequest(APG_CBDATA* spData);
   static apg_uint uiAst_SubtractToken(APG_CBDATA* spData);
   static apg_uint uiAst_SynchISDNToken(APG_CBDATA* spData);
   static apg_uint uiAst_termIDList(APG_CBDATA* spData);
   static apg_uint uiAst_terminationA(APG_CBDATA* spData);
   static apg_uint uiAst_terminationAudit(APG_CBDATA* spData);
   static apg_uint uiAst_terminationB(APG_CBDATA* spData);
   static apg_uint uiAst_TerminationID(APG_CBDATA* spData);
   static apg_uint uiAst_terminationIDList(APG_CBDATA* spData);
   static apg_uint uiAst_terminationStateDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_terminationStateParm(APG_CBDATA* spData);
   static apg_uint uiAst_TerminationStateToken(APG_CBDATA* spData);
   static apg_uint uiAst_TestToken(APG_CBDATA* spData);
   static apg_uint uiAst_Time(APG_CBDATA* spData);
   static apg_uint uiAst_TimeOutToken(APG_CBDATA* spData);
   static apg_uint uiAst_Timer(APG_CBDATA* spData);
   static apg_uint uiAst_TimeStamp(APG_CBDATA* spData);
   static apg_uint uiAst_topologyDescriptor(APG_CBDATA* spData);
   static apg_uint uiAst_topologyDirection(APG_CBDATA* spData);
   static apg_uint uiAst_TopologyToken(APG_CBDATA* spData);
   static apg_uint uiAst_topologyTriple(APG_CBDATA* spData);
   static apg_uint uiAst_transactionAck(APG_CBDATA* spData);
   static apg_uint uiAst_TransactionID(APG_CBDATA* spData);
   static apg_uint uiAst_transactionList(APG_CBDATA* spData);
   static apg_uint uiAst_transactionPending(APG_CBDATA* spData);
   static apg_uint uiAst_transactionReply(APG_CBDATA* spData);
   static apg_uint uiAst_transactionRequest(APG_CBDATA* spData);
   static apg_uint uiAst_transactionResponseAck(APG_CBDATA* spData);
   static apg_uint uiAst_TransToken(APG_CBDATA* spData);
   static apg_uint uiAst_UINT16(APG_CBDATA* spData);
   static apg_uint uiAst_UINT32(APG_CBDATA* spData);
   static apg_uint uiAst_V18Token(APG_CBDATA* spData);
   static apg_uint uiAst_V22bisToken(APG_CBDATA* spData);
   static apg_uint uiAst_V22Token(APG_CBDATA* spData);
   static apg_uint uiAst_V32bisToken(APG_CBDATA* spData);
   static apg_uint uiAst_V32Token(APG_CBDATA* spData);
   static apg_uint uiAst_V34Token(APG_CBDATA* spData);
   static apg_uint uiAst_V4hex(APG_CBDATA* spData);
   static apg_uint uiAst_V76Token(APG_CBDATA* spData);
   static apg_uint uiAst_V90Token(APG_CBDATA* spData);
   static apg_uint uiAst_V91Token(APG_CBDATA* spData);
   static apg_uint uiAst_VALUE(APG_CBDATA* spData);
   static apg_uint uiAst_Version(APG_CBDATA* spData);
   static apg_uint uiAst_VersionToken(APG_CBDATA* spData);
   static apg_uint uiAst_WSP(APG_CBDATA* spData);
};
#endif // MEGACO_H

//**** SABNF GRAMMAR ****
//megacoMessage = LWSP [authenticationHeader SEP] message
//authenticationHeader = AuthToken EQUAL SecurityParmIndex COLON
//  SequenceNum COLON AuthData
//SecurityParmIndex = "0x" 8(HEXDIG)
//SequenceNum = "0x" 8(HEXDIG)
//AuthData = "0x" 24*64(HEXDIG)
//Message = MegacopToken SLASH Version SEP mId SEP messageBody
//; The version of the protocol defined here is equal to 3.
//messageBody = (errorDescriptor / transactionList)
//
//transactionList = 1*(transactionRequest     /
//                     transactionReply       /
//                     transactionPending     /
//                     transactionResponseAck /
//                     segmentReply)
//
//transactionRequest = TransToken EQUAL TransactionID LBRKT
//  actionRequest *(COMMA actionRequest) RBRKT
//
//transactionReply = ReplyToken EQUAL TransactionID [SLASH segmentNumber
//  [SLASH SegmentationCompleteToken]] LBRKT
//  [ImmAckRequiredToken COMMA]
//  (errorDescriptor / actionReplyList) RBRKT
//
//transactionPending = PendingToken EQUAL TransactionID LBRKT RBRKT
//
//transactionResponseAck = ResponseAckToken LBRKT transactionAck *(COMMA transactionAck) RBRKT
//
//segmentReply = MessageSegmentToken EQUAL TransactionID SLASH segmentNumber [SLASH SegmentationCompleteToken]
//
//transactionAck = TransactionID / (TransactionID "-" TransactionID)
//actionRequest = CtxToken EQUAL ContextID LBRKT ((contextRequest
//  [COMMA commandRequestList]) /
//  commandRequestList) RBRKT
//contextRequest = ((contextProperties [COMMA contextAudit]) / contextAudit)
//contextProperties = contextProperty *(COMMA contextProperty)
//
//; at-most-once
//; EmergencyOff to be used in MG to MGC direction only in H.248.1 V1 and V2
//; EmergencyToken or EmergencyOffToken, but not both
//contextProperty = (topologyDescriptor / priority / EmergencyOffToken / EmergencyToken / iepsValue /
//  contextAttrDescriptor)
//contextAudit = ContextAuditToken LBRKT (contextAuditProperties
//  *(COMMA contextAuditProperties)) /
//  indAudcontextAttrDescriptor RBRKT
//
//; at-most-once except contextAuditSelector
//contextAuditProperties = (TopologyToken / EmergencyToken /
//  PriorityToken /IEPSToken/ pkgdName /
//  contextAuditSelector)
//
//; at-most-once
//contextAuditSelector = priority / emergencyValue / iepsValue / contextAttrDescriptor / auditSelectLogic
//auditSelectLogic = [ AndAUDITselectToken / OrAUDITselectToken ]
//
//; If empty, AND of selection conditions is assumed.
//indAudcontextAttrDescriptor = ContextAttrToken LBRKT contextAuditProperties
//  *(COMMA contextAuditProperties) RBRKT
//
//; "O-" indicates an optional command
//; "W-" indicates a wildcarded response to a command
//commandRequestList = ["O-"] ["W-"] commandRequest *(COMMA ["O-"] ["W-"] commandRequest)
//commandRequest = (ammRequest / subtractRequest / auditRequest / notifyRequest / serviceChangeRequest)
//
//segmentNumber = UINT16
//actionReplyList = actionReply *(COMMA actionReply)
//actionReply = CtxToken EQUAL ContextID [LBRKT (errorDescriptor /
//  commandReply /(commandReply COMMA
//  errorDescriptor)) RBRKT]
//commandReply = ((contextProperties [COMMA commandReplyList]) / commandReplyList)
//commandReplyList = commandReplys *(COMMA commandReplys)
//commandReplys = (serviceChangeReply / auditReply / ammsReply / notifyReply)
//
//;Add, Move and Modify have the same request parameters
//ammRequest = (AddToken / MoveToken / ModifyToken) EQUAL
//  termIDList [LBRKT ammParameter *(COMMA
//  ammParameter) RBRKT]
//
//;at-most-once
//ammParameter = (mediaDescriptor / modemDescriptor /muxDescriptor /
//  eventsDescriptor / signalsDescriptor /
//  digitMapDescriptor / eventBufferDescriptor /
//  auditDescriptor / statisticsDescriptor)
//ammsReply = (AddToken / MoveToken / ModifyToken / SubtractToken)
//  EQUAL termIDList [LBRKT terminationAudit RBRKT]
//subtractRequest = SubtractToken EQUAL termIDList [LBRKT auditDescriptor RBRKT]
//auditRequest = (AuditValueToken / AuditCapToken) EQUAL termIDList LBRKT auditDescriptor RBRKT
//auditReply = (AuditValueToken / AuditCapToken) (contextTerminationAudit / auditOther)
//auditOther = EQUAL termIDList [LBRKT terminationAudit RBRKT]
//terminationAudit = auditReturnParameter *(COMMA auditReturnParameter)
//contextTerminationAudit = EQUAL CtxToken (terminationIDList / LBRKT errorDescriptor RBRKT)
//auditReturnParameter = (mediaDescriptor / modemDescriptor / muxDescriptor /
//  eventsDescriptor / signalsDescriptor /
//  digitMapDescriptor / observedEventsDescriptor /
//  eventBufferDescriptor / statisticsDescriptor /
//  packagesDescriptor / errorDescriptor /
//  auditReturnItem)
//auditReturnItem = (MuxToken / ModemToken / MediaToken /
//  DigitMapToken / StatsToken / ObservedEventsToken /
//  PackagesToken)
//auditDescriptor = AuditToken LBRKT [auditItem *(COMMA auditItem)] RBRKT
//notifyRequest = NotifyToken EQUAL termIDList LBRKT
//  (observedEventsDescriptor [COMMA errorDescriptor]) RBRKT
//notifyReply = NotifyToken EQUAL termIDList [LBRKT errorDescriptor RBRKT]
//serviceChangeRequest = ServiceChangeToken EQUAL termIDList LBRKT
//  serviceChangeDescriptor RBRKT
//serviceChangeReply = ServiceChangeToken EQUAL termIDList [LBRKT
//  (errorDescriptor / serviceChangeReplyDescriptor) RBRKT]
//errorDescriptor = ErrorToken EQUAL ErrorCode LBRKT [quotedString] RBRKT
//ErrorCode = 1*4(DIGIT) ; could be extended
//TransactionID = UINT32
//mId = ((domainAddress / domainName) [":" portNumber]) /
//  mtpAddress / deviceName
//
//; ABNF allows two or more consecutive "." although it is meaningless
//; in a domain name.
//domainName = "<" (ALPHA / DIGIT) *63(ALPHA / DIGIT / "-" / ".") ">"
//deviceName = pathNAME
//
//;The values 0x0, 0xFFFFFFFE and 0xFFFFFFFF are reserved.
//;'-' is used for NULL context. '*' is ALL. '$' is CHOOSE.
//ContextID = (UINT32 / "*" / "-" / "$")
//domainAddress = "[" (IPv4address / IPv6address) "]"
//
//;RFC 2373 contains the definition of IPv6 addresses.
//IPv6address = hexpart [":" IPv4address]
//IPv4address = V4hex DOT V4hex DOT V4hex DOT V4hex
//V4hex = 1*3(DIGIT) ; "0".."255"
//
//; this production, while occurring in RFC 2373, is not referenced
//; IPv6prefix = hexpart SLASH 1*2DIGIT
//hexpart = hexseq "::" [hexseq] / "::" [hexseq] / hexseq
//hexseq = hex4 *(":" hex4)
//hex4 = 1*4HEXDIG
//portNumber = UINT16
//
//; Addressing structure of mtpAddress:
//; 25 - 15 0
//; | PC | NI |
//; 24 - 14 bits 2 bits
//; NOTE : 14 bits are defined for international use.
//; Two national options exist where the point code is 16 or 24 bits.
//; To octet align the mtpAddress the MSBs shall be encoded as 0s.
//; An octet shall be represented by 2 hex digits.
//; LDT: fixed 6/7/2011: original: mtpAddress = MTPToken LBRKT 4*8(HEXDIG) RBRKT
//mtpAddress = MTPToken LBRKT 4*8(HEXDIG) LWSP "}"
//termIDList = (TerminationID / LSBRKT TerminationID 1*(COMMA TerminationID) RSBRKT)
//terminationIDList = LBRKT TerminationID *(COMMA TerminationID) RBRKT
//
//; Total length of pathNAME must not exceed 64 chars.
//pathNAME = ["*"] NAME *("/" / "*"/ ALPHA / DIGIT /"_" / "$") ["@" pathDomainName]
//
//; ABNF allows two or more consecutive "." although it is meaningless
//; in a path domain name.
//pathDomainName = (ALPHA / DIGIT / "*") *63(ALPHA / DIGIT / "-" / "*" / ".")
//
//; '*' is ALL. '$' is CHOOSE.
//; LDT 07/19/07: "ROOT" is also a pathNAME and is not otherwise distinguished
//;                The ambiguity cannot be resolved with FSD and rearrangement of the order.
//;TerminationID = "ROOT" / pathNAME / "$" / "*"
//TerminationID = pathNAME / "$" / "*"
//mediaDescriptor = MediaToken LBRKT mediaParm *(COMMA mediaParm) RBRKT
//
//; at-most one terminationStateDescriptor
//; and either streamParm(s) or streamDescriptor(s) but not both
//mediaParm = (streamParm / streamDescriptor / terminationStateDescriptor)
//
//; at-most-once per item
//streamParm = (localDescriptor / remoteDescriptor / localControlDescriptor / statisticsDescriptor)
//streamDescriptor = StreamToken EQUAL StreamID LBRKT streamParm *(COMMA streamParm) RBRKT
//localControlDescriptor = LocalControlToken LBRKT localParm *(COMMA localParm) RBRKT
//
//; at-most-once per item except for propertyParm
//localParm = (streamMode / propertyParm / reservedValueMode / reservedGroupMode)
//reservedValueMode = ReservedValueToken EQUAL ("ON" / "OFF")
//reservedGroupMode = ReservedGroupToken EQUAL ("ON" / "OFF")
//streamMode = ModeToken EQUAL streamModes
//streamModes = (SendonlyToken / RecvonlyToken / SendrecvToken / InactiveToken / LoopbackToken)
//propertyParm = pkgdName parmValue
//
//; the (Safe)Char '$' means CHOOSE
//; the (Safe)Char '*' means ALL
//parmValue = (EQUAL alternativeValue / INEQUAL VALUE)
//alternativeValue = (VALUE
//  / LSBRKT VALUE *(COMMA VALUE) RSBRKT
//  ; sublist (i.e., A AND B AND ...)
//  / LBRKT VALUE *(COMMA VALUE) RBRKT
//  ; alternatives (i.e., A OR B OR ...)
//  / LSBRKT VALUE COLON VALUE RSBRKT)
//  ; range
//INEQUAL = LWSP (">" / "<" / "#") LWSP ; '#' means "not equal"
//LSBRKT = LWSP "[" LWSP
//RSBRKT = LWSP "]" LWSP
//
//; NOTE : The octet zero is not among the permitted characters in octet
//; string. As the current definition is limited to SDP, and a zero octet
//; would not be a legal character in SDP, this is not a concern.
//localDescriptor = LocalToken LBRKT octetString RBRKT
//remoteDescriptor = RemoteToken LBRKT octetString RBRKT
//eventBufferDescriptor = EventBufferToken [LBRKT eventSpec *(COMMA eventSpec) RBRKT]
//eventSpec = pkgdName [LBRKT eventSpecParameter *(COMMA eventSpecParameter) RBRKT]
//eventSpecParameter = (eventStream / eventOther)
//eventBufferControl = BufferToken EQUAL eventBufferControlValue
//eventBufferControlValue = ("OFF" / LockStepToken)
//terminationStateDescriptor = TerminationStateToken LBRKT terminationStateParm
//  *(COMMA terminationStateParm) RBRKT
//
//; at-most-once per item except for propertyParm
//terminationStateParm = (propertyParm / serviceStates / eventBufferControl)
//serviceStates = ServiceStatesToken EQUAL serviceStatesValue
//serviceStatesValue = (TestToken / OutOfSvcToken / InSvcToken)
//muxDescriptor = MuxToken EQUAL MuxType terminationIDList
//MuxType = (H221Token / H223Token / H226Token / V76Token / extensionParameter / Nx64kToken)
//StreamID = UINT16
//pkgdName = (PackageName SLASH ItemID) ;specific item
//  / (PackageName SLASH "*") ;all items in package
//  / ("*" SLASH "*") ; all items supported by the MG
//PackageName = NAME
//ItemID = NAME
//eventsDescriptor = EventsToken [EQUAL RequestID LBRKT requestedEvent
//  *(COMMA requestedEvent) RBRKT]
//requestedEvent = pkgdName [LBRKT eventParameter *(COMMA eventParameter) RBRKT]
//notifyRegulated = NotifyRegulatedToken [LBRKT (embedWithSig/ embedNoSig) RBRKT]
//notifyBehaviour = NeverNotifyToken / NotifyImmediateToken / notifyRegulated
//
//; at-most-once each of KeepActiveToken, notifyBehaviour,eventDM,
//; ResetEventsDescriptor and eventStream
//; at most one of either embedWithSig or embedNoSig but not both
//; KeepActiveToken and embedWithSig must not both be present
//eventParameter = (embedWithSig / embedNoSig / KeepActiveToken /
//  eventDM / eventStream / eventOther /
//  notifyBehaviour / ResetEventsDescriptorToken)
//embedWithSig = EmbedToken LBRKT signalsDescriptor [COMMA embedFirst] RBRKT
//embedNoSig = EmbedToken LBRKT embedFirst RBRKT
//
//; at-most-once of each
//embedFirst = EventsToken [EQUAL RequestID LBRKT
//  secondRequestedEvent *(COMMA secondRequestedEvent) RBRKT]
//secondRequestedEvent = pkgdName [LBRKT secondEventParameter *(COMMA
//  secondEventParameter) RBRKT]
//
//; at-most-once each of embedSig, KeepActiveToken, notifyBehaviour,eventDM
//; ResetEventsDescriptor or eventStream
//; KeepActiveToken and embedSig must not both be present
//secondEventParameter = (embedSig / KeepActiveToken / eventDM /
//  eventStream / eventOther / notifyBehaviour /
//  ResetEventsDescriptorToken)
//embedSig = EmbedToken LBRKT signalsDescriptor RBRKT
//eventStream = StreamToken EQUAL StreamID
//eventOther = eventParameterName parmValue
//eventParameterName = NAME
//eventDM = DigitMapToken EQUAL ((digitMapName) / (LBRKT digitMapValue RBRKT))
//signalsDescriptor = SignalsToken [LBRKT signalParm *(COMMA signalParm) RBRKT]
//signalParm = signalList / signalRequest
//signalRequest = signalName [LBRKT sigParameter *(COMMA sigParameter) RBRKT]
//signalList = SignalListToken EQUAL signalListId LBRKT
//  signalListParm *(COMMA signalListParm) RBRKT
//signalListId = UINT16
//
//;exactly once signalType, at most once duration and every signal
//;parameter
//signalListParm = signalRequest
//signalName = pkgdName
//
//;at-most-once sigStream, at-most-once sigSignalType,
//;at-most-once sigDuration, at-most-once sigDirection,
//;at-most-once sigRequestID, at-most-once sigIntsigDelay
//;every signalParameterName at most once
//sigParameter = sigStream / sigSignalType / sigDuration / sigOther /
//  notifyCompletion / KeepActiveToken /
//  sigDirection / sigRequestID / sigIntsigDelay
//sigStream = StreamToken EQUAL StreamID
//sigOther = sigParameterName parmValue
//sigParameterName = NAME
//sigSignalType = SignalTypeToken EQUAL signalType
//signalType = (OnOffToken / TimeOutToken / BriefToken)
//sigDuration = DurationToken EQUAL UINT16
//sigDirection = DirectionToken EQUAL direction
//direction = ExternalToken / InternalToken / BothToken
//sigRequestID = RequestIDToken EQUAL RequestID
//sigIntsigDelay = IntsigDelayToken EQUAL UINT16
//notifyCompletion = NotifyCompletionToken EQUAL (LBRKT
//  notificationReason *(COMMA notificationReason) RBRKT)
//notificationReason = TimeOutToken / InterruptByEventToken /
//  InterruptByNewSignalsDescrToken / OtherReasonToken /
//  IterationToken
//observedEventsDescriptor = ObservedEventsToken EQUAL RequestID LBRKT
//  observedEvent *(COMMA observedEvent) RBRKT
//
//; time per event, because it might be buffered
//observedEvent = [TimeStamp LWSP COLON] LWSP pkgdName [LBRKT
//  observedEventParameter *(COMMA
//  observedEventParameter) RBRKT]
//
//; at-most-once eventStream, every eventParameterName at most once
//observedEventParameter = eventStream / eventOther
//
//; For an AuditCapReply with all events, the RequestID should be ALL.
//RequestID = UINT32 / "*"
//modemDescriptor = ModemToken ((EQUAL modemType) / (LSBRKT modemType
//  *(COMMA modemType) RSBRKT)) [LBRKT propertyParm
//  *(COMMA propertyParm) RBRKT]
//
//; at-most-once except for extensionParameter
//modemType = V32bisToken / V22bisToken / V18Token / V22Token /
//  V32Token / V34Token / V90Token / V91Token /
//  SynchISDNToken / extensionParameter
//digitMapDescriptor = DigitMapToken EQUAL ((LBRKT digitMapValue RBRKT) /
//  (digitMapName [LBRKT digitMapValue RBRKT]))
//digitMapName = NAME
//digitMapValue = ["T" COLON Timer COMMA] ["S" COLON Timer COMMA] ["L"
//  COLON Timer COMMA] ["Z" COLON Timer COMMA] digitMap
//Timer = 1*2DIGIT
//
//; Units are seconds for T, S, and L timers, and hundreds of
//; milliseconds for Z timer. Thus T, S, and L range from 1 to 99
//; seconds and Z from 100 ms to 9.9 s
//digitMap = (digitString / LWSP "(" LWSP digitStringList LWSP ")" LWSP)
//digitStringList = digitString *(LWSP "|" LWSP digitString)
//digitString = 1*(digitStringElement)
//digitStringElement = digitPosition [DOT]
//digitPosition = digitMapLetter / digitMapRange
//digitMapRange = ("x" / (LWSP "[" LWSP digitLetter LWSP "]" LWSP))
//digitLetter = *((DIGIT "-" DIGIT) / digitMapLetter)
//digitMapLetter = DIGIT ;Basic event symbols
//  / %x41-4B / %x61-6B ; a-k, A-K
//  / "L" / "S" / "T" ;Inter-event timers
//  ; (long, short, start)
//  / "Z" ;Long duration modifier
//
//; at-most-once, and DigitMapToken and PackagesToken are not allowed
//; in AuditCapabilities command
//auditItem = auditReturnItem / SignalsToken / EventBufferToken /
//  EventsToken / indAudterminationAudit
//indAudterminationAudit = indAudauditReturnParameter *(COMMA indAudauditReturnParameter)
//indAudauditReturnParameter = indAudmediaDescriptor / indAudeventsDescriptor /
//  indAudsignalsDescriptor /
//  indAuddigitMapDescriptor /
//  indAudeventBufferDescriptor /
//  indAudstatisticsDescriptor /
//  indAudpackagesDescriptor
//indAudmediaDescriptor = MediaToken LBRKT indAudmediaParm *(COMMA
//  indAudmediaParm) RBRKT
//
//; either streamParm or streamDescriptor but not both
//indAudmediaParm = indAudstreamParm / indAudstreamDescriptor /
//  indAudterminationStateDescriptor
//
//; at-most-once
//indAudstreamParm = (indAudlocalControlDescriptor /
//  indAudstatisticsDescriptor /
//  indAudremoteDescriptor / indAudlocalDescriptor )
//indAudremoteDescriptor = RemoteToken LBRKT octetString RBRKT
//indAudlocalDescriptor = LocalToken LBRKT octetString RBRKT
//indAudstreamDescriptor = StreamToken EQUAL StreamID LBRKT indAudstreamParm RBRKT
//indAudlocalControlDescriptor = LocalControlToken LBRKT indAudlocalParm
//  *(COMMA indAudlocalParm) RBRKT
//
//; at-most-once per item
//indAudlocalParm = ModeToken [(EQUAL/INEQUAL) streamModes]/ pkgdName /
//  propertyParm / ReservedValueToken /
//  ReservedGroupToken
//
//; propertyparm and streamModes are used only to specify audit selection
//; criteria. AND/OR selection logic is specified at context level.
//
//indAudterminationStateDescriptor = TerminationStateToken LBRKT
//  indAudterminationStateParm RBRKT
//
//; at-most-once per item
//indAudterminationStateParm = pkgdName / propertyParm / ServiceStatesToken
//  [(EQUAL/INEQUAL) serviceStatesValue ] / BufferToken
//
//; When values are included a Select operation is implied.
//; AND/OR logic is specified at context level.
//indAudeventBufferDescriptor = EventBufferToken LBRKT indAudeventSpec RBRKT
//indAudeventSpec = pkgdName [LBRKT indAudeventSpecParameter RBRKT]
//indAudeventSpecParameter= eventStream / eventParameterName
//indAudeventsDescriptor = EventsToken [EQUAL RequestID] LBRKT indAudrequestedEvent RBRKT
//indAudrequestedEvent = pkgdName
//indAudsignalsDescriptor = SignalsToken LBRKT [indAudsignalParm] RBRKT
//indAudsignalParm = indAudsignalList / indAudsignalRequest
//indAudsignalRequest = signalName [LBRKT indAudsignalRequestParm
//  *(COMMA indAudsignalRequestParm) RBRKT]
//indAudsignalRequestParm = sigStream / sigRequestID
//indAudsignalList = SignalListToken EQUAL signalListId [LBRKT
//  indAudsignalListParm RBRKT]
//indAudsignalListParm = indAudsignalRequest
//indAuddigitMapDescriptor= DigitMapToken EQUAL (digitMapName)
//indAudstatisticsDescriptor = StatsToken LBRKT pkgdName RBRKT
//indAudpackagesDescriptor= PackagesToken LBRKT packagesItem RBRKT
//serviceChangeDescriptor = ServicesToken LBRKT serviceChangeParm *(COMMA
//  serviceChangeParm) RBRKT
//
//; each parameter at-most-once, except auditItem
//; at most one of either serviceChangeAddress or serviceChangeMgcId but
//; not both
//; serviceChangeMethod and serviceChangeReason are REQUIRED
//serviceChangeParm = serviceChangeMethod / serviceChangeReason /
//  serviceChangeDelay / serviceChangeAddress /
//  serviceChangeProfile / extension / TimeStamp /
//  serviceChangeMgcId / serviceChangeVersion /
//  ServiceChangeIncompleteToken / auditItem
//serviceChangeReplyDescriptor = ServicesToken LBRKT servChgReplyParm *(COMMA
//  servChgReplyParm) RBRKT
//
//; at-most-once. Version is REQUIRED on first ServiceChange response
//; at most one of either serviceChangeAddress or serviceChangeMgcId but
//; not both
//
//servChgReplyParm = serviceChangeAddress / serviceChangeMgcId /
//  serviceChangeProfile / serviceChangeVersion / TimeStamp
//serviceChangeMethod = MethodToken EQUAL (FailoverToken / ForcedToken /
//  GracefulToken / RestartToken / DisconnectedToken /
//  HandOffToken / extensionParameter)
//
//; A serviceChangeReason consists of a numeric reason code
//; and an optional text description.
//; A serviceChangeReason must be encoded using the quotedString
//; form of VALUE.
//; The quotedString shall contain a decimal reason code,
//; optionally followed by a single space character and a
//; textual description string.
//serviceChangeReason = ReasonToken EQUAL VALUE
//serviceChangeDelay = DelayToken EQUAL UINT32
//serviceChangeAddress = ServiceChangeAddressToken EQUAL (mId / portNumber)
//serviceChangeMgcId = MgcIdToken EQUAL mId
//serviceChangeProfile = ProfileToken EQUAL NAME SLASH Version
//serviceChangeVersion = VersionToken EQUAL Version
//extension = extensionParameter parmValue
//packagesDescriptor = PackagesToken LBRKT packagesItem *(COMMA packagesItem) RBRKT
//Version = 1*2(DIGIT)
//packagesItem = NAME "-" UINT16
//TimeStamp = Date "T" Time ; per ISO 8601:2004
//
//; Date = yyyymmdd
//Date = 8(DIGIT)
//
//; Time = hhmmssss
//Time = 8(DIGIT)
//statisticsDescriptor = StatsToken LBRKT statisticsParameter *(COMMA
//  statisticsParameter) RBRKT
//
//;at-most-once per item
//statisticsParameter = pkgdName [EQUAL VALUE /
//  (LSBRKT VALUE *(COMMA VALUE) RSBRKT)]
//topologyDescriptor = TopologyToken LBRKT topologyTriple *(COMMA
//  topologyTriple) RBRKT
//topologyTriple = terminationA COMMA terminationB COMMA
//  topologyDirection [COMMA eventStream]
//terminationA = TerminationID
//terminationB = TerminationID
//topologyDirection = BothwayToken / IsolateToken / OnewayToken /
//  OnewayExternalToken / OnewayBothToken
//
//priority = PriorityToken EQUAL UINT16
//iepsValue = IEPSToken EQUAL ("ON" / "OFF")
//emergencyValue = EmergencyValueToken EQUAL (EmergencyToken / EmergencyOffToken)
//contextAttrDescriptor = ContextAttrToken LBRKT (contextIdList /
//  propertyParm *(COMMA propertyParm)) RBRKT
//
//; When using the contextIdList construct, the ContextID in the
//; actionReply construct shall be the same as the ContextID in the
//; associated actionRequest
//contextIdList = ContextListToken EQUAL LBRKT ContextID *(COMMA ContextID) RBRKT
//extensionParameter = "X" ("-" / "+") 1*6(ALPHA / DIGIT)
//
//; octetString is used to describe SDP defined in RFC 2327.
//; Caution should be taken if CRLF in RFC 2327 is used.
//; To be safe, use EOL in this ABNF.
//; Whenever "}" appears in SDP, it is escaped by "\", e.g., "\}"
//octetString = *(nonEscapeChar)
//nonEscapeChar = ("\}" / %x01-7C / %x7E-FF)
//
//; NOTE : The double-quote character is not allowed in quotedString.
//quotedString = DQUOTE *(SafeChar / EOL / %x80-FF / RestChar / WSP) DQUOTE
//UINT16 = 1*5(DIGIT) ; %x0-FFFF
//UINT32 = 1*10(DIGIT) ; %x0-FFFFFFFF
//NAME = ALPHA *63(ALPHA / DIGIT / "_")
//VALUE = quotedString / 1*(SafeChar / %x80-FF)
//SafeChar = DIGIT / ALPHA / "+" / "-" / "&" /
//  "!" / "_" / "/" / "'" / "?" / "@" /
//  "^" / "`" / "~" / "*" / "$" / "\" /
//  "(" / ")" / "%" / "|" / "."
//EQUAL = LWSP %x3D LWSP ; "="
//COLON = %x3A ; ":"
//LBRKT = LWSP %x7B LWSP ; "{"
//RBRKT = LWSP %x7D LWSP ; "}"
//COMMA = LWSP %x2C LWSP ; ","
//DOT = %x2E ; "."
//SLASH = %x2F ; "/"
//ALPHA = %x41-5A / %x61-7A ; A-Z / a-z
//DIGIT = %x30-39 ; 0-9
//DQUOTE = %x22 ; " (Double Quote)
//HEXDIG = DIGIT / "A" / "B" / "C" / "D" / "E" / "F"
//SP = %x20 ; space
//HTAB = %x09 ; horizontal tab
//CR = %x0D ; Carriage return
//LF = %x0A ; linefeed
//LWSP = *(WSP / COMMENT / EOL)
//EOL = (CR [LF] / LF)
//WSP = SP / HTAB ; white space
//SEP = (WSP / EOL / COMMENT) LWSP
//COMMENT = ";" *(SafeChar/ RestChar / WSP / %x22) EOL
//RestChar = ";" / "[" / "]" / "{" / "}" / ":" / "," / "#" / "<" / ">" / "="
//
//; New Tokens added to sigParameter must take the format of SPA*
//; * may be of any form i.e., SPAM
//; New Tokens added to eventParameter must take the form of EPA*
//; * may be of any form i.e., EPAD
//AddToken = ("Add" / "A")
//AndAUDITSelectToken = ("ANDLgc")
//AuditToken = ("Audit" / "AT")
//AuditCapToken = ("AuditCapability" / "AC")
//AuditValueToken = ("AuditValue" / "AV")
//AuthToken = ("Authentication" / "AU")
//BothToken = ("Both" / "B")
//BothwayToken = ("Bothway" / "BW")
//BriefToken = ("Brief" / "BR")
//BufferToken = ("Buffer" / "BF")
//CtxToken = ("Context" / "C")
//ContextAuditToken = ("ContextAudit" / "CA")
//ContextAttrToken = ("ContextAttr" / "CT")
//ContextListToken = ("ContextList" / "CLT")
//DigitMapToken = ("DigitMap" / "DM")
//DirectionToken = ("SPADirection" / "SPADI")
//DisconnectedToken = ("Disconnected" / "DC")
//DelayToken = ("Delay" / "DL")
//DurationToken = ("Duration" / "DR")
//EmbedToken = ("Embed" / "EM")
//EmergencyToken = ("Emergency" / "EG")
//EmergencyOffToken = ("EmergencyOff" / "EGO")
//EmergencyValueToken = ("EmergencyValue" / "EGV")
//ErrorToken = ("Error" / "ER")
//EventBufferToken = ("EventBuffer" / "EB")
//EventsToken = ("Events" / "E")
//ExternalToken = ("External" / "EX")
//FailoverToken = ("Failover" / "FL")
//ForcedToken = ("Forced" / "FO")
//GracefulToken = ("Graceful" / "GR")
//H221Token = ("H221")
//H223Token = ("H223")
//H226Token = ("H226")
//HandOffToken = ("HandOff" / "HO")
//IEPSToken = ("IEPSCall" / "IEPS")
//ImmAckRequiredToken = ("ImmAckRequired" / "IA")
//InactiveToken = ("Inactive" / "IN")
//InternalToken = ("Internal" / "IT")
//IntsigDelayToken = ("Intersignal" / "SPAIS")
//IsolateToken = ("Isolate" / "IS")
//InSvcToken = ("InService" / "IV")
//InterruptByEventToken = ("IntByEvent" / "IBE")
//InterruptByNewSignalsDescrToken = ("IntBySigDescr" / "IBS")
//IterationToken = ("Iteration" / "IR")
//KeepActiveToken = ("KeepActive" / "KA")
//LocalToken = ("Local" / "L")
//LocalControlToken = ("LocalControl" / "O")
//LockStepToken = ("LockStep" / "SP")
//LoopbackToken = ("Loopback" / "LB")
//MediaToken = ("Media" / "M")
//MegacopToken = ("MEGACO" / "!")
//MessageSegmentToken = ("Segment" / "SM")
//MethodToken = ("Method" / "MT")
//MgcIdToken = ("MgcIdToTry" / "MG")
//ModeToken = ("Mode" / "MO")
//ModifyToken = ("Modify" / "MF")
//ModemToken = ("Modem" / "MD")
//MoveToken = ("Move" / "MV")
//MTPToken = ("MTP")
//MuxToken = ("Mux" / "MX")
//NeverNotifyToken = ("NeverNotify" / "NBNN")
//NotifyToken = ("Notify" / "N")
//NotifyCompletionToken = ("NotifyCompletion" / "NC")
//NotifyImmediateToken = ("ImmediateNotify" / "NBIN")
//NotifyRegulatedToken = ("RegulatedNotify" / "NBRN")
//Nx64kToken = ("Nx64Kservice" / "N64")
//ObservedEventsToken = ("ObservedEvents" / "OE")
//OnewayToken = ("Oneway" / "OW")
//OnewayBothToken = ("OnewayBoth" / "OWB")
//OnewayExternalToken = ("OnewayExternal" / "OWE")
//OnOffToken = ("OnOff" / "OO")
//OrAUDITselectToken = ("ORLgc")
//OtherReasonToken = ("OtherReason" / "OR")
//OutOfSvcToken = ("OutOfService" / "OS")
//PackagesToken = ("Packages" / "PG")
//PendingToken = ("Pending" / "PN")
//PriorityToken = ("Priority" / "PR")
//ProfileToken = ("Profile" / "PF")
//ReasonToken = ("Reason" / "RE")
//RecvonlyToken = ("ReceiveOnly" / "RC")
//ReplyToken = ("Reply" / "P")
//ResetEventsDescriptorToken = ("ResetEventsDescriptor" / "RSE")
//RestartToken = ("Restart" / "RS")
//RemoteToken = ("Remote" / "R")
//RequestIDToken = ("SPARequestID" / "SPARQ")
//ReservedGroupToken = ("ReservedGroup" / "RG")
//ReservedValueToken = ("ReservedValue" / "RV")
//SegmentationCompleteToken = ("END" / "&")
//SendonlyToken = ("SendOnly" / "SO")
//SendrecvToken = ("SendReceive" / "SR")
//ServicesToken = ("Services" / "SV")
//ServiceStatesToken = ("ServiceStates" / "SI")
//ServiceChangeIncompleteToken = ("ServiceChangeInc" / "SIC")
//ServiceChangeToken = ("ServiceChange" / "SC")
//ServiceChangeAddressToken = ("ServiceChangeAddress" / "AD")
//SignalListToken = ("SignalList" / "SL")
//SignalsToken = ("Signals" / "SG")
//SignalTypeToken = ("SignalType" / "SY")
//StatsToken = ("Statistics" / "SA")
//StreamToken = ("Stream" / "ST")
//SubtractToken = ("Subtract" / "S")
//SynchISDNToken = ("SynchISDN" / "SN")
//TerminationStateToken = ("TerminationState" / "TS")
//TestToken = ("Test" / "TE")
//TimeOutToken = ("TimeOut" / "TO")
//TopologyToken = ("Topology" / "TP")
//TransToken = ("Transaction" / "T")
//ResponseAckToken = ("TransactionResponseAck" / "K")
//V18Token = ("V18")
//V22Token = ("V22")
//V22bisToken = ("V22b")
//V32Token = ("V32")
//V32bisToken = ("V32b")
//V34Token = ("V34")
//V76Token = ("V76")
//V90Token = ("V90")
//V91Token = ("V91")
//VersionToken = ("Version" / "V")
////**** SABNF GRAMMAR ***

