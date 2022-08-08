#!/bin/bash

set -e

neuron_bin="/usr/local/bin/neuron"
neuron_include="/usr/local/include/neuron"
neuron_lib="/usr/local/lib/neuron"

cp neuron.conf /etc/ld.so.conf.d/

mkdir -p /usr/local/lib/cmake/neuron/
cp neuron-config.cmake /usr/local/lib/cmake/neuron/

mkdir -p ${neuron_include}
cp -r include/neuron/* ${neuron_include}/

mkdir -p ${neuron_lib}
cp lib/* ${neuron_lib}/

mkdir -p ${neuron_bin}
mkdir -p ${neuron_bin}/config
mkdir -p ${neuron_bin}/persistence
mkdir -p ${neuron_bin}/plugins

cp ./neuron ${neuron_bin}/
cp config/sdk-zlog.conf ${neuron_bin}/config/zlog.conf
cp config/dev.conf ${neuron_bin}/config/
cp config/neuron.key ${neuron_bin}/config/
cp config/neuron.pem ${neuron_bin}/config/

cp config/default_plugins.json ${neuron_bin}/persistence/plugins.json
cp persistence/* ${neuron_bin}/persistence/
cp -r plugins/* ${neuron_bin}/plugins/

cp -r dist ${neuron_bin}/

ldconfig