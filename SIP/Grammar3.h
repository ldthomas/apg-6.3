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
#ifndef GRAMMAR3_H
#define GRAMMAR3_H

// rule ids
#define RULE_GRAMMAR3_ABS_PATH 47 // abs-path
#define RULE_GRAMMAR3_ABSOLUTEURI 44 // absoluteURI
#define RULE_GRAMMAR3_ACCEPT 63 // Accept
#define RULE_GRAMMAR3_ACCEPT_ENCODING 70 // Accept-Encoding
#define RULE_GRAMMAR3_ACCEPT_LANGUAGE 74 // Accept-Language
#define RULE_GRAMMAR3_ACCEPT_PARAM 66 // accept-param
#define RULE_GRAMMAR3_ACCEPT_RANGE 64 // accept-range
#define RULE_GRAMMAR3_ACKM 6 // ACKm
#define RULE_GRAMMAR3_ADDR_SPEC 108 // addr-spec
#define RULE_GRAMMAR3_AINFO 98 // ainfo
#define RULE_GRAMMAR3_ALERT_INFO 77 // Alert-Info
#define RULE_GRAMMAR3_ALERT_PARAM 78 // alert-param
#define RULE_GRAMMAR3_ALGORITHM 176 // algorithm
#define RULE_GRAMMAR3_ALLOW 79 // Allow
#define RULE_GRAMMAR3_ALPHA 262 // ALPHA
#define RULE_GRAMMAR3_AREA_SPECIFIER 233 // area-specifier
#define RULE_GRAMMAR3_AUTH_PARAM 93 // auth-param
#define RULE_GRAMMAR3_AUTH_PARAM_NAME 94 // auth-param-name
#define RULE_GRAMMAR3_AUTH_SCHEME 96 // auth-scheme
#define RULE_GRAMMAR3_AUTHENTICATION_INFO 97 // Authentication-Info
#define RULE_GRAMMAR3_AUTHORITY 55 // authority
#define RULE_GRAMMAR3_AUTHORIZATION 80 // Authorization
#define RULE_GRAMMAR3_BASE_PHONE_NUMBER 229 // base-phone-number
#define RULE_GRAMMAR3_BLANKSPACE 1 // BlankSpace
#define RULE_GRAMMAR3_BYEM 8 // BYEm
#define RULE_GRAMMAR3_C_P_EXPIRES 113 // c-p-expires
#define RULE_GRAMMAR3_C_P_Q 112 // c-p-q
#define RULE_GRAMMAR3_CALL_INFO 102 // Call-Info
#define RULE_GRAMMAR3_CANCELM 9 // CANCELm
#define RULE_GRAMMAR3_CHALLENGE 165 // challenge
#define RULE_GRAMMAR3_CHAR 263 // CHAR
#define RULE_GRAMMAR3_CNONCE 89 // cnonce
#define RULE_GRAMMAR3_CNONCE_VALUE 90 // cnonce-value
#define RULE_GRAMMAR3_CODINGS 72 // codings
#define RULE_GRAMMAR3_COMMENT 255 // comment
#define RULE_GRAMMAR3_COMPOSITE_TYPE 132 // composite-type
#define RULE_GRAMMAR3_CONTACT 105 // Contact
#define RULE_GRAMMAR3_CONTACT_EXTENSION 114 // contact-extension
#define RULE_GRAMMAR3_CONTACT_PARAM 106 // contact-param
#define RULE_GRAMMAR3_CONTACT_PARAMS 111 // contact-params
#define RULE_GRAMMAR3_CONTENT_CODING 73 // content-coding
#define RULE_GRAMMAR3_CONTENT_DISPOSITION 116 // Content-Disposition
#define RULE_GRAMMAR3_CONTENT_ENCODING 122 // Content-Encoding
#define RULE_GRAMMAR3_CONTENT_LANGUAGE 123 // Content-Language
#define RULE_GRAMMAR3_CONTENT_LENGTH 127 // Content-Length
#define RULE_GRAMMAR3_CONTENT_TYPE 128 // Content-Type
#define RULE_GRAMMAR3_CR 264 // CR
#define RULE_GRAMMAR3_CREDENTIALS 81 // credentials
#define RULE_GRAMMAR3_CSEQ 141 // CSeq
#define RULE_GRAMMAR3_CTEXT 256 // ctext
#define RULE_GRAMMAR3_D_NAME 110 // d-name
#define RULE_GRAMMAR3_DATE 142 // Date
#define RULE_GRAMMAR3_DATE1 145 // date1
#define RULE_GRAMMAR3_DELAY 200 // delay
#define RULE_GRAMMAR3_DELTA_SECONDS 115 // delta-seconds
#define RULE_GRAMMAR3_DIG_RESP 83 // dig-resp
#define RULE_GRAMMAR3_DIGEST_CLN 167 // digest-cln
#define RULE_GRAMMAR3_DIGEST_RESPONSE 82 // digest-response
#define RULE_GRAMMAR3_DIGEST_URI 86 // digest-uri
#define RULE_GRAMMAR3_DIGEST_URI_VALUE 87 // digest-uri-value
#define RULE_GRAMMAR3_DIGIT 265 // DIGIT
#define RULE_GRAMMAR3_DISCRETE_TYPE 131 // discrete-type
#define RULE_GRAMMAR3_DISP_EXTENSION_TOKEN 121 // disp-extension-token
#define RULE_GRAMMAR3_DISP_PARAM 118 // disp-param
#define RULE_GRAMMAR3_DISP_TYPE 117 // disp-type
#define RULE_GRAMMAR3_DISPLAY_NAME 109 // display-name
#define RULE_GRAMMAR3_DOMAIN 170 // domain
#define RULE_GRAMMAR3_DRESPONSE 92 // dresponse
#define RULE_GRAMMAR3_DTMF_DIGIT 250 // dtmf-digit
#define RULE_GRAMMAR3_ENCODING 71 // encoding
#define RULE_GRAMMAR3_ERROR_INFO 149 // Error-Info
#define RULE_GRAMMAR3_ERROR_URI 150 // error-uri
#define RULE_GRAMMAR3_EXPIRES 151 // Expires
#define RULE_GRAMMAR3_EXTENSION_METHOD 12 // extension-method
#define RULE_GRAMMAR3_EXTENSION_TOKEN 133 // extension-token
#define RULE_GRAMMAR3_FROM 152 // From
#define RULE_GRAMMAR3_FROM_PARAM 154 // from-param
#define RULE_GRAMMAR3_FROM_SPEC 153 // from-spec
#define RULE_GRAMMAR3_FUTURE_EXTENSION 242 // future-extension
#define RULE_GRAMMAR3_GEN_VALUE 69 // gen-value
#define RULE_GRAMMAR3_GENERIC_PARAM 68 // generic-param
#define RULE_GRAMMAR3_GLOBAL_NETWORK_PREFIX 237 // global-network-prefix
#define RULE_GRAMMAR3_GLOBAL_PHONE_NUMBER 228 // global-phone-number
#define RULE_GRAMMAR3_HANDLING_PARAM 119 // handling-param
#define RULE_GRAMMAR3_HEADER 39 // header
#define RULE_GRAMMAR3_HEADER_NAME 226 // header-name
#define RULE_GRAMMAR3_HEADERS 38 // headers
#define RULE_GRAMMAR3_HEXDIG 266 // HEXDIG
#define RULE_GRAMMAR3_HIER_PART 45 // hier-part
#define RULE_GRAMMAR3_HNAME 40 // hname
#define RULE_GRAMMAR3_HNV_UNRESERVED 42 // hnv-unreserved
#define RULE_GRAMMAR3_HOST 24 // host
#define RULE_GRAMMAR3_HOSTNAME 25 // hostname
#define RULE_GRAMMAR3_HOSTPORT 23 // hostport
#define RULE_GRAMMAR3_HVALUE 41 // hvalue
#define RULE_GRAMMAR3_IANA_TOKEN 137 // iana-token
#define RULE_GRAMMAR3_IETF_TOKEN 134 // ietf-token
#define RULE_GRAMMAR3_IN_REPLY_TO 156 // In-Reply-To
#define RULE_GRAMMAR3_INFO 103 // info
#define RULE_GRAMMAR3_INFO_PARAM 104 // info-param
#define RULE_GRAMMAR3_INVITEM 5 // INVITEm
#define RULE_GRAMMAR3_IPV4ADDRESS 59 // IPv4address
#define RULE_GRAMMAR3_IPV6ADDRESS 61 // IPv6address
#define RULE_GRAMMAR3_IPV6REFERENCE 60 // IPv6reference
#define RULE_GRAMMAR3_ISDN_SUBADDRESS 231 // isdn-subaddress
#define RULE_GRAMMAR3_LANGUAGE 75 // language
#define RULE_GRAMMAR3_LANGUAGE_RANGE 76 // language-range
#define RULE_GRAMMAR3_LANGUAGE_TAG 124 // language-tag
#define RULE_GRAMMAR3_LF 267 // LF
#define RULE_GRAMMAR3_LOCAL_NETWORK_PREFIX 238 // local-network-prefix
#define RULE_GRAMMAR3_LOCAL_PHONE_NUMBER 230 // local-phone-number
#define RULE_GRAMMAR3_LR_PARAM 36 // lr-param
#define RULE_GRAMMAR3_M_ATTRIBUTE 139 // m-attribute
#define RULE_GRAMMAR3_M_PARAMETER 138 // m-parameter
#define RULE_GRAMMAR3_M_SUBTYPE 136 // m-subtype
#define RULE_GRAMMAR3_M_TYPE 130 // m-type
#define RULE_GRAMMAR3_M_VALUE 140 // m-value
#define RULE_GRAMMAR3_MADDR_PARAM 35 // maddr-param
#define RULE_GRAMMAR3_MAX_FORWARDS 157 // Max-Forwards
#define RULE_GRAMMAR3_MEDIA_RANGE 65 // media-range
#define RULE_GRAMMAR3_MEDIA_TYPE 129 // media-type
#define RULE_GRAMMAR3_MESSAGE_HEADER 62 // message-header
#define RULE_GRAMMAR3_MESSAGE_QOP 88 // message-qop
#define RULE_GRAMMAR3_METHOD 11 // Method
#define RULE_GRAMMAR3_METHOD_PARAM 33 // method-param
#define RULE_GRAMMAR3_MIME_VERSION 158 // MIME-Version
#define RULE_GRAMMAR3_MIN_EXPIRES 159 // Min-Expires
#define RULE_GRAMMAR3_MONTH 148 // month
#define RULE_GRAMMAR3_NAME_ADDR 107 // name-addr
#define RULE_GRAMMAR3_NET_PATH 46 // net-path
#define RULE_GRAMMAR3_NETWORK_PREFIX 236 // network-prefix
#define RULE_GRAMMAR3_NEXTNONCE 99 // nextnonce
#define RULE_GRAMMAR3_NONCE 172 // nonce
#define RULE_GRAMMAR3_NONCE_COUNT 91 // nonce-count
#define RULE_GRAMMAR3_NONCE_VALUE 173 // nonce-value
#define RULE_GRAMMAR3_ONE_SECOND_PAUSE 248 // one-second-pause
#define RULE_GRAMMAR3_OPAQUE 174 // opaque
#define RULE_GRAMMAR3_OPAQUE_PART 48 // opaque-part
#define RULE_GRAMMAR3_OPTION_TAG 181 // option-tag
#define RULE_GRAMMAR3_OPTIONSM 7 // OPTIONSm
#define RULE_GRAMMAR3_ORGANIZATION 160 // Organization
#define RULE_GRAMMAR3_OTHER_CHALLENGE 166 // other-challenge
#define RULE_GRAMMAR3_OTHER_HANDLING 120 // other-handling
#define RULE_GRAMMAR3_OTHER_PARAM 37 // other-param
#define RULE_GRAMMAR3_OTHER_PRIORITY 163 // other-priority
#define RULE_GRAMMAR3_OTHER_RESPONSE 95 // other-response
#define RULE_GRAMMAR3_OTHER_TRANSPORT 30 // other-transport
#define RULE_GRAMMAR3_OTHER_USER 32 // other-user
#define RULE_GRAMMAR3_PARAM 53 // param
#define RULE_GRAMMAR3_PASSWORD 22 // password
#define RULE_GRAMMAR3_PATH_SEGMENTS 51 // path-segments
#define RULE_GRAMMAR3_PAUSE_CHARACTER 247 // pause-character
#define RULE_GRAMMAR3_PCHAR 54 // pchar
#define RULE_GRAMMAR3_PHONE_CONTEXT_IDENT 235 // phone-context-ident
#define RULE_GRAMMAR3_PHONE_CONTEXT_TAG 234 // phone-context-tag
#define RULE_GRAMMAR3_PHONEDIGIT 245 // phonedigit
#define RULE_GRAMMAR3_PORT 26 // port
#define RULE_GRAMMAR3_POST_DIAL 232 // post-dial
#define RULE_GRAMMAR3_PRIMARY_TAG 125 // primary-tag
#define RULE_GRAMMAR3_PRIORITY 161 // Priority
#define RULE_GRAMMAR3_PRIORITY_VALUE 162 // priority-value
#define RULE_GRAMMAR3_PRIVATE_PREFIX 239 // private-prefix
#define RULE_GRAMMAR3_PRODUCT 195 // product
#define RULE_GRAMMAR3_PRODUCT_VERSION 196 // product-version
#define RULE_GRAMMAR3_PROTOCOL_NAME 214 // protocol-name
#define RULE_GRAMMAR3_PROTOCOL_VERSION 215 // protocol-version
#define RULE_GRAMMAR3_PROVIDER_TAG 241 // provider-tag
#define RULE_GRAMMAR3_PROXY_AUTHENTICATE 164 // Proxy-Authenticate
#define RULE_GRAMMAR3_PROXY_AUTHORIZATION 179 // Proxy-Authorization
#define RULE_GRAMMAR3_PROXY_REQUIRE 180 // Proxy-Require
#define RULE_GRAMMAR3_PSEUDONYM 224 // pseudonym
#define RULE_GRAMMAR3_Q_STRING 258 // q-string
#define RULE_GRAMMAR3_QDTEXT 259 // qdtext
#define RULE_GRAMMAR3_QOP_OPTIONS 177 // qop-options
#define RULE_GRAMMAR3_QOP_VALUE 178 // qop-value
#define RULE_GRAMMAR3_QUERY 58 // query
#define RULE_GRAMMAR3_QUOTED_PAIR 260 // quoted-pair
#define RULE_GRAMMAR3_QUOTED_STRING 257 // quoted-string
#define RULE_GRAMMAR3_QVALUE 67 // qvalue
#define RULE_GRAMMAR3_REALM 168 // realm
#define RULE_GRAMMAR3_REALM_VALUE 169 // realm-value
#define RULE_GRAMMAR3_REASON_PHRASE 16 // Reason-Phrase
#define RULE_GRAMMAR3_REC_ROUTE 183 // rec-route
#define RULE_GRAMMAR3_RECORD_ROUTE 182 // Record-Route
#define RULE_GRAMMAR3_REG_NAME 57 // reg-name
#define RULE_GRAMMAR3_REGISTERM 10 // REGISTERm
#define RULE_GRAMMAR3_REPLY_TO 185 // Reply-To
#define RULE_GRAMMAR3_REQUEST 2 // Request
#define RULE_GRAMMAR3_REQUEST_LINE 3 // Request-Line
#define RULE_GRAMMAR3_REQUEST_URI 43 // Request-URI
#define RULE_GRAMMAR3_REQUIRE 188 // Require
#define RULE_GRAMMAR3_RESERVED 251 // reserved
#define RULE_GRAMMAR3_RESPONSE 13 // Response
#define RULE_GRAMMAR3_RESPONSE_AUTH 100 // response-auth
#define RULE_GRAMMAR3_RESPONSE_DIGEST 101 // response-digest
#define RULE_GRAMMAR3_RETRY_AFTER 189 // Retry-After
#define RULE_GRAMMAR3_RETRY_PARAM 190 // retry-param
#define RULE_GRAMMAR3_RFC1123_DATE 144 // rfc1123-date
#define RULE_GRAMMAR3_ROUTE 191 // Route
#define RULE_GRAMMAR3_ROUTE_PARAM 192 // route-param
#define RULE_GRAMMAR3_RPLYTO_PARAM 187 // rplyto-param
#define RULE_GRAMMAR3_RPLYTO_SPEC 186 // rplyto-spec
#define RULE_GRAMMAR3_RR_PARAM 184 // rr-param
#define RULE_GRAMMAR3_SEGMENT 52 // segment
#define RULE_GRAMMAR3_SENT_BY 217 // sent-by
#define RULE_GRAMMAR3_SENT_PROTOCOL 213 // sent-protocol
#define RULE_GRAMMAR3_SERVER 193 // Server
#define RULE_GRAMMAR3_SERVER_VAL 194 // server-val
#define RULE_GRAMMAR3_SERVICE_PROVIDER 240 // service-provider
#define RULE_GRAMMAR3_SIP_DATE 143 // SIP-date
#define RULE_GRAMMAR3_SIP_MESSAGE 0 // SIP-message
#define RULE_GRAMMAR3_SIP_URI 17 // SIP-URI
#define RULE_GRAMMAR3_SIP_VERSION 4 // SIP-Version
#define RULE_GRAMMAR3_SIPS_URI 18 // SIPS-URI
#define RULE_GRAMMAR3_SP 268 // SP
#define RULE_GRAMMAR3_SRVR 56 // srvr
#define RULE_GRAMMAR3_STALE 175 // stale
#define RULE_GRAMMAR3_STATUS_CODE 15 // Status-Code
#define RULE_GRAMMAR3_STATUS_LINE 14 // Status-Line
#define RULE_GRAMMAR3_SUBJECT 197 // Subject
#define RULE_GRAMMAR3_SUBTAG 126 // subtag
#define RULE_GRAMMAR3_SUPPORTED 198 // Supported
#define RULE_GRAMMAR3_TAG_PARAM 155 // tag-param
#define RULE_GRAMMAR3_TEL_QUOTED_STRING 244 // tel-quoted-string
#define RULE_GRAMMAR3_TELEPHONE_SUBSCRIBER 227 // telephone-subscriber
#define RULE_GRAMMAR3_TEXT_UTF8CHAR 252 // TEXT-UTF8char
#define RULE_GRAMMAR3_TIME 146 // time
#define RULE_GRAMMAR3_TIMESTAMP 199 // Timestamp
#define RULE_GRAMMAR3_TO 201 // To
#define RULE_GRAMMAR3_TO_PARAM 202 // to-param
#define RULE_GRAMMAR3_TOKEN_CHAR 243 // token-char
#define RULE_GRAMMAR3_TRANSPORT 216 // transport
#define RULE_GRAMMAR3_TRANSPORT_PARAM 29 // transport-param
#define RULE_GRAMMAR3_TTL 218 // ttl
#define RULE_GRAMMAR3_TTL_PARAM 34 // ttl-param
#define RULE_GRAMMAR3_UNSUPPORTED 203 // Unsupported
#define RULE_GRAMMAR3_URI 171 // URI
#define RULE_GRAMMAR3_URI_PARAMETER 28 // uri-parameter
#define RULE_GRAMMAR3_URI_PARAMETERS 27 // uri-parameters
#define RULE_GRAMMAR3_URIC 49 // uric
#define RULE_GRAMMAR3_URIC_NO_SLASH 50 // uric-no-slash
#define RULE_GRAMMAR3_USER 20 // user
#define RULE_GRAMMAR3_USER_AGENT 204 // User-Agent
#define RULE_GRAMMAR3_USER_PARAM 31 // user-param
#define RULE_GRAMMAR3_USER_UNRESERVED 21 // user-unreserved
#define RULE_GRAMMAR3_USERINFO 19 // userinfo
#define RULE_GRAMMAR3_USERNAME 84 // username
#define RULE_GRAMMAR3_USERNAME_VALUE 85 // username-value
#define RULE_GRAMMAR3_UTF8_CONT 254 // UTF8-CONT
#define RULE_GRAMMAR3_UTF8_NONASCII 253 // UTF8-NONASCII
#define RULE_GRAMMAR3_VIA 205 // Via
#define RULE_GRAMMAR3_VIA_BRANCH 211 // via-branch
#define RULE_GRAMMAR3_VIA_EXTENSION 212 // via-extension
#define RULE_GRAMMAR3_VIA_MADDR 209 // via-maddr
#define RULE_GRAMMAR3_VIA_PARAMS 207 // via-params
#define RULE_GRAMMAR3_VIA_PARM 206 // via-parm
#define RULE_GRAMMAR3_VIA_RECEIVED 210 // via-received
#define RULE_GRAMMAR3_VIA_TTL 208 // via-ttl
#define RULE_GRAMMAR3_VISUAL_SEPARATOR 246 // visual-separator
#define RULE_GRAMMAR3_WAIT_FOR_DIAL_TONE 249 // wait-for-dial-tone
#define RULE_GRAMMAR3_WARN_AGENT 222 // warn-agent
#define RULE_GRAMMAR3_WARN_CODE 221 // warn-code
#define RULE_GRAMMAR3_WARN_TEXT 223 // warn-text
#define RULE_GRAMMAR3_WARNING 219 // Warning
#define RULE_GRAMMAR3_WARNING_VALUE 220 // warning-value
#define RULE_GRAMMAR3_WKDAY 147 // wkday
#define RULE_GRAMMAR3_WSP 261 // WSP
#define RULE_GRAMMAR3_WWW_AUTHENTICATE 225 // WWW-Authenticate
#define RULE_GRAMMAR3_X_TOKEN 135 // x-token
#define RULE_COUNT_GRAMMAR3 269

// UDT ids
#define UDT_GRAMMAR3_E_DIGIT 29 // e_digit
#define UDT_GRAMMAR3_E_DOMAINLABEL 6 // e_domainlabel
#define UDT_GRAMMAR3_E_MESSAGE_BODY 1 // e_message-body
#define UDT_GRAMMAR3_E_SWS 34 // e_SWS
#define UDT_GRAMMAR3_E_TEXT_UTF8_TRIM 28 // e_TEXT-UTF8-TRIM
#define UDT_GRAMMAR3_U_CALLID 13 // u_callid
#define UDT_GRAMMAR3_U_COLON 30 // u_COLON
#define UDT_GRAMMAR3_U_COMMA 15 // u_COMMA
#define UDT_GRAMMAR3_U_CRLF 0 // u_CRLF
#define UDT_GRAMMAR3_U_EQUAL 18 // u_EQUAL
#define UDT_GRAMMAR3_U_ESCAPED 5 // u_escaped
#define UDT_GRAMMAR3_U_EXTENSION_HEADER 14 // u_extension-header
#define UDT_GRAMMAR3_U_HCOLON 12 // u_HCOLON
#define UDT_GRAMMAR3_U_LAQUOT 19 // u_LAQUOT
#define UDT_GRAMMAR3_U_LDQUOT 22 // u_LDQUOT
#define UDT_GRAMMAR3_U_LHEX 26 // u_LHEX
#define UDT_GRAMMAR3_U_LPAREN 32 // u_LPAREN
#define UDT_GRAMMAR3_U_LWS 21 // u_LWS
#define UDT_GRAMMAR3_U_NC_VALUE 24 // u_nc-value
#define UDT_GRAMMAR3_U_ONE_OR_MORE_UNRESERVED 4 // u_one-or-more-unreserved
#define UDT_GRAMMAR3_U_ONEORMOREDIGIT 2 // u_OneOrMoreDigit
#define UDT_GRAMMAR3_U_PNANE 8 // u_pnane
#define UDT_GRAMMAR3_U_PVALUE 9 // u_pvalue
#define UDT_GRAMMAR3_U_RAQUOT 20 // u_RAQUOT
#define UDT_GRAMMAR3_U_RDQUOT 23 // u_RDQUOT
#define UDT_GRAMMAR3_U_REQUEST_DIGEST 25 // u_request-digest
#define UDT_GRAMMAR3_U_RFC1035DOMAIN 31 // u_RFC1035domain
#define UDT_GRAMMAR3_U_RPAREN 33 // u_RPAREN
#define UDT_GRAMMAR3_U_SCHEME 10 // u_scheme
#define UDT_GRAMMAR3_U_SEMI 16 // u_SEMI
#define UDT_GRAMMAR3_U_SLASH 17 // u_SLASH
#define UDT_GRAMMAR3_U_STAR 27 // u_STAR
#define UDT_GRAMMAR3_U_TOKEN 3 // u_token
#define UDT_GRAMMAR3_U_TOPLABEL 7 // u_toplabel
#define UDT_GRAMMAR3_U_UNRESERVED 11 // u_unreserved
#define UDT_COUNT_GRAMMAR3 35

// Parser initialization data
extern void* vpParserInit_Grammar3;

#endif // GRAMMAR3_H

//**** SABNF GRAMMAR ****
//;
//; Grammar3 - removal of message-body(OCTET) & paramchar & escaped
//;
//; SIP MESSAGE
//SIP-message       =  BlankSpace (Request / Response) ; forgiving on leading characters
//BlankSpace        = *(%d0-31/%d128-255)
//
//; REQUEST
//Request           =  Request-Line *( message-header ) u_CRLF  e_message-body
//Request-Line      =  Method SP Request-URI SP SIP-Version u_CRLF
//SIP-Version       =  "SIP" "/" u_OneOrMoreDigit "." u_OneOrMoreDigit
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
//Response          =  Status-Line *( message-header ) u_CRLF e_message-body
//Status-Line       =  SIP-Version SP Status-Code SP Reason-Phrase u_CRLF
//Status-Code       =  3DIGIT ; to be analyzed semantically (see RFC 3621)
//Reason-Phrase     =  *(reserved / u_one-or-more-unreserved / u_escaped / UTF8-NONASCII / UTF8-CONT / (%x20 / %x09))
//
//; SIP URI
//SIP-URI           =  "sip:" [ userinfo ] hostport uri-parameters [ headers ]
//SIPS-URI          =  "sips:" [ userinfo ] hostport uri-parameters [ headers ]
//userinfo          =  ( user / telephone-subscriber ) [ ":" password ] "@"
//user              =  1*( u_one-or-more-unreserved / u_escaped / user-unreserved )
//user-unreserved   =  "&" / "=" / "+" / "$" / "," / ";" / "?" / "/"
//password          =  *( u_one-or-more-unreserved / u_escaped / "&" / "=" / "+" / "$" / "," )
//hostport          =  host [ ":" port ]
//host              =  hostname / IPv4address / IPv6reference
//hostname          =  e_domainlabel u_toplabel
//port              =  u_OneOrMoreDigit
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
//other-param       =  u_pnane [ "=" u_pvalue ]
//;pname             =  1*paramchar
//;pvalue            =  1*paramchar
//;paramchar         =  param-unreserved / u_unreserved / u_escaped
//;param-unreserved  =  "[" / "]" / "/" / ":" / "&" / "+" / "$"
//headers           =  "?" header *( "&" header )
//header            =  hname "=" hvalue
//hname             =  1*( hnv-unreserved / u_one-or-more-unreserved / u_escaped )
//hvalue            =  *( hnv-unreserved / u_one-or-more-unreserved / u_escaped )
//hnv-unreserved    =  "[" / "]" / "/" / "?" / ":" / "+" / "$"
//
//; REQUEST URI
//Request-URI    =  SIP-URI / SIPS-URI / absoluteURI
//absoluteURI    =  u_scheme ":" ( hier-part / opaque-part )
//hier-part      =  ( net-path / abs-path ) [ "?" query ]
//net-path       =  "//" authority [ abs-path ]
//abs-path       =  "/" path-segments
//opaque-part    =  uric-no-slash *uric
//uric           =  reserved / u_unreserved / u_escaped
//uric-no-slash  =  u_unreserved / u_escaped / ";" / "?" / ":" / "@" / "&" / "=" / "+" / "$" / ","
//path-segments  =  segment *( "/" segment )
//segment        =  *pchar *( ";" param )
//param          =  *pchar
//pchar          =  u_unreserved / u_escaped / ":" / "@" / "&" / "=" / "+" / "$" / ","
//authority      =  srvr / reg-name
//srvr           =  [ [ userinfo ] hostport ]
//reg-name       =  1*( u_one-or-more-unreserved / u_escaped / "$" / "," / ";" / ":" / "@" / "&" / "=" / "+" )
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
//                      /  header-name                u_HCOLON u_extension-header) u_CRLF
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
//delta-seconds       =  u_OneOrMoreDigit
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
//Content-Length      =  u_OneOrMoreDigit
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
//CSeq                =  u_OneOrMoreDigit u_LWS Method
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
//Max-Forwards        =  u_OneOrMoreDigit
//MIME-Version        =  u_OneOrMoreDigit "." u_OneOrMoreDigit
//Min-Expires         =  delta-seconds
//Organization        =  e_TEXT-UTF8-TRIM
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
//Subject             =  e_TEXT-UTF8-TRIM
//Supported           =  [option-tag *(u_COMMA option-tag)]
//Timestamp           =  u_OneOrMoreDigit [ "." e_digit ] [ u_LWS delay ]
//delay               =  e_digit [ "." e_digit ]
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
//;extension-header    =  header-value
//header-name         =  u_token
//;header-value        =  *(TEXT-UTF8char / UTF8-CONT / u_LWS)
//;message-body        =  *OCTET
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
//phonedigit            = %x30-39 / visual-separator
//visual-separator      = "-" / "." / "(" / ")"
//pause-character       = one-second-pause / wait-for-dial-tone
//one-second-pause      = "p"
//wait-for-dial-tone    = "w"
//dtmf-digit            = "*" / "#" / "A" / "B" / "C" / "D"
//
//; 25.1 Basic Rules
//reserved        =  ";" / "/" / "?" / ":" / "@" / "&" / "=" / "+" / "$" / ","
//;escaped         =  "%" HEXDIG HEXDIG
//;TEXT-UTF8-TRIM  =  1*TEXT-UTF8char *(u_LWS 1*TEXT-UTF8char)
//TEXT-UTF8char   =  %x21-7E / UTF8-NONASCII
//UTF8-NONASCII   =  %xC0-DF UTF8-CONT /
//                   %xE0-EF 2UTF8-CONT /
//                   %xF0-F7 3UTF8-CONT /
//                   %xF8-Fb 4UTF8-CONT /
//                   %xFC-FD 5UTF8-CONT
//UTF8-CONT       =  %x80-BF
//;HCOLON          =  *WSP ":" SWS
//;LHEX            =  %x30-39 / %x61-66    ;lowercase a-f
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
//;CRLF           =  (CR LF) / LF / CR; modified to be forgiving on line ender
//DIGIT          =  %x30-39 ; 0-9
//;DQUOTE         =  %x22 ; " (Double Quote)
//HEXDIG         =  %x30-39 / "A" / "B" / "C" / "D" / "E" / "F"
//LF             =  %x0A ; linefeed
//;OCTET          =  %x00-FF ; 8 bits of data
//SP             =  %x20
////**** SABNF GRAMMAR ***

