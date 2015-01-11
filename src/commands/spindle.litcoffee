Basic spindle toggle.

    module.exports = (tinyg) ->
      (command) ->
        if command
          tinyg.command gc: "M3S#{(command / 100) * (tinyg.maxSpeed or 100)}"
        else
          tinyg.command gc: 'M5'
