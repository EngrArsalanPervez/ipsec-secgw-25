# Global

```bash
1. IKEve Settings:
  a. Enable/Disable
  b. Timer in Hours
```

# Add Tunnel

Any IP Address should never be in /32 form. It must be a single IP

If /32 is required in the backend, just hardcode it in the backend

No /32 on frontend

## Encapsulation

```bash
Port:    # encapsulation_port No Range Check
Src Mac: # encapsulation_src_mac
Dst Mac: # encapsulation_dst_mac
Src IP:  # encapsulation_src_ip
Dst IP:  # encapsulation_dst_ip
```

## Tunnel

```bash
Tunnel Name: # Single/Unique Word
Port:    # tunnel_port No Range Check
Src Mac: # tunnel_src_mac
Dst Mac: # tunnel_dst_mac
Src IP:  # tunnel_src_ip
Dst IP:  # tunnel_dst_ip

SrcID:
DstID:
Pre-Shared Key:
Comment
Enable/Disable

```

# Example

```bash
#######################################################################################################

#SP Rules
#1
sp ipv4 out esp protect 102 pri 1 dst 10.10.10.2/32 sport 0:65535 dport 0:65535
sp ipv4 in esp protect 101 pri 1 dst 10.10.10.1/32 sport 0:65535 dport 0:65535

#SA Rules
#1
sa out 102 cipher_algo aes-128-cbc cipher_key a0:a0:a0:a0:a0:a0:a0:a0:a0:a0:a0:\
a0:a0:a0:a0:a0 auth_algo sha1-hmac auth_key a0:a0:a0:a0:a0:a0:a0:a0:a0:a0:a0:\
a0:a0:a0:a0:a0:a0:a0:a0:a0 mode ipv4-tunnel src 1.1.1.1 dst 1.1.1.2

sa in 101 cipher_algo aes-128-cbc cipher_key a0:a0:a0:a0:a0:a0:a0:a0:a0:a0:a0:\
a0:a0:a0:a0:a0 auth_algo sha1-hmac auth_key a0:a0:a0:a0:a0:a0:a0:a0:a0:a0:a0:\
a0:a0:a0:a0:a0:a0:a0:a0:a0 mode ipv4-tunnel src 1.1.1.2 dst 1.1.1.1

#Routing Rules
#1
rt ipv4 dst 10.10.10.1/32 port 0
rt ipv4 dst 1.1.1.2/32 port 4

#Neighbour Rules
#1
neigh port 0 aa:bb:cc:00:00:00


#######################################################################################################
```

# Co-Relation

```bash
spi_number = Formula
10.10.10.1 = encapsulation_src_ip
10.10.10.2 = encapsulation_dst_ip
1.1.1.1 = tunnel_src_ip
1.1.1.2 = tunnel_dst_ip
aa:bb:cc:00:00:00 = encapsulation_src_mac

rt ipv4 dst encapsulation_src_ip/32 port encapsulation_port
rt ipv4 dst tunnel_dst_ip/32 port tunnel_port
neigh port encapsulation_port encapsulation_src_mac
```
