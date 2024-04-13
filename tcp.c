#include "types.h"
#include "defs.h"
#include "stddef.h"
#include "tcp.h"
#include "socket.h"
#include "ip.h"

extern struct port ports[];

struct tcp_request requests[MAX_PENDING_REQUESTS];

void tcp_receive(void *tcp_segment, int size, uint dst_ip) {
  struct tcp_packet *rx_pkt = (struct tcp_packet*) tcp_segment;
  ushort port = rx_pkt.header.dst_port;
  struct socket *soc;
  int i;

  if(ports[port].pid == -1)
    return;
  if((soc = ports[port].socket) == 0)
    return;
  if(soc->state == SOCKET_UNBOUND)
    return;

  if((rx_pkt->header.flags & TCP_FLAG_SYN) != 0) {
    if(soc->state == SOCKET_LISTENING || soc->state == SOCKET_ACCPETING) {
      for(i = 0; i < MAX_PENDING_REQUESTS; i++) {
        if(requests[i].client_ip != 0) 
          break;
      }
      requests[i].client_ip = dst_ip;
      memmove((void*) &requests[i].request_packet, tcp_segment, size);
      // enqueue

      if(soc->state == SOCKET_ACCEPTING)
      // wakeup
    }

    else if(soc->state == SOCKET_CONNECTING && (rx_pkt->header.flags & TCP_FLAG_SYN) != 0) {
      // add packet to buffer
      // wakeup
    }
    return;
  }

  if(soc->state == SOCKET_WAITING_FOR_ACK) {
    // ??
    // wakeup
    return;
  }
}

void tcp_send(ushort src_port, ushort dst_port, uint dst_ip, uint seq_num, uint ack_num, uchar flags, uchar hdr_size,  void* data, int data_size) {
  // Construct TCP packet
  struct tcp_packet packet;
  uint total_size = hdr_size + data_size;
  packet.header.src_port = htons(src_port);
  packet.header.dst_port = htons(dst_port);
  packet.header.seq_num = htonl(seq_num);
  packet.header.ack_num = htonl(ack_num);
  packet.header.offset = (hdr_size >> 2) << 4;
  packet.header.flags = flags;
  packet.header.window_size = htons(WINDOW_SIZE);

  // Copy data into packet
  memmove(packet.options_data, data, data_size);

  // Calculate TCP header checksum
  packet.header.checksum = checksum(&packet.header,sizeof(struct tcp_hdr));

  // Send packet using IP layer
  ip_send(IP_PROTOCOL_TCP, &packet, MY_IP, dst_ip, total_size);

  return;
}
