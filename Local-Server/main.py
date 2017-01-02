#!/usr/bin/env python3

from Daemon import daemon
from db import db
from XBeeConnect import XBeeHandler
from Web import web
import logging
import sys
import signal
import datetime
import urllib.request
from flask import Flask


class manager(daemon):
    """docstring for manager"""

    def setup(self):
        config = self.parse_config()

        logging.basicConfig(
            filename='server.log',
            level=getattr(logging, config['log_level'].upper())
            )
        self.log = logging.getLogger()

        self.log.info(
            "Starting Mass-Tach Server at {}".format(datetime.datetime.utcnow()))

        self.log.info("MANAGER: Starting DB")
        self.db = db(
            config["db_host"],
            config["db_user"],
            config["db_name"],
            config["db_pass"],
            supress=config["supress"]
            )
        # db.write_ping(0x01234567, 15, datetime.datetime.utcnow())

        self.log.info("MANAGER: Starting XBee")
        self.xbee = XBeeHandler(self.db, config["xbee_api_level"], supress=config["supress"])
        self.xbee.start()
        signal.signal(signal.SIGTERM, self.shutdown)
        self.app = Flask(__name__)
        self.web = web(self)
        self.web.register(self.app)
        self.log.info("MANAGER: Startup Complete")

    def run(self):
        self.setup()
        self.app.run()

    def shutdown(self, signum, frame):
        self.log.info("MANAGER: received SIGTERM, shutting down...")
        self.db.close()
        self.xbee.stop()
        # unhook handler so flask doesnt call it when we shut it down
        signal.signal(signal.SIGTERM, signal.SIG_DFL)
        urllib.request.urlopen("http://localhost:5000/shutdown").read()

    def parse_config(self):
        return dict(
            line.strip().split('=')
            for line in open('config.txt')
            if line.strip() != "")

if __name__ == '__main__':
        daemon = manager('/tmp/mass-tach.pid')
        daemon.debug = True
        if len(sys.argv) == 2:
            if 'start' == sys.argv[1]:
                daemon.start()
            elif 'stop' == sys.argv[1]:
                daemon.stop()
            elif 'restart' == sys.argv[1]:
                daemon.restart()
            else:
                print("Unknown command")
                sys.exit(2)
            sys.exit(0)
        else:
            print("usage: {} start|stop|restart".format(sys.argv[0]))
            sys.exit(2)
