#This file is executed on every boot (including wake-boot from deepsleep)

import esp
esp.osdebug(None)   #this disable debug output
import gc

def do_connect(ssid,password):
    import network
    station = network.WLAN(network.STA_IF)
    station.active(True)
    if not station.isconnected():
        print('connecting to network...')
        station.connect(ssid,password)
        while not station.isconnected():
            pass
    print('network config:', station.ifconfig())


do_connect('reshu','@#caribcolz123$%')

import webrepl
webrepl.start()

gc.collect()

