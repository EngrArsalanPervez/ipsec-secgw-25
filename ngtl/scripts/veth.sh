################### H1 ###################
#!/bin/sh

sleep 10

ip link set vEth0_0 up
ip addr add 1.1.1.1/24 dev vEth0_0
ip neigh add 1.1.1.2 lladdr ee:bb:cc:00:00:01 dev vEth0_0 nud permanent

echo "vEth0_0 configured successfully."

################### H2 ###################
#!/bin/sh

sleep 10

ip link set vEth0_0 up
ip addr add 1.1.1.2/24 dev vEth0_0
ip addr add 2.2.2.1/24 dev vEth0_0
ip addr add 3.3.3.1/24 dev vEth0_0
ip neigh add 1.1.1.1 lladdr ee:bb:cc:00:00:00 dev vEth0_0 nud permanent
ip neigh add 2.2.2.2 lladdr ee:bb:cc:00:00:03 dev vEth0_0 nud permanent
ip neigh add 3.3.3.2 lladdr ee:bb:cc:00:00:05 dev vEth0_0 nud permanent

echo "vEth0_0 configured successfully."

################### L2 ###################
#!/bin/sh

sleep 10

ip link set vEth0_0 up
ip addr add 2.2.2.2/24 dev vEth0_0
ip neigh add 2.2.2.1 lladdr ee:bb:cc:00:00:01 dev vEth0_0 nud permanent

echo "vEth0_0 configured successfully."

################### L4 ###################
#!/bin/sh

sleep 10

ip link set vEth0_0 up
ip addr add 3.3.3.2/24 dev vEth0_0
ip neigh add 3.3.3.1 lladdr ee:bb:cc:00:00:01 dev vEth0_0 nud permanent

echo "vEth0_0 configured successfully."
