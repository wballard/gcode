

TABLE=json-range 100 100 1100 100 100 2000
TABLEDRILL=json-range 106 100 1106 106 100 2006
VACUUM_TABLE_MAJOR=json-range 65 100 1100 100 100 500
VACUUM_TABLE_MINOR=json-range 115 100 1100 150 100 500
VACUUM_TABLE_AIR=json-range 215 100 350 250 100 350
TABLE_LEVEL=json-range 0 1238 0 0 18 2060
T_TRACK_LOW=json-range 50 100 250 2060 2060 2060
T_TRACK_HIGH=json-range 950 100 1150 2060 2060 2060

.PHONY: all

all:
	$(MAKE) --always-make TableLevel.gcode TTrack.gcode TTrackPilot.gcode

TableLevel.gcode:
	$(TABLE_LEVEL) | mustache - TableLevel.mustache > $@

TTrack.gcode:
	$(T_TRACK_LOW) | mustache - TTrack.mustache > $@
	$(T_TRACK_HIGH) | mustache - TTrack.mustache >> $@
	echo "M5" >> $@
	echo "G0 X0 Y0" >> $@
	echo "M30" >> $@

TTrackPilot.gcode:
	$(T_TRACK_LOW) | mustache - TTrackPilot.mustache > $@
	$(T_TRACK_HIGH) | mustache - TTrackPilot.mustache >> $@
	echo "M5" >> $@
	echo "G0 X0 Y0" >> $@
	echo "M30" >> $@
