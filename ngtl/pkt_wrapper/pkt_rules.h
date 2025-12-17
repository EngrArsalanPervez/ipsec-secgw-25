#ifndef _PKT_RULES_H_
#define _PKT_RULES_H_

#include <stdint.h>
#include <rte_ether.h>
#include <rte_ip.h>
#include <stdbool.h>
#include <rte_lcore.h>

#define MAX_CLIENT_PORTS RTE_MAX_ETHPORTS

typedef enum PORT_TYPE_e { CLIENT_PORT = 0, TUNNEL_PORT = 1 } PORT_TYPE;
typedef enum DEVICE_TYPE_e { DUAL_PORT = 0, MULTI_PORT = 1 } DEVICE_TYPE;

typedef struct {
    const struct rte_ether_addr src_mac;
    const struct rte_ether_addr dst_mac;
    const uint32_t src_ip;
    const uint32_t dst_ip;
} pkt_rules_t;
extern const pkt_rules_t *active_rules;

typedef struct {
    DEVICE_TYPE type;
    uint8_t kni_rx_core;
    uint8_t kni_tx_core;
    struct rte_ether_addr vEth0;
} device_type_t;
extern device_type_t device_type;

int config_hclos_lclos(char *optarg);
bool client_ports_contains(uint8_t port);
uint8_t get_outport(uint16_t portid);

#endif
