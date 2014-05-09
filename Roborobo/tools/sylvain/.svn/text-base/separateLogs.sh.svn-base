#! /bin/bash
egrep "^STATUSGLOBAL" log.txt | cut -d " " -f 2- > nest_stat.txt
egrep "^STATUSFORAGE" log.txt | cut -d " " -f 2- > nest_forage.txt
egrep "^STATUSALLFORAGE" log.txt | cut -d " " -f 2- > nest_foragingtime.txt
egrep "^STATUSAGENT" log.txt | cut -d " " -f 3- > ant_stat.txt
egrep "^LIFAGENT" log.txt | cut -d " " -f 3- > pot_lif.txt
egrep "^QIFAGENT" log.txt | cut -d " " -f 3- > pot_qif.txt
egrep "^STATUSALLAGENT" log.txt | cut -d " " -f 2- > ants_stat.txt
egrep "^STATUSAVOID" log.txt | cut -d " " -f 3- | tail -n 1 > ant_collision.txt
