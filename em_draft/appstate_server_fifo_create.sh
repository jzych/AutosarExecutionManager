#!/bin/bash
dir=/usr/run/execution-manager
if ! [[ -d $dir ]]; then
    mkdir -p $dir
fi

pipe=$dir/appstate-server-fifo
if ! [[ -p $pipe ]]; then
    mkfifo $pipe
fi
