#!/usr/bin/expect --
set timeout 600  

set file [lindex $argv 0]
set remoteDir [lindex $argv 1]
set login [lindex $argv 2]
set pass [lindex $argv 3]

spawn scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -P 3333 $file $login@localhost:$remoteDir
expect -re {@[^\n]*:}
send -- "$pass\r"
expect -re {@[^\n]*:}
return
