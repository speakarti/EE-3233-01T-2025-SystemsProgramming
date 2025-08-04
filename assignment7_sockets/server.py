from socket import socket, AF_INET, SOCK_STREAM
import sys


# 1.) Socket
server_fd = socket(AF_INET, SOCK_STREAM, 0)
if not server_fd:
    print("socket error")
    sys.exit()

# 2.) Bind
port = 8081
host = "127.0.0.1"
server_info = (host, port)

server_fd.bind(server_info)

# 3.) Listen
server_fd.listen(1)

# 4.) Accept
client_fd, client_addr = server_fd.accept()

print("connected to client")
data = client_fd.recv(1024)
print(f"Msg received from client: {data}")
msg="world"
print(f"Responding with: {msg} \n")
client_fd.sendall(msg.encode('utf-8'))

data = client_fd.recv(1024)
print(f"Msg received from client: {data} ")

data="exit"
print(f"Responding with: {data} ")

client_fd.sendall(data.encode())


print(f"closing connection")
server_fd.close()
client_fd.close()
