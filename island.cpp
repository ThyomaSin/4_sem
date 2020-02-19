#include <iostream>
#include <iostream>
#include <vector>
#include <fstream>

int getWidth()
{
  std::cout << "How many columns?" << std::endl;
  
  int n = 0;
  while (n <= 0)
    std::cin >> n;
  return n;
} 

int getHeigth()
{
  std::cout << "How many rows?" << std::endl;
  
  int n = 0;
  while (n <= 0)
    std::cin >> n;
  return n;
} 

void removeIsland(std::vector<std::vector<int> >* ocean, int i, int j)
{
  (*ocean)[i][j] = 0;

  if ((i > 0) and ((*ocean)[i-1][j] == 1))
    removeIsland(ocean, i-1, j);
  if ((j > 0) and ((*ocean)[i][j - 1] == 1))
    removeIsland(ocean, i, j - 1);
  if ((i < (*ocean).size() - 1) and ((*ocean)[i + 1][j] == 1))
    removeIsland(ocean, i + 1, j);
  if ((j < (*ocean)[0].size() - 1) and ((*ocean)[i][j + 1] == 1))
    removeIsland(ocean, i, j + 1);
}

int countIslands(std::vector<std::vector<int> > ocean)
{
  int islands = 0;

  for (int i = 0; i < ocean.size(); i++)
    for (int j = 0; j < ocean[0].size(); j++)
      if (ocean[i][j] == 1)
      {
        islands += 1;
        removeIsland(&ocean, i, j);
      }
  return islands;
}

int main()
{
  int n = getHeigth();
  int m = getWidth();

  std::vector<std::vector<int> > ocean(n, std::vector<int>(m));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      std::cin >> ocean[i][j];
  
  std::cout << std::endl;
  

  int islands = countIslands(ocean);
 
  std::cout << "There are " << islands << " islands in the ocean";
  
}












