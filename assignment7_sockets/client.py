from socket import socket, AF_INET, SOCK_STREAM
import sys

# 1.) socket
server_fd = socket(AF_INET, SOCK_STREAM, 0)
if not server_fd:
    print("socket error")
    sys.exit()

# 2.) connect
port = 8081
host = "127.0.0.1"
server_info = (host, port)
server_fd.connect(server_info)

msg="hello"
print(f"Msg to send: {msg}")
server_fd.sendall(msg.encode('utf-8'))

data = server_fd.recv(1024)
print(f"Server responded with: {data} \n")

#data = input("what would you like to send? ")
data = "exit"
print(f"Msg to send: {data}")
server_fd.sendall(data.encode())

data = server_fd.recv(1024)
print(f"Server responded with: {data}")

print(f"closing connection")
server_fd.close()
