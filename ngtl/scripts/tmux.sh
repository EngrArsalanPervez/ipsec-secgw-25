#!/bin/bash

# Name of the tmux session
SESSION_NAME="eup"

# Check if the session already exists
tmux has-session -t $SESSION_NAME 2>/dev/null

# If the session doesn't exist, create it
if [ $? != 0 ]; then
  # Create the :0 window (tab)
  tmux new-session -d -s $SESSION_NAME -n "DPDK"
  tmux send-keys -t $SESSION_NAME:0 "cd /home/network/Desktop/bootstartup/" Enter
  tmux send-keys -t $SESSION_NAME:0 "./dpdk.sh" Enter

  # Create the :1 window (tab)
  tmux new-window -t $SESSION_NAME:1 -n "ipsec-secgw"
  tmux send-keys -t $SESSION_NAME:1 "cd /home/network/Desktop/dpdk/examples/ipsec-secgw" Enter

  # Create the :2 window (tab)
  tmux new-window -t $SESSION_NAME:2 -n "config"
  tmux send-keys -t $SESSION_NAME:2 "cd /home/network/Desktop/dpdk/examples/ipsec-secgw/ngtl/config" Enter
  tmux send-keys -t $SESSION_NAME:2 "ls -lah" Enter

  # Create the :3 window (tab)
  tmux new-window -t $SESSION_NAME:3 -n "scripts"
  tmux send-keys -t $SESSION_NAME:3 "cd /home/network/Desktop/dpdk/examples/ipsec-secgw/ngtl/scripts" Enter
  tmux send-keys -t $SESSION_NAME:3 "ls -lah" Enter

  # Create the :4 window (tab)
  tmux new-window -t $SESSION_NAME:4 -n "dpdk"
  tmux send-keys -t $SESSION_NAME:4 "cat /home/network/Desktop/bootstartup/dpdk.sh" Enter

  # Create the :5 window (tab)
  tmux new-window -t $SESSION_NAME:5 -n "setup_veth.sh"
  tmux send-keys -t $SESSION_NAME:5 "/home/network/Desktop/bootstartup/setup_veth.sh" Enter
  tmux send-keys -t $SESSION_NAME:5 "cat /home/network/Desktop/bootstartup/setup_veth.sh" Enter

  # Create the :6 window (tab)
  tmux new-window -t $SESSION_NAME:6 -n "ipsec.conf"
  tmux send-keys -t $SESSION_NAME:6 "cat /etc/ipsec.conf" Enter

  # Create the :7 window (tab)
  tmux new-window -t $SESSION_NAME:7 -n "ipsec.secrets"
  tmux send-keys -t $SESSION_NAME:7 "cat /etc/ipsec.secrets" Enter

  # Create the :8 window (tab)
  tmux new-window -t $SESSION_NAME:8 -n "DB"
  tmux send-keys -t $SESSION_NAME:8 "mongosh" Enter

  # Create the :9 window (tab)
  tmux new-window -t $SESSION_NAME:9 -n "ipsec.py"
  tmux send-keys -t $SESSION_NAME:9 "cat /home/network/Desktop/dpdk/examples/ipsec-secgw/ngtl/scripts/ipsec.py" Enter
  #tmux send-keys -t $SESSION_NAME:8 "python3 ipsec.py" Enter

  # Create the 10 window (tab)
  tmux new-window -t $SESSION_NAME:10 -n "vEth"
  tmux send-keys -t $SESSION_NAME:10 "cat /home/network/Desktop/dpdk/examples/ipsec-secgw/ngtl/scripts/veth.py" Enter
  #tmux send-keys -t $SESSION_NAME:9 "python3 vEth0_0.py --device LCLOS" Enter

  # Create the :11 window (tab)
  tmux new-window -t $SESSION_NAME:11 -n "node"
  tmux send-keys -t $SESSION_NAME:11 "cd /home/network/" Enter
  tmux send-keys -t $SESSION_NAME:11 "pm2 status" Enter

  # Create the :12 window (tab)
  tmux new-window -t $SESSION_NAME:12 -n "htop"
  tmux send-keys -t $SESSION_NAME:12 "htop" Enter

  # Create the :13 window (tab)
  tmux new-window -t $SESSION_NAME:13 -n "bash"
  tmux send-keys -t $SESSION_NAME:13 "cd" Enter

  # Select the 0 window
  tmux select-window -t $SESSION_NAME:0

  echo "New tmux session '$SESSION_NAME' created with 11 tabs running different scripts."
else
  echo "Session '$SESSION_NAME' already exists. Attaching to it..."
fi

# Attach to the session
tmux attach-session -t $SESSION_NAME
