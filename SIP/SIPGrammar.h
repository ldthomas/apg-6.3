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
#ifndef SIPGRAMMAR_H
#define SIPGRAMMAR_H

// rule ids
#define RULE_SIPGRAMMAR_ABS_PATH 53 // abs-path
#define RULE_SIPGRAMMAR_ABSOLUTEURI 50 // absoluteURI
#define RULE_SIPGRAMMAR_ACCEPT 70 // Accept
#define RULE_SIPGRAMMAR_ACCEPT_ENCODING 77 // Accept-Encoding
#define RULE_SIPGRAMMAR_ACCEPT_LANGUAGE 81 // Accept-Language
#define RULE_SIPGRAMMAR_ACCEPT_PARAM 73 // accept-param
#define RULE_SIPGRAMMAR_ACCEPT_RANGE 71 // accept-range
#define RULE_SIPGRAMMAR_ACKM 6 // ACKm
#define RULE_SIPGRAMMAR_ADDR_SPEC 119 // addr-spec
#define RULE_SIPGRAMMAR_AINFO 107 // ainfo
#define RULE_SIPGRAMMAR_ALERT_INFO 84 // Alert-Info
#define RULE_SIPGRAMMAR_ALERT_PARAM 85 // alert-param
#define RULE_SIPGRAMMAR_ALGORITHM 187 // algorithm
#define RULE_SIPGRAMMAR_ALLOW 86 // Allow
#define RULE_SIPGRAMMAR_ALPHA 303 // ALPHA
#define RULE_SIPGRAMMAR_ALPHANUM 269 // alphanum
#define RULE_SIPGRAMMAR_AREA_SPECIFIER 247 // area-specifier
#define RULE_SIPGRAMMAR_AUTH_PARAM 102 // auth-param
#define RULE_SIPGRAMMAR_AUTH_PARAM_NAME 103 // auth-param-name
#define RULE_SIPGRAMMAR_AUTH_SCHEME 105 // auth-scheme
#define RULE_SIPGRAMMAR_AUTHENTICATION_INFO 106 // Authentication-Info
#define RULE_SIPGRAMMAR_AUTHORITY 62 // authority
#define RULE_SIPGRAMMAR_AUTHORIZATION 87 // Authorization
#define RULE_SIPGRAMMAR_BASE_PHONE_NUMBER 243 // base-phone-number
#define RULE_SIPGRAMMAR_BLANKSPACE 1 // BlankSpace
#define RULE_SIPGRAMMAR_BYEM 8 // BYEm
#define RULE_SIPGRAMMAR_C_P_EXPIRES 124 // c-p-expires
#define RULE_SIPGRAMMAR_C_P_Q 123 // c-p-q
#define RULE_SIPGRAMMAR_CALL_ID 111 // Call-ID
#define RULE_SIPGRAMMAR_CALL_INFO 113 // Call-Info
#define RULE_SIPGRAMMAR_CALLID 112 // callid
#define RULE_SIPGRAMMAR_CANCELM 9 // CANCELm
#define RULE_SIPGRAMMAR_CHALLENGE 176 // challenge
#define RULE_SIPGRAMMAR_CHAR 304 // CHAR
#define RULE_SIPGRAMMAR_CNONCE 96 // cnonce
#define RULE_SIPGRAMMAR_CNONCE_VALUE 97 // cnonce-value
#define RULE_SIPGRAMMAR_CODINGS 79 // codings
#define RULE_SIPGRAMMAR_COLON 291 // COLON
#define RULE_SIPGRAMMAR_COMMA 289 // COMMA
#define RULE_SIPGRAMMAR_COMMENT 294 // comment
#define RULE_SIPGRAMMAR_COMPOSITE_TYPE 143 // composite-type
#define RULE_SIPGRAMMAR_CONTACT 116 // Contact
#define RULE_SIPGRAMMAR_CONTACT_EXTENSION 125 // contact-extension
#define RULE_SIPGRAMMAR_CONTACT_PARAM 117 // contact-param
#define RULE_SIPGRAMMAR_CONTACT_PARAMS 122 // contact-params
#define RULE_SIPGRAMMAR_CONTENT_CODING 80 // content-coding
#define RULE_SIPGRAMMAR_CONTENT_DISPOSITION 127 // Content-Disposition
#define RULE_SIPGRAMMAR_CONTENT_ENCODING 133 // Content-Encoding
#define RULE_SIPGRAMMAR_CONTENT_LANGUAGE 134 // Content-Language
#define RULE_SIPGRAMMAR_CONTENT_LENGTH 138 // Content-Length
#define RULE_SIPGRAMMAR_CONTENT_TYPE 139 // Content-Type
#define RULE_SIPGRAMMAR_CR 305 // CR
#define RULE_SIPGRAMMAR_CREDENTIALS 88 // credentials
#define RULE_SIPGRAMMAR_CRLF 306 // CRLF
#define RULE_SIPGRAMMAR_CSEQ 152 // CSeq
#define RULE_SIPGRAMMAR_CTEXT 295 // ctext
#define RULE_SIPGRAMMAR_D_NAME 121 // d-name
#define RULE_SIPGRAMMAR_DATE 153 // Date
#define RULE_SIPGRAMMAR_DATE1 156 // date1
#define RULE_SIPGRAMMAR_DELAY 211 // delay
#define RULE_SIPGRAMMAR_DELTA_SECONDS 126 // delta-seconds
#define RULE_SIPGRAMMAR_DIG_RESP 90 // dig-resp
#define RULE_SIPGRAMMAR_DIGEST_CLN 178 // digest-cln
#define RULE_SIPGRAMMAR_DIGEST_RESPONSE 89 // digest-response
#define RULE_SIPGRAMMAR_DIGEST_URI 93 // digest-uri
#define RULE_SIPGRAMMAR_DIGEST_URI_VALUE 94 // digest-uri-value
#define RULE_SIPGRAMMAR_DIGIT 307 // DIGIT
#define RULE_SIPGRAMMAR_DISCRETE_TYPE 142 // discrete-type
#define RULE_SIPGRAMMAR_DISP_EXTENSION_TOKEN 132 // disp-extension-token
#define RULE_SIPGRAMMAR_DISP_PARAM 129 // disp-param
#define RULE_SIPGRAMMAR_DISP_TYPE 128 // disp-type
#define RULE_SIPGRAMMAR_DISPLAY_NAME 120 // display-name
#define RULE_SIPGRAMMAR_DOMAIN 181 // domain
#define RULE_SIPGRAMMAR_DOMAINLABEL 26 // domainlabel
#define RULE_SIPGRAMMAR_DQUOTE 308 // DQUOTE
#define RULE_SIPGRAMMAR_DRESPONSE 100 // dresponse
#define RULE_SIPGRAMMAR_DTMF_DIGIT 265 // dtmf-digit
#define RULE_SIPGRAMMAR_ENCODING 78 // encoding
#define RULE_SIPGRAMMAR_EQUAL 284 // EQUAL
#define RULE_SIPGRAMMAR_ERROR_INFO 160 // Error-Info
#define RULE_SIPGRAMMAR_ERROR_URI 161 // error-uri
#define RULE_SIPGRAMMAR_ESCAPED 273 // escaped
#define RULE_SIPGRAMMAR_EXPIRES 162 // Expires
#define RULE_SIPGRAMMAR_EXTENSION_HEADER 237 // extension-header
#define RULE_SIPGRAMMAR_EXTENSION_METHOD 12 // extension-method
#define RULE_SIPGRAMMAR_EXTENSION_TOKEN 144 // extension-token
#define RULE_SIPGRAMMAR_FROM 163 // From
#define RULE_SIPGRAMMAR_FROM_PARAM 165 // from-param
#define RULE_SIPGRAMMAR_FROM_SPEC 164 // from-spec
#define RULE_SIPGRAMMAR_FUTURE_EXTENSION 257 // future-extension
#define RULE_SIPGRAMMAR_GEN_VALUE 76 // gen-value
#define RULE_SIPGRAMMAR_GENERIC_PARAM 75 // generic-param
#define RULE_SIPGRAMMAR_GLOBAL_NETWORK_PREFIX 251 // global-network-prefix
#define RULE_SIPGRAMMAR_GLOBAL_PHONE_NUMBER 242 // global-phone-number
#define RULE_SIPGRAMMAR_HANDLING_PARAM 130 // handling-param
#define RULE_SIPGRAMMAR_HCOLON 280 // HCOLON
#define RULE_SIPGRAMMAR_HEADER 45 // header
#define RULE_SIPGRAMMAR_HEADER_NAME 238 // header-name
#define RULE_SIPGRAMMAR_HEADER_VALUE 239 // header-value
#define RULE_SIPGRAMMAR_HEADERS 44 // headers
#define RULE_SIPGRAMMAR_HEXDIG 309 // HEXDIG
#define RULE_SIPGRAMMAR_HIER_PART 51 // hier-part
#define RULE_SIPGRAMMAR_HNAME 46 // hname
#define RULE_SIPGRAMMAR_HNV_UNRESERVED 48 // hnv-unreserved
#define RULE_SIPGRAMMAR_HOST 24 // host
#define RULE_SIPGRAMMAR_HOSTNAME 25 // hostname
#define RULE_SIPGRAMMAR_HOSTPORT 23 // hostport
#define RULE_SIPGRAMMAR_HVALUE 47 // hvalue
#define RULE_SIPGRAMMAR_IANA_TOKEN 148 // iana-token
#define RULE_SIPGRAMMAR_IETF_TOKEN 145 // ietf-token
#define RULE_SIPGRAMMAR_IN_REPLY_TO 167 // In-Reply-To
#define RULE_SIPGRAMMAR_INFO 114 // info
#define RULE_SIPGRAMMAR_INFO_PARAM 115 // info-param
#define RULE_SIPGRAMMAR_INVITEM 5 // INVITEm
#define RULE_SIPGRAMMAR_IPV4ADDRESS 66 // IPv4address
#define RULE_SIPGRAMMAR_IPV6ADDRESS 68 // IPv6address
#define RULE_SIPGRAMMAR_IPV6REFERENCE 67 // IPv6reference
#define RULE_SIPGRAMMAR_ISDN_SUBADDRESS 245 // isdn-subaddress
#define RULE_SIPGRAMMAR_LANGUAGE 82 // language
#define RULE_SIPGRAMMAR_LANGUAGE_RANGE 83 // language-range
#define RULE_SIPGRAMMAR_LANGUAGE_TAG 135 // language-tag
#define RULE_SIPGRAMMAR_LAQUOT 288 // LAQUOT
#define RULE_SIPGRAMMAR_LDQUOT 292 // LDQUOT
#define RULE_SIPGRAMMAR_LF 310 // LF
#define RULE_SIPGRAMMAR_LHEX 281 // LHEX
#define RULE_SIPGRAMMAR_LOCAL_NETWORK_PREFIX 252 // local-network-prefix
#define RULE_SIPGRAMMAR_LOCAL_PHONE_NUMBER 244 // local-phone-number
#define RULE_SIPGRAMMAR_LPAREN 285 // LPAREN
#define RULE_SIPGRAMMAR_LR_PARAM 38 // lr-param
#define RULE_SIPGRAMMAR_LWS 300 // LWS
#define RULE_SIPGRAMMAR_M_ATTRIBUTE 150 // m-attribute
#define RULE_SIPGRAMMAR_M_PARAMETER 149 // m-parameter
#define RULE_SIPGRAMMAR_M_SUBTYPE 147 // m-subtype
#define RULE_SIPGRAMMAR_M_TYPE 141 // m-type
#define RULE_SIPGRAMMAR_M_VALUE 151 // m-value
#define RULE_SIPGRAMMAR_MADDR_PARAM 37 // maddr-param
#define RULE_SIPGRAMMAR_MARK 272 // mark
#define RULE_SIPGRAMMAR_MAX_FORWARDS 168 // Max-Forwards
#define RULE_SIPGRAMMAR_MEDIA_RANGE 72 // media-range
#define RULE_SIPGRAMMAR_MEDIA_TYPE 140 // media-type
#define RULE_SIPGRAMMAR_MESSAGE_BODY 240 // message-body
#define RULE_SIPGRAMMAR_MESSAGE_HEADER 69 // message-header
#define RULE_SIPGRAMMAR_MESSAGE_QOP 95 // message-qop
#define RULE_SIPGRAMMAR_METHOD 11 // Method
#define RULE_SIPGRAMMAR_METHOD_PARAM 35 // method-param
#define RULE_SIPGRAMMAR_MIME_VERSION 169 // MIME-Version
#define RULE_SIPGRAMMAR_MIN_EXPIRES 170 // Min-Expires
#define RULE_SIPGRAMMAR_MONTH 159 // month
#define RULE_SIPGRAMMAR_NAME_ADDR 118 // name-addr
#define RULE_SIPGRAMMAR_NC_VALUE 99 // nc-value
#define RULE_SIPGRAMMAR_NET_PATH 52 // net-path
#define RULE_SIPGRAMMAR_NETWORK_PREFIX 250 // network-prefix
#define RULE_SIPGRAMMAR_NEXTNONCE 108 // nextnonce
#define RULE_SIPGRAMMAR_NONCE 183 // nonce
#define RULE_SIPGRAMMAR_NONCE_COUNT 98 // nonce-count
#define RULE_SIPGRAMMAR_NONCE_VALUE 184 // nonce-value
#define RULE_SIPGRAMMAR_OCTET 311 // OCTET
#define RULE_SIPGRAMMAR_ONE_SECOND_PAUSE 263 // one-second-pause
#define RULE_SIPGRAMMAR_OPAQUE 185 // opaque
#define RULE_SIPGRAMMAR_OPAQUE_PART 54 // opaque-part
#define RULE_SIPGRAMMAR_OPTION_TAG 192 // option-tag
#define RULE_SIPGRAMMAR_OPTIONSM 7 // OPTIONSm
#define RULE_SIPGRAMMAR_ORGANIZATION 171 // Organization
#define RULE_SIPGRAMMAR_OTHER_CHALLENGE 177 // other-challenge
#define RULE_SIPGRAMMAR_OTHER_HANDLING 131 // other-handling
#define RULE_SIPGRAMMAR_OTHER_PARAM 39 // other-param
#define RULE_SIPGRAMMAR_OTHER_PRIORITY 174 // other-priority
#define RULE_SIPGRAMMAR_OTHER_RESPONSE 104 // other-response
#define RULE_SIPGRAMMAR_OTHER_TRANSPORT 32 // other-transport
#define RULE_SIPGRAMMAR_OTHER_USER 34 // other-user
#define RULE_SIPGRAMMAR_PARAM 59 // param
#define RULE_SIPGRAMMAR_PARAM_UNRESERVED 43 // param-unreserved
#define RULE_SIPGRAMMAR_PARAMCHAR 42 // paramchar
#define RULE_SIPGRAMMAR_PASSWORD 22 // password
#define RULE_SIPGRAMMAR_PATH_SEGMENTS 57 // path-segments
#define RULE_SIPGRAMMAR_PAUSE_CHARACTER 262 // pause-character
#define RULE_SIPGRAMMAR_PCHAR 60 // pchar
#define RULE_SIPGRAMMAR_PHONE_CONTEXT_IDENT 249 // phone-context-ident
#define RULE_SIPGRAMMAR_PHONE_CONTEXT_TAG 248 // phone-context-tag
#define RULE_SIPGRAMMAR_PHONEDIGIT 260 // phonedigit
#define RULE_SIPGRAMMAR_PNAME 40 // pname
#define RULE_SIPGRAMMAR_PORT 28 // port
#define RULE_SIPGRAMMAR_POST_DIAL 246 // post-dial
#define RULE_SIPGRAMMAR_PRIMARY_TAG 136 // primary-tag
#define RULE_SIPGRAMMAR_PRIORITY 172 // Priority
#define RULE_SIPGRAMMAR_PRIORITY_VALUE 173 // priority-value
#define RULE_SIPGRAMMAR_PRIVATE_PREFIX 253 // private-prefix
#define RULE_SIPGRAMMAR_PRODUCT 206 // product
#define RULE_SIPGRAMMAR_PRODUCT_VERSION 207 // product-version
#define RULE_SIPGRAMMAR_PROTOCOL_NAME 225 // protocol-name
#define RULE_SIPGRAMMAR_PROTOCOL_VERSION 226 // protocol-version
#define RULE_SIPGRAMMAR_PROVIDER_HOSTNAME 256 // provider-hostname
#define RULE_SIPGRAMMAR_PROVIDER_TAG 255 // provider-tag
#define RULE_SIPGRAMMAR_PROXY_AUTHENTICATE 175 // Proxy-Authenticate
#define RULE_SIPGRAMMAR_PROXY_AUTHORIZATION 190 // Proxy-Authorization
#define RULE_SIPGRAMMAR_PROXY_REQUIRE 191 // Proxy-Require
#define RULE_SIPGRAMMAR_PSEUDONYM 235 // pseudonym
#define RULE_SIPGRAMMAR_PVALUE 41 // pvalue
#define RULE_SIPGRAMMAR_Q_STRING 297 // q-string
#define RULE_SIPGRAMMAR_QDTEXT 298 // qdtext
#define RULE_SIPGRAMMAR_QOP_OPTIONS 188 // qop-options
#define RULE_SIPGRAMMAR_QOP_VALUE 189 // qop-value
#define RULE_SIPGRAMMAR_QUERY 65 // query
#define RULE_SIPGRAMMAR_QUOTED_PAIR 299 // quoted-pair
#define RULE_SIPGRAMMAR_QUOTED_STRING 296 // quoted-string
#define RULE_SIPGRAMMAR_QVALUE 74 // qvalue
#define RULE_SIPGRAMMAR_RAQUOT 287 // RAQUOT
#define RULE_SIPGRAMMAR_RDQUOT 293 // RDQUOT
#define RULE_SIPGRAMMAR_REALM 179 // realm
#define RULE_SIPGRAMMAR_REALM_VALUE 180 // realm-value
#define RULE_SIPGRAMMAR_REASON_PHRASE 16 // Reason-Phrase
#define RULE_SIPGRAMMAR_REC_ROUTE 194 // rec-route
#define RULE_SIPGRAMMAR_RECORD_ROUTE 193 // Record-Route
#define RULE_SIPGRAMMAR_REG_NAME 64 // reg-name
#define RULE_SIPGRAMMAR_REGISTERM 10 // REGISTERm
#define RULE_SIPGRAMMAR_REPLY_TO 196 // Reply-To
#define RULE_SIPGRAMMAR_REQUEST 2 // Request
#define RULE_SIPGRAMMAR_REQUEST_DIGEST 101 // request-digest
#define RULE_SIPGRAMMAR_REQUEST_LINE 3 // Request-Line
#define RULE_SIPGRAMMAR_REQUEST_URI 49 // Request-URI
#define RULE_SIPGRAMMAR_REQUIRE 199 // Require
#define RULE_SIPGRAMMAR_RESERVED 270 // reserved
#define RULE_SIPGRAMMAR_RESPONSE 13 // Response
#define RULE_SIPGRAMMAR_RESPONSE_AUTH 109 // response-auth
#define RULE_SIPGRAMMAR_RESPONSE_DIGEST 110 // response-digest
#define RULE_SIPGRAMMAR_RETRY_AFTER 200 // Retry-After
#define RULE_SIPGRAMMAR_RETRY_PARAM 201 // retry-param
#define RULE_SIPGRAMMAR_RFC1035DOMAIN 266 // RFC1035domain
#define RULE_SIPGRAMMAR_RFC1035LABEL 268 // RFC1035label
#define RULE_SIPGRAMMAR_RFC1035SUBDOMAIN 267 // RFC1035subdomain
#define RULE_SIPGRAMMAR_RFC1123_DATE 155 // rfc1123-date
#define RULE_SIPGRAMMAR_ROUTE 202 // Route
#define RULE_SIPGRAMMAR_ROUTE_PARAM 203 // route-param
#define RULE_SIPGRAMMAR_RPAREN 286 // RPAREN
#define RULE_SIPGRAMMAR_RPLYTO_PARAM 198 // rplyto-param
#define RULE_SIPGRAMMAR_RPLYTO_SPEC 197 // rplyto-spec
#define RULE_SIPGRAMMAR_RR_PARAM 195 // rr-param
#define RULE_SIPGRAMMAR_SCHEME 61 // scheme
#define RULE_SIPGRAMMAR_SEGMENT 58 // segment
#define RULE_SIPGRAMMAR_SEMI 290 // SEMI
#define RULE_SIPGRAMMAR_SENT_BY 228 // sent-by
#define RULE_SIPGRAMMAR_SENT_PROTOCOL 224 // sent-protocol
#define RULE_SIPGRAMMAR_SERVER 204 // Server
#define RULE_SIPGRAMMAR_SERVER_VAL 205 // server-val
#define RULE_SIPGRAMMAR_SERVICE_PROVIDER 254 // service-provider
#define RULE_SIPGRAMMAR_SIP_DATE 154 // SIP-date
#define RULE_SIPGRAMMAR_SIP_MESSAGE 0 // SIP-message
#define RULE_SIPGRAMMAR_SIP_URI 17 // SIP-URI
#define RULE_SIPGRAMMAR_SIP_VERSION 4 // SIP-Version
#define RULE_SIPGRAMMAR_SIPS_URI 18 // SIPS-URI
#define RULE_SIPGRAMMAR_SLASH 283 // SLASH
#define RULE_SIPGRAMMAR_SP 312 // SP
#define RULE_SIPGRAMMAR_SRVR 63 // srvr
#define RULE_SIPGRAMMAR_STALE 186 // stale
#define RULE_SIPGRAMMAR_STAR 282 // STAR
#define RULE_SIPGRAMMAR_STATUS_CODE 15 // Status-Code
#define RULE_SIPGRAMMAR_STATUS_LINE 14 // Status-Line
#define RULE_SIPGRAMMAR_SUBJECT 208 // Subject
#define RULE_SIPGRAMMAR_SUBTAG 137 // subtag
#define RULE_SIPGRAMMAR_SUPPORTED 209 // Supported
#define RULE_SIPGRAMMAR_SWS 301 // SWS
#define RULE_SIPGRAMMAR_TAG_PARAM 166 // tag-param
#define RULE_SIPGRAMMAR_TEL_QUOTED_STRING 259 // tel-quoted-string
#define RULE_SIPGRAMMAR_TELEPHONE_SUBSCRIBER 241 // telephone-subscriber
#define RULE_SIPGRAMMAR_TEXT_UTF8_TRIM 274 // TEXT-UTF8-TRIM
#define RULE_SIPGRAMMAR_TEXT_UTF8CHAR 275 // TEXT-UTF8char
#define RULE_SIPGRAMMAR_TIME 157 // time
#define RULE_SIPGRAMMAR_TIMESTAMP 210 // Timestamp
#define RULE_SIPGRAMMAR_TO 212 // To
#define RULE_SIPGRAMMAR_TO_PARAM 213 // to-param
#define RULE_SIPGRAMMAR_TOKEN 278 // token
#define RULE_SIPGRAMMAR_TOKEN_CHAR 258 // token-char
#define RULE_SIPGRAMMAR_TOPLABEL 27 // toplabel
#define RULE_SIPGRAMMAR_TRANSPORT 227 // transport
#define RULE_SIPGRAMMAR_TRANSPORT_PARAM 31 // transport-param
#define RULE_SIPGRAMMAR_TTL 229 // ttl
#define RULE_SIPGRAMMAR_TTL_PARAM 36 // ttl-param
#define RULE_SIPGRAMMAR_UNRESERVED 271 // unreserved
#define RULE_SIPGRAMMAR_UNSUPPORTED 214 // Unsupported
#define RULE_SIPGRAMMAR_URI 182 // URI
#define RULE_SIPGRAMMAR_URI_PARAMETER 30 // uri-parameter
#define RULE_SIPGRAMMAR_URI_PARAMETERS 29 // uri-parameters
#define RULE_SIPGRAMMAR_URIC 55 // uric
#define RULE_SIPGRAMMAR_URIC_NO_SLASH 56 // uric-no-slash
#define RULE_SIPGRAMMAR_USER 20 // user
#define RULE_SIPGRAMMAR_USER_AGENT 215 // User-Agent
#define RULE_SIPGRAMMAR_USER_PARAM 33 // user-param
#define RULE_SIPGRAMMAR_USER_UNRESERVED 21 // user-unreserved
#define RULE_SIPGRAMMAR_USERINFO 19 // userinfo
#define RULE_SIPGRAMMAR_USERNAME 91 // username
#define RULE_SIPGRAMMAR_USERNAME_VALUE 92 // username-value
#define RULE_SIPGRAMMAR_UTF8_CONT 277 // UTF8-CONT
#define RULE_SIPGRAMMAR_UTF8_NONASCII 276 // UTF8-NONASCII
#define RULE_SIPGRAMMAR_VIA 216 // Via
#define RULE_SIPGRAMMAR_VIA_BRANCH 222 // via-branch
#define RULE_SIPGRAMMAR_VIA_EXTENSION 223 // via-extension
#define RULE_SIPGRAMMAR_VIA_MADDR 220 // via-maddr
#define RULE_SIPGRAMMAR_VIA_PARAMS 218 // via-params
#define RULE_SIPGRAMMAR_VIA_PARM 217 // via-parm
#define RULE_SIPGRAMMAR_VIA_RECEIVED 221 // via-received
#define RULE_SIPGRAMMAR_VIA_TTL 219 // via-ttl
#define RULE_SIPGRAMMAR_VISUAL_SEPARATOR 261 // visual-separator
#define RULE_SIPGRAMMAR_WAIT_FOR_DIAL_TONE 264 // wait-for-dial-tone
#define RULE_SIPGRAMMAR_WARN_AGENT 233 // warn-agent
#define RULE_SIPGRAMMAR_WARN_CODE 232 // warn-code
#define RULE_SIPGRAMMAR_WARN_TEXT 234 // warn-text
#define RULE_SIPGRAMMAR_WARNING 230 // Warning
#define RULE_SIPGRAMMAR_WARNING_VALUE 231 // warning-value
#define RULE_SIPGRAMMAR_WKDAY 158 // wkday
#define RULE_SIPGRAMMAR_WORD 279 // word
#define RULE_SIPGRAMMAR_WSP 302 // WSP
#define RULE_SIPGRAMMAR_WWW_AUTHENTICATE 236 // WWW-Authenticate
#define RULE_SIPGRAMMAR_X_TOKEN 146 // x-token
#define RULE_COUNT_SIPGRAMMAR 313

// Parser initialization data
extern void* vpParserInit_SIPGrammar;

#endif // SIPGRAMMAR_H

//**** SABNF GRAMMAR ****
//; SIP MESSAGE
//SIP-message       =  BlankSpace (Request / Response) ; forgiving on leading characters
//BlankSpace        = *(%d0-31/%d128-255)
//
//; REQUEST
//Request           =  Request-Line *( message-header ) CRLF [ message-body ]
//Request-Line      =  Method SP Request-URI SP SIP-Version CRLF
//SIP-Version       =  "SIP" "/" 1*DIGIT "." 1*DIGIT
//INVITEm           =  %x49.4E.56.49.54.45 ; INVITE in caps
//ACKm              =  %x41.43.4B ; ACK in caps
//OPTIONSm          =  %x4F.50.54.49.4F.4E.53 ; OPTIONS in caps
//BYEm              =  %x42.59.45 ; BYE in caps
//CANCELm           =  %x43.41.4E.43.45.4C ; CANCEL in caps
//REGISTERm         =  %x52.45.47.49.53.54.45.52 ; REGISTER in caps
//Method            =  INVITEm / ACKm / OPTIONSm / BYEm / CANCELm / REGISTERm / extension-method
//extension-method  =  token
//
//; RESPONSE
//Response          =  Status-Line *( message-header ) CRLF [ message-body ]
//Status-Line       =  SIP-Version SP Status-Code SP Reason-Phrase CRLF
//Status-Code       =  3DIGIT ; to be analyzed semantically (see RFC 3621)
//Reason-Phrase     =  *(reserved / unreserved / escaped / UTF8-NONASCII / UTF8-CONT / WSP)
//
//; SIP URI
//SIP-URI           =  "sip:" [ userinfo ] hostport uri-parameters [ headers ]
//SIPS-URI          =  "sips:" [ userinfo ] hostport uri-parameters [ headers ]
//userinfo          =  ( user / telephone-subscriber ) [ ":" password ] "@"
//user              =  1*( unreserved / escaped / user-unreserved )
//user-unreserved   =  "&" / "=" / "+" / "$" / "," / ";" / "?" / "/"
//password          =  *( unreserved / escaped / "&" / "=" / "+" / "$" / "," )
//hostport          =  host [ ":" port ]
//host              =  hostname / IPv4address / IPv6reference
//hostname          =  *( domainlabel "." &(alphanum/"-")) toplabel [ "." ]
//domainlabel       =  1*alphanum *(1*"-" 1*alphanum)
//toplabel          =  ALPHA *alphanum *(1*"-" 1*alphanum)
//;
//; prioritized-choice will always fail for these rules
//;domainlabel       =  alphanum / alphanum *( alphanum / "-" ) alphanum
//;toplabel          =  ALPHA / ALPHA *( alphanum / "-" ) alphanum
//;
//port              =  1*DIGIT
//uri-parameters    =  *( ";" uri-parameter)
//uri-parameter     =  transport-param / user-param / method-param / ttl-param / maddr-param / lr-param / other-param
//transport-param   =  "transport=" ( "udp" / "tcp" / "sctp" / "tls" / other-transport)
//other-transport   =  token
//user-param        =  "user=" ( "phone" / "ip" / other-user)
//other-user        =  token
//method-param      =  "method=" Method
//ttl-param         =  "ttl=" ttl
//maddr-param       =  "maddr=" host
//lr-param          =  "lr"
//other-param       =  pname [ "=" pvalue ]
//pname             =  1*paramchar
//pvalue            =  1*paramchar
//paramchar         =  param-unreserved / unreserved / escaped
//param-unreserved  =  "[" / "]" / "/" / ":" / "&" / "+" / "$"
//headers           =  "?" header *( "&" header )
//header            =  hname "=" hvalue
//hname             =  1*( hnv-unreserved / unreserved / escaped )
//hvalue            =  *( hnv-unreserved / unreserved / escaped )
//hnv-unreserved    =  "[" / "]" / "/" / "?" / ":" / "+" / "$"
//
//; REQUEST URI
//Request-URI    =  SIP-URI / SIPS-URI / absoluteURI
//absoluteURI    =  scheme ":" ( hier-part / opaque-part )
//hier-part      =  ( net-path / abs-path ) [ "?" query ]
//net-path       =  "//" authority [ abs-path ]
//abs-path       =  "/" path-segments
//opaque-part    =  uric-no-slash *uric
//uric           =  reserved / unreserved / escaped
//uric-no-slash  =  unreserved / escaped / ";" / "?" / ":" / "@" / "&" / "=" / "+" / "$" / ","
//path-segments  =  segment *( "/" segment )
//segment        =  *pchar *( ";" param )
//param          =  *pchar
//pchar          =  unreserved / escaped / ":" / "@" / "&" / "=" / "+" / "$" / ","
//scheme         =  ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )
//authority      =  srvr / reg-name
//;srvr           =  [ [ userinfo "@" ] hostport ] ; LDT: 07/11/07: I don't think they want two "@" here
//srvr           =  [ [ userinfo ] hostport ]
//reg-name       =  1*( unreserved / escaped / "$" / "," / ";" / ":" / "@" / "&" / "=" / "+" )
//query          =  *uric
//
//; IP ADDRESSES
//IPv4address    =  1*3DIGIT "." 1*3DIGIT "." 1*3DIGIT "." 1*3DIGIT
//IPv6reference  =  "[" IPv6address "]"
//IPv6address    =  *(HEXDIG / ":" / ".") ; to be parsed in semantics
//
//; MESSAGE HEADERS
//message-header      = (  "Accept"                   HCOLON Accept
//                      /  "Accept-Encoding"          HCOLON Accept-Encoding
//                      /  "Accept-Language"          HCOLON Accept-Language
//                      /  "Alert-Info"               HCOLON Alert-Info
//                      /  "Allow"                    HCOLON Allow
//                      /  "Authentication-Info"      HCOLON Authentication-Info
//                      /  "Authorization"            HCOLON Authorization
//                      /  ( "Call-ID" / "i" )        HCOLON Call-ID
//                      /  "Call-Info"                HCOLON Call-Info
//                      /  ("Contact" / "m" )         HCOLON Contact
//                      /  "Content-Disposition"      HCOLON Content-Disposition
//                      /  ("Content-Encoding" / "e") HCOLON Content-Encoding
//                      /  "Content-Language"         HCOLON Content-Language
//                      /  ("Content-Length" / "l")   HCOLON Content-Length
//                      /  ( "Content-Type" / "c" )   HCOLON Content-Type
//                      /  "CSeq"                     HCOLON CSeq
//                      /  "Date"                     HCOLON Date
//                      /  "Error-Info"               HCOLON Error-Info
//                      /  "Expires"                  HCOLON Expires
//                      /  ( "From" / "f" )           HCOLON From
//                      /  "In-Reply-To"              HCOLON In-Reply-To
//                      /  "Max-Forwards"             HCOLON Max-Forwards
//                      /  "MIME-Version"             HCOLON MIME-Version
//                      /  "Min-Expires"              HCOLON Min-Expires
//                      /  "Organization"             HCOLON Organization
//                      /  "Priority"                 HCOLON Priority
//                      /  "Proxy-Authenticate"       HCOLON Proxy-Authenticate
//                      /  "Proxy-Authorization"      HCOLON Proxy-Authorization
//                      /  "Proxy-Require"            HCOLON Proxy-Require
//                      /  "Record-Route"             HCOLON Record-Route
//                      /  "Reply-To"                 HCOLON Reply-To
//                      /  "Require"                  HCOLON Require
//                      /  "Retry-After"              HCOLON Retry-After
//                      /  "Route"                    HCOLON Route
//                      /  "Server"                   HCOLON Server
//                      /  ( "Subject" / "s" )        HCOLON Subject
//                      /  ( "Supported" / "k" )      HCOLON Supported
//                      /  "Timestamp"                HCOLON Timestamp
//                      /  ( "To" / "t" )             HCOLON To
//                      /  "Unsupported"              HCOLON Unsupported
//                      /  "User-Agent"               HCOLON User-Agent
//                      /  ( "Via" / "v" )            HCOLON Via
//                      /  "Warning"                  HCOLON Warning
//                      /  "WWW-Authenticate"         HCOLON WWW-Authenticate
//                      /  header-name                HCOLON extension-header) CRLF
//
//Accept              =  [ accept-range *(COMMA accept-range) ]
//accept-range        =  media-range *(SEMI accept-param)
//;media-range         =  ( "*/*" / ( m-type SLASH "*" ) / ( m-type SLASH m-subtype ) ) *( SEMI m-parameter )
//; LDT 07/11/07: I've left factored (m-type SLASH)
//media-range         =  ( "*/*" / ( m-type SLASH ("*" / m-subtype) ) ) *( SEMI m-parameter )
//accept-param        =  ("q" EQUAL qvalue) / generic-param
//qvalue              =  ( "0" [ "." 0*3DIGIT ] ) / ( "1" [ "." 0*3("0") ] )
//generic-param       =  token [ EQUAL gen-value ]
//gen-value           =  token / host / quoted-string
//
//Accept-Encoding     =  [ encoding *(COMMA encoding) ]
//encoding            =  codings *(SEMI accept-param)
//codings             =  content-coding / "*"
//content-coding      =  token
//
//Accept-Language     =  [ language *(COMMA language) ]
//language            =  language-range *(SEMI accept-param)
//language-range      =  ( ( 1*8ALPHA *( "-" 1*8ALPHA ) ) / "*" )
//
//Alert-Info          =  alert-param *(COMMA alert-param)
//alert-param         =  LAQUOT absoluteURI RAQUOT *( SEMI generic-param )
//
//Allow               =  [Method *(COMMA Method)]
//
//Authorization       =  credentials
//credentials         =  ("Digest" LWS digest-response) / other-response
//digest-response     =  dig-resp *(COMMA dig-resp)
//dig-resp            =  username / realm / nonce / digest-uri
//                      / dresponse / algorithm / cnonce
//                      / opaque / message-qop
//                      / nonce-count / auth-param
//username            =  "username" EQUAL username-value
//username-value      =  quoted-string
//digest-uri          =  "uri" EQUAL LDQUOT digest-uri-value RDQUOT
//digest-uri-value    =  *(%x20-21/%x23-FF)
//;digest-uri-value   =  rquest-uri ; Equal to request-uri as specified by HTTP/1.1
//                       ; any character not double quote (%x22) - see RFC 2068 (HTTP/1.1)
//message-qop         =  "qop" EQUAL qop-value
//cnonce              =  "cnonce" EQUAL cnonce-value
//cnonce-value        =  nonce-value
//nonce-count         =  "nc" EQUAL nc-value
//nc-value            =  8LHEX
//dresponse           =  "response" EQUAL request-digest
//request-digest      =  LDQUOT 32LHEX RDQUOT
//auth-param          =  auth-param-name EQUAL ( token / quoted-string )
//auth-param-name     =  token
//other-response      =  auth-scheme LWS auth-param *(COMMA auth-param)
//auth-scheme         =  token
//
//Authentication-Info =  ainfo *(COMMA ainfo)
//ainfo               =  nextnonce / message-qop / response-auth / cnonce / nonce-count
//nextnonce           =  "nextnonce" EQUAL nonce-value
//response-auth       =  "rspauth" EQUAL response-digest
//response-digest     =  LDQUOT *LHEX RDQUOT
//
//Call-ID             =  word [ "@" word ]
//callid              =  word [ "@" word ]
//
//Call-Info           =  info *(COMMA info)
//info                =  LAQUOT absoluteURI RAQUOT *( SEMI info-param)
//info-param          =  ( "purpose" EQUAL ( "icon" / "info" / "card" / token ) ) / generic-param
//
//Contact             =  ( STAR / (contact-param *(COMMA contact-param)))
//contact-param       =  (name-addr / addr-spec) *(SEMI contact-params)
//; LDT 07/11/07: display-name is an empty string acceptor, optional brackets are unneccessary
//;name-addr           =  [ display-name ] LAQUOT addr-spec RAQUOT
//name-addr           =  display-name LAQUOT addr-spec RAQUOT
//addr-spec           =  SIP-URI / SIPS-URI / absoluteURI
//; LDT 07/11/07: want to identify the display name with a rule name we can find in the parse tree
//;display-name        =  *(token LWS)/ quoted-string
//; LDT 07/11/07: prioritized choice requires quoted-string first
//display-name        =  quoted-string / d-name
//; see comment on optional white space
//; RFC 4475, example 3.1.1.6, pg. 12
//;d-name              =  *(token LWS)
//d-name              =  [token *(LWS token)]
//contact-params      =  c-p-q / c-p-expires / contact-extension
//c-p-q               =  "q" EQUAL qvalue
//c-p-expires         =  "expires" EQUAL delta-seconds
//contact-extension   =  generic-param
//delta-seconds       =  1*DIGIT
//
//Content-Disposition =  disp-type *( SEMI disp-param )
//disp-type           =  "render" / "session" / "icon" / "alert" / disp-extension-token
//disp-param          =  handling-param / generic-param
//handling-param      =  "handling" EQUAL ( "optional" / "required" / other-handling )
//other-handling      =  token
//disp-extension-token=  token
//
//Content-Encoding    =  content-coding *(COMMA content-coding)
//
//Content-Language    =  language-tag *(COMMA language-tag)
//language-tag        =  primary-tag *( "-" subtag )
//primary-tag         =  1*8ALPHA
//subtag              =  1*8ALPHA
//
//Content-Length      =  1*DIGIT
//
//Content-Type        =  media-type
//media-type          =  m-type SLASH m-subtype *(SEMI m-parameter)
//m-type              =  discrete-type / composite-type
//discrete-type       =  "text" / "image" / "audio" / "video" / "application" / extension-token
//composite-type      =  "message" / "multipart" / extension-token
//extension-token     =  ietf-token / x-token
//ietf-token          =  token
//x-token             =  "x-" token
//m-subtype           =  extension-token / iana-token
//iana-token          =  token
//m-parameter         =  m-attribute EQUAL m-value
//m-attribute         =  token
//m-value             =  token / quoted-string
//
//CSeq                =  1*DIGIT LWS Method
//
//Date                =  SIP-date
//SIP-date            =  rfc1123-date
//rfc1123-date        =  wkday "," SP date1 SP time SP "GMT"
//date1               =  2DIGIT SP month SP 4DIGIT ; day month year (e.g., 02 Jun 1982)
//time                =  2DIGIT ":" 2DIGIT ":" 2DIGIT ; 00:00:00 - 23:59:59
//wkday               =  "Mon" / "Tue" / "Wed" / "Thu" / "Fri" / "Sat" / "Sun"
//month               =  "Jan" / "Feb" / "Mar" / "Apr" / "May" / "Jun" / "Jul" / "Aug" / "Sep" / "Oct" / "Nov" / "Dec"
//
//Error-Info          =  error-uri *(COMMA error-uri)
//error-uri           =  LAQUOT absoluteURI RAQUOT *( SEMI generic-param )
//
//Expires             =  delta-seconds
//
//From                =  from-spec
//from-spec           =  ( name-addr / addr-spec ) *( SEMI from-param )
//from-param          =  tag-param / generic-param
//tag-param           =  "tag" EQUAL token
//
//In-Reply-To         =  callid *(COMMA callid)
//
//Max-Forwards        =  1*DIGIT
//
//MIME-Version        =  1*DIGIT "." 1*DIGIT
//
//Min-Expires         =  delta-seconds
//
//Organization        =  [TEXT-UTF8-TRIM]
//
//Priority            =  priority-value
//priority-value      =  "emergency" / "urgent" / "normal" / "non-urgent" / other-priority
//other-priority      =  token
//
//Proxy-Authenticate  =  challenge
//challenge           =  ("Digest" LWS digest-cln *(COMMA digest-cln)) / other-challenge
//other-challenge     =  auth-scheme LWS auth-param *(COMMA auth-param)
//digest-cln          =  realm / domain / nonce / opaque / stale / algorithm / qop-options / auth-param
//realm               =  "realm" EQUAL realm-value
//realm-value         =  quoted-string
//domain              =  "domain" EQUAL LDQUOT URI *( 1*SP URI ) RDQUOT
//URI                 =  absoluteURI / abs-path
//nonce               =  "nonce" EQUAL nonce-value
//nonce-value         =  quoted-string
//opaque              =  "opaque" EQUAL quoted-string
//stale               =  "stale" EQUAL ( "true" / "false" )
//algorithm           =  "algorithm" EQUAL ( "MD5" / "MD5-sess" / token )
//qop-options         =  "qop" EQUAL LDQUOT qop-value *("," qop-value) RDQUOT
//qop-value           =  "auth" / "auth-int" / token
//
//Proxy-Authorization =  credentials
//
//Proxy-Require       =  option-tag *(COMMA option-tag)
//option-tag          =  token
//
//Record-Route        =  rec-route *(COMMA rec-route)
//rec-route           =  name-addr *( SEMI rr-param )
//rr-param            =  generic-param
//
//Reply-To            =  rplyto-spec
//rplyto-spec         =  ( name-addr / addr-spec ) *( SEMI rplyto-param )
//rplyto-param        =  generic-param
//
//Require             =  option-tag *(COMMA option-tag)
//
//Retry-After         =  delta-seconds [ comment ] *( SEMI retry-param )
//retry-param         =  ("duration" EQUAL delta-seconds) / generic-param
//
//Route               =  route-param *(COMMA route-param)
//route-param         =  name-addr *( SEMI rr-param )
//
//Server              =  server-val *(LWS server-val)
//server-val          =  product / comment
//product             =  token [SLASH product-version]
//product-version     =  token
//
//Subject             =  [TEXT-UTF8-TRIM]
//
//Supported           =  [option-tag *(COMMA option-tag)]
//
//Timestamp           =  1*(DIGIT) [ "." *(DIGIT) ] [ LWS delay ]
//delay               =  *(DIGIT) [ "." *(DIGIT) ]
//
//To                  =  ( name-addr / addr-spec ) *( SEMI to-param )
//to-param            =  tag-param / generic-param
//
//Unsupported         =  option-tag *(COMMA option-tag)
//
//User-Agent          =  server-val *(LWS server-val)
//
//Via                 =  via-parm *(COMMA via-parm)
//via-parm            =  sent-protocol LWS sent-by *( SEMI via-params )
//via-params          =  via-ttl / via-maddr / via-received / via-branch / via-extension
//via-ttl             =  "ttl" EQUAL ttl
//via-maddr           =  "maddr" EQUAL host
//via-received        =  "received" EQUAL (IPv4address / IPv6address)
//via-branch          =  "branch" EQUAL token
//via-extension       =  generic-param
//sent-protocol       =  protocol-name SLASH protocol-version SLASH transport
//protocol-name       =  "SIP" / token
//protocol-version    =  token
//transport           =  "UDP" / "TCP" / "TLS" / "SCTP" / other-transport
//sent-by             =  host [ COLON port ]
//ttl                 =  1*3DIGIT ; 0 to 255
//
//Warning             =  warning-value *(COMMA warning-value)
//warning-value       =  warn-code SP warn-agent SP warn-text
//warn-code           =  3DIGIT
//warn-agent          =  hostport / pseudonym
//                        ;  the name or pseudonym of the server adding
//                        ;  the Warning header, for use in debugging
//warn-text           =  quoted-string
//pseudonym           =  token
//
//WWW-Authenticate    =  challenge
//extension-header    =  header-value
//header-name         =  token
//header-value        =  *(TEXT-UTF8char / UTF8-CONT / LWS)
//message-body        =  *OCTET
//
//; 2.2 "tel" URL scheme, see [RFC2303]
//; NOTE: domain is defined in RFC1035 and is different that the domain defined above
//telephone-subscriber  = global-phone-number / local-phone-number
//global-phone-number   = "+" base-phone-number [isdn-subaddress] [post-dial] *(area-specifier / service-provider / future-extension)
//base-phone-number     = 1*phonedigit
//local-phone-number    = 1*(phonedigit / dtmf-digit /
//                         pause-character) [isdn-subaddress] [post-dial] area-specifier
//                         *(area-specifier / service-provider / future-extension)
//isdn-subaddress       = ";isub=" 1*phonedigit
//post-dial             = ";postd=" 1*(phonedigit / dtmf-digit / pause-character)
//area-specifier        = ";" phone-context-tag "=" phone-context-ident
//phone-context-tag     = "phone-context"
//phone-context-ident   = network-prefix / private-prefix
//network-prefix        = global-network-prefix / local-network-prefix
//global-network-prefix = "+" 1*phonedigit
//local-network-prefix  = 1*(phonedigit / dtmf-digit / pause-character)
//private-prefix        = (%x21-22 / %x24-27 / %x2C / %x2F / %x3A /
//                        %x3C-40 / %x45-4F / %x51-56 / %x58-60 /
//                        %x65-6F / %x71-76 / %x78-7E)
//                        *(%x21-3A / %x3C-7E)
//                        ; Characters in URLs must follow escaping rules
//                        ; as explained in [RFC2396]
//                        ; See sections 1.2 and 2.5.2
//service-provider      = ";" provider-tag "=" provider-hostname
//provider-tag          = "tsp"
//provider-hostname     = RFC1035domain ; <domain> is defined in [RFC1035] ; See section 2.5.10
//future-extension      = ";" 1*(token-char) ["=" ((1*(token-char) ["?" 1*(token-char)]) / tel-quoted-string )]
//                        ; See section 2.5.11 and [RFC2543]
//token-char            = (%x21 / %x23-27 / %x2A-2B / %x2D-2E / %x30-39 / %x41-5A / %x5E-7A / %x7C / %x7E)
//                        ; Characters in URLs must follow escaping rules
//                        ; as explained in [RFC2396]
//                        ; See sections 1.2 and 2.5.11
//tel-quoted-string     = %x22 *( "\" CHAR / (%x20-21 / %x23-7E / %x80-FF )) %x22
//                        ; Characters in URLs must follow escaping rules
//                        ; as explained in [RFC2396]
//                        ; See sections 1.2 and 2.5.11
//phonedigit            = DIGIT / visual-separator
//visual-separator      = "-" / "." / "(" / ")"
//pause-character       = one-second-pause / wait-for-dial-tone
//one-second-pause      = "p"
//wait-for-dial-tone    = "w"
//dtmf-digit            = "*" / "#" / "A" / "B" / "C" / "D"
//
//; RFC 1035
//RFC1035domain = RFC1035subdomain / " "
//
//;RFC1035subdomain = RFC1035label / RFC1035subdomain "." RFC1035label
//RFC1035subdomain = RFC1035label *("." RFC1035label)
//
//; LDT: assuming they want "begin with alpha, alphanum or hyphen, end with alphanum
//;RFC1035label = ALPHA [ [ ldh-str ] alphanum ]
//; prioritized-choice grammar for that
//RFC1035label = ALPHA *alphanum *("-" 1*alphanum)
//
//;ldh-str = alphanum-hyp / alphanum-hyp ldh-str
//;ldh-str = 1*alphanum-hyp
//
//;alphanum-hyp = alphanum / "-"
//
//;alphanum = ALPHA / DIGIT
//;
//;ALPHA = any one of the 52 alphabetic characters A through Z in
//;upper case and a through z in lower case
//;
//;DIGIT = any one of the ten DIGITs 0 through 9
//
//; 25.1 Basic Rules
//alphanum        =  ALPHA / DIGIT
//reserved        =  ";" / "/" / "?" / ":" / "@" / "&" / "=" / "+" / "$" / ","
//unreserved      =  alphanum / mark
//mark            =  "-" / "_" / "." / "!" / "~" / "*" / "'" / "(" / ")"
//escaped         =  "%" HEXDIG HEXDIG
//TEXT-UTF8-TRIM  =  1*TEXT-UTF8char *(LWS 1*TEXT-UTF8char)
//TEXT-UTF8char   =  %x21-7E / UTF8-NONASCII
//UTF8-NONASCII   =  %xC0-DF UTF8-CONT /
//                   %xE0-EF 2UTF8-CONT /
//                   %xF0-F7 3UTF8-CONT /
//                   %xF8-Fb 4UTF8-CONT /
//                   %xFC-FD 5UTF8-CONT
//UTF8-CONT       =  %x80-BF
//token           =  1*(alphanum / "-" / "." / "!" / "%" / "*" / "_" / "+" / "`" / "'" / "~" )
//word            =  1*(alphanum /
//                   "-" / "." / "!" / "%" / "*" / "_" / "+" / "`" / "'" / "~" /
//                    "(" / ")" / "<" / ">" / ":" / "\" / DQUOTE /
//                    "/" / "[" / "]" / "?" / "{" / "}" )
//;HCOLON          =  *( SP / HTAB ) ":" SWS
//HCOLON          =  *WSP ":" SWS
//LHEX            =  DIGIT / %x61-66    ;lowercase a-f
//STAR            =  SWS "*" SWS        ; asterisk
//SLASH           =  SWS "/" SWS        ; slash
//EQUAL           =  SWS "=" SWS        ; equal
//LPAREN          =  SWS "(" SWS        ; left parenthesis
//RPAREN          =  SWS ")" SWS        ; right parenthesis
//RAQUOT          =  ">" SWS            ; right angle quote
//LAQUOT          =  SWS "<"            ; left angle quote
//COMMA           =  SWS "," SWS        ; comma
//SEMI            =  SWS ";" SWS        ; semicolon
//COLON           =  SWS ":" SWS        ; colon
//LDQUOT          =  SWS DQUOTE         ; open double quotation mark
//RDQUOT          =  DQUOTE SWS         ; close double quotation mark
//comment         =  LPAREN *(ctext / quoted-pair / comment) RPAREN
//ctext           =  %x21-27 / %x2A-5B / %x5D-7E / UTF8-NONASCII / LWS
//; LDT 07/11/07: want to be able to identify the string in the parse tree
//;quoted-string   =  SWS DQUOTE *(qdtext / quoted-pair ) DQUOTE
//quoted-string   =  SWS DQUOTE q-string DQUOTE
//q-string        =  *(qdtext / quoted-pair )
//qdtext          =  LWS / %x21 / %x23-5B / %x5D-7E / UTF8-NONASCII
//quoted-pair     =  "\" (%x00-09 / %x0B-0C / %x0E-7F)
//LWS             =  [*WSP CRLF] 1*WSP  ; linear whitespace (one or more line continue or space)
//SWS             =  [LWS]              ; sep (optional) whitespace (zero or more line continue or space)
//WSP             =  %x20 / %x09
//
//; B.1.  Core Rules ; RFC 4234 ABNF October 2005
//ALPHA          =  %x41-5A / %x61-7A   ; A-Z / a-z
//CHAR           =  %x01-7F ; any 7-bit US-ASCII character, ;  excluding NUL
//CR             =  %x0D ; carriage return
//CRLF           =  CR LF / LF / CR; modified to be forgiving on line ender
//DIGIT          =  %x30-39 ; 0-9
//DQUOTE         =  %x22 ; " (Double Quote)
//HEXDIG         =  DIGIT / "A" / "B" / "C" / "D" / "E" / "F"
//LF             =  %x0A ; linefeed
//OCTET          =  %x00-FF ; 8 bits of data
//SP             =  %x20
//
////**** SABNF GRAMMAR ***

