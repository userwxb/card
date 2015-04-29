#!/usr/bin/env python
import os,sys
import logging
import time

class CmdBase:
    def __init__(self,modulepath):
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

    def pack_cmd(self,cmd,*args):
        data=cmd
        return data

    def unpack_cmd(self,data):
        return data


