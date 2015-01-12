Send the machine home.

    module.exports = (tinyg) ->
      ->
        tinyg.command gc: 'G90'
        tinyg.command gc: 'G0X0Y0Z0'
        tinyg.command md: ''
