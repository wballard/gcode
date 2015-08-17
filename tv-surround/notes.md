Left TV, with soundbar and XBox
1390mm wide, 810mm high
next, inset 210mm each side, 130mm high for
  soundbar 970mm wide, 130mm high
--leaves 140mm above/below to center on a 4x8 sheet

Full plywood sheet will *just* cover over the xbox, maybe mount it to
the right instead of down to get a nicer v-align.

Right TV 340mm in from wall, so 1660mmx1220mm for the panel.

Mask out the TV with 135,270,1525,1080 mm so in 20mm cells with a 20mm border
6,12,76,53

Mask out the sound bar with 5,16,12,66

Panel is turned on its side compared to the TV
./bin/mazecarver 1200 1680 12.7 60 84 13,7,53,76 6,17,12,66  > ../gcode/tv-surround/left.gcode
./bin/mazecarver 1200 1680 12.7 60 84 13,7,53,76 > ../gcode/tv-surround/right.gcode
./bin/mazecarver 1200 600 12.7 60 30 > ../gcode/tv-surround/a.gcode
./bin/mazecarver 1200 600 12.7 60 30 > ../gcode/tv-surround/b.gcode
./bin/mazecarver 1200 600 12.7 60 30 > ../gcode/tv-surround/c.gcode
./bin/mazecarver 200 200 12.7 10 10 > ../gcode/tv-surround/tile.gcode
