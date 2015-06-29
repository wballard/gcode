

TABLE=json-range 100 100 1100 100 100 2000
VACUUM_TABLE_MAJOR=json-range 65 100 1100 100 100 500
VACUUM_TABLE_MINOR=json-range 115 100 1100 150 100 500
VACUUM_TABLE_AIR=json-range 215 100 350 250 100 350

all: NutHoleTableTop.gcode WasherHoleTableTop.gcode BoltHoleTableTop.gcode VacuumTableMajor.gcode VacuumTableMinor.gcode VacuumTableAir.gcode
	cat $? | sed s/M30// >	 scratch.gcode

VacuumTable.gcode: VacuumTableMajor.gcode VacuumTableMinor.gcode VacuumTableAir.gcode
	cat $? | sed s/M30// > $@
	echo M30 >> $@

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
