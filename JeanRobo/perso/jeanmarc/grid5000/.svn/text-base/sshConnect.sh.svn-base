#!/usr/bin/expect --
set timeout 120

set arg1 [lindex $argv 0]
set arg2 [lindex $argv 1]
set arg3 [lindex $argv 2]
set arg4 [lindex $argv 3]

spawn ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no $arg1@$arg2 $arg4
expect -re {@[^\n]*:}
send -- "$arg3\r"
expect -re {[0-9]+}
expect -re {tunnel not built|tunnel successfully built}
return
