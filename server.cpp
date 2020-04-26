#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <cstdlib>

//g++ server.cpp -o server -lpthread -lsfml-system -lsfml-network

int findLetter(char c, std::string s)
{
  for (int i = 0; i < s.size(); i++)
    if (s[i] == c)
      return i;
  return s.size();
}


int main()
{
    sf::TcpListener listner;
    sf::TcpSocket socket;
    //std::string messageBuffer;
    std::size_t bytesRecieved;
    char messageBuffer[100] = {};
    std::string lastMessage = "          ";
    bytesRecieved = 0;

    
    for(;;)
    {
        if(listner.listen(53000) != sf::Socket::Done)
        {
          std::cout << "Port problems" << '\n';
        }  
    
            
        if(listner.accept(socket) == sf::Socket::Done)
        {
        

        
        bytesRecieved = 0;

        char receivedMessage[100];
        char newMessage[10000];
        std::string s;
        int n = 0;
        int j = 0;
        bool fl = true;
        std::size_t bytesReceived;
        while (fl)
        { 
          if (socket.receive(receivedMessage, 90, bytesReceived) == sf::Socket::Done)
          {
            for (int k = 0; k < bytesReceived; k++)
            {
              newMessage[j] = receivedMessage[k];
              if (newMessage[j] == '\0')
              {
                fl = false;
                break;
              }
              j++;
            }

          }
          s.assign(newMessage);
          /*std::cout << s << std::endl;
          n = findLetter('C', s);
          if (n != 0)
            n = std::atoi((s.substr(0, n+1)).c_str());
          if ( n == s.size())
            fl = false;
          fl = false;*/
        }
        
       if ((lastMessage != s) and (s != "956"))
       {
         std::cout << s << std::endl;
         lastMessage = s;
       } 

       if (s.find( "shut down server") != std::string::npos)
       {
         listner.close();
         return 0;
       }
       sf::Socket::Status status = socket.send(lastMessage.c_str(), lastMessage.size() + 1);
       

       
    }
    }


}
