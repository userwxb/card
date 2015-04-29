#!/usr/bin/env python
#coding=utf-8
import os,sys,re
import splinter
from splinter.browser import Browser 
p = os.path.join(os.path.dirname(os.path.realpath(__file__)), '..','lib')
sys.path.insert(0, p)
import logging
import yaml

os_version = sys.platform
import time
from splinter import Browser


def get_config(cfgfile):
    txt=''
    with open(cfgfile, "r") as fp:
        txt = fp.read()
    print txt
    dconf = yaml.load(txt)
    return dconf['web']


def splinter(brow,url,id,pwd):
    browser = Browser(brow)
    #login 126 email websize
    browser.visit(url)
    #wait web element loading
    time.sleep(5)
    #fill in account and password
    browser.find_by_id('idInput').fill(id)
    browser.find_by_id('pwdInput').fill(pwd)
    #click the button of login
    browser.find_by_id('loginBtn').click()
    #close the window of brower
    # browser.quit()

if __name__ == '__main__':
    print "config file: %s " % sys.argv[1]
    config=get_config(sys.argv[1])
    splinter(config['browser'],config['url'],config['id'],config['password'])
