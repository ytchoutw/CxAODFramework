#!/bin/bash

BIN_DIR=/phys/groups/tev/scratch3/users/ytchou/monoWZ/CxAODFramework_tev05/stack_hists
SAMPLE_DIR=/phys/groups/tev/scratch3/users/ytchou/monoWZ/CxAODFramework_tev05/stack_hists/TF

cd TF

$BIN_DIR/stack_hists all_TF Sample \
$SAMPLE_DIR/TF_Curve:1_TF.root jetveto 0 \
$SAMPLE_DIR/TF_Curve:2_TF.root miniPhi 0 \
$SAMPLE_DIR/TF_Curve:3_TF.root fJmass_WZ 0 \
$SAMPLE_DIR/TF_Curve:4_TF.root fJmass_H 0 \
$SAMPLE_DIR/TF_Curve:5_TF.root 1subB 0 \
$SAMPLE_DIR/TF_Curve:6_TF.root 2subB 0 \

cd ..
