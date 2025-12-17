#ifndef _PKT_DUMP_H_
#define _PKT_DUMP_H_

#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <rte_mbuf.h>
#include <rte_hexdump.h>

// #define DUMP_PCAP

void open_pcap_file(const char *filename);
void dump_packet(struct rte_mbuf *pkt);
void print_mbuf_hex(const char *title, struct rte_mbuf *m);

#endif
