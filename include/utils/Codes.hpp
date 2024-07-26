/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Codes.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 03:13:05 by gmachado          #+#    #+#             */
/*   Updated: 2024/07/26 17:19:43 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODES_HPP
# define CODES_HPP

typedef enum {
	NO_CODE = 000, // Ok
	RPL_WELCOME = 001, // Ok
	RPL_YOURHOST = 002, // Ok
	RPL_CREATED = 003,
	RPL_MYINFO = 004, // Ok
	RPL_ISUPPORT = 005,
	RPL_BOUNCE = 010,
	RPL_STATSCOMMANDS = 212,
	RPL_ENDOFSTATS = 219,
	RPL_UMODEIS = 221, // Ok
	RPL_STATSUPTIME = 242,
	RPL_LUSERCLIENT = 251,
	RPL_LUSEROP = 252,
	RPL_LUSERUNKNOWN = 253,
	RPL_LUSERCHANNELS = 254,
	RPL_LUSERME = 255,
	RPL_ADMINME = 256,
	RPL_ADMINLOC1 = 257,
	RPL_ADMINLOC2 = 258,
	RPL_ADMINEMAIL = 259,
	RPL_TRYAGAIN = 263,
	RPL_LOCALUSERS = 265,
	RPL_GLOBALUSERS = 266,
	RPL_WHOISCERTFP = 276,
	RPL_NONE = 300,
	RPL_AWAY = 301,
	RPL_USERHOST = 302,
	RPL_UNAWAY = 305,
	RPL_NOWAWAY = 306,
	RPL_WHOISREGNICK = 307,
	RPL_WHOISUSER = 311,
	RPL_WHOISSERVER = 312,
	RPL_WHOISOPERATOR = 313,
	RPL_WHOWASUSER = 314,
	RPL_ENDOFWHO = 315,
	RPL_WHOISIDLE = 317,
	RPL_ENDOFWHOIS = 318,
	RPL_WHOISCHANNELS = 319,
	RPL_WHOISSPECIAL = 320,
	RPL_LISTSTART = 321,
	RPL_LIST = 322,
	RPL_LISTEND = 323,
	RPL_CHANNELMODEIS = 324, // Ok
	RPL_CREATIONTIME = 329,
	RPL_WHOISACCOUNT = 330,
	RPL_NOTOPIC = 331, // Ok
	RPL_TOPIC = 332, // Ok
	RPL_TOPICWHOTIME = 333,
	RPL_INVITELIST = 336,
	RPL_ENDOFINVITELIST = 337,
	RPL_WHOISACTUALLY = 338,
	RPL_INVITING = 341, // Ok
	RPL_INVEXLIST = 346,
	RPL_ENDOFINVEXLIST = 347,
	RPL_EXCEPTLIST = 348,
	RPL_ENDOFEXCEPTLIST = 349,
	RPL_VERSION = 351,
	RPL_WHOREPLY = 352,
	RPL_NAMREPLY = 353, // Ok
	RPL_LINKS = 364,
	RPL_ENDOFLINKS = 365,
	RPL_ENDOFNAMES = 366, // Ok
	RPL_BANLIST = 367,
	RPL_ENDOFBANLIST = 368,
	RPL_ENDOFWHOWAS = 369,
	RPL_INFO = 371,
	RPL_MOTD = 372,
	RPL_ENDOFINFO = 374,
	RPL_MOTDSTART = 375,
	RPL_ENDOFMOTD = 376,
	RPL_WHOISHOST = 378,
	RPL_WHOISMODES = 379,
	RPL_YOUREOPER = 381,
	RPL_REHASHING = 382,
	RPL_TIME = 391,
	ERR_UNKNOWNERROR = 400, // Ok
	ERR_NOSUCHNICK = 401, // Ok
	ERR_NOSUCHSERVER = 402,
	ERR_NOSUCHCHANNEL = 403, // Ok
	ERR_CANNOTSENDTOCHAN = 404, // Ok
	ERR_TOOMANYCHANNELS = 405, // Ok
	ERR_WASNOSUCHNICK = 406,
	ERR_NOORIGIN = 409,
	ERR_NORECIPIENT = 411, // Ok
	ERR_NOTEXTTOSEND = 412, // Ok
	ERR_INPUTTOOLONG = 417, // Ok
	ERR_UNKNOWNCOMMAND = 421,
	ERR_NOMOTD = 422,
	ERR_NONICKNAMEGIVEN = 431, // Ok
	ERR_ERRONEUSNICKNAME = 432, // Ok
	ERR_NICKNAMEINUSE = 433, // Ok
	ERR_NICKCOLLISION = 436,
	ERR_USERNOTINCHANNEL = 441, // Ok
	ERR_NOTONCHANNEL = 442, // Ok
	ERR_USERONCHANNEL = 443, // Ok
	ERR_NOTREGISTERED = 451,// Ok
	ERR_NEEDMOREPARAMS = 461, // Ok
	ERR_ALREADYREGISTERED = 462, // Ok
	ERR_PASSWDMISMATCH = 464, // Ok
	ERR_YOUREBANNEDCREEP = 465,
	ERR_KEYSET = 467, // Ok
	ERR_CHANNELISFULL = 471, // Ok
	ERR_UNKNOWNMODE = 472, // Ok
	ERR_INVITEONLYCHAN = 473, // Ok
	ERR_BANNEDFROMCHAN = 474, // Ok
	ERR_BADCHANNELKEY = 475, // Ok
	ERR_BADCHANMASK = 476, // Ok
	ERR_NOPRIVILEGES = 481,
	ERR_CHANOPRIVSNEEDED = 482, // Ok
	ERR_CANTKILLSERVER = 483,
	ERR_NOOPERHOST = 491,
	ERR_UMODEUNKNOWNFLAG = 501,
	ERR_USERSDONTMATCH = 502, // Ok
	ERR_HELPNOTFOUND = 524,
	ERR_INVALIDKEY = 525,
	RPL_STARTTLS = 670,
	RPL_WHOISSECURE = 671,
	ERR_STARTTLS = 691,
	ERR_INVALIDMODEPARAM = 696,
	RPL_HELPSTART = 704,
	RPL_HELPTXT = 705,
	RPL_ENDOFHELP = 706,
	ERR_NOPRIVS = 723,
	RPL_LOGGEDIN = 900,
	RPL_LOGGEDOUT = 901,
	ERR_NICKLOCKED = 902,
	RPL_SASLSUCCESS = 903,
	ERR_SASLFAIL = 904,
	ERR_SASLTOOLONG = 905,
	ERR_SASLABORTED = 906,
	ERR_SASLALREADY = 907,
	RPL_SASLMECHS = 908
} t_numCode;

#endif
