#! /bin/sh
# -*- mode: bash; tab-width: 4; -*-
# vi:ts=4 noexpandtab autoindent

#colors
clr_red=$(tput setab 1)
clr_green=$(tput setab 2)
clr_plain=$(tput op)

trap 'echo "${clr_plain}"' 0


g_pass_counter=0
g_fail_counter=0

make_project() {
	make
	makeExit=$?
	if [ $makeExit -ne 0 ]
	then
		echo make exited with exit code $makeExit
		exit $makeExit
	fi

}

# Set stat command based off of operating system
set_stat_size_string() {
	uname=$(uname)
	if [ "$uname" = "Linux" ]
	then
    	eval "$1='stat --format=%s'"
	elif [ "$uname" = "Darwin" ]
	then
    	eval "$1='stat -f %z'"
	else
	    echo "Operating system \"$uname\" is not supported"
    	exit 1
	fi
}

echo_and_run() {
    printf "\t$*: "
    eval $*
}

pass_fail() {
    if [ $1 ]
    then
        echo "${clr_green}PASS${clr_plain}"
		g_pass_counter=$(expr $g_pass_counter + 1)
    else
		echo "${clr_red}FAIL${clr_plain}"
		g_fail_counter=$(expr $g_fail_counter + 1)
    fi
}

print_pass_fail_stats() {
	echo "Passed Tests: ${clr_green}$g_pass_counter${clr_plain}/$(expr $g_pass_counter + $g_fail_counter)"
	echo "Failed Tests: \c"
	if [ $g_fail_counter -gt 0 ]
	then
		echo "${clr_red}$g_fail_counter${clr_plain}\c"
	else
		echo "$g_fail_counter\c"
	fi
	echo "/$(expr $g_pass_counter + $g_fail_counter)"
}
