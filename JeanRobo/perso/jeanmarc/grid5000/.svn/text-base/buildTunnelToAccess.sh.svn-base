#!/usr/bin/expect --
set timeout 10

set login [lindex $argv 0]
set gateaway [lindex $argv 1]
set port [lindex $argv 2]
set pass [lindex $argv 3]

spawn ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -S ~/.ssh/blah.ctl -N -f -L 3333:localhost:$port $login@$gateaway
#expect -re {@[^\n]*:}
expect -re {@[^\n]*password:}
send -- "$pass\r"
send -- "\r"
#expect -re {@[^\n]*:}
#expect -re {[0-9]+}
#expect -re {tunnel not built|tunnel successfully built}
#after 10000
expect eof
#return
