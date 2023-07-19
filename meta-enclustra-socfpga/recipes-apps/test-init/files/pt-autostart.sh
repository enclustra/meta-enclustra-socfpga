#!/bin/sh

# mute kernel messages
sysctl -w kernel.printk="0 4 1 0"

# start production test software
cd /home/root
./main
