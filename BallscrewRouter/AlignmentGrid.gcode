G90 G21
G0 Z10
G53 G0 X0 Y0
G10 P1 L20 X0 Y0
G54
M3 S15000
G4 P10

G0 X10 Y10
G1 Z-0.2
G1 F400 X1100
G1 Y2000
G1 X10
G1 Y10
G0 Z10

G0 X50 Y50
G1 Z-0.2
G1 F400 X1100
G1 X50
G1 Y2000
G1 Y50
G0 Z10

G0 X100 Y100
G1 Z-0.2
G1 F400 X1100
G1 X100
G1 Y2000
G1 Y100
G0 Z10

M05

G53 G0 X0 Y0 (home)
M30
