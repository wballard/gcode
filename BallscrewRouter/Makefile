

TABLE=json-range 100 100 1100 100 100 2000
TABLEDRILL=json-range 106 100 1106 106 100 2006
VACUUM_TABLE_MAJOR=json-range 65 100 1100 100 100 500
VACUUM_TABLE_MINOR=json-range 115 100 1100 150 100 500
VACUUM_TABLE_AIR=json-range 215 100 350 250 100 350
TABLE_LEVEL=json-range 0 1238 0 0 18 2060
T_TRACK=json-range 50 100 1238 2060 2060 2060

TableLevel.gcode:
	$(TABLE_LEVEL) | mustache - TableLevel.mustache > $@

TTrack.gcode:
	$(T_TRACK) | mustache - TTrack.mustache > $@
