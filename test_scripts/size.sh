#! /bin/sh
# -*- mode: bash; tab-width: 4; -*-
# vi:ts=4 noexpandtab autoindent

. ./helper_functions.sh

cd ..
make_project

set_stat_size_string stat_size

fileName="test"
fileSize=1
echo_and_run "./testfile_maker -s $(($fileSize))k"
pass_fail "$($stat_size $fileName) -eq $(($fileSize * 1024))"
rm -f $fileName

echo_and_run "./testfile_maker -s $(($fileSize))m"
pass_fail "$($stat_size $fileName) -eq $(($fileSize * 1024 * 1024))"
rm -f $fileName

echo_and_run "./testfile_maker -s $(($fileSize))g"
pass_fail "$($stat_size $fileName) -eq $(($fileSize * 1024 * 1024 * 1024))"
rm -f $fileName

print_pass_fail_stats

return exit_status
