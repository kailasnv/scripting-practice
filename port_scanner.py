1#port scanner
# takes a target ip/domain -> scans for open ports -> returns list of open ports

import socket

target = input('Enter target IP/domain: ')
#port = int(input('Enter port to scan: ')) #only scans 1 port 

#scan for common ports
for port in range(1,101):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.settimeout(1)

    result  = sock.connect_ex((target, port))

    # print(result)
    if result == 0:
        print(f"Port {port} is open")
    # else:
    #     print(f"Port {port} is closed")

    sock.close()
    

