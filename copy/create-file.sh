#!/bin/bash

FILENAME="$1"
COUNT=1
BLOCKSIZE="1k"

if [ $# -ne 2 ]
then
    echo "Usage: $0 <filename> <size>"
    echo "Example: $0 a.rand 1GB"
    exit 1
fi

UNIT=$(echo -n "$2" | tail -c 2)
SIZE=$(echo -n "$2" | head -c -2)

case $UNIT in

    "KB")
        COUNT="$SIZE"
        ;;

    "MB")
        COUNT=$(echo "$SIZE * 1024" | bc)
        ;;

    "GB")
        COUNT=$(echo "$SIZE * 1024 * 1024" | bc)
        ;;

    *)
        echo "Unknown option $2"
        exit 1
        ;;
esac

dd if=/dev/urandom of="$FILENAME" bs="$BLOCKSIZE" count="$COUNT" > /dev/null 2>&1
