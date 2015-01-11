    doc = """
    Usage:
    tinyg [options] <tinyg-serial-port>

    Options:
    -h --help                show this help message and exit
    --version                show version and exit

    This server will connect and manage a tinyg robotics board from
    an Intel Edison connected via serial.

    The features:

    * Jog Control via bluetooth PS3 Controller

    """

    _ = require 'lodash-node'
    events = require 'events'
    serialport = require 'serialport'
    require 'colors'
    {docopt} = require 'docopt'
    {exec} = require 'child_process'
    options = docopt doc
    Jog = require './jog.litcoffee'


    connect = ->
      console.log 'connected to tinyg'.green
      tinyg.state =
        qr: 0
        sr:
          posx: 0
          posy: 0
          posz: 0
          vel: 0

Listen to tinyg, this will get the state.

      tinyg.on 'data', (data) ->
        try
          feedback = JSON.parse data
          _.extend tinyg.state, feedback
          console.log tinyg.state
        catch e
          console.error "#{e}".red

Set up for JSON verbose mode.

      tinyg.command ee: 0
      tinyg.command ec: 0
      tinyg.command jv: 5
      tinyg.command gc: "M5"

Joystick jog control.

      jogControl = new Jog()
      jogControl.on 'move', require('./commands/move.litcoffee')(tinyg)
      jogControl.on 'sethome', require('./commands/sethome.litcoffee')(tinyg)
      jogControl.on 'home', require('./commands/home.litcoffee')(tinyg)
      jogControl.on 'spindle', require('./commands/spindle.litcoffee')(tinyg)

Application start here, mostly to allow bypassing the serial port for some light
testing.

    if options['<tinyg-serial-port>'] isnt '-'
      tinyg = new serialport.SerialPort options['<tinyg-serial-port>'],
        baudRate: 115200
        parser: serialport.parsers.readline("\n")
      tinyg.on 'open', connect
    else
      tinyg = new events.EventEmitter()
      tinyg.write = (data) ->
        process.stdout.write data.blue
      setTimeout connect

We're going to use JSON object control, so tack on some handy methods
to dispatch commands.

    tinyg.command = (cmd) ->
      tinyg.write "#{JSON.stringify(cmd)}\n"

    tinyg.hold = ->
      tinyg.write '!'

    tinyg.flush = ->
      tinyg.write '%'

    tinyg.reset = ->
      tinyg.write '\u0018'
