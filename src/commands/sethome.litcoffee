Home the machine at the current location.

    module.exports = (tinyg) ->
      ->
        tinyg.command gc: 'G28.3X0Y0Z0'
