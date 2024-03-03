#include "types.h"
#include "defs.h"

ushort htons(ushort n) {
  ushort a = 0;
  ushort b;
  int bytes = sizeof(n);
  for(int i = 0; i < bytes; i++) {
    b = (n >> (i * 8)) & 0xff;
    a |= b << (8 * (bytes - i - 1));
  }
  return a;
}

uint htonl(uint n) {
  uint a = 0;
  uint b;
  int bytes = sizeof(n);
  for(int i = 0; i < bytes; i++) {
    b = (n >> (i * 8)) & 0xff;
    a |= b << (8 * (bytes - i - 1));
  }
  return a;
}

uint inet_addr(char ip_str[]) {
  int byte = 0;
  int ip = 0;
  int i = 0;

  while(ip_str[i] != 0) {
    if(ip_str[i] == '.') {
      ip = ip << 8;
      ip |= byte;
      byte = 0;
    }
    else {
      byte = byte * 10 + (ip_str[i] - '0');
    }
    i++;
  }
  ip = ip << 8;
  ip |= byte;
  return ip;
}