    doc = """
    Usage:
    tinyg [options]

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
    require 'colors'
    {docopt} = require 'docopt'
    {exec} = require 'child_process'
    options = docopt doc
    Jog = require './jog.litcoffee'

    jogControl = new Jog()
    jogControl.on 'move', (move) ->
      console.log 'move', JSON.stringify(move).blue
