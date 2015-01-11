This is the main move command, the only trick is that this is a bit
table driven since we need to move on all axes simultaneously.


    module.exports = (tinyg) ->
      (command) ->
        step = 0.1
        xTable =
          'halt': ''
          '+': "X#{tinyg.maxX or 2000}"
          '-': "X0"
          '1': "X#{step}"
          '-1': "X-#{step}"
        yTable =
          'halt': ''
          '+': "Y#{tinyg.maxY or 3000}"
          '-': "Y0"
          '1': "Y#{step}"
          '-1': "Y-#{step}"
        zTable =
          'halt': ''
          '+': "Z#{tinyg.maxZ or 300}"
          '-': "Z0"
          '1': "Z#{step}"
          '-1': "Z-#{step}"
        if command.x is command.y is command.z is 'halt'
          tinyg.hold()
          tinyg.flush()
        else
          tinyg.command gc: 'G91'
          tinyg.command gc: "G0#{xTable[command.x]}#{yTable[command.y]}#{zTable[command.z]}"
