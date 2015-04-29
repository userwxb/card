#!/usr/bin/env python
import os,sys
import logging
import time
from ctypes import *


class Base:
    def __init__(self,modulepath,module,type="WIN32"):
        tt = time.strftime("%m-%d_%H.%M",time.localtime(time.time()))
        # get current file absolutely path
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

        so = os.path.join(modulepath,module)
        self.log.info("C lib path: %s" % so)
        #if not os.path.exists(so):
        #    self.log.error("Module [ %s ] is not exists" % so)
        #    raise "Module [ %s ] is not exists" % so

        if type == "WIN32": # using window standard export the function
            self.capi=WinDLL(so)
            #self.capi=windll.LoadLibrary(so)
        else:
            self.capi=cdll.LoadLibrary(so) #for extern "C"  export: cdecl
            #self.capi=CDLL(so) #for C dll
        if not self.capi:
            self.log.error("Load Module [ %s ] Failed" % so)
            raise "Load Module [ %s ] Failed" % so

if __name__=="__main__":
    b=Base("/home/xiaobi2x","test.so")
