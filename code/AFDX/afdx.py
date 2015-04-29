#!/usr/bin/env python
class afdx:
    def __init__(self):
        print dir(self)
        self._cmd="cmd_"
        self._cmd_list = []
        for attr in dir(self):
            print "attribute: %s" % attr
            if attr.startswith(self._cmd):
                self._cmd_list.append(attr[len(self._cmd):])
        print self._cmd_list

    def exe_cmd(self,cmd):
        getattr(self,self._cmd+cmd)()
    def cmd_aa(self):
        print "cmd_aa"
    def cmd_bb(self):
        print "cmd_bb"


if __name__ == "__main__":
    a=afdx()
    a.exe_cmd('aa')
    a.exe_cmd('bb')
    print "Done"
