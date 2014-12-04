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
#ifndef GRAMMAR4_H
#define GRAMMAR4_H

// rule ids
#define RULE_GRAMMAR4_ABS_PATH 46 // abs-path
#define RULE_GRAMMAR4_ABSOLUTEURI 43 // absoluteURI
#define RULE_GRAMMAR4_ACCEPT 61 // Accept
#define RULE_GRAMMAR4_ACCEPT_ENCODING 68 // Accept-Encoding
#define RULE_GRAMMAR4_ACCEPT_LANGUAGE 72 // Accept-Language
#define RULE_GRAMMAR4_ACCEPT_PARAM 64 // accept-param
#define RULE_GRAMMAR4_ACCEPT_RANGE 62 // accept-range
#define RULE_GRAMMAR4_ACKM 6 // ACKm
#define RULE_GRAMMAR4_ADDR_SPEC 106 // addr-spec
#define RULE_GRAMMAR4_AINFO 96 // ainfo
#define RULE_GRAMMAR4_ALERT_INFO 75 // Alert-Info
#define RULE_GRAMMAR4_ALERT_PARAM 76 // alert-param
#define RULE_GRAMMAR4_ALGORITHM 174 // algorithm
#define RULE_GRAMMAR4_ALLOW 77 // Allow
#define RULE_GRAMMAR4_ALPHA 257 // ALPHA
#define RULE_GRAMMAR4_AREA_SPECIFIER 231 // area-specifier
#define RULE_GRAMMAR4_AUTH_PARAM 91 // auth-param
#define RULE_GRAMMAR4_AUTH_PARAM_NAME 92 // auth-param-name
#define RULE_GRAMMAR4_AUTH_SCHEME 94 // auth-scheme
#define RULE_GRAMMAR4_AUTHENTICATION_INFO 95 // Authentication-Info
#define RULE_GRAMMAR4_AUTHORITY 54 // authority
#define RULE_GRAMMAR4_AUTHORIZATION 78 // Authorization
#define RULE_GRAMMAR4_BASE_PHONE_NUMBER 227 // base-phone-number
#define RULE_GRAMMAR4_BLANKSPACE 1 // BlankSpace
#define RULE_GRAMMAR4_BYEM 8 // BYEm
#define RULE_GRAMMAR4_C_P_EXPIRES 111 // c-p-expires
#define RULE_GRAMMAR4_C_P_Q 110 // c-p-q
#define RULE_GRAMMAR4_CALL_INFO 100 // Call-Info
#define RULE_GRAMMAR4_CANCELM 9 // CANCELm
#define RULE_GRAMMAR4_CHALLENGE 163 // challenge
#define RULE_GRAMMAR4_CHAR 258 // CHAR
#define RULE_GRAMMAR4_CNONCE 87 // cnonce
#define RULE_GRAMMAR4_CNONCE_VALUE 88 // cnonce-value
#define RULE_GRAMMAR4_CODINGS 70 // codings
#define RULE_GRAMMAR4_COMMENT 253 // comment
#define RULE_GRAMMAR4_COMPOSITE_TYPE 130 // composite-type
#define RULE_GRAMMAR4_CONTACT 103 // Contact
#define RULE_GRAMMAR4_CONTACT_EXTENSION 112 // contact-extension
#define RULE_GRAMMAR4_CONTACT_PARAM 104 // contact-param
#define RULE_GRAMMAR4_CONTACT_PARAMS 109 // contact-params
#define RULE_GRAMMAR4_CONTENT_CODING 71 // content-coding
#define RULE_GRAMMAR4_CONTENT_DISPOSITION 114 // Content-Disposition
#define RULE_GRAMMAR4_CONTENT_ENCODING 120 // Content-Encoding
#define RULE_GRAMMAR4_CONTENT_LANGUAGE 121 // Content-Language
#define RULE_GRAMMAR4_CONTENT_LENGTH 125 // Content-Length
#define RULE_GRAMMAR4_CONTENT_TYPE 126 // Content-Type
#define RULE_GRAMMAR4_CR 259 // CR
#define RULE_GRAMMAR4_CREDENTIALS 79 // credentials
#define RULE_GRAMMAR4_CSEQ 139 // CSeq
#define RULE_GRAMMAR4_CTEXT 254 // ctext
#define RULE_GRAMMAR4_D_NAME 108 // d-name
#define RULE_GRAMMAR4_DATE 140 // Date
#define RULE_GRAMMAR4_DATE1 143 // date1
#define RULE_GRAMMAR4_DELAY 198 // delay
#define RULE_GRAMMAR4_DELTA_SECONDS 113 // delta-seconds
#define RULE_GRAMMAR4_DIG_RESP 81 // dig-resp
#define RULE_GRAMMAR4_DIGEST_CLN 165 // digest-cln
#define RULE_GRAMMAR4_DIGEST_RESPONSE 80 // digest-response
#define RULE_GRAMMAR4_DIGEST_URI 84 // digest-uri
#define RULE_GRAMMAR4_DIGEST_URI_VALUE 85 // digest-uri-value
#define RULE_GRAMMAR4_DIGIT 260 // DIGIT
#define RULE_GRAMMAR4_DISCRETE_TYPE 129 // discrete-type
#define RULE_GRAMMAR4_DISP_EXTENSION_TOKEN 119 // disp-extension-token
#define RULE_GRAMMAR4_DISP_PARAM 116 // disp-param
#define RULE_GRAMMAR4_DISP_TYPE 115 // disp-type
#define RULE_GRAMMAR4_DISPLAY_NAME 107 // display-name
#define RULE_GRAMMAR4_DOMAIN 168 // domain
#define RULE_GRAMMAR4_DRESPONSE 90 // dresponse
#define RULE_GRAMMAR4_DTMF_DIGIT 248 // dtmf-digit
#define RULE_GRAMMAR4_ENCODING 69 // encoding
#define RULE_GRAMMAR4_ERROR_INFO 147 // Error-Info
#define RULE_GRAMMAR4_ERROR_URI 148 // error-uri
#define RULE_GRAMMAR4_EXPIRES 149 // Expires
#define RULE_GRAMMAR4_EXTENSION_METHOD 12 // extension-method
#define RULE_GRAMMAR4_EXTENSION_TOKEN 131 // extension-token
#define RULE_GRAMMAR4_FROM 150 // From
#define RULE_GRAMMAR4_FROM_PARAM 152 // from-param
#define RULE_GRAMMAR4_FROM_SPEC 151 // from-spec
#define RULE_GRAMMAR4_FUTURE_EXTENSION 240 // future-extension
#define RULE_GRAMMAR4_GEN_VALUE 67 // gen-value
#define RULE_GRAMMAR4_GENERIC_PARAM 66 // generic-param
#define RULE_GRAMMAR4_GLOBAL_NETWORK_PREFIX 235 // global-network-prefix
#define RULE_GRAMMAR4_GLOBAL_PHONE_NUMBER 226 // global-phone-number
#define RULE_GRAMMAR4_HANDLING_PARAM 117 // handling-param
#define RULE_GRAMMAR4_HEADER 38 // header
#define RULE_GRAMMAR4_HEADER_NAME 224 // header-name
#define RULE_GRAMMAR4_HEADERS 37 // headers
#define RULE_GRAMMAR4_HEXDIG 261 // HEXDIG
#define RULE_GRAMMAR4_HIER_PART 44 // hier-part
#define RULE_GRAMMAR4_HNAME 39 // hname
#define RULE_GRAMMAR4_HNV_UNRESERVED 41 // hnv-unreserved
#define RULE_GRAMMAR4_HOST 23 // host
#define RULE_GRAMMAR4_HOSTNAME 24 // hostname
#define RULE_GRAMMAR4_HOSTPORT 22 // hostport
#define RULE_GRAMMAR4_HVALUE 40 // hvalue
#define RULE_GRAMMAR4_IANA_TOKEN 135 // iana-token
#define RULE_GRAMMAR4_IETF_TOKEN 132 // ietf-token
#define RULE_GRAMMAR4_IN_REPLY_TO 154 // In-Reply-To
#define RULE_GRAMMAR4_INFO 101 // info
#define RULE_GRAMMAR4_INFO_PARAM 102 // info-param
#define RULE_GRAMMAR4_INVITEM 5 // INVITEm
#define RULE_GRAMMAR4_IPV6ADDRESS 59 // IPv6address
#define RULE_GRAMMAR4_IPV6REFERENCE 58 // IPv6reference
#define RULE_GRAMMAR4_ISDN_SUBADDRESS 229 // isdn-subaddress
#define RULE_GRAMMAR4_LANGUAGE 73 // language
#define RULE_GRAMMAR4_LANGUAGE_RANGE 74 // language-range
#define RULE_GRAMMAR4_LANGUAGE_TAG 122 // language-tag
#define RULE_GRAMMAR4_LF 262 // LF
#define RULE_GRAMMAR4_LOCAL_NETWORK_PREFIX 236 // local-network-prefix
#define RULE_GRAMMAR4_LOCAL_PHONE_NUMBER 228 // local-phone-number
#define RULE_GRAMMAR4_LR_PARAM 35 // lr-param
#define RULE_GRAMMAR4_M_ATTRIBUTE 137 // m-attribute
#define RULE_GRAMMAR4_M_PARAMETER 136 // m-parameter
#define RULE_GRAMMAR4_M_SUBTYPE 134 // m-subtype
#define RULE_GRAMMAR4_M_TYPE 128 // m-type
#define RULE_GRAMMAR4_M_VALUE 138 // m-value
#define RULE_GRAMMAR4_MADDR_PARAM 34 // maddr-param
#define RULE_GRAMMAR4_MAX_FORWARDS 155 // Max-Forwards
#define RULE_GRAMMAR4_MEDIA_RANGE 63 // media-range
#define RULE_GRAMMAR4_MEDIA_TYPE 127 // media-type
#define RULE_GRAMMAR4_MESSAGE_HEADER 60 // message-header
#define RULE_GRAMMAR4_MESSAGE_QOP 86 // message-qop
#define RULE_GRAMMAR4_METHOD 11 // Method
#define RULE_GRAMMAR4_METHOD_PARAM 32 // method-param
#define RULE_GRAMMAR4_MIME_VERSION 156 // MIME-Version
#define RULE_GRAMMAR4_MIN_EXPIRES 157 // Min-Expires
#define RULE_GRAMMAR4_MONTH 146 // month
#define RULE_GRAMMAR4_NAME_ADDR 105 // name-addr
#define RULE_GRAMMAR4_NET_PATH 45 // net-path
#define RULE_GRAMMAR4_NETWORK_PREFIX 234 // network-prefix
#define RULE_GRAMMAR4_NEXTNONCE 97 // nextnonce
#define RULE_GRAMMAR4_NONCE 170 // nonce
#define RULE_GRAMMAR4_NONCE_COUNT 89 // nonce-count
#define RULE_GRAMMAR4_NONCE_VALUE 171 // nonce-value
#define RULE_GRAMMAR4_ONE_SECOND_PAUSE 246 // one-second-pause
#define RULE_GRAMMAR4_OPAQUE 172 // opaque
#define RULE_GRAMMAR4_OPAQUE_PART 47 // opaque-part
#define RULE_GRAMMAR4_OPTION_TAG 179 // option-tag
#define RULE_GRAMMAR4_OPTIONSM 7 // OPTIONSm
#define RULE_GRAMMAR4_ORGANIZATION 158 // Organization
#define RULE_GRAMMAR4_OTHER_CHALLENGE 164 // other-challenge
#define RULE_GRAMMAR4_OTHER_HANDLING 118 // other-handling
#define RULE_GRAMMAR4_OTHER_PARAM 36 // other-param
#define RULE_GRAMMAR4_OTHER_PRIORITY 161 // other-priority
#define RULE_GRAMMAR4_OTHER_RESPONSE 93 // other-response
#define RULE_GRAMMAR4_OTHER_TRANSPORT 29 // other-transport
#define RULE_GRAMMAR4_OTHER_USER 31 // other-user
#define RULE_GRAMMAR4_PARAM 52 // param
#define RULE_GRAMMAR4_PASSWORD 21 // password
#define RULE_GRAMMAR4_PATH_SEGMENTS 50 // path-segments
#define RULE_GRAMMAR4_PAUSE_CHARACTER 245 // pause-character
#define RULE_GRAMMAR4_PCHAR 53 // pchar
#define RULE_GRAMMAR4_PHONE_CONTEXT_IDENT 233 // phone-context-ident
#define RULE_GRAMMAR4_PHONE_CONTEXT_TAG 232 // phone-context-tag
#define RULE_GRAMMAR4_PHONEDIGIT 243 // phonedigit
#define RULE_GRAMMAR4_PORT 25 // port
#define RULE_GRAMMAR4_POST_DIAL 230 // post-dial
#define RULE_GRAMMAR4_PRIMARY_TAG 123 // primary-tag
#define RULE_GRAMMAR4_PRIORITY 159 // Priority
#define RULE_GRAMMAR4_PRIORITY_VALUE 160 // priority-value
#define RULE_GRAMMAR4_PRIVATE_PREFIX 237 // private-prefix
#define RULE_GRAMMAR4_PRODUCT 193 // product
#define RULE_GRAMMAR4_PRODUCT_VERSION 194 // product-version
#define RULE_GRAMMAR4_PROTOCOL_NAME 212 // protocol-name
#define RULE_GRAMMAR4_PROTOCOL_VERSION 213 // protocol-version
#define RULE_GRAMMAR4_PROVIDER_TAG 239 // provider-tag
#define RULE_GRAMMAR4_PROXY_AUTHENTICATE 162 // Proxy-Authenticate
#define RULE_GRAMMAR4_PROXY_AUTHORIZATION 177 // Proxy-Authorization
#define RULE_GRAMMAR4_PROXY_REQUIRE 178 // Proxy-Require
#define RULE_GRAMMAR4_PSEUDONYM 222 // pseudonym
#define RULE_GRAMMAR4_QOP_OPTIONS 175 // qop-options
#define RULE_GRAMMAR4_QOP_VALUE 176 // qop-value
#define RULE_GRAMMAR4_QUERY 57 // query
#define RULE_GRAMMAR4_QUOTED_PAIR 255 // quoted-pair
#define RULE_GRAMMAR4_QVALUE 65 // qvalue
#define RULE_GRAMMAR4_REALM 166 // realm
#define RULE_GRAMMAR4_REALM_VALUE 167 // realm-value
#define RULE_GRAMMAR4_REASON_PHRASE 16 // Reason-Phrase
#define RULE_GRAMMAR4_REC_ROUTE 181 // rec-route
#define RULE_GRAMMAR4_RECORD_ROUTE 180 // Record-Route
#define RULE_GRAMMAR4_REG_NAME 56 // reg-name
#define RULE_GRAMMAR4_REGISTERM 10 // REGISTERm
#define RULE_GRAMMAR4_REPLY_TO 183 // Reply-To
#define RULE_GRAMMAR4_REQUEST 2 // Request
#define RULE_GRAMMAR4_REQUEST_LINE 3 // Request-Line
#define RULE_GRAMMAR4_REQUEST_URI 42 // Request-URI
#define RULE_GRAMMAR4_REQUIRE 186 // Require
#define RULE_GRAMMAR4_RESERVED 249 // reserved
#define RULE_GRAMMAR4_RESPONSE 13 // Response
#define RULE_GRAMMAR4_RESPONSE_AUTH 98 // response-auth
#define RULE_GRAMMAR4_RESPONSE_DIGEST 99 // response-digest
#define RULE_GRAMMAR4_RETRY_AFTER 187 // Retry-After
#define RULE_GRAMMAR4_RETRY_PARAM 188 // retry-param
#define RULE_GRAMMAR4_RFC1123_DATE 142 // rfc1123-date
#define RULE_GRAMMAR4_ROUTE 189 // Route
#define RULE_GRAMMAR4_ROUTE_PARAM 190 // route-param
#define RULE_GRAMMAR4_RPLYTO_PARAM 185 // rplyto-param
#define RULE_GRAMMAR4_RPLYTO_SPEC 184 // rplyto-spec
#define RULE_GRAMMAR4_RR_PARAM 182 // rr-param
#define RULE_GRAMMAR4_SEGMENT 51 // segment
#define RULE_GRAMMAR4_SENT_BY 215 // sent-by
#define RULE_GRAMMAR4_SENT_PROTOCOL 211 // sent-protocol
#define RULE_GRAMMAR4_SERVER 191 // Server
#define RULE_GRAMMAR4_SERVER_VAL 192 // server-val
#define RULE_GRAMMAR4_SERVICE_PROVIDER 238 // service-provider
#define RULE_GRAMMAR4_SIP_DATE 141 // SIP-date
#define RULE_GRAMMAR4_SIP_MESSAGE 0 // SIP-message
#define RULE_GRAMMAR4_SIP_URI 17 // SIP-URI
#define RULE_GRAMMAR4_SIP_VERSION 4 // SIP-Version
#define RULE_GRAMMAR4_SIPS_URI 18 // SIPS-URI
#define RULE_GRAMMAR4_SP 263 // SP
#define RULE_GRAMMAR4_SRVR 55 // srvr
#define RULE_GRAMMAR4_STALE 173 // stale
#define RULE_GRAMMAR4_STATUS_CODE 15 // Status-Code
#define RULE_GRAMMAR4_STATUS_LINE 14 // Status-Line
#define RULE_GRAMMAR4_SUBJECT 195 // Subject
#define RULE_GRAMMAR4_SUBTAG 124 // subtag
#define RULE_GRAMMAR4_SUPPORTED 196 // Supported
#define RULE_GRAMMAR4_TAG_PARAM 153 // tag-param
#define RULE_GRAMMAR4_TEL_QUOTED_STRING 242 // tel-quoted-string
#define RULE_GRAMMAR4_TELEPHONE_SUBSCRIBER 225 // telephone-subscriber
#define RULE_GRAMMAR4_TEXT_UTF8CHAR 250 // TEXT-UTF8char
#define RULE_GRAMMAR4_TIME 144 // time
#define RULE_GRAMMAR4_TIMESTAMP 197 // Timestamp
#define RULE_GRAMMAR4_TO 199 // To
#define RULE_GRAMMAR4_TO_PARAM 200 // to-param
#define RULE_GRAMMAR4_TOKEN_CHAR 241 // token-char
#define RULE_GRAMMAR4_TRANSPORT 214 // transport
#define RULE_GRAMMAR4_TRANSPORT_PARAM 28 // transport-param
#define RULE_GRAMMAR4_TTL 216 // ttl
#define RULE_GRAMMAR4_TTL_PARAM 33 // ttl-param
#define RULE_GRAMMAR4_UNSUPPORTED 201 // Unsupported
#define RULE_GRAMMAR4_URI 169 // URI
#define RULE_GRAMMAR4_URI_PARAMETER 27 // uri-parameter
#define RULE_GRAMMAR4_URI_PARAMETERS 26 // uri-parameters
#define RULE_GRAMMAR4_URIC 48 // uric
#define RULE_GRAMMAR4_URIC_NO_SLASH 49 // uric-no-slash
#define RULE_GRAMMAR4_USER_AGENT 202 // User-Agent
#define RULE_GRAMMAR4_USER_PARAM 30 // user-param
#define RULE_GRAMMAR4_USER_UNRESERVED 20 // user-unreserved
#define RULE_GRAMMAR4_USERINFO 19 // userinfo
#define RULE_GRAMMAR4_USERNAME 82 // username
#define RULE_GRAMMAR4_USERNAME_VALUE 83 // username-value
#define RULE_GRAMMAR4_UTF8_CONT 252 // UTF8-CONT
#define RULE_GRAMMAR4_UTF8_NONASCII 251 // UTF8-NONASCII
#define RULE_GRAMMAR4_VIA 203 // Via
#define RULE_GRAMMAR4_VIA_BRANCH 209 // via-branch
#define RULE_GRAMMAR4_VIA_EXTENSION 210 // via-extension
#define RULE_GRAMMAR4_VIA_MADDR 207 // via-maddr
#define RULE_GRAMMAR4_VIA_PARAMS 205 // via-params
#define RULE_GRAMMAR4_VIA_PARM 204 // via-parm
#define RULE_GRAMMAR4_VIA_RECEIVED 208 // via-received
#define RULE_GRAMMAR4_VIA_TTL 206 // via-ttl
#define RULE_GRAMMAR4_VISUAL_SEPARATOR 244 // visual-separator
#define RULE_GRAMMAR4_WAIT_FOR_DIAL_TONE 247 // wait-for-dial-tone
#define RULE_GRAMMAR4_WARN_AGENT 220 // warn-agent
#define RULE_GRAMMAR4_WARN_CODE 219 // warn-code
#define RULE_GRAMMAR4_WARN_TEXT 221 // warn-text
#define RULE_GRAMMAR4_WARNING 217 // Warning
#define RULE_GRAMMAR4_WARNING_VALUE 218 // warning-value
#define RULE_GRAMMAR4_WKDAY 145 // wkday
#define RULE_GRAMMAR4_WSP 256 // WSP
#define RULE_GRAMMAR4_WWW_AUTHENTICATE 223 // WWW-Authenticate
#define RULE_GRAMMAR4_X_TOKEN 133 // x-token
#define RULE_COUNT_GRAMMAR4 264

// UDT ids
#define UDT_GRAMMAR4_E_DIGIT 32 // e_digit
#define UDT_GRAMMAR4_E_DOMAINLABEL 8 // e_domainlabel
#define UDT_GRAMMAR4_E_MESSAGE_BODY 1 // e_message-body
#define UDT_GRAMMAR4_E_TEXT_UTF8_TRIM 31 // e_TEXT-UTF8-TRIM
#define UDT_GRAMMAR4_U_CALLID 15 // u_callid
#define UDT_GRAMMAR4_U_COLON 33 // u_COLON
#define UDT_GRAMMAR4_U_COMMA 17 // u_COMMA
#define UDT_GRAMMAR4_U_CRLF 0 // u_CRLF
#define UDT_GRAMMAR4_U_EQUAL 20 // u_EQUAL
#define UDT_GRAMMAR4_U_ESCAPED 5 // u_escaped
#define UDT_GRAMMAR4_U_EXTENSION_HEADER 16 // u_extension-header
#define UDT_GRAMMAR4_U_HCOLON 14 // u_HCOLON
#define UDT_GRAMMAR4_U_IPV4ADDRESS 7 // u_IPv4address
#define UDT_GRAMMAR4_U_LAQUOT 22 // u_LAQUOT
#define UDT_GRAMMAR4_U_LDQUOT 25 // u_LDQUOT
#define UDT_GRAMMAR4_U_LHEX 29 // u_LHEX
#define UDT_GRAMMAR4_U_LPAREN 35 // u_LPAREN
#define UDT_GRAMMAR4_U_LWS 24 // u_LWS
#define UDT_GRAMMAR4_U_NC_VALUE 27 // u_nc-value
#define UDT_GRAMMAR4_U_ONE_OR_MORE_UNRESERVED 4 // u_one-or-more-unreserved
#define UDT_GRAMMAR4_U_ONEORMOREDIGIT 2 // u_OneOrMoreDigit
#define UDT_GRAMMAR4_U_PNANE 10 // u_pnane
#define UDT_GRAMMAR4_U_PVALUE 11 // u_pvalue
#define UDT_GRAMMAR4_U_QUOTED_STRING 21 // u_quoted-string
#define UDT_GRAMMAR4_U_RAQUOT 23 // u_RAQUOT
#define UDT_GRAMMAR4_U_RDQUOT 26 // u_RDQUOT
#define UDT_GRAMMAR4_U_REQUEST_DIGEST 28 // u_request-digest
#define UDT_GRAMMAR4_U_RFC1035DOMAIN 34 // u_RFC1035domain
#define UDT_GRAMMAR4_U_RPAREN 36 // u_RPAREN
#define UDT_GRAMMAR4_U_SCHEME 12 // u_scheme
#define UDT_GRAMMAR4_U_SEMI 18 // u_SEMI
#define UDT_GRAMMAR4_U_SLASH 19 // u_SLASH
#define UDT_GRAMMAR4_U_STAR 30 // u_STAR
#define UDT_GRAMMAR4_U_TOKEN 3 // u_token
#define UDT_GRAMMAR4_U_TOPLABEL 9 // u_toplabel
#define UDT_GRAMMAR4_U_UNRESERVED 13 // u_unreserved
#define UDT_GRAMMAR4_U_USER 6 // u_user
#define UDT_COUNT_GRAMMAR4 37

// Parser initialization data
extern void* vpParserInit_Grammar4;

#endif // GRAMMAR4_H

//**** SABNF GRAMMAR ****
//;
//; Grammar4 - IPV4address
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
//userinfo          =  ( u_user / telephone-subscriber ) [ ":" password ] "@"
//;user              =  1*( u_one-or-more-unreserved / u_escaped / user-unreserved )
//user-unreserved   =  "&" / "=" / "+" / "$" / "," / ";" / "?" / "/"
//password          =  *( u_one-or-more-unreserved / u_escaped / "&" / "=" / "+" / "$" / "," )
//hostport          =  host [ ":" port ]
//host              =  hostname / u_IPv4address / IPv6reference
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
//;IPv4address    =  1*3DIGIT "." 1*3DIGIT "." 1*3DIGIT "." 1*3DIGIT
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
//gen-value           =  u_token / host / u_quoted-string
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
//username-value      =  u_quoted-string
//digest-uri          =  "uri" u_EQUAL u_LDQUOT digest-uri-value u_RDQUOT
//digest-uri-value    =  *(%x20-21/%x23-FF)
//message-qop         =  "qop" u_EQUAL qop-value
//cnonce              =  "cnonce" u_EQUAL cnonce-value
//cnonce-value        =  nonce-value
//nonce-count         =  "nc" u_EQUAL u_nc-value
//;nc-value            =  8LHEX
//dresponse           =  "response" u_EQUAL u_request-digest
//;request-digest      =  u_LDQUOT u_32LHEX u_RDQUOT
//auth-param          =  auth-param-name u_EQUAL ( u_token / u_quoted-string )
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
//display-name        =  u_quoted-string / d-name
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
//m-value             =  u_token / u_quoted-string
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
//realm-value         =  u_quoted-string
//domain              =  "domain" u_EQUAL u_LDQUOT URI *( 1*SP URI ) u_RDQUOT
//URI                 =  absoluteURI / abs-path
//nonce               =  "nonce" u_EQUAL nonce-value
//nonce-value         =  u_quoted-string
//opaque              =  "opaque" u_EQUAL u_quoted-string
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
//via-received        =  "received" u_EQUAL (u_IPv4address / IPv6address)
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
//warn-text           =  u_quoted-string
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
//;quoted-string   =  e_SWS %x22 q-string %x22
//;q-string        =  *(qdtext / quoted-pair )
//;qdtext          =  u_LWS / %x21 / %x23-5B / %x5D-7E / UTF8-NONASCII
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

