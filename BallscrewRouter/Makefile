
all: NutHoleTableTop.gcode WasherHoleTableTop.gcode BoltHoleTableTop.gcode VacuumTableMajor.gcode VacuumTableMinor.gcode VacuumTableAir.gcode
	echo $?
	cat $? | sed s/M30// >	 scratch.gcode

TABLE=json-range 100 100 1100 100 100 2000
VACUUM_TABLE_MAJOR=json-range 200 100 1000 200 100 600
VACUUM_TABLE_MINOR=json-range 250 100 1000 250 100 600
VACUUM_TABLE_AIR=json-range 350 100 550 350 100 550

NutHoleTableTop.gcode:
	$(TABLE) | mustache - NutHole.mustache > $@

WasherHoleTableTop.gcode:
	$(TABLE) | mustache - WasherHole.mustache > $@

BoltHoleTableTop.gcode:
	$(TABLE) | mustache - BoltHole.mustache > $@

VacuumTableMajor.gcode:
	$(VACUUM_TABLE_MAJOR) | mustache - VacuumCircle.mustache > $@

VacuumTableMinor.gcode:
	$(VACUUM_TABLE_MINOR) | mustache - VacuumCircle.mustache > $@

VacuumTableAir.gcode:
	$(VACUUM_TABLE_AIR) | mustache - VacuumAirPort.mustache > $@
