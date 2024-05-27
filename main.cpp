#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sysexits.h>
#include <unistd.h>

int main() {
  const auto fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    std::cout << strerror(errno) << std::endl;
    return -1;
  }

  sockaddr_in socket{};
  socket.sin_family = AF_INET;
  socket.sin_addr.s_addr = htonl(INADDR_ANY);
  socket.sin_port = htons(8080);

  if (bind(fd, (sockaddr *)(&socket), sizeof(socket)) != 0) {
    std::cout << strerror(errno) << std::endl;
    return -1;
  }

  if (listen(fd, 0) != 0) {
    std::cout << strerror(errno) << std::endl;
    return -1;
  }

  sockaddr_in client{};
  socklen_t len = sizeof(client);
  const auto connectfd = accept(fd, (sockaddr *)(&client), &len);
  if (connectfd < 0) {
    std::cout << strerror(errno) << std::endl;
    return -1;
  } else {
    std::cout << client.sin_addr.s_addr << " connected" << std::endl;
  }

  close(fd);
  return EX_OK;
}
