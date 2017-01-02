from xbee import ZigBee
import SensorData_pb2
import struct
import serial
import sys
import glob

class XBeeHandler():
    def __init__(self):
        self.escaped = True
        self.supress = False
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
        print(data)

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
        if not self.supress:
            raise SystemError("No Serial Port Found")

    def start(self):
        port = self.serial_ports()
        self.serial_port = serial.Serial("/dev/cu.usbserial-DA01M9KA", 9600)
        self.xbee = ZigBee(
            self.serial_port,
            callback=self.xbee_callback,
            escaped=True
            )
        self.alive = True

    def stop(self):
        self.xbee.halt()
        self.serial_port.close()
        self.alive = False

    def _id_handler(self, data):
        print(data)

    def _rx_handler(self, data):
        print(data)

    def _sensor_data(self, data):
        pass

if __name__ == '__main__':
    bee = XBeeHandler()
    bee.start()
    conf = SensorData_pb2.ChannelConfig()
    print(conf.SerializeToString())
    conf.channel_serial_number.append(2)
    conf.channel_type.append(conf.BIKE_CADENCE)
    print(conf.SerializeToString())
    bee.xbee.send("tx", data=conf.SerializeToString(), dest_addr_long=struct.pack(">Q", 0x0013a20040e8331b), dest_addr=struct.pack(">H", 0xFFFE))


