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
#ifndef GRAMMAR2_H
#define GRAMMAR2_H

// rule ids
#define RULE_GRAMMAR2_ABS_PATH 51 // abs-path
#define RULE_GRAMMAR2_ABSOLUTEURI 48 // absoluteURI
#define RULE_GRAMMAR2_ACCEPT 67 // Accept
#define RULE_GRAMMAR2_ACCEPT_ENCODING 74 // Accept-Encoding
#define RULE_GRAMMAR2_ACCEPT_LANGUAGE 78 // Accept-Language
#define RULE_GRAMMAR2_ACCEPT_PARAM 70 // accept-param
#define RULE_GRAMMAR2_ACCEPT_RANGE 68 // accept-range
#define RULE_GRAMMAR2_ACKM 6 // ACKm
#define RULE_GRAMMAR2_ADDR_SPEC 112 // addr-spec
#define RULE_GRAMMAR2_AINFO 102 // ainfo
#define RULE_GRAMMAR2_ALERT_INFO 81 // Alert-Info
#define RULE_GRAMMAR2_ALERT_PARAM 82 // alert-param
#define RULE_GRAMMAR2_ALGORITHM 180 // algorithm
#define RULE_GRAMMAR2_ALLOW 83 // Allow
#define RULE_GRAMMAR2_ALPHA 271 // ALPHA
#define RULE_GRAMMAR2_AREA_SPECIFIER 240 // area-specifier
#define RULE_GRAMMAR2_AUTH_PARAM 97 // auth-param
#define RULE_GRAMMAR2_AUTH_PARAM_NAME 98 // auth-param-name
#define RULE_GRAMMAR2_AUTH_SCHEME 100 // auth-scheme
#define RULE_GRAMMAR2_AUTHENTICATION_INFO 101 // Authentication-Info
#define RULE_GRAMMAR2_AUTHORITY 59 // authority
#define RULE_GRAMMAR2_AUTHORIZATION 84 // Authorization
#define RULE_GRAMMAR2_BASE_PHONE_NUMBER 236 // base-phone-number
#define RULE_GRAMMAR2_BLANKSPACE 1 // BlankSpace
#define RULE_GRAMMAR2_BYEM 8 // BYEm
#define RULE_GRAMMAR2_C_P_EXPIRES 117 // c-p-expires
#define RULE_GRAMMAR2_C_P_Q 116 // c-p-q
#define RULE_GRAMMAR2_CALL_INFO 106 // Call-Info
#define RULE_GRAMMAR2_CANCELM 9 // CANCELm
#define RULE_GRAMMAR2_CHALLENGE 169 // challenge
#define RULE_GRAMMAR2_CHAR 272 // CHAR
#define RULE_GRAMMAR2_CNONCE 93 // cnonce
#define RULE_GRAMMAR2_CNONCE_VALUE 94 // cnonce-value
#define RULE_GRAMMAR2_CODINGS 76 // codings
#define RULE_GRAMMAR2_COMMENT 264 // comment
#define RULE_GRAMMAR2_COMPOSITE_TYPE 136 // composite-type
#define RULE_GRAMMAR2_CONTACT 109 // Contact
#define RULE_GRAMMAR2_CONTACT_EXTENSION 118 // contact-extension
#define RULE_GRAMMAR2_CONTACT_PARAM 110 // contact-param
#define RULE_GRAMMAR2_CONTACT_PARAMS 115 // contact-params
#define RULE_GRAMMAR2_CONTENT_CODING 77 // content-coding
#define RULE_GRAMMAR2_CONTENT_DISPOSITION 120 // Content-Disposition
#define RULE_GRAMMAR2_CONTENT_ENCODING 126 // Content-Encoding
#define RULE_GRAMMAR2_CONTENT_LANGUAGE 127 // Content-Language
#define RULE_GRAMMAR2_CONTENT_LENGTH 131 // Content-Length
#define RULE_GRAMMAR2_CONTENT_TYPE 132 // Content-Type
#define RULE_GRAMMAR2_CR 273 // CR
#define RULE_GRAMMAR2_CREDENTIALS 85 // credentials
#define RULE_GRAMMAR2_CRLF 274 // CRLF
#define RULE_GRAMMAR2_CSEQ 145 // CSeq
#define RULE_GRAMMAR2_CTEXT 265 // ctext
#define RULE_GRAMMAR2_D_NAME 114 // d-name
#define RULE_GRAMMAR2_DATE 146 // Date
#define RULE_GRAMMAR2_DATE1 149 // date1
#define RULE_GRAMMAR2_DELAY 204 // delay
#define RULE_GRAMMAR2_DELTA_SECONDS 119 // delta-seconds
#define RULE_GRAMMAR2_DIG_RESP 87 // dig-resp
#define RULE_GRAMMAR2_DIGEST_CLN 171 // digest-cln
#define RULE_GRAMMAR2_DIGEST_RESPONSE 86 // digest-response
#define RULE_GRAMMAR2_DIGEST_URI 90 // digest-uri
#define RULE_GRAMMAR2_DIGEST_URI_VALUE 91 // digest-uri-value
#define RULE_GRAMMAR2_DIGIT 275 // DIGIT
#define RULE_GRAMMAR2_DISCRETE_TYPE 135 // discrete-type
#define RULE_GRAMMAR2_DISP_EXTENSION_TOKEN 125 // disp-extension-token
#define RULE_GRAMMAR2_DISP_PARAM 122 // disp-param
#define RULE_GRAMMAR2_DISP_TYPE 121 // disp-type
#define RULE_GRAMMAR2_DISPLAY_NAME 113 // display-name
#define RULE_GRAMMAR2_DOMAIN 174 // domain
#define RULE_GRAMMAR2_DRESPONSE 96 // dresponse
#define RULE_GRAMMAR2_DTMF_DIGIT 257 // dtmf-digit
#define RULE_GRAMMAR2_ENCODING 75 // encoding
#define RULE_GRAMMAR2_ERROR_INFO 153 // Error-Info
#define RULE_GRAMMAR2_ERROR_URI 154 // error-uri
#define RULE_GRAMMAR2_ESCAPED 259 // escaped
#define RULE_GRAMMAR2_EXPIRES 155 // Expires
#define RULE_GRAMMAR2_EXTENSION_HEADER 230 // extension-header
#define RULE_GRAMMAR2_EXTENSION_METHOD 12 // extension-method
#define RULE_GRAMMAR2_EXTENSION_TOKEN 137 // extension-token
#define RULE_GRAMMAR2_FROM 156 // From
#define RULE_GRAMMAR2_FROM_PARAM 158 // from-param
#define RULE_GRAMMAR2_FROM_SPEC 157 // from-spec
#define RULE_GRAMMAR2_FUTURE_EXTENSION 249 // future-extension
#define RULE_GRAMMAR2_GEN_VALUE 73 // gen-value
#define RULE_GRAMMAR2_GENERIC_PARAM 72 // generic-param
#define RULE_GRAMMAR2_GLOBAL_NETWORK_PREFIX 244 // global-network-prefix
#define RULE_GRAMMAR2_GLOBAL_PHONE_NUMBER 235 // global-phone-number
#define RULE_GRAMMAR2_HANDLING_PARAM 123 // handling-param
#define RULE_GRAMMAR2_HEADER 43 // header
#define RULE_GRAMMAR2_HEADER_NAME 231 // header-name
#define RULE_GRAMMAR2_HEADER_VALUE 232 // header-value
#define RULE_GRAMMAR2_HEADERS 42 // headers
#define RULE_GRAMMAR2_HEXDIG 276 // HEXDIG
#define RULE_GRAMMAR2_HIER_PART 49 // hier-part
#define RULE_GRAMMAR2_HNAME 44 // hname
#define RULE_GRAMMAR2_HNV_UNRESERVED 46 // hnv-unreserved
#define RULE_GRAMMAR2_HOST 24 // host
#define RULE_GRAMMAR2_HOSTNAME 25 // hostname
#define RULE_GRAMMAR2_HOSTPORT 23 // hostport
#define RULE_GRAMMAR2_HVALUE 45 // hvalue
#define RULE_GRAMMAR2_IANA_TOKEN 141 // iana-token
#define RULE_GRAMMAR2_IETF_TOKEN 138 // ietf-token
#define RULE_GRAMMAR2_IN_REPLY_TO 160 // In-Reply-To
#define RULE_GRAMMAR2_INFO 107 // info
#define RULE_GRAMMAR2_INFO_PARAM 108 // info-param
#define RULE_GRAMMAR2_INVITEM 5 // INVITEm
#define RULE_GRAMMAR2_IPV4ADDRESS 63 // IPv4address
#define RULE_GRAMMAR2_IPV6ADDRESS 65 // IPv6address
#define RULE_GRAMMAR2_IPV6REFERENCE 64 // IPv6reference
#define RULE_GRAMMAR2_ISDN_SUBADDRESS 238 // isdn-subaddress
#define RULE_GRAMMAR2_LANGUAGE 79 // language
#define RULE_GRAMMAR2_LANGUAGE_RANGE 80 // language-range
#define RULE_GRAMMAR2_LANGUAGE_TAG 128 // language-tag
#define RULE_GRAMMAR2_LF 277 // LF
#define RULE_GRAMMAR2_LOCAL_NETWORK_PREFIX 245 // local-network-prefix
#define RULE_GRAMMAR2_LOCAL_PHONE_NUMBER 237 // local-phone-number
#define RULE_GRAMMAR2_LR_PARAM 36 // lr-param
#define RULE_GRAMMAR2_M_ATTRIBUTE 143 // m-attribute
#define RULE_GRAMMAR2_M_PARAMETER 142 // m-parameter
#define RULE_GRAMMAR2_M_SUBTYPE 140 // m-subtype
#define RULE_GRAMMAR2_M_TYPE 134 // m-type
#define RULE_GRAMMAR2_M_VALUE 144 // m-value
#define RULE_GRAMMAR2_MADDR_PARAM 35 // maddr-param
#define RULE_GRAMMAR2_MAX_FORWARDS 161 // Max-Forwards
#define RULE_GRAMMAR2_MEDIA_RANGE 69 // media-range
#define RULE_GRAMMAR2_MEDIA_TYPE 133 // media-type
#define RULE_GRAMMAR2_MESSAGE_BODY 233 // message-body
#define RULE_GRAMMAR2_MESSAGE_HEADER 66 // message-header
#define RULE_GRAMMAR2_MESSAGE_QOP 92 // message-qop
#define RULE_GRAMMAR2_METHOD 11 // Method
#define RULE_GRAMMAR2_METHOD_PARAM 33 // method-param
#define RULE_GRAMMAR2_MIME_VERSION 162 // MIME-Version
#define RULE_GRAMMAR2_MIN_EXPIRES 163 // Min-Expires
#define RULE_GRAMMAR2_MONTH 152 // month
#define RULE_GRAMMAR2_NAME_ADDR 111 // name-addr
#define RULE_GRAMMAR2_NET_PATH 50 // net-path
#define RULE_GRAMMAR2_NETWORK_PREFIX 243 // network-prefix
#define RULE_GRAMMAR2_NEXTNONCE 103 // nextnonce
#define RULE_GRAMMAR2_NONCE 176 // nonce
#define RULE_GRAMMAR2_NONCE_COUNT 95 // nonce-count
#define RULE_GRAMMAR2_NONCE_VALUE 177 // nonce-value
#define RULE_GRAMMAR2_OCTET 278 // OCTET
#define RULE_GRAMMAR2_ONE_SECOND_PAUSE 255 // one-second-pause
#define RULE_GRAMMAR2_OPAQUE 178 // opaque
#define RULE_GRAMMAR2_OPAQUE_PART 52 // opaque-part
#define RULE_GRAMMAR2_OPTION_TAG 185 // option-tag
#define RULE_GRAMMAR2_OPTIONSM 7 // OPTIONSm
#define RULE_GRAMMAR2_ORGANIZATION 164 // Organization
#define RULE_GRAMMAR2_OTHER_CHALLENGE 170 // other-challenge
#define RULE_GRAMMAR2_OTHER_HANDLING 124 // other-handling
#define RULE_GRAMMAR2_OTHER_PARAM 37 // other-param
#define RULE_GRAMMAR2_OTHER_PRIORITY 167 // other-priority
#define RULE_GRAMMAR2_OTHER_RESPONSE 99 // other-response
#define RULE_GRAMMAR2_OTHER_TRANSPORT 30 // other-transport
#define RULE_GRAMMAR2_OTHER_USER 32 // other-user
#define RULE_GRAMMAR2_PARAM 57 // param
#define RULE_GRAMMAR2_PARAM_UNRESERVED 41 // param-unreserved
#define RULE_GRAMMAR2_PARAMCHAR 40 // paramchar
#define RULE_GRAMMAR2_PASSWORD 22 // password
#define RULE_GRAMMAR2_PATH_SEGMENTS 55 // path-segments
#define RULE_GRAMMAR2_PAUSE_CHARACTER 254 // pause-character
#define RULE_GRAMMAR2_PCHAR 58 // pchar
#define RULE_GRAMMAR2_PHONE_CONTEXT_IDENT 242 // phone-context-ident
#define RULE_GRAMMAR2_PHONE_CONTEXT_TAG 241 // phone-context-tag
#define RULE_GRAMMAR2_PHONEDIGIT 252 // phonedigit
#define RULE_GRAMMAR2_PNAME 38 // pname
#define RULE_GRAMMAR2_PORT 26 // port
#define RULE_GRAMMAR2_POST_DIAL 239 // post-dial
#define RULE_GRAMMAR2_PRIMARY_TAG 129 // primary-tag
#define RULE_GRAMMAR2_PRIORITY 165 // Priority
#define RULE_GRAMMAR2_PRIORITY_VALUE 166 // priority-value
#define RULE_GRAMMAR2_PRIVATE_PREFIX 246 // private-prefix
#define RULE_GRAMMAR2_PRODUCT 199 // product
#define RULE_GRAMMAR2_PRODUCT_VERSION 200 // product-version
#define RULE_GRAMMAR2_PROTOCOL_NAME 218 // protocol-name
#define RULE_GRAMMAR2_PROTOCOL_VERSION 219 // protocol-version
#define RULE_GRAMMAR2_PROVIDER_TAG 248 // provider-tag
#define RULE_GRAMMAR2_PROXY_AUTHENTICATE 168 // Proxy-Authenticate
#define RULE_GRAMMAR2_PROXY_AUTHORIZATION 183 // Proxy-Authorization
#define RULE_GRAMMAR2_PROXY_REQUIRE 184 // Proxy-Require
#define RULE_GRAMMAR2_PSEUDONYM 228 // pseudonym
#define RULE_GRAMMAR2_PVALUE 39 // pvalue
#define RULE_GRAMMAR2_Q_STRING 267 // q-string
#define RULE_GRAMMAR2_QDTEXT 268 // qdtext
#define RULE_GRAMMAR2_QOP_OPTIONS 181 // qop-options
#define RULE_GRAMMAR2_QOP_VALUE 182 // qop-value
#define RULE_GRAMMAR2_QUERY 62 // query
#define RULE_GRAMMAR2_QUOTED_PAIR 269 // quoted-pair
#define RULE_GRAMMAR2_QUOTED_STRING 266 // quoted-string
#define RULE_GRAMMAR2_QVALUE 71 // qvalue
#define RULE_GRAMMAR2_REALM 172 // realm
#define RULE_GRAMMAR2_REALM_VALUE 173 // realm-value
#define RULE_GRAMMAR2_REASON_PHRASE 16 // Reason-Phrase
#define RULE_GRAMMAR2_REC_ROUTE 187 // rec-route
#define RULE_GRAMMAR2_RECORD_ROUTE 186 // Record-Route
#define RULE_GRAMMAR2_REG_NAME 61 // reg-name
#define RULE_GRAMMAR2_REGISTERM 10 // REGISTERm
#define RULE_GRAMMAR2_REPLY_TO 189 // Reply-To
#define RULE_GRAMMAR2_REQUEST 2 // Request
#define RULE_GRAMMAR2_REQUEST_LINE 3 // Request-Line
#define RULE_GRAMMAR2_REQUEST_URI 47 // Request-URI
#define RULE_GRAMMAR2_REQUIRE 192 // Require
#define RULE_GRAMMAR2_RESERVED 258 // reserved
#define RULE_GRAMMAR2_RESPONSE 13 // Response
#define RULE_GRAMMAR2_RESPONSE_AUTH 104 // response-auth
#define RULE_GRAMMAR2_RESPONSE_DIGEST 105 // response-digest
#define RULE_GRAMMAR2_RETRY_AFTER 193 // Retry-After
#define RULE_GRAMMAR2_RETRY_PARAM 194 // retry-param
#define RULE_GRAMMAR2_RFC1123_DATE 148 // rfc1123-date
#define RULE_GRAMMAR2_ROUTE 195 // Route
#define RULE_GRAMMAR2_ROUTE_PARAM 196 // route-param
#define RULE_GRAMMAR2_RPLYTO_PARAM 191 // rplyto-param
#define RULE_GRAMMAR2_RPLYTO_SPEC 190 // rplyto-spec
#define RULE_GRAMMAR2_RR_PARAM 188 // rr-param
#define RULE_GRAMMAR2_SEGMENT 56 // segment
#define RULE_GRAMMAR2_SENT_BY 221 // sent-by
#define RULE_GRAMMAR2_SENT_PROTOCOL 217 // sent-protocol
#define RULE_GRAMMAR2_SERVER 197 // Server
#define RULE_GRAMMAR2_SERVER_VAL 198 // server-val
#define RULE_GRAMMAR2_SERVICE_PROVIDER 247 // service-provider
#define RULE_GRAMMAR2_SIP_DATE 147 // SIP-date
#define RULE_GRAMMAR2_SIP_MESSAGE 0 // SIP-message
#define RULE_GRAMMAR2_SIP_URI 17 // SIP-URI
#define RULE_GRAMMAR2_SIP_VERSION 4 // SIP-Version
#define RULE_GRAMMAR2_SIPS_URI 18 // SIPS-URI
#define RULE_GRAMMAR2_SP 279 // SP
#define RULE_GRAMMAR2_SRVR 60 // srvr
#define RULE_GRAMMAR2_STALE 179 // stale
#define RULE_GRAMMAR2_STATUS_CODE 15 // Status-Code
#define RULE_GRAMMAR2_STATUS_LINE 14 // Status-Line
#define RULE_GRAMMAR2_SUBJECT 201 // Subject
#define RULE_GRAMMAR2_SUBTAG 130 // subtag
#define RULE_GRAMMAR2_SUPPORTED 202 // Supported
#define RULE_GRAMMAR2_TAG_PARAM 159 // tag-param
#define RULE_GRAMMAR2_TEL_QUOTED_STRING 251 // tel-quoted-string
#define RULE_GRAMMAR2_TELEPHONE_SUBSCRIBER 234 // telephone-subscriber
#define RULE_GRAMMAR2_TEXT_UTF8_TRIM 260 // TEXT-UTF8-TRIM
#define RULE_GRAMMAR2_TEXT_UTF8CHAR 261 // TEXT-UTF8char
#define RULE_GRAMMAR2_TIME 150 // time
#define RULE_GRAMMAR2_TIMESTAMP 203 // Timestamp
#define RULE_GRAMMAR2_TO 205 // To
#define RULE_GRAMMAR2_TO_PARAM 206 // to-param
#define RULE_GRAMMAR2_TOKEN_CHAR 250 // token-char
#define RULE_GRAMMAR2_TRANSPORT 220 // transport
#define RULE_GRAMMAR2_TRANSPORT_PARAM 29 // transport-param
#define RULE_GRAMMAR2_TTL 222 // ttl
#define RULE_GRAMMAR2_TTL_PARAM 34 // ttl-param
#define RULE_GRAMMAR2_UNSUPPORTED 207 // Unsupported
#define RULE_GRAMMAR2_URI 175 // URI
#define RULE_GRAMMAR2_URI_PARAMETER 28 // uri-parameter
#define RULE_GRAMMAR2_URI_PARAMETERS 27 // uri-parameters
#define RULE_GRAMMAR2_URIC 53 // uric
#define RULE_GRAMMAR2_URIC_NO_SLASH 54 // uric-no-slash
#define RULE_GRAMMAR2_USER 20 // user
#define RULE_GRAMMAR2_USER_AGENT 208 // User-Agent
#define RULE_GRAMMAR2_USER_PARAM 31 // user-param
#define RULE_GRAMMAR2_USER_UNRESERVED 21 // user-unreserved
#define RULE_GRAMMAR2_USERINFO 19 // userinfo
#define RULE_GRAMMAR2_USERNAME 88 // username
#define RULE_GRAMMAR2_USERNAME_VALUE 89 // username-value
#define RULE_GRAMMAR2_UTF8_CONT 263 // UTF8-CONT
#define RULE_GRAMMAR2_UTF8_NONASCII 262 // UTF8-NONASCII
#define RULE_GRAMMAR2_VIA 209 // Via
#define RULE_GRAMMAR2_VIA_BRANCH 215 // via-branch
#define RULE_GRAMMAR2_VIA_EXTENSION 216 // via-extension
#define RULE_GRAMMAR2_VIA_MADDR 213 // via-maddr
#define RULE_GRAMMAR2_VIA_PARAMS 211 // via-params
#define RULE_GRAMMAR2_VIA_PARM 210 // via-parm
#define RULE_GRAMMAR2_VIA_RECEIVED 214 // via-received
#define RULE_GRAMMAR2_VIA_TTL 212 // via-ttl
#define RULE_GRAMMAR2_VISUAL_SEPARATOR 253 // visual-separator
#define RULE_GRAMMAR2_WAIT_FOR_DIAL_TONE 256 // wait-for-dial-tone
#define RULE_GRAMMAR2_WARN_AGENT 226 // warn-agent
#define RULE_GRAMMAR2_WARN_CODE 225 // warn-code
#define RULE_GRAMMAR2_WARN_TEXT 227 // warn-text
#define RULE_GRAMMAR2_WARNING 223 // Warning
#define RULE_GRAMMAR2_WARNING_VALUE 224 // warning-value
#define RULE_GRAMMAR2_WKDAY 151 // wkday
#define RULE_GRAMMAR2_WSP 270 // WSP
#define RULE_GRAMMAR2_WWW_AUTHENTICATE 229 // WWW-Authenticate
#define RULE_GRAMMAR2_X_TOKEN 139 // x-token
#define RULE_COUNT_GRAMMAR2 280

// UDT ids
#define UDT_GRAMMAR2_E_DOMAINLABEL 2 // e_domainlabel
#define UDT_GRAMMAR2_E_SWS 25 // e_SWS
#define UDT_GRAMMAR2_U_CALLID 7 // u_callid
#define UDT_GRAMMAR2_U_COLON 21 // u_COLON
#define UDT_GRAMMAR2_U_COMMA 8 // u_COMMA
#define UDT_GRAMMAR2_U_EQUAL 11 // u_EQUAL
#define UDT_GRAMMAR2_U_HCOLON 6 // u_HCOLON
#define UDT_GRAMMAR2_U_LAQUOT 12 // u_LAQUOT
#define UDT_GRAMMAR2_U_LDQUOT 15 // u_LDQUOT
#define UDT_GRAMMAR2_U_LHEX 19 // u_LHEX
#define UDT_GRAMMAR2_U_LPAREN 23 // u_LPAREN
#define UDT_GRAMMAR2_U_LWS 14 // u_LWS
#define UDT_GRAMMAR2_U_NC_VALUE 17 // u_nc-value
#define UDT_GRAMMAR2_U_ONE_OR_MORE_UNRESERVED 1 // u_one-or-more-unreserved
#define UDT_GRAMMAR2_U_RAQUOT 13 // u_RAQUOT
#define UDT_GRAMMAR2_U_RDQUOT 16 // u_RDQUOT
#define UDT_GRAMMAR2_U_REQUEST_DIGEST 18 // u_request-digest
#define UDT_GRAMMAR2_U_RFC1035DOMAIN 22 // u_RFC1035domain
#define UDT_GRAMMAR2_U_RPAREN 24 // u_RPAREN
#define UDT_GRAMMAR2_U_SCHEME 5 // u_scheme
#define UDT_GRAMMAR2_U_SEMI 9 // u_SEMI
#define UDT_GRAMMAR2_U_SLASH 10 // u_SLASH
#define UDT_GRAMMAR2_U_STAR 20 // u_STAR
#define UDT_GRAMMAR2_U_TOKEN 0 // u_token
#define UDT_GRAMMAR2_U_TOPLABEL 3 // u_toplabel
#define UDT_GRAMMAR2_U_UNRESERVED 4 // u_unreserved
#define UDT_COUNT_GRAMMAR2 26

// Parser initialization data
extern void* vpParserInit_Grammar2;

#endif // GRAMMAR2_H

//**** SABNF GRAMMAR ****
//;
//; Grammar2 - removal of white space (WSP, SWS & LWS) and line ends (CRLF, CR, LF)
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
//Reason-Phrase     =  *(reserved / u_one-or-more-unreserved / escaped / UTF8-NONASCII / UTF8-CONT / (%x20 / %x09))
//
//; SIP URI
//SIP-URI           =  "sip:" [ userinfo ] hostport uri-parameters [ headers ]
//SIPS-URI          =  "sips:" [ userinfo ] hostport uri-parameters [ headers ]
//userinfo          =  ( user / telephone-subscriber ) [ ":" password ] "@"
//user              =  1*( u_one-or-more-unreserved / escaped / user-unreserved )
//user-unreserved   =  "&" / "=" / "+" / "$" / "," / ";" / "?" / "/"
//password          =  *( u_one-or-more-unreserved / escaped / "&" / "=" / "+" / "$" / "," )
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
//hname             =  1*( hnv-unreserved / u_one-or-more-unreserved / escaped )
//hvalue            =  *( hnv-unreserved / u_one-or-more-unreserved / escaped )
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
//reg-name       =  1*( u_one-or-more-unreserved / escaped / "$" / "," / ";" / ":" / "@" / "&" / "=" / "+" )
//query          =  *uric
//
//; IP ADDRESSES
//IPv4address    =  1*3DIGIT "." 1*3DIGIT "." 1*3DIGIT "." 1*3DIGIT
//IPv6reference  =  "[" IPv6address "]"
//IPv6address    =  *(HEXDIG / ":" / ".") ; to be parsed in semantics
//
//; MESSAGE HEADERS
//message-header      = (  "Accept"                   u_HCOLON Accept
//                      /  "Accept-Encoding"          u_HCOLON Accept-Encoding
//                      /  "Accept-Language"          u_HCOLON Accept-Language
//                      /  "Alert-Info"               u_HCOLON Alert-Info
//                      /  "Allow"                    u_HCOLON Allow
//                      /  "Authentication-Info"      u_HCOLON Authentication-Info
//                      /  "Authorization"            u_HCOLON Authorization
//                      /  ( "Call-ID" / "i" )        u_HCOLON u_callid
//                      /  "Call-Info"                u_HCOLON Call-Info
//                      /  ("Contact" / "m" )         u_HCOLON Contact
//                      /  "Content-Disposition"      u_HCOLON Content-Disposition
//                      /  ("Content-Encoding" / "e") u_HCOLON Content-Encoding
//                      /  "Content-Language"         u_HCOLON Content-Language
//                      /  ("Content-Length" / "l")   u_HCOLON Content-Length
//                      /  ( "Content-Type" / "c" )   u_HCOLON Content-Type
//                      /  "CSeq"                     u_HCOLON CSeq
//                      /  "Date"                     u_HCOLON Date
//                      /  "Error-Info"               u_HCOLON Error-Info
//                      /  "Expires"                  u_HCOLON Expires
//                      /  ( "From" / "f" )           u_HCOLON From
//                      /  "In-Reply-To"              u_HCOLON In-Reply-To
//                      /  "Max-Forwards"             u_HCOLON Max-Forwards
//                      /  "MIME-Version"             u_HCOLON MIME-Version
//                      /  "Min-Expires"              u_HCOLON Min-Expires
//                      /  "Organization"             u_HCOLON Organization
//                      /  "Priority"                 u_HCOLON Priority
//                      /  "Proxy-Authenticate"       u_HCOLON Proxy-Authenticate
//                      /  "Proxy-Authorization"      u_HCOLON Proxy-Authorization
//                      /  "Proxy-Require"            u_HCOLON Proxy-Require
//                      /  "Record-Route"             u_HCOLON Record-Route
//                      /  "Reply-To"                 u_HCOLON Reply-To
//                      /  "Require"                  u_HCOLON Require
//                      /  "Retry-After"              u_HCOLON Retry-After
//                      /  "Route"                    u_HCOLON Route
//                      /  "Server"                   u_HCOLON Server
//                      /  ( "Subject" / "s" )        u_HCOLON Subject
//                      /  ( "Supported" / "k" )      u_HCOLON Supported
//                      /  "Timestamp"                u_HCOLON Timestamp
//                      /  ( "To" / "t" )             u_HCOLON To
//                      /  "Unsupported"              u_HCOLON Unsupported
//                      /  "User-Agent"               u_HCOLON User-Agent
//                      /  ( "Via" / "v" )            u_HCOLON Via
//                      /  "Warning"                  u_HCOLON Warning
//                      /  "WWW-Authenticate"         u_HCOLON WWW-Authenticate
//                      /  header-name                u_HCOLON extension-header) CRLF
//
//Accept              =  [ accept-range *(u_COMMA accept-range) ]
//accept-range        =  media-range *(u_SEMI accept-param)
//media-range         =  ( "*/*" / ( m-type u_SLASH ("*" / m-subtype) ) ) *( u_SEMI m-parameter )
//accept-param        =  ("q" u_EQUAL qvalue) / generic-param
//qvalue              =  ( "0" [ "." 0*3DIGIT ] ) / ( "1" [ "." 0*3("0") ] )
//generic-param       =  u_token [ u_EQUAL gen-value ]
//gen-value           =  u_token / host / quoted-string
//Accept-Encoding     =  [ encoding *(u_COMMA encoding) ]
//encoding            =  codings *(u_SEMI accept-param)
//codings             =  content-coding / "*"
//content-coding      =  u_token
//Accept-Language     =  [ language *(u_COMMA language) ]
//language            =  language-range *(u_SEMI accept-param)
//language-range      =  ( ( 1*8ALPHA *( "-" 1*8ALPHA ) ) / "*" )
//Alert-Info          =  alert-param *(u_COMMA alert-param)
//alert-param         =  u_LAQUOT absoluteURI u_RAQUOT *( u_SEMI generic-param )
//Allow               =  [Method *(u_COMMA Method)]
//Authorization       =  credentials
//credentials         =  ("Digest" u_LWS digest-response) / other-response
//digest-response     =  dig-resp *(u_COMMA dig-resp)
//dig-resp            =  username / realm / nonce / digest-uri
//                      / dresponse / algorithm / cnonce
//                      / opaque / message-qop
//                      / nonce-count / auth-param
//username            =  "username" u_EQUAL username-value
//username-value      =  quoted-string
//digest-uri          =  "uri" u_EQUAL u_LDQUOT digest-uri-value u_RDQUOT
//digest-uri-value    =  *(%x20-21/%x23-FF)
//message-qop         =  "qop" u_EQUAL qop-value
//cnonce              =  "cnonce" u_EQUAL cnonce-value
//cnonce-value        =  nonce-value
//nonce-count         =  "nc" u_EQUAL u_nc-value
//;nc-value            =  8LHEX
//dresponse           =  "response" u_EQUAL u_request-digest
//;request-digest      =  u_LDQUOT u_32LHEX u_RDQUOT
//auth-param          =  auth-param-name u_EQUAL ( u_token / quoted-string )
//auth-param-name     =  u_token
//other-response      =  auth-scheme u_LWS auth-param *(u_COMMA auth-param)
//auth-scheme         =  u_token
//Authentication-Info =  ainfo *(u_COMMA ainfo)
//ainfo               =  nextnonce / message-qop / response-auth / cnonce / nonce-count
//nextnonce           =  "nextnonce" u_EQUAL nonce-value
//response-auth       =  "rspauth" u_EQUAL response-digest
//response-digest     =  u_LDQUOT *u_LHEX u_RDQUOT
//Call-Info           =  info *(u_COMMA info)
//info                =  u_LAQUOT absoluteURI u_RAQUOT *( u_SEMI info-param)
//info-param          =  ( "purpose" u_EQUAL ( "icon" / "info" / "card" / u_token ) ) / generic-param
//Contact             =  ( u_STAR / (contact-param *(u_COMMA contact-param)))
//contact-param       =  (name-addr / addr-spec) *(u_SEMI contact-params)
//name-addr           =  display-name u_LAQUOT addr-spec u_RAQUOT
//addr-spec           =  SIP-URI / SIPS-URI / absoluteURI
//display-name        =  quoted-string / d-name
//d-name              =  [u_token *(u_LWS u_token)]
//contact-params      =  c-p-q / c-p-expires / contact-extension
//c-p-q               =  "q" u_EQUAL qvalue
//c-p-expires         =  "expires" u_EQUAL delta-seconds
//contact-extension   =  generic-param
//delta-seconds       =  1*DIGIT
//Content-Disposition =  disp-type *( u_SEMI disp-param )
//disp-type           =  "render" / "session" / "icon" / "alert" / disp-extension-token
//disp-param          =  handling-param / generic-param
//handling-param      =  "handling" u_EQUAL ( "optional" / "required" / other-handling )
//other-handling      =  u_token
//disp-extension-token=  u_token
//Content-Encoding    =  content-coding *(u_COMMA content-coding)
//Content-Language    =  language-tag *(u_COMMA language-tag)
//language-tag        =  primary-tag *( "-" subtag )
//primary-tag         =  1*8ALPHA
//subtag              =  1*8ALPHA
//Content-Length      =  1*DIGIT
//Content-Type        =  media-type
//media-type          =  m-type u_SLASH m-subtype *(u_SEMI m-parameter)
//m-type              =  discrete-type / composite-type
//discrete-type       =  "text" / "image" / "audio" / "video" / "application" / extension-token
//composite-type      =  "message" / "multipart" / extension-token
//extension-token     =  ietf-token / x-token
//ietf-token          =  u_token
//x-token             =  "x-" u_token
//m-subtype           =  extension-token / iana-token
//iana-token          =  u_token
//m-parameter         =  m-attribute u_EQUAL m-value
//m-attribute         =  u_token
//m-value             =  u_token / quoted-string
//CSeq                =  1*DIGIT u_LWS Method
//Date                =  SIP-date
//SIP-date            =  rfc1123-date
//rfc1123-date        =  wkday "," SP date1 SP time SP "GMT"
//date1               =  2DIGIT SP month SP 4DIGIT ; day month year (e.g., 02 Jun 1982)
//time                =  2DIGIT ":" 2DIGIT ":" 2DIGIT ; 00:00:00 - 23:59:59
//wkday               =  "Mon" / "Tue" / "Wed" / "Thu" / "Fri" / "Sat" / "Sun"
//month               =  "Jan" / "Feb" / "Mar" / "Apr" / "May" / "Jun" / "Jul" / "Aug" / "Sep" / "Oct" / "Nov" / "Dec"
//Error-Info          =  error-uri *(u_COMMA error-uri)
//error-uri           =  u_LAQUOT absoluteURI u_RAQUOT *( u_SEMI generic-param )
//Expires             =  delta-seconds
//From                =  from-spec
//from-spec           =  ( name-addr / addr-spec ) *( u_SEMI from-param )
//from-param          =  tag-param / generic-param
//tag-param           =  "tag" u_EQUAL u_token
//In-Reply-To         =  u_callid *(u_COMMA u_callid)
//Max-Forwards        =  1*DIGIT
//MIME-Version        =  1*DIGIT "." 1*DIGIT
//Min-Expires         =  delta-seconds
//Organization        =  [TEXT-UTF8-TRIM]
//Priority            =  priority-value
//priority-value      =  "emergency" / "urgent" / "normal" / "non-urgent" / other-priority
//other-priority      =  u_token
//Proxy-Authenticate  =  challenge
//challenge           =  ("Digest" u_LWS digest-cln *(u_COMMA digest-cln)) / other-challenge
//other-challenge     =  auth-scheme u_LWS auth-param *(u_COMMA auth-param)
//digest-cln          =  realm / domain / nonce / opaque / stale / algorithm / qop-options / auth-param
//realm               =  "realm" u_EQUAL realm-value
//realm-value         =  quoted-string
//domain              =  "domain" u_EQUAL u_LDQUOT URI *( 1*SP URI ) u_RDQUOT
//URI                 =  absoluteURI / abs-path
//nonce               =  "nonce" u_EQUAL nonce-value
//nonce-value         =  quoted-string
//opaque              =  "opaque" u_EQUAL quoted-string
//stale               =  "stale" u_EQUAL ( "true" / "false" )
//algorithm           =  "algorithm" u_EQUAL ( "MD5" / "MD5-sess" / u_token )
//qop-options         =  "qop" u_EQUAL u_LDQUOT qop-value *("," qop-value) u_RDQUOT
//qop-value           =  "auth" / "auth-int" / u_token
//Proxy-Authorization =  credentials
//Proxy-Require       =  option-tag *(u_COMMA option-tag)
//option-tag          =  u_token
//Record-Route        =  rec-route *(u_COMMA rec-route)
//rec-route           =  name-addr *( u_SEMI rr-param )
//rr-param            =  generic-param
//Reply-To            =  rplyto-spec
//rplyto-spec         =  ( name-addr / addr-spec ) *( u_SEMI rplyto-param )
//rplyto-param        =  generic-param
//Require             =  option-tag *(u_COMMA option-tag)
//Retry-After         =  delta-seconds [ comment ] *( u_SEMI retry-param )
//retry-param         =  ("duration" u_EQUAL delta-seconds) / generic-param
//Route               =  route-param *(u_COMMA route-param)
//route-param         =  name-addr *( u_SEMI rr-param )
//Server              =  server-val *(u_LWS server-val)
//server-val          =  product / comment
//product             =  u_token [u_SLASH product-version]
//product-version     =  u_token
//Subject             =  [TEXT-UTF8-TRIM]
//Supported           =  [option-tag *(u_COMMA option-tag)]
//Timestamp           =  1*(DIGIT) [ "." *(DIGIT) ] [ u_LWS delay ]
//delay               =  *(DIGIT) [ "." *(DIGIT) ]
//To                  =  ( name-addr / addr-spec ) *( u_SEMI to-param )
//to-param            =  tag-param / generic-param
//Unsupported         =  option-tag *(u_COMMA option-tag)
//User-Agent          =  server-val *(u_LWS server-val)
//Via                 =  via-parm *(u_COMMA via-parm)
//via-parm            =  sent-protocol u_LWS sent-by *( u_SEMI via-params )
//via-params          =  via-ttl / via-maddr / via-received / via-branch / via-extension
//via-ttl             =  "ttl" u_EQUAL ttl
//via-maddr           =  "maddr" u_EQUAL host
//via-received        =  "received" u_EQUAL (IPv4address / IPv6address)
//via-branch          =  "branch" u_EQUAL u_token
//via-extension       =  generic-param
//sent-protocol       =  protocol-name u_SLASH protocol-version u_SLASH transport
//protocol-name       =  "SIP" / u_token
//protocol-version    =  u_token
//transport           =  "UDP" / "TCP" / "TLS" / "SCTP" / other-transport
//sent-by             =  host [ u_COLON port ]
//ttl                 =  1*3DIGIT ; 0 to 255
//Warning             =  warning-value *(u_COMMA warning-value)
//warning-value       =  warn-code SP warn-agent SP warn-text
//warn-code           =  3DIGIT
//warn-agent          =  hostport / pseudonym
//warn-text           =  quoted-string
//pseudonym           =  u_token
//WWW-Authenticate    =  challenge
//extension-header    =  header-value
//header-name         =  u_token
//header-value        =  *(TEXT-UTF8char / UTF8-CONT / u_LWS)
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
//TEXT-UTF8-TRIM  =  1*TEXT-UTF8char *(u_LWS 1*TEXT-UTF8char)
//TEXT-UTF8char   =  %x21-7E / UTF8-NONASCII
//UTF8-NONASCII   =  %xC0-DF UTF8-CONT /
//                   %xE0-EF 2UTF8-CONT /
//                   %xF0-F7 3UTF8-CONT /
//                   %xF8-Fb 4UTF8-CONT /
//                   %xFC-FD 5UTF8-CONT
//UTF8-CONT       =  %x80-BF
//;HCOLON          =  *WSP ":" SWS
//;LHEX            =  DIGIT / %x61-66    ;lowercase a-f
//;STAR            =  SWS "*" SWS        ; asterisk
//;SLASH           =  SWS "/" SWS        ; slash
//;EQUAL           =  SWS "=" SWS        ; equal
//;LPAREN          =  SWS "(" SWS        ; left parenthesis
//;RPAREN          =  SWS ")" SWS        ; right parenthesis
//;RAQUOT          =  ">" SWS            ; right angle quote
//;LAQUOT          =  SWS "<"            ; left angle quote
//;COMMA           =  SWS "," SWS        ; comma
//;SEMI            =  SWS ";" SWS        ; semicolon
//;COLON           =  SWS ":" SWS        ; colon
//;LDQUOT          =  SWS DQUOTE         ; open double quotation mark
//;RDQUOT          =  DQUOTE SWS         ; close double quotation mark
//comment         =  u_LPAREN *(ctext / quoted-pair / comment) u_RPAREN
//ctext           =  %x21-27 / %x2A-5B / %x5D-7E / UTF8-NONASCII / u_LWS
//quoted-string   =  e_SWS %x22 q-string %x22
//q-string        =  *(qdtext / quoted-pair )
//qdtext          =  u_LWS / %x21 / %x23-5B / %x5D-7E / UTF8-NONASCII
//quoted-pair     =  "\" (%x00-09 / %x0B-0C / %x0E-7F)
//;LWS             =  [*WSP CRLF] 1*WSP  ; linear whitespace (one or more line continue or space)
//;SWS             =  [u_LWS]              ; sep (optional) whitespace (zero or more line continue or space)
//WSP             =  %x20 / %x09
//
//; B.1.  Core Rules ; RFC 4234 ABNF October 2005
//ALPHA          =  %x41-5A / %x61-7A   ; A-Z / a-z
//CHAR           =  %x01-7F ; any 7-bit US-ASCII character, ;  excluding NUL
//CR             =  %x0D ; carriage return
//CRLF           =  (CR LF) / LF / CR; modified to be forgiving on line ender
//DIGIT          =  %x30-39 ; 0-9
//;DQUOTE         =  %x22 ; " (Double Quote)
//HEXDIG         =  DIGIT / "A" / "B" / "C" / "D" / "E" / "F"
//LF             =  %x0A ; linefeed
//OCTET          =  %x00-FF ; 8 bits of data
//SP             =  %x20
////**** SABNF GRAMMAR ***

