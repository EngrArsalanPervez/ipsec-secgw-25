################### H ###################
cd /home/network/Desktop/dpdk
modprobe uio
insmod ./dpdk-kmods/linux/igb_uio/igb_uio.ko
insmod ./build/kernel/linux/kni/rte_kni.ko carrier=on
ifconfig enp6s0f0 down
ifconfig enp6s0f1 down
ifconfig enp6s0f2 down
ifconfig enp6s0f3 down
ifconfig enp7s0f0 down
ifconfig enp7s0f1 down
ifconfig enp7s0f2 down
ifconfig enp7s0f3 down
./usertools/dpdk-devbind.py --bind=igb_uio enp6s0f0
./usertools/dpdk-devbind.py --bind=igb_uio enp6s0f1
./usertools/dpdk-devbind.py --bind=igb_uio enp6s0f2
./usertools/dpdk-devbind.py --bind=igb_uio enp6s0f3
./usertools/dpdk-devbind.py --bind=igb_uio enp7s0f0
./usertools/dpdk-devbind.py --bind=igb_uio enp7s0f1
./usertools/dpdk-devbind.py --bind=igb_uio enp7s0f2
./usertools/dpdk-devbind.py --bind=igb_uio enp7s0f3
echo 2048 >/sys/devices/system/node/node0/hugepages/hugepages-2048kB/nr_hugepages
cd examples/ipsec-secgw/
./build/ipsec-secgw -c 0xfff -n 4 --socket-mem 1024,0 --vdev "crypto_openssl" -- -p 0xff -P -u 0xf0 --config="(0,0,0),(1,0,1),(2,0,2),(3,0,3),(4,0,4),(5,0,5),(6,0,6),(7,0,7)" -d H1 -f ./ngtl/config/IPE_H1.cfg --transfer-mode poll -t 1
until ipsec-secgw; do
  echo "Server 'ipsec-secgw' crashed with exit code $?.  Respawning.." >&2
  sleep 2
  ./build/ipsec-secgw -c 0xfff -n 4 --socket-mem 1024,0 --vdev "crypto_openssl" -- -p 0xff -P -u 0xf0 --config="(0,0,0),(1,0,1),(2,0,2),(3,0,3),(4,0,4),(5,0,5),(6,0,6),(7,0,7)" -d H1 -f ./ngtl/config/IPE_H1.cfg --transfer-mode poll -t 1
done

################### L ###################
modprobe uio
insmod ./dpdk-kmods/linux/igb_uio/igb_uio.ko
insmod ./build/kernel/linux/kni/rte_kni.ko carrier=on
ifconfig enp2s0f2 down
ifconfig enp2s0f3 down
./usertools/dpdk-devbind.py --bind=igb_uio enp2s0f2
./usertools/dpdk-devbind.py --bind=igb_uio enp2s0f3
echo 1024 >/sys/devices/system/node/node0/hugepages/hugepages-2048kB/nr_hugepages
cd examples/ipsec-secgw/
./build/ipsec-secgw -c 0xf -n 4 --socket-mem 1024,0 --vdev "crypto_openssl" -- -p 0x3 -P -u 0x2 --config="(0,0,0),(1,0,1)" -d L1 -f ./ngtl/config/IPE_L1.cfg --transfer-mode poll -t 1
until ipsec-secgw; do
  echo "Server 'ipsec-secgw' crashed with exit code $?.  Respawning.." >&2
  sleep 2
  ./build/ipsec-secgw -c 0xf -n 4 --socket-mem 1024,0 --vdev "crypto_openssl" -- -p 0x3 -P -u 0x2 --config="(0,0,0),(1,0,1)" -d L1 -f ./ngtl/config/IPE_L1.cfg --transfer-mode poll -t 1
done
