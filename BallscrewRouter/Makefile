
all: NutHoleTableTop.gcode WasherHoleTableTop.gcode BoltHoleTableTop.gcode
	echo $?
	cat $? | sed s/M30// >	 scratch.gcode

TABLE=json-range 0 100 1200 0 100 2300

NutHoleTableTop.gcode:
	$(TABLE) | mustache - NutHole.mustache > $@

WasherHoleTableTop.gcode:
	$(TABLE) | mustache - WasherHole.mustache > $@

BoltHoleTableTop.gcode:
	$(TABLE) | mustache - BoltHole.mustache > $@
