from xbee import ZigBee
import serial
import sys
import glob
import logging
import threading

API_ESCAPED = 2

STATUS_LOOKUP = [
    "HARDWARE_RESET",
    "WATCHDOG_TIMER_RESET",
    "ASSOCIATED",
    "DISASSOCIATED",
    "SYNCHRONIZATION_LOST",
    "COORDINATOR_REALIGNMENT",
    "COORDINATOR_STARTED"
]


class XBeeHandler():
    def __init__(self, db, xbee_api_level, supress=False):
        self.db = db
        self.escaped = (int(xbee_api_level) == API_ESCAPED)
        self.log = logging.getLogger()
        self.supress = supress
        self.handlers = {
            'status': self._id_handler,
            'rx': self._rx_handler
        }
        self.rx_handlers = {
            0: self._sensor_data
        }

    def xbee_callback(self, data):
        """
        handles all function messages from xbees
        """
        self.log.debug("XBEE: Message:{}".format(data))
        try:
            self.handlers[data['id']](data)
        except KeyError:
            self.log.warning("XBEE: No handler for message type: {}".format(
                data['id']))
        except Exception as e:
            self.xbee_error_handler(e)

    def xbee_error_handler(self, e):
        self.log.error("XBEE: {}".format(e))

    def serial_ports(self):
        """ Lists serial port names

            :raises EnvironmentError:
                On unsupported or unknown platforms
            :returns:
                A list of the serial ports available on the system
        """
        if sys.platform.startswith('win'):
            ports = ['COM%s' % (i + 1) for i in range(256)]
        elif sys.platform.startswith('linux') or \
                sys.platform.startswith('cygwin'):
            # this excludes your current terminal "/dev/tty"
            ports = glob.glob('/dev/tty[A-Za-z]*')
        elif sys.platform.startswith('darwin'):
            ports = glob.glob('/dev/tty.*')
        else:
            raise EnvironmentError('Unsupported platform')

        result = []
        for port in ports:
            try:
                s = serial.Serial(port)
                s.close()
                result.append(port)
            except (OSError, serial.SerialException):
                pass
        for r in result:
            if -1 == r.find("Bluetooth"):
                return r
        self.log.critical("XBEE: No serial port found")
        if not self.supress:
            raise SystemError("No Serial Port Found")

    def start(self):
        port = self.serial_ports()
        self.log.info("XBEE: connecting to serial port: {}".format(port))
        self.serial_port = serial.Serial(port, 9600)
        self.log.info("XBEE: configuring escapes: {}".format(self.escaped))
        self.xbee = ZigBee(
            self.serial_port,
            callback=self.xbee_callback,
            escaped=self.escaped
            )
        self.log.info("XBEE: Xbee Started")
        threading.Timer(10.0, self.running_checks).start()
        self.alive = True

    def stop(self):
        self.log.info("XBEE: Stopping XBee")
        self.xbee.halt()
        self.log.info("XBEE: Closing Serial Port")
        self.serial_port.close()
        self.log.info("XBEE: Shutdown Complete")
        self.alive = False

    def running_checks(self):
        # handle checks if xbees have not checked in yet here
        self.log.info("XBEE: Running network health check")
        if self.alive:
            threading.Timer(5.0, self.running_checks).start()

    def _id_handler(self, data):
        self.log.info("XBEE: Status: {}".format(
            STATUS_LOOKUP[int.from_bytes(data['status'], 'big')]))

    def _rx_handler(self, data):
        try:
            self.rx_handlers[data.datapage](data)
        except KeyError:
            self.log.warning(
                "XBEE: No handler for datapage: {}".format(datapage))

    def _sensor_data(self, data):
        pass


class XbeeMessage():
    """docstring for XbeeMessage"""
    _datapage_size_lookup = {
        0: 17
    }

    def __init__(self, msg):
        self.msg = msg
        self.datapage = int.from_bytes(data["rf_data"], "little") & 0xFF
