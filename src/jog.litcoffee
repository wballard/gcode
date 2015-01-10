Jog control via PS3 SixAxis.

    dualShock = require 'dualshock-controller'
    events = require 'events'

Two speeds seems like enough, so this is a threshold.

    THRESHOLD = 255 / 4
    MID = 255 / 2

    module.exports = class Jog extends events.EventEmitter

      halt: ->
        @move =
          x: 'halt'
          y: 'halt'
          z: 'halt'


Signal a move, with some diff logic.

      lastMove: ''
      signalMove: (force) ->
        currentMove = JSON.stringify @move
        if currentMove isnt @lastMove or force
          @lastMove = currentMove
          @emit 'move', @move

      constructor: ->
        @halt()
        @controller = dualShock
          config : "dualShock3"
          accelerometerSmoothing : true
          analogStickSmoothing : true

Left stick seeks the gantry.

        @controller.on 'left:move', (data) =>
          @move.x = 'halt'
          @move.y = 'halt'
          if data.x > (MID + THRESHOLD)
            @move.x = '+'
          if data.x < (MID - THRESHOLD)
            @move.x = '-'
          if data.y < (MID - THRESHOLD)
            @move.y = '+'
          if data.y > (MID + THRESHOLD)
            @move.y = '-'
          @signalMove()

Right stick seeks the spindle.

        @controller.on 'right:move', (data) =>
          @move.z = 'halt'
          if data.x > (MID + THRESHOLD)
            @move.z = '+'
          if data.x < (MID - THRESHOLD)
            @move.z = '-'
          if data.y < (MID - THRESHOLD)
            @move.z = '+'
          if data.y > (MID + THRESHOLD)
            @move.z = '-'
          @signalMove()

Dpad is fine motion on the gantry.

        @controller.on 'dpadUp:press', (data) =>
          @halt()
          @move.y = '1'
          @signalMove true
        @controller.on 'dpadRight:press', (data) =>
          @halt()
          @move.x = '1'
          @signalMove true
        @controller.on 'dpadDown:press', (data) =>
          @halt()
          @move.y = '-1'
          @signalMove true
        @controller.on 'dpadLeft:press', (data) =>
          @halt()
          @move.x = '-1'
          @signalMove true
