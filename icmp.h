#include "types.h"
#include "defs.h"

#define ICMP_TYPE_ECHOREPLY 0
#define ICMP_TYPE_DEST_UNREACH 3
#define ICMP_TYPE_SOURCE_QUENCH 4
#define ICMP_TYPE_REDIRECT 5
#define ICMP_TYPE_ECHO 8
#define ICMP_TYPE_TIME_EXCEEDED 11
#define ICMP_TYPE_PARAM_PROBLEM 12
#define ICMP_TYPE_TIMESTAMP 13
#define ICMP_TYPE_TIMESTAMPREPLY 14
#define ICMP_TYPE_INFO_REQUEST 15
#define ICMP_TYPE_INFO_REPLY 16

/* for UNREACH */
#define ICMP_CODE_NET_UNREACH 0
#define ICMP_CODE_HOST_UNREACH 1
#define ICMP_CODE_PROTO_UNREACH 2
#define ICMP_CODE_PORT_UNREACH 3
#define ICMP_CODE_FRAGMENT_NEEDED 4
#define ICMP_CODE_SOURCE_ROUTE_FAILED 5

/* for REDIRECT */
#define ICMP_CODE_REDIRECT_NET 0
#define ICMP_CODE_REDIRECT_HOST 1
#define ICMP_CODE_REDIRECT_TOS_NET 2
#define ICMP_CODE_REDIRECT_TOS_HOST 3

/* for TIME_EXEEDED */
#define ICMP_CODE_EXCEEDED_TTL 0
#define ICMP_CODE_EXCEEDED_FRAGMENT 1

typedef struct icmp_echo {
    ushort id;
    ushort seq;
} icmp_echo;

typedef struct icmp_hdr {
    uchar type;
    uchar code;
    ushort sum;
    union {
        icmp_echo echo;
        uint gateway;
        uchar ptr;
        uint unused;
    } un;
    uchar data[0];
} icmp_hdr;

struct icmp_reply_packet {
    int size;
    uint src_ip;
    ushort seq_no;
};

#define ICMP_HDR_SIZE		(sizeof(icmp_hdr))
#define IP_ICMP_HDR_SIZE	(IP_HDR_SIZE + ICMP_HDR_SIZE)
