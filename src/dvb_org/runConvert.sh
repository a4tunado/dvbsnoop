#!/bin/sh
names="ca_system_id network_id data_broadcast_id original_network_id private_data_spec_id bouquet_id"

for name in $names ; do
	wget -q -O - "http://www.dvbservices.com/identifiers/$name?command=set_limit&data_per_page=1000&tab=table" \
	| xsltproc --html convert.xsl - 2> /dev/null \
	> $name.inc
done
