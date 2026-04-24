1#port scanner
# takes a target ip/domain -> scans for open ports -> returns list of open ports

import socket
import threading

target = input('Enter target IP/domain: ')

def scan_port(port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.settimeout(1)
    res = sock.connect_ex((target,port))
    if res == 0:
        print(f'[+] Port {port} is open')
    sock.close()
    
for port in range(1, 1000):
    t = threading.Thread(target=scan_port, args=(port,))
    t.start()
    
    
      

