# -*- coding: utf-8 -*-
import subprocess

def test_internet(log, cfg_i18n):
    """ Test ping on interner
        1. test a ping on an ip to check if network is ok
        2. test a ping on an url to check if DNS is working
    """
    ip = "8.8.8.8"  # google dns server
    log.debug("Ping '{0}'...".format(ip))
    response_ip = ping(log, ip)  # Google DNS server

    # ip ping ko
    if response_ip != 0:
        log.warning("Unable to ping '{0}'".format(ip))
        return cfg_i18n['NO_IP_ACCESS']
    # ip ping ok
    else:
        log.debug("Ping OK")
        dom = "www.free.fr"
        log.debug("Ping '{0}'".format(dom))
        response_dns = ping(log, dom)
        if response_dns != 0:
            log.warning("Unable to ping '{0}'".format(dom))
            return cfg_i18n['NO_DNS_ACCESS']
        else:
            log.debug("Ping OK")
            return cfg_i18n['OK']

def ping(log, remote):
    cmd = ["/bin/ping", "-c1", "-w2", remote]
    log.debug("Ping command : {0}".format(cmd))
    ping_action = subprocess.Popen(cmd, stdout=subprocess.PIPE)
    ping_action.communicate()
    return ping_action.returncode

