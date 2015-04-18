#!/bin/bash

BIN_DIR=/phys/groups/tev/scratch3/users/ytchou/monoWZ/mono-higgs-master/stack_hists
SAMPLE_DIR=/phys/groups/tev/scratch3/users/ytchou/monoWZ/CxAODFramework/Workdir_13TeV 

mkdir stacked_plots
rm stacked_plots/*
cd stacked_plots

$BIN_DIR/stack_hists all_samples Sample \
$SAMPLE_DIR/hist-monoWjjIsrConD5m50.root monoWjjIsrConD5m50x40 0 \
$SAMPLE_DIR/hist-monoWjjIsrConD5m1300.root monoWjjIsrConD5m1300x40 0 \
$SAMPLE_DIR/hist-ttbar.root ttbar 1 \
$SAMPLE_DIR/hist-singletop.root singletop 1 \
$SAMPLE_DIR/hist-Zll.root Zll 1 \
$SAMPLE_DIR/hist-Wlv.root Wvl 1 \
$SAMPLE_DIR/hist-Zvv.root Zvv 1

cd ..
