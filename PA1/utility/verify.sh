#!/bin/bash

#############################################################################
# Author: Chi-Sheng Liu
# Synopsis:
#     verify.sh <NTU_sort> <input_dir> <output_dir> <checker> <mode>
# Description:
#     Execute codes and check for correctness.

# Example Usage:
# At PA1/, type the following command
# ./utility/verify.sh ./bin/NTU_sort ./inputs ./outputs ./utility/PA1_Result_Checker IS

#############################################################################

executable=$1
inputDir=$2
outputDir=$3
checker=$4
mode=$5

# Check whether the mode is valid
echo $mode
if [ "$mode" != "IS" -a "$mode" != "MS" -a "$mode" != "QS" -a "$mode" != "HS" ]; then
    echo "mode ${mode} is not valid!"
    exit
fi

# execute and check each test case
for inputFileFullName in "${inputDir}"/*
do
    echo "================"
    inputFileName="$(basename ${inputFileFullName})"
    echo ${inputFileName}
    echo ""
    inputFileName="${inputFileName%.*}" # trim the file extension
    outputFileFullName="${outputDir}/${inputFileName}.${mode}"

    # execute
    ${executable} -${mode} ${inputFileFullName} ${outputFileFullName}
    # check correctness
    ${checker} ${inputFileFullName} ${outputFileFullName}
done
