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
#ifndef GRAMMAR1_H
#define GRAMMAR1_H

// rule ids
#define RULE_GRAMMAR1_ABS_PATH 51 // abs-path
#define RULE_GRAMMAR1_ABSOLUTEURI 48 // absoluteURI
#define RULE_GRAMMAR1_ACCEPT 67 // Accept
#define RULE_GRAMMAR1_ACCEPT_ENCODING 74 // Accept-Encoding
#define RULE_GRAMMAR1_ACCEPT_LANGUAGE 78 // Accept-Language
#define RULE_GRAMMAR1_ACCEPT_PARAM 70 // accept-param
#define RULE_GRAMMAR1_ACCEPT_RANGE 68 // accept-range
#define RULE_GRAMMAR1_ACKM 6 // ACKm
#define RULE_GRAMMAR1_ADDR_SPEC 114 // addr-spec
#define RULE_GRAMMAR1_AINFO 104 // ainfo
#define RULE_GRAMMAR1_ALERT_INFO 81 // Alert-Info
#define RULE_GRAMMAR1_ALERT_PARAM 82 // alert-param
#define RULE_GRAMMAR1_ALGORITHM 182 // algorithm
#define RULE_GRAMMAR1_ALLOW 83 // Allow
#define RULE_GRAMMAR1_ALPHA 289 // ALPHA
#define RULE_GRAMMAR1_AREA_SPECIFIER 242 // area-specifier
#define RULE_GRAMMAR1_AUTH_PARAM 99 // auth-param
#define RULE_GRAMMAR1_AUTH_PARAM_NAME 100 // auth-param-name
#define RULE_GRAMMAR1_AUTH_SCHEME 102 // auth-scheme
#define RULE_GRAMMAR1_AUTHENTICATION_INFO 103 // Authentication-Info
#define RULE_GRAMMAR1_AUTHORITY 59 // authority
#define RULE_GRAMMAR1_AUTHORIZATION 84 // Authorization
#define RULE_GRAMMAR1_BASE_PHONE_NUMBER 238 // base-phone-number
#define RULE_GRAMMAR1_BLANKSPACE 1 // BlankSpace
#define RULE_GRAMMAR1_BYEM 8 // BYEm
#define RULE_GRAMMAR1_C_P_EXPIRES 119 // c-p-expires
#define RULE_GRAMMAR1_C_P_Q 118 // c-p-q
#define RULE_GRAMMAR1_CALL_INFO 108 // Call-Info
#define RULE_GRAMMAR1_CANCELM 9 // CANCELm
#define RULE_GRAMMAR1_CHALLENGE 171 // challenge
#define RULE_GRAMMAR1_CHAR 290 // CHAR
#define RULE_GRAMMAR1_CNONCE 93 // cnonce
#define RULE_GRAMMAR1_CNONCE_VALUE 94 // cnonce-value
#define RULE_GRAMMAR1_CODINGS 76 // codings
#define RULE_GRAMMAR1_COLON 277 // COLON
#define RULE_GRAMMAR1_COMMA 275 // COMMA
#define RULE_GRAMMAR1_COMMENT 280 // comment
#define RULE_GRAMMAR1_COMPOSITE_TYPE 138 // composite-type
#define RULE_GRAMMAR1_CONTACT 111 // Contact
#define RULE_GRAMMAR1_CONTACT_EXTENSION 120 // contact-extension
#define RULE_GRAMMAR1_CONTACT_PARAM 112 // contact-param
#define RULE_GRAMMAR1_CONTACT_PARAMS 117 // contact-params
#define RULE_GRAMMAR1_CONTENT_CODING 77 // content-coding
#define RULE_GRAMMAR1_CONTENT_DISPOSITION 122 // Content-Disposition
#define RULE_GRAMMAR1_CONTENT_ENCODING 128 // Content-Encoding
#define RULE_GRAMMAR1_CONTENT_LANGUAGE 129 // Content-Language
#define RULE_GRAMMAR1_CONTENT_LENGTH 133 // Content-Length
#define RULE_GRAMMAR1_CONTENT_TYPE 134 // Content-Type
#define RULE_GRAMMAR1_CR 291 // CR
#define RULE_GRAMMAR1_CREDENTIALS 85 // credentials
#define RULE_GRAMMAR1_CRLF 292 // CRLF
#define RULE_GRAMMAR1_CSEQ 147 // CSeq
#define RULE_GRAMMAR1_CTEXT 281 // ctext
#define RULE_GRAMMAR1_D_NAME 116 // d-name
#define RULE_GRAMMAR1_DATE 148 // Date
#define RULE_GRAMMAR1_DATE1 151 // date1
#define RULE_GRAMMAR1_DELAY 206 // delay
#define RULE_GRAMMAR1_DELTA_SECONDS 121 // delta-seconds
#define RULE_GRAMMAR1_DIG_RESP 87 // dig-resp
#define RULE_GRAMMAR1_DIGEST_CLN 173 // digest-cln
#define RULE_GRAMMAR1_DIGEST_RESPONSE 86 // digest-response
#define RULE_GRAMMAR1_DIGEST_URI 90 // digest-uri
#define RULE_GRAMMAR1_DIGEST_URI_VALUE 91 // digest-uri-value
#define RULE_GRAMMAR1_DIGIT 293 // DIGIT
#define RULE_GRAMMAR1_DISCRETE_TYPE 137 // discrete-type
#define RULE_GRAMMAR1_DISP_EXTENSION_TOKEN 127 // disp-extension-token
#define RULE_GRAMMAR1_DISP_PARAM 124 // disp-param
#define RULE_GRAMMAR1_DISP_TYPE 123 // disp-type
#define RULE_GRAMMAR1_DISPLAY_NAME 115 // display-name
#define RULE_GRAMMAR1_DOMAIN 176 // domain
#define RULE_GRAMMAR1_DQUOTE 294 // DQUOTE
#define RULE_GRAMMAR1_DRESPONSE 97 // dresponse
#define RULE_GRAMMAR1_DTMF_DIGIT 259 // dtmf-digit
#define RULE_GRAMMAR1_ENCODING 75 // encoding
#define RULE_GRAMMAR1_EQUAL 270 // EQUAL
#define RULE_GRAMMAR1_ERROR_INFO 155 // Error-Info
#define RULE_GRAMMAR1_ERROR_URI 156 // error-uri
#define RULE_GRAMMAR1_ESCAPED 261 // escaped
#define RULE_GRAMMAR1_EXPIRES 157 // Expires
#define RULE_GRAMMAR1_EXTENSION_HEADER 232 // extension-header
#define RULE_GRAMMAR1_EXTENSION_METHOD 12 // extension-method
#define RULE_GRAMMAR1_EXTENSION_TOKEN 139 // extension-token
#define RULE_GRAMMAR1_FROM 158 // From
#define RULE_GRAMMAR1_FROM_PARAM 160 // from-param
#define RULE_GRAMMAR1_FROM_SPEC 159 // from-spec
#define RULE_GRAMMAR1_FUTURE_EXTENSION 251 // future-extension
#define RULE_GRAMMAR1_GEN_VALUE 73 // gen-value
#define RULE_GRAMMAR1_GENERIC_PARAM 72 // generic-param
#define RULE_GRAMMAR1_GLOBAL_NETWORK_PREFIX 246 // global-network-prefix
#define RULE_GRAMMAR1_GLOBAL_PHONE_NUMBER 237 // global-phone-number
#define RULE_GRAMMAR1_HANDLING_PARAM 125 // handling-param
#define RULE_GRAMMAR1_HCOLON 266 // HCOLON
#define RULE_GRAMMAR1_HEADER 43 // header
#define RULE_GRAMMAR1_HEADER_NAME 233 // header-name
#define RULE_GRAMMAR1_HEADER_VALUE 234 // header-value
#define RULE_GRAMMAR1_HEADERS 42 // headers
#define RULE_GRAMMAR1_HEXDIG 295 // HEXDIG
#define RULE_GRAMMAR1_HIER_PART 49 // hier-part
#define RULE_GRAMMAR1_HNAME 44 // hname
#define RULE_GRAMMAR1_HNV_UNRESERVED 46 // hnv-unreserved
#define RULE_GRAMMAR1_HOST 24 // host
#define RULE_GRAMMAR1_HOSTNAME 25 // hostname
#define RULE_GRAMMAR1_HOSTPORT 23 // hostport
#define RULE_GRAMMAR1_HVALUE 45 // hvalue
#define RULE_GRAMMAR1_IANA_TOKEN 143 // iana-token
#define RULE_GRAMMAR1_IETF_TOKEN 140 // ietf-token
#define RULE_GRAMMAR1_IN_REPLY_TO 162 // In-Reply-To
#define RULE_GRAMMAR1_INFO 109 // info
#define RULE_GRAMMAR1_INFO_PARAM 110 // info-param
#define RULE_GRAMMAR1_INVITEM 5 // INVITEm
#define RULE_GRAMMAR1_IPV4ADDRESS 63 // IPv4address
#define RULE_GRAMMAR1_IPV6ADDRESS 65 // IPv6address
#define RULE_GRAMMAR1_IPV6REFERENCE 64 // IPv6reference
#define RULE_GRAMMAR1_ISDN_SUBADDRESS 240 // isdn-subaddress
#define RULE_GRAMMAR1_LANGUAGE 79 // language
#define RULE_GRAMMAR1_LANGUAGE_RANGE 80 // language-range
#define RULE_GRAMMAR1_LANGUAGE_TAG 130 // language-tag
#define RULE_GRAMMAR1_LAQUOT 274 // LAQUOT
#define RULE_GRAMMAR1_LDQUOT 278 // LDQUOT
#define RULE_GRAMMAR1_LF 296 // LF
#define RULE_GRAMMAR1_LHEX 267 // LHEX
#define RULE_GRAMMAR1_LOCAL_NETWORK_PREFIX 247 // local-network-prefix
#define RULE_GRAMMAR1_LOCAL_PHONE_NUMBER 239 // local-phone-number
#define RULE_GRAMMAR1_LPAREN 271 // LPAREN
#define RULE_GRAMMAR1_LR_PARAM 36 // lr-param
#define RULE_GRAMMAR1_LWS 286 // LWS
#define RULE_GRAMMAR1_M_ATTRIBUTE 145 // m-attribute
#define RULE_GRAMMAR1_M_PARAMETER 144 // m-parameter
#define RULE_GRAMMAR1_M_SUBTYPE 142 // m-subtype
#define RULE_GRAMMAR1_M_TYPE 136 // m-type
#define RULE_GRAMMAR1_M_VALUE 146 // m-value
#define RULE_GRAMMAR1_MADDR_PARAM 35 // maddr-param
#define RULE_GRAMMAR1_MAX_FORWARDS 163 // Max-Forwards
#define RULE_GRAMMAR1_MEDIA_RANGE 69 // media-range
#define RULE_GRAMMAR1_MEDIA_TYPE 135 // media-type
#define RULE_GRAMMAR1_MESSAGE_BODY 235 // message-body
#define RULE_GRAMMAR1_MESSAGE_HEADER 66 // message-header
#define RULE_GRAMMAR1_MESSAGE_QOP 92 // message-qop
#define RULE_GRAMMAR1_METHOD 11 // Method
#define RULE_GRAMMAR1_METHOD_PARAM 33 // method-param
#define RULE_GRAMMAR1_MIME_VERSION 164 // MIME-Version
#define RULE_GRAMMAR1_MIN_EXPIRES 165 // Min-Expires
#define RULE_GRAMMAR1_MONTH 154 // month
#define RULE_GRAMMAR1_NAME_ADDR 113 // name-addr
#define RULE_GRAMMAR1_NC_VALUE 96 // nc-value
#define RULE_GRAMMAR1_NET_PATH 50 // net-path
#define RULE_GRAMMAR1_NETWORK_PREFIX 245 // network-prefix
#define RULE_GRAMMAR1_NEXTNONCE 105 // nextnonce
#define RULE_GRAMMAR1_NONCE 178 // nonce
#define RULE_GRAMMAR1_NONCE_COUNT 95 // nonce-count
#define RULE_GRAMMAR1_NONCE_VALUE 179 // nonce-value
#define RULE_GRAMMAR1_OCTET 297 // OCTET
#define RULE_GRAMMAR1_ONE_SECOND_PAUSE 257 // one-second-pause
#define RULE_GRAMMAR1_OPAQUE 180 // opaque
#define RULE_GRAMMAR1_OPAQUE_PART 52 // opaque-part
#define RULE_GRAMMAR1_OPTION_TAG 187 // option-tag
#define RULE_GRAMMAR1_OPTIONSM 7 // OPTIONSm
#define RULE_GRAMMAR1_ORGANIZATION 166 // Organization
#define RULE_GRAMMAR1_OTHER_CHALLENGE 172 // other-challenge
#define RULE_GRAMMAR1_OTHER_HANDLING 126 // other-handling
#define RULE_GRAMMAR1_OTHER_PARAM 37 // other-param
#define RULE_GRAMMAR1_OTHER_PRIORITY 169 // other-priority
#define RULE_GRAMMAR1_OTHER_RESPONSE 101 // other-response
#define RULE_GRAMMAR1_OTHER_TRANSPORT 30 // other-transport
#define RULE_GRAMMAR1_OTHER_USER 32 // other-user
#define RULE_GRAMMAR1_PARAM 57 // param
#define RULE_GRAMMAR1_PARAM_UNRESERVED 41 // param-unreserved
#define RULE_GRAMMAR1_PARAMCHAR 40 // paramchar
#define RULE_GRAMMAR1_PASSWORD 22 // password
#define RULE_GRAMMAR1_PATH_SEGMENTS 55 // path-segments
#define RULE_GRAMMAR1_PAUSE_CHARACTER 256 // pause-character
#define RULE_GRAMMAR1_PCHAR 58 // pchar
#define RULE_GRAMMAR1_PHONE_CONTEXT_IDENT 244 // phone-context-ident
#define RULE_GRAMMAR1_PHONE_CONTEXT_TAG 243 // phone-context-tag
#define RULE_GRAMMAR1_PHONEDIGIT 254 // phonedigit
#define RULE_GRAMMAR1_PNAME 38 // pname
#define RULE_GRAMMAR1_PORT 26 // port
#define RULE_GRAMMAR1_POST_DIAL 241 // post-dial
#define RULE_GRAMMAR1_PRIMARY_TAG 131 // primary-tag
#define RULE_GRAMMAR1_PRIORITY 167 // Priority
#define RULE_GRAMMAR1_PRIORITY_VALUE 168 // priority-value
#define RULE_GRAMMAR1_PRIVATE_PREFIX 248 // private-prefix
#define RULE_GRAMMAR1_PRODUCT 201 // product
#define RULE_GRAMMAR1_PRODUCT_VERSION 202 // product-version
#define RULE_GRAMMAR1_PROTOCOL_NAME 220 // protocol-name
#define RULE_GRAMMAR1_PROTOCOL_VERSION 221 // protocol-version
#define RULE_GRAMMAR1_PROVIDER_TAG 250 // provider-tag
#define RULE_GRAMMAR1_PROXY_AUTHENTICATE 170 // Proxy-Authenticate
#define RULE_GRAMMAR1_PROXY_AUTHORIZATION 185 // Proxy-Authorization
#define RULE_GRAMMAR1_PROXY_REQUIRE 186 // Proxy-Require
#define RULE_GRAMMAR1_PSEUDONYM 230 // pseudonym
#define RULE_GRAMMAR1_PVALUE 39 // pvalue
#define RULE_GRAMMAR1_Q_STRING 283 // q-string
#define RULE_GRAMMAR1_QDTEXT 284 // qdtext
#define RULE_GRAMMAR1_QOP_OPTIONS 183 // qop-options
#define RULE_GRAMMAR1_QOP_VALUE 184 // qop-value
#define RULE_GRAMMAR1_QUERY 62 // query
#define RULE_GRAMMAR1_QUOTED_PAIR 285 // quoted-pair
#define RULE_GRAMMAR1_QUOTED_STRING 282 // quoted-string
#define RULE_GRAMMAR1_QVALUE 71 // qvalue
#define RULE_GRAMMAR1_RAQUOT 273 // RAQUOT
#define RULE_GRAMMAR1_RDQUOT 279 // RDQUOT
#define RULE_GRAMMAR1_REALM 174 // realm
#define RULE_GRAMMAR1_REALM_VALUE 175 // realm-value
#define RULE_GRAMMAR1_REASON_PHRASE 16 // Reason-Phrase
#define RULE_GRAMMAR1_REC_ROUTE 189 // rec-route
#define RULE_GRAMMAR1_RECORD_ROUTE 188 // Record-Route
#define RULE_GRAMMAR1_REG_NAME 61 // reg-name
#define RULE_GRAMMAR1_REGISTERM 10 // REGISTERm
#define RULE_GRAMMAR1_REPLY_TO 191 // Reply-To
#define RULE_GRAMMAR1_REQUEST 2 // Request
#define RULE_GRAMMAR1_REQUEST_DIGEST 98 // request-digest
#define RULE_GRAMMAR1_REQUEST_LINE 3 // Request-Line
#define RULE_GRAMMAR1_REQUEST_URI 47 // Request-URI
#define RULE_GRAMMAR1_REQUIRE 194 // Require
#define RULE_GRAMMAR1_RESERVED 260 // reserved
#define RULE_GRAMMAR1_RESPONSE 13 // Response
#define RULE_GRAMMAR1_RESPONSE_AUTH 106 // response-auth
#define RULE_GRAMMAR1_RESPONSE_DIGEST 107 // response-digest
#define RULE_GRAMMAR1_RETRY_AFTER 195 // Retry-After
#define RULE_GRAMMAR1_RETRY_PARAM 196 // retry-param
#define RULE_GRAMMAR1_RFC1123_DATE 150 // rfc1123-date
#define RULE_GRAMMAR1_ROUTE 197 // Route
#define RULE_GRAMMAR1_ROUTE_PARAM 198 // route-param
#define RULE_GRAMMAR1_RPAREN 272 // RPAREN
#define RULE_GRAMMAR1_RPLYTO_PARAM 193 // rplyto-param
#define RULE_GRAMMAR1_RPLYTO_SPEC 192 // rplyto-spec
#define RULE_GRAMMAR1_RR_PARAM 190 // rr-param
#define RULE_GRAMMAR1_SEGMENT 56 // segment
#define RULE_GRAMMAR1_SEMI 276 // SEMI
#define RULE_GRAMMAR1_SENT_BY 223 // sent-by
#define RULE_GRAMMAR1_SENT_PROTOCOL 219 // sent-protocol
#define RULE_GRAMMAR1_SERVER 199 // Server
#define RULE_GRAMMAR1_SERVER_VAL 200 // server-val
#define RULE_GRAMMAR1_SERVICE_PROVIDER 249 // service-provider
#define RULE_GRAMMAR1_SIP_DATE 149 // SIP-date
#define RULE_GRAMMAR1_SIP_MESSAGE 0 // SIP-message
#define RULE_GRAMMAR1_SIP_URI 17 // SIP-URI
#define RULE_GRAMMAR1_SIP_VERSION 4 // SIP-Version
#define RULE_GRAMMAR1_SIPS_URI 18 // SIPS-URI
#define RULE_GRAMMAR1_SLASH 269 // SLASH
#define RULE_GRAMMAR1_SP 298 // SP
#define RULE_GRAMMAR1_SRVR 60 // srvr
#define RULE_GRAMMAR1_STALE 181 // stale
#define RULE_GRAMMAR1_STAR 268 // STAR
#define RULE_GRAMMAR1_STATUS_CODE 15 // Status-Code
#define RULE_GRAMMAR1_STATUS_LINE 14 // Status-Line
#define RULE_GRAMMAR1_SUBJECT 203 // Subject
#define RULE_GRAMMAR1_SUBTAG 132 // subtag
#define RULE_GRAMMAR1_SUPPORTED 204 // Supported
#define RULE_GRAMMAR1_SWS 287 // SWS
#define RULE_GRAMMAR1_TAG_PARAM 161 // tag-param
#define RULE_GRAMMAR1_TEL_QUOTED_STRING 253 // tel-quoted-string
#define RULE_GRAMMAR1_TELEPHONE_SUBSCRIBER 236 // telephone-subscriber
#define RULE_GRAMMAR1_TEXT_UTF8_TRIM 262 // TEXT-UTF8-TRIM
#define RULE_GRAMMAR1_TEXT_UTF8CHAR 263 // TEXT-UTF8char
#define RULE_GRAMMAR1_TIME 152 // time
#define RULE_GRAMMAR1_TIMESTAMP 205 // Timestamp
#define RULE_GRAMMAR1_TO 207 // To
#define RULE_GRAMMAR1_TO_PARAM 208 // to-param
#define RULE_GRAMMAR1_TOKEN_CHAR 252 // token-char
#define RULE_GRAMMAR1_TRANSPORT 222 // transport
#define RULE_GRAMMAR1_TRANSPORT_PARAM 29 // transport-param
#define RULE_GRAMMAR1_TTL 224 // ttl
#define RULE_GRAMMAR1_TTL_PARAM 34 // ttl-param
#define RULE_GRAMMAR1_UNSUPPORTED 209 // Unsupported
#define RULE_GRAMMAR1_URI 177 // URI
#define RULE_GRAMMAR1_URI_PARAMETER 28 // uri-parameter
#define RULE_GRAMMAR1_URI_PARAMETERS 27 // uri-parameters
#define RULE_GRAMMAR1_URIC 53 // uric
#define RULE_GRAMMAR1_URIC_NO_SLASH 54 // uric-no-slash
#define RULE_GRAMMAR1_USER 20 // user
#define RULE_GRAMMAR1_USER_AGENT 210 // User-Agent
#define RULE_GRAMMAR1_USER_PARAM 31 // user-param
#define RULE_GRAMMAR1_USER_UNRESERVED 21 // user-unreserved
#define RULE_GRAMMAR1_USERINFO 19 // userinfo
#define RULE_GRAMMAR1_USERNAME 88 // username
#define RULE_GRAMMAR1_USERNAME_VALUE 89 // username-value
#define RULE_GRAMMAR1_UTF8_CONT 265 // UTF8-CONT
#define RULE_GRAMMAR1_UTF8_NONASCII 264 // UTF8-NONASCII
#define RULE_GRAMMAR1_VIA 211 // Via
#define RULE_GRAMMAR1_VIA_BRANCH 217 // via-branch
#define RULE_GRAMMAR1_VIA_EXTENSION 218 // via-extension
#define RULE_GRAMMAR1_VIA_MADDR 215 // via-maddr
#define RULE_GRAMMAR1_VIA_PARAMS 213 // via-params
#define RULE_GRAMMAR1_VIA_PARM 212 // via-parm
#define RULE_GRAMMAR1_VIA_RECEIVED 216 // via-received
#define RULE_GRAMMAR1_VIA_TTL 214 // via-ttl
#define RULE_GRAMMAR1_VISUAL_SEPARATOR 255 // visual-separator
#define RULE_GRAMMAR1_WAIT_FOR_DIAL_TONE 258 // wait-for-dial-tone
#define RULE_GRAMMAR1_WARN_AGENT 228 // warn-agent
#define RULE_GRAMMAR1_WARN_CODE 227 // warn-code
#define RULE_GRAMMAR1_WARN_TEXT 229 // warn-text
#define RULE_GRAMMAR1_WARNING 225 // Warning
#define RULE_GRAMMAR1_WARNING_VALUE 226 // warning-value
#define RULE_GRAMMAR1_WKDAY 153 // wkday
#define RULE_GRAMMAR1_WSP 288 // WSP
#define RULE_GRAMMAR1_WWW_AUTHENTICATE 231 // WWW-Authenticate
#define RULE_GRAMMAR1_X_TOKEN 141 // x-token
#define RULE_COUNT_GRAMMAR1 299

// UDT ids
#define UDT_GRAMMAR1_E_DOMAINLABEL 2 // e_domainlabel
#define UDT_GRAMMAR1_U_CALLID 5 // u_callid
#define UDT_GRAMMAR1_U_RFC1035DOMAIN 6 // u_RFC1035domain
#define UDT_GRAMMAR1_U_SCHEME 4 // u_scheme
#define UDT_GRAMMAR1_U_TOKEN 0 // u_token
#define UDT_GRAMMAR1_U_TOPLABEL 3 // u_toplabel
#define UDT_GRAMMAR1_U_UNRESERVED 1 // u_unreserved
#define UDT_COUNT_GRAMMAR1 7

// Parser initialization data
extern void* vpParserInit_Grammar1;

#endif // GRAMMAR1_H

//**** SABNF GRAMMAR ****
//;
//; Grammar1 - removal of most ALPHA rules
//;
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
//extension-method  =  u_token
//
//; RESPONSE
//Response          =  Status-Line *( message-header ) CRLF [ message-body ]
//Status-Line       =  SIP-Version SP Status-Code SP Reason-Phrase CRLF
//Status-Code       =  3DIGIT ; to be analyzed semantically (see RFC 3621)
//Reason-Phrase     =  *(reserved / u_unreserved / escaped / UTF8-NONASCII / UTF8-CONT / WSP)
//
//; SIP URI
//SIP-URI           =  "sip:" [ userinfo ] hostport uri-parameters [ headers ]
//SIPS-URI          =  "sips:" [ userinfo ] hostport uri-parameters [ headers ]
//userinfo          =  ( user / telephone-subscriber ) [ ":" password ] "@"
//user              =  1*( u_unreserved / escaped / user-unreserved )
//user-unreserved   =  "&" / "=" / "+" / "$" / "," / ";" / "?" / "/"
//password          =  *( u_unreserved / escaped / "&" / "=" / "+" / "$" / "," )
//hostport          =  host [ ":" port ]
//host              =  hostname / IPv4address / IPv6reference
//hostname          =  e_domainlabel u_toplabel
//port              =  1*DIGIT
//uri-parameters    =  *( ";" uri-parameter)
//uri-parameter     =  transport-param / user-param / method-param / ttl-param / maddr-param / lr-param / other-param
//transport-param   =  "transport=" ( "udp" / "tcp" / "sctp" / "tls" / other-transport)
//other-transport   =  u_token
//user-param        =  "user=" ( "phone" / "ip" / other-user)
//other-user        =  u_token
//method-param      =  "method=" Method
//ttl-param         =  "ttl=" ttl
//maddr-param       =  "maddr=" host
//lr-param          =  "lr"
//other-param       =  pname [ "=" pvalue ]
//pname             =  1*paramchar
//pvalue            =  1*paramchar
//paramchar         =  param-unreserved / u_unreserved / escaped
//param-unreserved  =  "[" / "]" / "/" / ":" / "&" / "+" / "$"
//headers           =  "?" header *( "&" header )
//header            =  hname "=" hvalue
//hname             =  1*( hnv-unreserved / u_unreserved / escaped )
//hvalue            =  *( hnv-unreserved / u_unreserved / escaped )
//hnv-unreserved    =  "[" / "]" / "/" / "?" / ":" / "+" / "$"
//
//; REQUEST URI
//Request-URI    =  SIP-URI / SIPS-URI / absoluteURI
//absoluteURI    =  u_scheme ":" ( hier-part / opaque-part )
//hier-part      =  ( net-path / abs-path ) [ "?" query ]
//net-path       =  "//" authority [ abs-path ]
//abs-path       =  "/" path-segments
//opaque-part    =  uric-no-slash *uric
//uric           =  reserved / u_unreserved / escaped
//uric-no-slash  =  u_unreserved / escaped / ";" / "?" / ":" / "@" / "&" / "=" / "+" / "$" / ","
//path-segments  =  segment *( "/" segment )
//segment        =  *pchar *( ";" param )
//param          =  *pchar
//pchar          =  u_unreserved / escaped / ":" / "@" / "&" / "=" / "+" / "$" / ","
//authority      =  srvr / reg-name
//srvr           =  [ [ userinfo ] hostport ]
//reg-name       =  1*( u_unreserved / escaped / "$" / "," / ";" / ":" / "@" / "&" / "=" / "+" )
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
//                      /  ( "Call-ID" / "i" )        HCOLON u_callid
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
//media-range         =  ( "*/*" / ( m-type SLASH ("*" / m-subtype) ) ) *( SEMI m-parameter )
//accept-param        =  ("q" EQUAL qvalue) / generic-param
//qvalue              =  ( "0" [ "." 0*3DIGIT ] ) / ( "1" [ "." 0*3("0") ] )
//generic-param       =  u_token [ EQUAL gen-value ]
//gen-value           =  u_token / host / quoted-string
//Accept-Encoding     =  [ encoding *(COMMA encoding) ]
//encoding            =  codings *(SEMI accept-param)
//codings             =  content-coding / "*"
//content-coding      =  u_token
//Accept-Language     =  [ language *(COMMA language) ]
//language            =  language-range *(SEMI accept-param)
//language-range      =  ( ( 1*8ALPHA *( "-" 1*8ALPHA ) ) / "*" )
//Alert-Info          =  alert-param *(COMMA alert-param)
//alert-param         =  LAQUOT absoluteURI RAQUOT *( SEMI generic-param )
//Allow               =  [Method *(COMMA Method)]
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
//message-qop         =  "qop" EQUAL qop-value
//cnonce              =  "cnonce" EQUAL cnonce-value
//cnonce-value        =  nonce-value
//nonce-count         =  "nc" EQUAL nc-value
//nc-value            =  8LHEX
//dresponse           =  "response" EQUAL request-digest
//request-digest      =  LDQUOT 32LHEX RDQUOT
//auth-param          =  auth-param-name EQUAL ( u_token / quoted-string )
//auth-param-name     =  u_token
//other-response      =  auth-scheme LWS auth-param *(COMMA auth-param)
//auth-scheme         =  u_token
//Authentication-Info =  ainfo *(COMMA ainfo)
//ainfo               =  nextnonce / message-qop / response-auth / cnonce / nonce-count
//nextnonce           =  "nextnonce" EQUAL nonce-value
//response-auth       =  "rspauth" EQUAL response-digest
//response-digest     =  LDQUOT *LHEX RDQUOT
//Call-Info           =  info *(COMMA info)
//info                =  LAQUOT absoluteURI RAQUOT *( SEMI info-param)
//info-param          =  ( "purpose" EQUAL ( "icon" / "info" / "card" / u_token ) ) / generic-param
//Contact             =  ( STAR / (contact-param *(COMMA contact-param)))
//contact-param       =  (name-addr / addr-spec) *(SEMI contact-params)
//name-addr           =  display-name LAQUOT addr-spec RAQUOT
//addr-spec           =  SIP-URI / SIPS-URI / absoluteURI
//display-name        =  quoted-string / d-name
//d-name              =  [u_token *(LWS u_token)]
//contact-params      =  c-p-q / c-p-expires / contact-extension
//c-p-q               =  "q" EQUAL qvalue
//c-p-expires         =  "expires" EQUAL delta-seconds
//contact-extension   =  generic-param
//delta-seconds       =  1*DIGIT
//Content-Disposition =  disp-type *( SEMI disp-param )
//disp-type           =  "render" / "session" / "icon" / "alert" / disp-extension-token
//disp-param          =  handling-param / generic-param
//handling-param      =  "handling" EQUAL ( "optional" / "required" / other-handling )
//other-handling      =  u_token
//disp-extension-token=  u_token
//Content-Encoding    =  content-coding *(COMMA content-coding)
//Content-Language    =  language-tag *(COMMA language-tag)
//language-tag        =  primary-tag *( "-" subtag )
//primary-tag         =  1*8ALPHA
//subtag              =  1*8ALPHA
//Content-Length      =  1*DIGIT
//Content-Type        =  media-type
//media-type          =  m-type SLASH m-subtype *(SEMI m-parameter)
//m-type              =  discrete-type / composite-type
//discrete-type       =  "text" / "image" / "audio" / "video" / "application" / extension-token
//composite-type      =  "message" / "multipart" / extension-token
//extension-token     =  ietf-token / x-token
//ietf-token          =  u_token
//x-token             =  "x-" u_token
//m-subtype           =  extension-token / iana-token
//iana-token          =  u_token
//m-parameter         =  m-attribute EQUAL m-value
//m-attribute         =  u_token
//m-value             =  u_token / quoted-string
//CSeq                =  1*DIGIT LWS Method
//Date                =  SIP-date
//SIP-date            =  rfc1123-date
//rfc1123-date        =  wkday "," SP date1 SP time SP "GMT"
//date1               =  2DIGIT SP month SP 4DIGIT ; day month year (e.g., 02 Jun 1982)
//time                =  2DIGIT ":" 2DIGIT ":" 2DIGIT ; 00:00:00 - 23:59:59
//wkday               =  "Mon" / "Tue" / "Wed" / "Thu" / "Fri" / "Sat" / "Sun"
//month               =  "Jan" / "Feb" / "Mar" / "Apr" / "May" / "Jun" / "Jul" / "Aug" / "Sep" / "Oct" / "Nov" / "Dec"
//Error-Info          =  error-uri *(COMMA error-uri)
//error-uri           =  LAQUOT absoluteURI RAQUOT *( SEMI generic-param )
//Expires             =  delta-seconds
//From                =  from-spec
//from-spec           =  ( name-addr / addr-spec ) *( SEMI from-param )
//from-param          =  tag-param / generic-param
//tag-param           =  "tag" EQUAL u_token
//In-Reply-To         =  u_callid *(COMMA u_callid)
//Max-Forwards        =  1*DIGIT
//MIME-Version        =  1*DIGIT "." 1*DIGIT
//Min-Expires         =  delta-seconds
//Organization        =  [TEXT-UTF8-TRIM]
//Priority            =  priority-value
//priority-value      =  "emergency" / "urgent" / "normal" / "non-urgent" / other-priority
//other-priority      =  u_token
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
//algorithm           =  "algorithm" EQUAL ( "MD5" / "MD5-sess" / u_token )
//qop-options         =  "qop" EQUAL LDQUOT qop-value *("," qop-value) RDQUOT
//qop-value           =  "auth" / "auth-int" / u_token
//Proxy-Authorization =  credentials
//Proxy-Require       =  option-tag *(COMMA option-tag)
//option-tag          =  u_token
//Record-Route        =  rec-route *(COMMA rec-route)
//rec-route           =  name-addr *( SEMI rr-param )
//rr-param            =  generic-param
//Reply-To            =  rplyto-spec
//rplyto-spec         =  ( name-addr / addr-spec ) *( SEMI rplyto-param )
//rplyto-param        =  generic-param
//Require             =  option-tag *(COMMA option-tag)
//Retry-After         =  delta-seconds [ comment ] *( SEMI retry-param )
//retry-param         =  ("duration" EQUAL delta-seconds) / generic-param
//Route               =  route-param *(COMMA route-param)
//route-param         =  name-addr *( SEMI rr-param )
//Server              =  server-val *(LWS server-val)
//server-val          =  product / comment
//product             =  u_token [SLASH product-version]
//product-version     =  u_token
//Subject             =  [TEXT-UTF8-TRIM]
//Supported           =  [option-tag *(COMMA option-tag)]
//Timestamp           =  1*(DIGIT) [ "." *(DIGIT) ] [ LWS delay ]
//delay               =  *(DIGIT) [ "." *(DIGIT) ]
//To                  =  ( name-addr / addr-spec ) *( SEMI to-param )
//to-param            =  tag-param / generic-param
//Unsupported         =  option-tag *(COMMA option-tag)
//User-Agent          =  server-val *(LWS server-val)
//Via                 =  via-parm *(COMMA via-parm)
//via-parm            =  sent-protocol LWS sent-by *( SEMI via-params )
//via-params          =  via-ttl / via-maddr / via-received / via-branch / via-extension
//via-ttl             =  "ttl" EQUAL ttl
//via-maddr           =  "maddr" EQUAL host
//via-received        =  "received" EQUAL (IPv4address / IPv6address)
//via-branch          =  "branch" EQUAL u_token
//via-extension       =  generic-param
//sent-protocol       =  protocol-name SLASH protocol-version SLASH transport
//protocol-name       =  "SIP" / u_token
//protocol-version    =  u_token
//transport           =  "UDP" / "TCP" / "TLS" / "SCTP" / other-transport
//sent-by             =  host [ COLON port ]
//ttl                 =  1*3DIGIT ; 0 to 255
//Warning             =  warning-value *(COMMA warning-value)
//warning-value       =  warn-code SP warn-agent SP warn-text
//warn-code           =  3DIGIT
//warn-agent          =  hostport / pseudonym
//warn-text           =  quoted-string
//pseudonym           =  u_token
//WWW-Authenticate    =  challenge
//extension-header    =  header-value
//header-name         =  u_token
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
//service-provider      = ";" provider-tag "=" u_RFC1035domain
//;service-provider      = ";" provider-tag "=" provider-hostname
//provider-tag          = "tsp"
//;provider-hostname     = u_RFC1035domain ; <domain> is defined in [RFC1035] ; See section 2.5.10
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
//; 25.1 Basic Rules
//reserved        =  ";" / "/" / "?" / ":" / "@" / "&" / "=" / "+" / "$" / ","
//escaped         =  "%" HEXDIG HEXDIG
//TEXT-UTF8-TRIM  =  1*TEXT-UTF8char *(LWS 1*TEXT-UTF8char)
//TEXT-UTF8char   =  %x21-7E / UTF8-NONASCII
//UTF8-NONASCII   =  %xC0-DF UTF8-CONT /
//                   %xE0-EF 2UTF8-CONT /
//                   %xF0-F7 3UTF8-CONT /
//                   %xF8-Fb 4UTF8-CONT /
//                   %xFC-FD 5UTF8-CONT
//UTF8-CONT       =  %x80-BF
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
//CRLF           =  (CR LF) / LF / CR; modified to be forgiving on line ender
//DIGIT          =  %x30-39 ; 0-9
//DQUOTE         =  %x22 ; " (Double Quote)
//HEXDIG         =  DIGIT / "A" / "B" / "C" / "D" / "E" / "F"
//LF             =  %x0A ; linefeed
//OCTET          =  %x00-FF ; 8 bits of data
//SP             =  %x20
////**** SABNF GRAMMAR ***

