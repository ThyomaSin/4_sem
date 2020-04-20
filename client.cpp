#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <cstdlib>
//g++ client.cpp -o client.app -lpthread -lsfml-system -lsfml-network

int findLetter(char c, std::string s)
{
  for (int i = 0; i < s.size(); i++)
    if (s[i] == c)
      return i;
  return s.size() + 10;
}


void serverConnection(std::string* myMessage, std::string* lastMessage, std::string userName)
{
  int i = 0;
  sf::TcpSocket socket;
  while (true)
  {
    i++;
    if ((i%10000000 == 0)) 
    {
      while (socket.connect("127.0.0.1", 53000) != sf::Socket::Done);
      
      if (*myMessage == *lastMessage)
      {
        std::string message = std::to_string((*myMessage).size() + 1) + *myMessage;
        socket.send(message.c_str(), message.size() + 1);
      }

      char receivedMessage[100];
      char newMessage[10000];
      std::string s;
      int n = 0;
      int j = 0;
      bool fl = false;
      std::size_t bytesReceived;
      while (!fl)
      { 
        if (socket.receive(receivedMessage, 100, bytesReceived) == sf::Socket::Done)
        {
          for (int k = 0; k < bytesReceived; k++)
          {
            newMessage[j] = receivedMessage[k];
            j++;
          }
          
        }
        s.assign(newMessage, j);
        n = findLetter('C', s);
        if (n < s.size())
          n = std::atoi((s.substr(0, n-1)).c_str());
        if ( n == s.size())
          fl = false;
      }

      s = s.substr(findLetter('C', s), n - findLetter('C', s));
      if (*lastMessage != s)
      {
        std::cout << s << std::endl;
        *lastMessage = s;
      }
      socket.disconnect();
    }
  }
}

void input(std::string* myMessage, std::string* lastMessage, std::string userName)
{
  while (true)
  {
    std::string s;
    std::cin >> s;
    *myMessage = userName + *myMessage;
    *lastMessage = *myMessage;
  }
}

int main()
{
  std::string userNumber;
  std::cout << "enter user number 0 - 9" << std::endl;
  std::cin >> userNumber;
  std::string userName = "Client" + userNumber + ": ";

  std::string myMessage;
  std::string lastMessage;
  std::thread t1(serverConnection, &myMessage, &lastMessage, userName);
  std::thread t2(input, &myMessage, &lastMessage, userName);
  
  t1.join();
  t2.join();
}
