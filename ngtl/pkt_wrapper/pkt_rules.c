#include "pkt_rules.h"
#include <stdint.h>

typedef struct {
    uint8_t ports[RTE_MAX_ETHPORTS];
    uint8_t total;
    uint64_t mask;
} client_ports_t;
client_ports_t client_ports;

const pkt_rules_t *active_rules = NULL;
device_type_t device_type;

void client_ports_init(void)
{
    client_ports.total = 0;
    client_ports.mask = 0;
}

bool client_ports_contains(uint8_t port)
{
    return client_ports.mask & (1ULL << port);
}

bool client_ports_add(uint8_t port)
{
    if (port >= MAX_CLIENT_PORTS)
        return false;

    if (client_ports_contains(port))
        return true;

    if (client_ports.total >= MAX_CLIENT_PORTS)
        return false;

    client_ports.ports[client_ports.total++] = port;
    client_ports.mask |= (1ULL << port);
    return true;
}

const pkt_rules_t pkt_rules_h1[RTE_MAX_ETHPORTS] = {
    [0] = { .src_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0x00, 0x00, 0x00 } },
            .dst_mac = { .addr_bytes = { 0xae, 0xdd, 0xee, 0x10, 0x00, 0x00 } },
            .src_ip = RTE_IPV4(10, 10, 10, 1),
            .dst_ip = RTE_IPV4(10, 10, 10, 2) },
};

const pkt_rules_t pkt_rules_h2[RTE_MAX_ETHPORTS] = {
    [0] = { .src_mac = { .addr_bytes = { 0xae, 0xdd, 0xee, 0x10, 0x00, 0x00 } },
            .dst_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0x00, 0x00, 0x00 } },
            .src_ip = RTE_IPV4(10, 10, 10, 2),
            .dst_ip = RTE_IPV4(10, 10, 10, 1) },
    [1] = { .src_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0x00, 0x00, 0x01 } },
            .dst_mac = { .addr_bytes = { 0xae, 0xdd, 0xee, 0x10, 0x00, 0x01 } },
            .src_ip = RTE_IPV4(20, 20, 20, 1),
            .dst_ip = RTE_IPV4(20, 20, 20, 2) },
    [2] = { .src_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0x00, 0x00, 0x02 } },
            .dst_mac = { .addr_bytes = { 0xae, 0xdd, 0xee, 0x10, 0x00, 0x02 } },
            .src_ip = RTE_IPV4(30, 30, 30, 1),
            .dst_ip = RTE_IPV4(30, 30, 30, 2) },
    [3] = { .src_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0x00, 0x00, 0x03 } },
            .dst_mac = { .addr_bytes = { 0xae, 0xdd, 0xee, 0x10, 0x00, 0x03 } },
            .src_ip = RTE_IPV4(40, 40, 40, 1),
            .dst_ip = RTE_IPV4(40, 40, 40, 2) },
};

const pkt_rules_t pkt_rules_l1[RTE_MAX_ETHPORTS] = {
    [0] = { .src_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0x00, 0x00, 0x01 } },
            .dst_mac = { .addr_bytes = { 0xae, 0xdd, 0xee, 0x10, 0x00, 0x01 } },
            .src_ip = RTE_IPV4(20, 20, 20, 1),
            .dst_ip = RTE_IPV4(20, 20, 20, 2) },
};

const pkt_rules_t pkt_rules_l2[RTE_MAX_ETHPORTS] = {
    [0] = { .src_mac = { .addr_bytes = { 0xae, 0xdd, 0xee, 0x10, 0x00, 0x01 } },
            .dst_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0x00, 0x00, 0x01 } },
            .src_ip = RTE_IPV4(20, 20, 20, 2),
            .dst_ip = RTE_IPV4(20, 20, 20, 1) },
};

const pkt_rules_t pkt_rules_l3[RTE_MAX_ETHPORTS] = {
    [0] = { .src_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0x00, 0x00, 0x02 } },
            .dst_mac = { .addr_bytes = { 0xae, 0xdd, 0xee, 0x10, 0x00, 0x02 } },
            .src_ip = RTE_IPV4(30, 30, 30, 1),
            .dst_ip = RTE_IPV4(30, 30, 30, 2) },
};

const pkt_rules_t pkt_rules_l4[RTE_MAX_ETHPORTS] = {
    [0] = { .src_mac = { .addr_bytes = { 0xae, 0xdd, 0xee, 0x10, 0x00, 0x02 } },
            .dst_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0x00, 0x00, 0x02 } },
            .src_ip = RTE_IPV4(30, 30, 30, 2),
            .dst_ip = RTE_IPV4(30, 30, 30, 1) },
};

const pkt_rules_t pkt_rules_l5[RTE_MAX_ETHPORTS] = {
    [0] = { .src_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0x00, 0x00, 0x03 } },
            .dst_mac = { .addr_bytes = { 0xae, 0xdd, 0xee, 0x10, 0x00, 0x03 } },
            .src_ip = RTE_IPV4(40, 40, 40, 1),
            .dst_ip = RTE_IPV4(40, 40, 40, 2) },
};

const pkt_rules_t pkt_rules_l6[RTE_MAX_ETHPORTS] = {
    [0] = { .src_mac = { .addr_bytes = { 0xae, 0xdd, 0xee, 0x10, 0x00, 0x03 } },
            .dst_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0x00, 0x00, 0x03 } },
            .src_ip = RTE_IPV4(40, 40, 40, 2),
            .dst_ip = RTE_IPV4(40, 40, 40, 1) },
};

int config_hclos_lclos(char *optarg)
{
    client_ports_init();

    uint32_t lcore_id;

    if (strcmp(optarg, "H1") == 0) {
        active_rules = pkt_rules_h1;
        client_ports_add(0);
        device_type = (device_type_t){ .type = DUAL_PORT,
                                       .kni_rx_core = 2,
                                       .kni_tx_core = 3,
                                       .vEth0 = { .addr_bytes = { 0xee, 0xbb, 0xcc, 0x00, 0x00,
                                                                  0x00 } } };
        return 0;
    } else if (strcmp(optarg, "H2") == 0) {
        active_rules = pkt_rules_h2;
        client_ports_add(0);
        client_ports_add(1);
        client_ports_add(2);
        client_ports_add(3);
        device_type = (device_type_t){ .type = MULTI_PORT,
                                       .kni_rx_core = 8,
                                       .kni_tx_core = 9,
                                       .vEth0 = { .addr_bytes = { 0xee, 0xbb, 0xcc, 0x00, 0x00,
                                                                  0x01 } } };
        return 0;
    } else if (strcmp(optarg, "L1") == 0) {
        active_rules = pkt_rules_l1;
        client_ports_add(0);
        device_type = (device_type_t){ .type = DUAL_PORT,
                                       .kni_rx_core = 2,
                                       .kni_tx_core = 3,
                                       .vEth0 = { .addr_bytes = { 0xee, 0xbb, 0xcc, 0x00, 0x00,
                                                                  0x02 } } };
        return 0;
    } else if (strcmp(optarg, "L2") == 0) {
        active_rules = pkt_rules_l2;
        client_ports_add(0);
        device_type = (device_type_t){ .type = DUAL_PORT,
                                       .kni_rx_core = 2,
                                       .kni_tx_core = 3,
                                       .vEth0 = { .addr_bytes = { 0xee, 0xbb, 0xcc, 0x00, 0x00,
                                                                  0x03 } } };
        return 0;
    } else if (strcmp(optarg, "L3") == 0) {
        active_rules = pkt_rules_l3;
        client_ports_add(0);
        device_type = (device_type_t){ .type = DUAL_PORT,
                                       .kni_rx_core = 2,
                                       .kni_tx_core = 3,
                                       .vEth0 = { .addr_bytes = { 0xee, 0xbb, 0xcc, 0x00, 0x00,
                                                                  0x04 } } };
        return 0;
    } else if (strcmp(optarg, "L4") == 0) {
        active_rules = pkt_rules_l4;
        client_ports_add(0);
        device_type = (device_type_t){ .type = DUAL_PORT,
                                       .kni_rx_core = 2,
                                       .kni_tx_core = 3,
                                       .vEth0 = { .addr_bytes = { 0xee, 0xbb, 0xcc, 0x00, 0x00,
                                                                  0x05 } } };
        return 0;
    } else if (strcmp(optarg, "L5") == 0) {
        active_rules = pkt_rules_l5;
        client_ports_add(0);
        device_type = (device_type_t){ .type = DUAL_PORT,
                                       .kni_rx_core = 2,
                                       .kni_tx_core = 3,
                                       .vEth0 = { .addr_bytes = { 0xee, 0xbb, 0xcc, 0x00, 0x00,
                                                                  0x06 } } };
        return 0;
    } else if (strcmp(optarg, "L6") == 0) {
        active_rules = pkt_rules_l5;
        client_ports_add(0);
        device_type = (device_type_t){ .type = DUAL_PORT,
                                       .kni_rx_core = 2,
                                       .kni_tx_core = 3,
                                       .vEth0 = { .addr_bytes = { 0xee, 0xbb, 0xcc, 0x00, 0x00,
                                                                  0x07 } } };
        return 0;
    }
    return -1;
}

uint8_t get_outport(uint16_t portid)
{
    if (device_type.type == DUAL_PORT)
        return (portid == 1) ? 0 : 1;

    // Mapping: (0->4), (1->5), (2->6), (3->7), (4->0), (5->1), (6->2), (7->3)
    return (portid + 4) & 0x7;
}
