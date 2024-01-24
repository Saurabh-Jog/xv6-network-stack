#define ETHERNET_HDR_SIZE 14
#define ETHERNET_TRL_SIZE 4
#define ETHERNET_FRAME_SIZE_MIN 64
#define ETHERNET_FRAME_SIZE_MAX 1518
#define ETHERNET_PAYLOAD_SIZE_MIN (ETHERNET_FRAME_SIZE_MIN - (ETHERNET_HDR_SIZE + ETHERNET_TRL_SIZE))
#define ETHERNET_PAYLOAD_SIZE_MAX (ETHERNET_FRAME_SIZE_MAX - (ETHERNET_HDR_SIZE + ETHERNET_TRL_SIZE))

#define ETHERNET_TYPE_IP   0x0800

typedef struct {
    unsigned char          dst[6];
    unsigned char          src[6];
    unsigned short           type;
} ether_hdr;
