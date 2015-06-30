#!/usr/bin/env coffee -l

Generate a grid of grids to drill a grill.

    iterate = (xStart, xStep, xEnd, yStart, yStep, yEnd, cb) ->
      y = yStart
      while y < yEnd
        x = xStart
        while x < xEnd
          cb x, y
          x += xStep
        y += yStep

    console.log """
    (Bit diameter: 3mm)
    G90 G21
    G0 Z4
    G53 G0 X0 Y0
    G10 P1 L20 X0 Y0
    G54
    M3 S15000
    G4 P10
    """
    iterate 100, 100, 1100, 100, 100, 600, (x, y) ->
      console.log "G53 G0 X#{x} Y#{y}"
      console.log "G10 P1 L20 X0 Y0"
      iterate 10, 5, 90, 10, 5, 90, (x, y) ->
        console.log "G0 X#{x} Y#{y}"
        console.log "G1 Z-14 F150"
        console.log "G0 Z4"

    console.log """
    M05
    G53 G0 X0 Y0 (home)
    M3
    """
