#!/usr/bin/env python

import os,sys
import shutil

_p = os.path.dirname(os.path.realpath(__file__))
sys.path.insert(0, os.path.join(_p,'..','lib'))

from base import *

class udisk(Base):
    def __init__(self,module):
        modulepath=os.path.dirname(os.path.realpath(__file__))
        
        Base.__init__(self,modulepath,module)
        self.log.info("class %s init" % self.__class__.__name__)
        self.volumn=[]


    def find_udisk(self):
        disk = (c_char*64)()
        self.capi.restype = c_ushort
        self.count=self.capi.enum_udisk(disk)
        print "Get u disk count: %d" % self.count
        if self.count > 0:
            for i in range(self.count):
                vol = disk[i] + ":"
                self.volumn.append(vol)
                self.log.info("Find U Disk: %s" % vol)
    def copyfiles(self,todir,*endstring):
        self.find_udisk()
        for fromdir in self.volumn:
            for root,dirs,files in os.walk(fromdir):
                for filename in files:
                    if True in map(filename.upper().endswith,endstring):
                        frompath=os.path.join(root,filename)
                        topath=os.path.join(todir,filename)
                        self.log.debug("from :%s copy file to: %s" % (frompath,topath))
                        shutil.copyfile(frompath,topath)
    def readfile(self,name):
        self.find_udisk()
        context=''
        for fromdir in self.volumn:
            for root,dirs,files in os.walk(fromdir):
                for filename in files:
                    if filename == name:
                        fullpath=os.path.join(root,filename)
                        with open(fullpath,"rU") as fp:
                            context=fp.read()
                        return context
        return None


if __name__ == '__main__':
    ud = udisk("udisk.dll")
    ud.copyfiles("D:\\test",".IMG")
