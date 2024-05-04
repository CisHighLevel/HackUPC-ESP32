import socket

ServerIP = "10.192.230.83"
ServerPort = 1999
bufferSize = 1024

TCPServerSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

TCPServerSocket.bind((ServerIP, ServerPort))

TCPServerSocket.listen(5)

print("TCP server up and listening")

clientSocket, address = TCPServerSocket.accept()

print("TCP server connected to server and ready to perform read write operations")

print(f"Connected by client {address}")

receivedData = ""
bufferSize = 1024

print("Server is waiting for incoming data")

switchState = 1

while True:
    
        try:
            receivedData = clientSocket.recv(bufferSize).decode('utf-8')
            if not receivedData:
                break
            else:
                print("[FromClient]: " + receivedData)
                if "close" in receivedData:
                    clientSocket.close()
                    print("Client has disconnected")
                    print("Close socket server")
                    TCPServerSocket.close()
                    break
        except KeyboardInterrupt:
            print("\nKeyboard interrupt detected. Continuing execution.")
            continue
        except ConnectionResetError:
            print("Client closed connection unexpectedly")
            clientSocket.close()
            TCPServerSocket.close()
            break

        print("Server is waiting to receive data from the keyboard")
        # switchState = not switchState
    