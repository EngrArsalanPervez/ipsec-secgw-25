#include "pkt_dump.h"

static pcap_dumper_t *pcap_dumper;
static pcap_t *pcap_handle;

void open_pcap_file(const char *filename) {
    char errbuf[PCAP_ERRBUF_SIZE];

    // Open a pcap file for packet capture (not for dumping)
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535); // Ethernet header
    if (!pcap_handle) {
        fprintf(stderr, "Failed to open pcap file for capture\n");
        exit(1);
    }

    // Open the pcap dump file (use pcap_dump_open for dumping packets)
    pcap_dumper = pcap_dump_open(pcap_handle, filename);
    if (pcap_dumper == NULL) {
        fprintf(stderr, "Failed to open pcap dump file: %s\n", filename);
        exit(1);
    }
}

/* Function to process and dump packets to pcap */
void dump_packet(struct rte_mbuf *pkt) {
    struct pcap_pkthdr header;
    uint8_t *packet_data;

    // Get packet data (you can extract headers here if needed)
    packet_data = rte_pktmbuf_mtod(pkt, uint8_t *);

    // Create the pcap header
    header.ts.tv_sec = time(NULL); // Timestamp
    header.ts.tv_usec = 0;
    header.caplen = pkt->pkt_len;
    header.len = pkt->pkt_len;

    // Dump the packet to pcap
    pcap_dump((u_char *) pcap_dumper, &header, packet_data);
}

void print_mbuf_hex(const char *title, struct rte_mbuf *m) {
    struct rte_mbuf *seg = m;
    unsigned seg_idx = 0;

    while (seg != NULL) {
        printf("=== %s: segment %u ===\n", title ? title : "mbuf", seg_idx);
        printf("pkt_len=%u, data_len=%u, data_off=%u\n", seg->pkt_len, seg->data_len,
               seg->data_off);

        // Dump the actual data in this segment
        rte_hexdump(stdout, "segment data", rte_pktmbuf_mtod(seg, void *), seg->data_len);

        seg = seg->next;
        seg_idx++;
    }
}