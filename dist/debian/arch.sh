#!/bin/sh

# Use: controlarch.sh template_file output_file ARCH-NAME

cat "$1" | sed "s/\${ARCH}/$3/g" > $2