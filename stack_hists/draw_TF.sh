#!/bin/bash

BIN_DIR=/phys/groups/tev/scratch3/users/ytchou/monoWZ/CxAODFramework_tev05/stack_hists
SAMPLE_DIR=/phys/groups/tev/scratch3/users/ytchou/monoWZ/CxAODFramework_tev05/Workdir_13TeV 

mkdir TF
rm TF/*
cd TF

$BIN_DIR/stack_hists TF Sample \
$SAMPLE_DIR/hist-Wmuv.root Wmuv 0 \
$SAMPLE_DIR/hist-Zvv.root Zvv 0 \

cd ..
