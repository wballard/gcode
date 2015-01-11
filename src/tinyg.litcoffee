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

    fs = require 'fs'
    path = require 'path'
    events = require 'events'
    serialport = require 'serialport'
    require 'colors'
    {docopt} = require 'docopt'
    {exec} = require 'child_process'
    options = docopt doc
    console.log options
    Jog = require './jog.litcoffee'

    if options['<tinyg-serial-port>'] isnt '-'
      tinyg = new serialport.SerialPort options['<tinyg-serial-port>'],
        baudRate: 115200
        parser: serialport.parsers.readline("\n")
    else
      tinyg = new events.EventEmitter()
      tinyg.write = (data) ->
        process.stdout.write data.blue

    tinyg.on 'data', (data) ->
      console.log data.green

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

    tinyg.command ee: 0
    tinyg.command ec: 0
    tinyg.command jv: 0

    jogControl = new Jog()
    jogControl.on 'move', require('./commands/move.litcoffee')(tinyg)
    jogControl.on 'home', require('./commands/home.litcoffee')(tinyg)
