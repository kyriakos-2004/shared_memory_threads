import socket

target = str(input("Enter ip of target to scan available ports, empty for localhost: "))

for port in range(1,65535):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        socket.setdefaulttimeout(0.1)
        
        if not target:
            target = "127.0.0.1"

        result = s.connect_ex((target,port))
        if result == 0:
            print("Port " + str(port) + " is open") 
        s.close()