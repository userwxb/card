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

	def read(self):
		n=self.com.InWaiting()
		if n:
			return self.com.read(n)
		return None

	def read_line(self):
        return self.com.readline().strip()

	def write(self,data):
        self.com.write(data)

    def read_data(self):
        n = self.com.inWaiting()
        data = self.com.read(n)
        self.data += data

    def write(self, value, timeout=10):
        self.com.writeTimeout = timeout
        r =  self.com.write(value)
        self.com.flush()
        return r





