/***************************************************************************
 *   Copyright (C) 2010 by lwp                                             *
 *   levin108@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Suite 500, Boston, MA 02110-1335, USA.            *
 *                                                                         *
 *   OpenSSL linking exception                                             *
 *   --------------------------                                            *
 *   If you modify this Program, or any covered work, by linking or        *
 *   combining it with the OpenSSL project's "OpenSSL" library (or a       *
 *   modified version of that library), containing parts covered by        *
 *   the terms of OpenSSL/SSLeay license, the licensors of this            *
 *   Program grant you additional permission to convey the resulting       *
 *   work. Corresponding Source for a non-source form of such a            *
 *   combination shall include the source code for the parts of the        *
 *   OpenSSL library used as well as that of the covered work.             *
 ***************************************************************************/

#ifndef FETION_TYPES_H
#define FETION_TYPES_H

#include "fetion.h"

/* inline function to trace program track */

/**
 * some other buddylists
 */
typedef enum {
    BUDDY_LIST_NOT_GROUPED = 0 ,
    BUDDY_LIST_STRANGER =   -1 ,
    BUDDY_LIST_PGGROUP =      -2
} BuddyListType;

/**
 * Presence states
 */
typedef enum {
    P_ONLINE =       400 , 
    P_RIGHTBACK =    300 ,
    P_AWAY =         100 ,
    P_BUSY =         600 ,
    P_OUTFORLUNCH =  500 ,
    P_ONTHEPHONE =   150 ,
    P_MEETING =      850 ,
    P_DONOTDISTURB = 800 ,
    P_HIDDEN =       0 ,
    P_OFFLINE =      -1
} StateType;

/**
 * Type to indicate user`s service status 
 */
typedef enum {
    STATUS_NORMAL = 1 ,                 /* normal status                                             */
    STATUS_OFFLINE ,                    /* user offline , deleted you from his list or out of service*/
    STATUS_NOT_AUTHENTICATED ,          /* user has not accept your add buddy request                */
    STATUS_SMS_ONLINE ,                 /* user has not start fetion service                         */
    STATUS_REJECTED ,                   /* user rejected your add buddy request,wait for deleting    */
    STATUS_SERVICE_CLOSED ,             /* user has closed his fetion service                        */
    STATUS_NOT_BOUND                    /* user doesn`t bound fetion number to a mobile number       */
} StatusType;

/**
 * Sip header that in form of "name: value" such as "AK: ak-value"
 */
typedef struct sipheader {
    char              name[8];          /* sip header namne*/
    char             *value;            /* sip header value*/
    struct sipheader *next;             /* next sip header */
} SipHeader;

/**
 * Sip type include some common attributes
 */
typedef struct {
    int type;                           /* sip message type                       */
    char from[20];                      /* sender`s fetion no ,in sip it`s "F: "  */
    int callid;
    int sequence;                       /* sequence number , in sip it`s "Q: "    */
    int threadCount;                    /* listening threads count using this sip */
    char sipuri[48];                    /* outer sipuri used when listening       */
    SipHeader* header;                  /* some othre header list                 */
} fetion_sip;

/**
 * Contact lists information (Two-way linked list) 
 */
typedef struct contact {
    char userId[16];                    /* userid used since v4 protocal                    */
    char sId[16];                       /* fetion no                                        */
    char sipuri[48];                    /* sipuri like 'sip:100@fetion.com.cn'              */
    char localname[256];                    /* name set by yourself                             */
    char nickname[256];                 /* user`s nickname                                  */
    char impression[2048];              /* user`s mood phrase                               */
    char mobileno[12];                  /* mobile phone number                              */
    char devicetype[10];                /* user`s client type , like PC and J2ME,etc        */
    char portraitCrc[12];               /* a number generated by crc algorithm              */
    char birthday[16];                  /* user`s bitrhday                                  */
    char country[6];                    /* user`s country`s simplified form,like CN         */
    char province[6];                   /* user`s province`s simplified form,like bj        */
    char city[6];                       /* user`s city`s code ,like 10 for beijing          */
    int identity;                       /* whethere to show mobileno to this user           */
    int scoreLevel;                     /* user`s score level,unused now                    */
    int serviceStatus;                  /* basic service status                             */
    int carrierStatus;
    int relationStatus;
    char carrier[16];
    StateType state;                    /* state type like online,busy,etc                  */
    int groupid;                        /* buddylist id                                     */
    int gender;                         /* gender 1 for male 2 for female,0 for private     */
    int imageChanged;                   /* whether user`s portrait has changed              */
    int dirty;                          /* whether the contact just read from the server is 
                                           newer than that int the local disk */
    struct contact* next;
    struct contact* pre;
} Contact;

/**
 * Buddy lists information (Two-way linked list)
 */
typedef struct group {
    char groupname[32];                 /* current buddy list name  */
    int groupid;                        /* current buddy list Id    */
    int dirty;
    struct group *next;
    struct group *pre;
} Group;

/**
 * Verification information used for picture code confirm
 */
typedef struct {
    char *algorithm;
    char *type;
    char *text;
    char *tips;
    char *code;
    char *guid;
} Verification;

/**
 * User`s personal information and some related structs 
 */
typedef struct {
    char sId[16];                       /* fetion number                                            */
    char userId[16];                    /* user id                                                  */
    char mobileno[16];                  /* mobile phone number                                      */
    char password[48];                  /* raw password not hashed                                  */
    char sipuri[48];                    /* sipuri like 'sip:100@fetion.com.cn'                      */
    char publicIp[32];                  /* public ip of current session                             */
    char lastLoginIp[32];               /* public ip of last login                                  */
    char lastLoginTime[48];             /* last login time , got after sipc authentication          */
    char sipcProxyIP[32];
    int  sipcProxyPort;

    char portraitServerName[48];        /* portrait server`s hostname ,read from configuration.xml*/
    char portraitServerPath[32];        /* portrait server`s path , such as /HD_POOL8             */
    char configServersVersion[16];      /* the version of some related servers such as sipc server  */
    char configParametersVersion[16];
    char configHintsVersion[16];        /* the version of hints                                     */
    char personalVersion[16];           /* the version of personal information                      */
    char contactVersion[16];            /* the version of contact information                       */
    char customConfigVersion[16];       /* the version of custom config string,unused now           */

    char nickname[48];                  /* nickname of yourself                                     */
    char impression[256];               /* mood phrase of yourself                                  */
    char portraitCrc[16];               /* a number generated by crc algorithm                      */
    char country[6];                    /* the country which your number belongs to                 */
    char province[6];                   /* the province which your number belongs to                */
    char city[6];                       /* the city which your number belongs to                    */
    int gender;                         /* the gender of your self                                  */
    char smsOnLineStatus[32];

    int smsDayLimit;
    int smsDayCount;
    int smsMonthLimit;
    int smsMonthCount;

    int pgGroupCallId;                  /* callid for get group list request */
    int groupInfoCallId;                    /* callid for get group info request */

    int state;                          /* presence state                                           */
    int loginType;                      /* using sid or mobileno                                    */
    int loginStatus;                    /* login status code                                        */
    int carrierStatus;
    int boundToMobile;                  /* whether this number is bound to a mobile number  */
    long loginTimes;
    int contactCount;
    int groupCount;
    char* ssic;                         /* cookie string read from reply message after ssi login    */
    char* customConfig;                 /* custom config string used to set personal information    */
    Verification* verification;         /* a struct used to generate picture code                   */   
    Contact* contactList;               /* friend list of current user                              */
    Group* groupList;                   /* buddylist list of current user                           */
    fetion_sip* sip;                        /* sip object used to handle sip event                      */
} User;

typedef struct {
    gint        sk;
    guint       conn;
    gint        left_len;
    User       *user;
    gchar      *data;
    gchar       userId[48];
    gint        chan_ready;             /* only used in chat session */
    GSList     *trans;
    GSList     *trans_wait;         /* only used in chat session */
    PurpleConnection *gc;
    PurpleProxyConnectData *conn_data;
    PurpleAccount *account;
} fetion_account;

struct transaction;

typedef gint(*TransCallback) (fetion_account *,
                  const gchar *, struct transaction *);

struct transaction {
    gint callid;
    gchar userId[32];
    gchar msg[1024];
    guint timer;
    TransCallback callback;
};

#endif
