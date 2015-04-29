#!/usr/bin/env python
import  sys,logging,threading, time,Serial

class SDevBase:
    def __init__(self, port,baudrate):
        tt = time.strftime("%m-%d_%H.%M",time.localtime(time.time()))
        # get current file absolutely path
        modulepath=os.path.dirname(os.path.realpath(__file__))
        self.log_config(modulpath)

        os_version = sys.platform

        self.baudrate= baudrate
        self.bytesize = 8
        self.parity = 'N'
        self.stopbits = 1
        self.timeout = 1
        self.writeTimeout = 10

        if os_version == 'win32':
            self.port = port
        else:
            self.port = os.path.join('/dev', port)
        self.com = Serial(self.port, baudrate=self.baudrate,
                          bytesize=self.bytesize, parity=self.parity,
                          stopbits=self.stopbits, timeout=self.timeout,
                          writeTimeout=self.writeTimeout)
        # self.open()
        self.dev_name = self.get_dev_name()
        try:
            self.name = self.dev_name.split(',')[1]
        except IndexError as e:
            raise "Equipment not found: %s" % (str(self.port)))
        self.log.info(self.dev_name)
    
    def log_config(self,modulpath):
        logpath=os.path.join(modulepath,"_log")
        if not os.path.exists(logpath):
            os.makedirs(logpath)
        log_file = os.path.join(logpath,"%s_%s.log" % (self.__class__.__name__,tt) )
        logging.basicConfig(level=logging.DEBUG,
                format='[%(asctime)s %(filename)s line:%(lineno)d func:%(funcName)s]:  %(message)s',
                datefmt='%d %H:%M:%S',
                filename=log_file,
                filemode='w')
        self.log = logging.getLogger(self.__class__.__name__)

        console = logging.StreamHandler()
        console.setLevel(logging.DEBUG)
        formatter = logging.Formatter('[%(filename)s line:%(lineno)d]:  %(message)s')
        console.setFormatter(formatter)
        # add output log to screen
        self.log.addHandler(console)

    def __str__(self):
        return self.dev_name

    def open(self):
        self.com = serial.Serial()
        self.com.port     = self.port
        self.com.baudrate = 9600
        self.com.timeout  = 1
        try:
            self.com.open()
        except:
            raise Exception('ERROR: Unable to open the COM port %s' % self.port)
            self.com.close()
            sys.exit(-1)

    def get_dev_name(self):
        self.com.write("*IDN?\n")
        return self.com.readline().strip()

    def connect(self):
        'set system to remote mode'
        self.com.write("SYSTEM:REMOTE\n")
        line = self.com.readline()

    def disconnect(self):
        self.com.write("SYSTEM:LOCAL\n")
        line = self.com.readline()

    def reset(self):
        self.com.write("*RST\n")
        line = self.com.readline()

    def __del__(self):
        self.disconnect()

class Power(SDevBase):
    def __init__(self, com,baudrate):
        SDevBase.__init__(self, com,baudrate)
        if self.dev_name != "E3646A":
            raise "Only E3631A is supported, got: %s" % (self.name)

    def apply(self, voltage, current):
        voltage = float(voltage)
        current = float(current)
        self.com.write("apply %.5f, %.5f\n" % (voltage, current))
        line = self.com.readline()
        self.com.write("apply?\n")
        line = self.com.readline()
        self.check_command(line.strip(), '"%.5f,%.5f"' % (voltage, current))

    def set_voltage(self, voltage):
        voltage = float(voltage)
        self.com.write("VOLT %.5f\n" % voltage)
        line = self.com.readline()
        self.com.write("VOLT?\n")
        line = self.com.readline()
        self.check_command(line.strip(), '%+.8E' % voltage)

    def set_current(self, current):
        current = float(current)
        self.com.write("CURR %.5f\n" % current)
        line = self.com.readline()
        self.com.write("CURR?\n")
        line = self.com.readline()
        self.check_command(line.strip(), '%+.8E' % current)

    def measure_current(self):
        line = self.com.readline()
        self.com.write("MEAS:CURR?\n")
        line = self.com.readline()
        return float(line.strip())

    def measure_voltage(self):
        line = self.com.readline()
        self.com.write("MEAS:VOLT?\n")
        line = self.com.readline()
        return float(line.strip())

    def check_command(self, line, expect):
        if line.strip != expect:
            raise PowerError(line + ', ' + expect)

    def select_power_port(self, index):
        if not index in [1,2]:
            raise ValueError("Only 1 or 2 can be provided")
        self.com.write("INST:SEL OUTP%d\n" % index)
        line = self.com.readline()
        self.com.write("INST:SEL?\n")
        line = self.com.readline()
        self.check_command(line, 'OUTP%d' % index)

    def on(self):
        self.com.write("OUTP ON\n")
        line = self.com.readline()
        self.com.write("OUTP?\n")
        line = self.com.readline()
        self.check_command(line, '1')

    def off(self):
        self.com.write("OUTP OFF\n")
        line = self.com.readline()
        self.com.write("OUTP?\n")
        line = self.com.readline()
        self.check_command(line, '0')

if __name__ == '__main__':
    import serial
    p = Power("COM0")
    p.connect()
    p.apply(5.0, 0.3)
    p.select_power_port(2)
    p.set_voltage(4.0)
    p.set_current(0.5)
    p.on()
    print p.measure_current()
    print p.measure_voltage()
    p.off()
    p.disconnect()
