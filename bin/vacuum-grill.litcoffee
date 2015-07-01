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
    G90 G21
    G0 Z4
    G53 G0 X0 Y0
    G10 P1 L20 X0 Y0
    G54
    M3 S10000
    G4 P10
    ?
    """
    iterate 100, 100, 1100, 100, 100, 600, (xMajor, yMajor) ->
      iterate 10, 5, 100, 10, 5, 100, (x, y) ->
        console.log "G0 X#{x + xMajor} Y#{y + yMajor}"
        console.log "G1 Z-14 F300"
        console.log "G0 Z4"

    console.log """
    M05
    G53 G0 X0 Y0 (home)
    """
