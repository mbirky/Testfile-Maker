#! /bin/sh
# -*- mode: bash; tab-width: 4; -*-
# vi:ts=4 noexpandtab autoindent

. ./helper_functions.sh


cd ..
make_project

set_stat_size_string stat_size

#reusable variables
passed=1
counter=0

fileName="test"
echo_and_run "./testfile_maker"
pass_fail "-e $fileName"
rm -f fileName



echo Name Tests

fileName=testfilename
echo_and_run "./testfile_maker $fileName"
pass_fail "-e $fileName0"
rm -f "$fileName"0	# The '0' must be outside of the quotes otherwise it looks
					# for the variable named "filename0"



echo Count Tests

fileCount=10
echo_and_run "./testfile_maker -c $fileCount"

while [ "$counter" -lt "$fileCount" ]
do
    fileName="test$counter"
    if [ ! -e $fileName ]
    then
        passed=0
    fi
    counter=$(expr $counter + 1)
done

pass_fail $passed
rm -f test[0-9]



echo Extension Tests

fileName="test.txt"
echo_and_run "./testfile_maker -e txt"
pass_fail "-e $fileName"
rm -f $fileName

echo_and_run "./testfile_maker -e .txt"
pass_fail "-e $fileName"
rm -f $fileName



echo Help

printf "./testfile_maker -h: "
output="$(eval ./testfile_maker -h | cut -c16- | sed -e 's/\[/\\\[/g' -e 's/]/\\]/g')"
readme="$(sed -n -e '/\[file name]/p' README.md | cut -c7- | sed -e 's/\[/\\\[/g' -e 's/]/\\]/g')"

stringEqual=
if [ "$output" = "$readme" ]
then
  stringEqual=1
fi

pass_fail "$stringEqual"



echo Separate Lines

fileName="test"
fileSize=5
echo_and_run "./testfile_maker -s $fileSize -l"
passed=0
if [ $(wc -l < $fileName) -eq $(expr $fileSize / 2) ] && [ $($stat_size $fileName) -eq $fileSize ]
then
  passed=1;
fi
pass_fail "$passed -ne 0"
rm -f $fileName

echo_and_run "./testfile_maker -l"
pass_fail "$(wc -l < $fileName) -eq 5"
rm -f $fileName

fileSize=100
echo_and_run "./testfile_maker -s $fileSize -l"
passed=0
if [ $(wc -l < $fileName) -eq $(expr $fileSize / 2) ] && [ $($stat_size $fileName) -eq $fileSize ]
then
  passed=1;
fi
pass_fail "$passed -ne 0"
rm -f $fileName



echo Size Tests

fileName="test"
fileSize=5
echo_and_run "./testfile_maker -s $fileSize"
pass_fail "$($stat_size $fileName) -eq $fileSize"
rm -f $fileName

echo_and_run "./testfile_maker"
pass_fail "$($stat_size $fileName) -eq 10"
rm -f $fileName

fileSize=100
echo_and_run "./testfile_maker -s $fileSize"
pass_fail "$($stat_size $fileName) -eq $fileSize"
rm -f $fileName

print_pass_fail_stats

exit_status
exit $?
