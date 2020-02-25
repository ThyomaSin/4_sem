#include <iostream>
#include <vector>
#include <fstream>

#include <string>
#include <cstdlib>

int getWidth(std::string s)
{
  int n = std::atoi(s.c_str());
  return n;
} 

int getHeigth(std::string s)
{
  int n = std::atoi(s.c_str());
  return n;
} 

void removeIsland(std::vector<std::vector<char> >* ocean, int i, int j)
{
  (*ocean)[i][j] = '0';

  if ((i > 0) and ((*ocean)[i-1][j] == '1'))
    removeIsland(ocean, i-1, j);
  if ((j > 0) and ((*ocean)[i][j - 1] == '1'))
    removeIsland(ocean, i, j - 1);
  if ((i < (*ocean).size() - 1) and ((*ocean)[i + 1][j] == '1'))
    removeIsland(ocean, i + 1, j);
  if ((j < (*ocean)[0].size() - 1) and ((*ocean)[i][j + 1] == '1'))
    removeIsland(ocean, i, j + 1);
}

int countIslands(std::vector<std::vector<char> > ocean)
{
  int islands = 0;

  for (int i = 0; i < ocean.size(); i++)
    for (int j = 0; j < ocean[0].size(); j++)
      if (ocean[i][j] == '1')
      {
        islands += 1;
        removeIsland(&ocean, i, j);
      }
  return islands;
}

int main()
{
  std::fstream f;
  f.open("island.txt");
  std::string s;

  std::getline(f, s, '\n');
  int n = getHeigth(s);
  std::getline(f, s, '\n');
  int m = getWidth(s);

  std::vector<std::vector<char> > ocean(n, std::vector<char>(m));
  for (int i = 0; i < n; i++)
  {
    std::getline(f, s, '\n');
    for (int j = 0; j < m; j++)
      ocean[i][j] = s[j];
  }
  
  std::cout << std::endl; 
  

  int islands = countIslands(ocean);
 
  std::cout << "There are " << islands << " islands in the ocean" << std::endl;
  
}












