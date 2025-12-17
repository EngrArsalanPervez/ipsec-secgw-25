#ifndef _PKT_WRAPPER_H_
#define _PKT_WRAPPER_H_

#include <stdint.h>

#include <rte_mbuf.h>
#include <rte_mempool.h>
#include <rte_ether.h>
#include <rte_ethdev.h>
#include <rte_ip.h>
#include <rte_memcpy.h>
#include <rte_byteorder.h>
#include <rte_lcore.h>

#include "pkt_rules.h"
#include "pkt_dump.h"

void encapsulate_pkt(struct rte_mbuf **pkts, uint8_t nb_pkts, struct rte_mempool *pool,
                     uint16_t portid);
void decapsulate_pkt(struct rte_mbuf **pkts, uint8_t nb_pkts);

#endif
