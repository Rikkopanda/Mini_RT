#!/bin/bash

show_cursor="\033[?25h"
hide_cursor="\033[?25l"
green="\033[0;32m"
red="\033[0;31m"
cyan="\033[0;36m"
purple="\033[35m"
reset="\033[0m"

program=bin/parser_tests
log_path=logs
maps_path=../maps
mem_args="--leak-check=full --show-leak-kinds=all --track-origins=yes"

assert_output() {
	local -r test_args=$1
	local -r expected=$2
	echo -e "$program $test_args"
	if [ "$($program $test_args 2>&1)" != "$expected" ]; then
		echo -e $red"[KO]"$reset
		echo -e $red"output: $($program $test_args)"$reset
		echo -e $green"expected: $expected"$reset
		exit 0
	else
		echo -ne $green"[OK] "$reset
	fi
	assert_mem $test_args
}

assert_mem() {
	local -r test_args=$1
	local tmpfile=$(mktemp)
	valgrind --log-file=$tmpfile $mem_args $program $test_args > /dev/null 2>&1
	if ! grep -q "no leaks are possible" $tmpfile; then
		echo -e $red"[MEM_KO]"$reset
		cat $tmpfile
		rm $tmpfile
		exit 0
	else
		echo -e $green"[MEM_OK]"$reset
	fi
	rm $tmpfile
}

echo -ne $hide_cursor

echo -e $purple"Running tests..."$reset

echo -e $cyan"[invalid input]"$reset

assert_output \
	"" \
	"Usage: $program examplefile.rt"

assert_output \
	"$maps_path/nonexistingfile.rt" \
	"../maps/nonexistingfile.rt: No such file or directory"

assert_output \
	"$maps_path/invalidextension.txt" \
	"Error: ../maps/invalidextension.txt: not an .rt file."

assert_output \
	"$maps_path/invalididentifier.rt" \
	"Error: pla: invalid identifier."

assert_output \
	"$maps_path/missingambient.rt" \
	"Error: missing ambient element(s)."

assert_output \
	"$maps_path/missingcamera.rt" \
	"Error: missing camera object(s)."

assert_output \
	"$maps_path/missinglight.rt" \
	"Error: missing light object(s)."

assert_output \
	"$maps_path/outofrangeratio.rt" \
	"Error: 1.10: ambient lighting ratio out of range [0.0, 1.0]"

assert_output \
	"$maps_path/outofrangevector.rt" \
	"Error: camera orientation vector out of range [-1, 1]"

assert_output \
	"$maps_path/toomanyobjects.rt" \
	"Error: too many ambient element(s)."

echo -e $cyan"\n[valid input]"$reset

assert_output \
	"$maps_path/multipleobjects.rt" \
	""

assert_output \
	"$maps_path/randomorder.rt" \
	""

assert_output \
	"$maps_path/subjectexample.rt" \
	""

echo -ne $show_cursor