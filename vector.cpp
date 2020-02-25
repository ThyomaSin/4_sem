#include <iostream>
#include <vector>
#include <fstream>

int getNum()
{
  std::cout << "How many numbers?" << std::endl;
  
  int n = 0;
  while (n <= 0)
    std::cin >> n;
  return n;
}

std::vector<int> doubleRow(const std::vector<int>& data)
{
  std::vector<int> preres(data.size());
  std::vector<int> res(data.size());
  for (int i = 0; i < data.size(); i++)
  {
    preres[i] = data[i]*data[i];
  }
  
  int pos1stPol = 0;
  for (int i = 0; i < data.size(); i++)
  {
    if (data[i] >= 0)
    {
      pos1stPol = i;
      break;
    }
    pos1stPol++;
  }

  int i = pos1stPol - 1;
  int j = pos1stPol;
  int k = 0;
  
  while(((i >= 0) or (j < data.size())) and (k < data.size()))
  {
      if (((preres[i] <= preres[j]) and (i >= 0)) or (j >= data.size())) 
      {
        res[k] = preres[i];
        i--;
        k++;
      }
      else if (((preres[i] > preres[j]) and (j < data.size())) or (i < 0))
      {
        res[k] = preres[j];
        j++;
        k++;
      }
    
  }  
  return res;
}

int main()
{
  int n = getNum();
  std::cout << "enter " << n << " numbers in the increasing order" << std::endl;
  
  std::vector<int> data(n);
  int x;
  for (int i = 0; i < n; i++)
  {
    std::cin >> x;
    data[i] = x;
  }
  
  std::vector<int> res(n);
  res = doubleRow(data);
  
  for (int i  = 0; i < res.size(); i++)
    std::cout << res[i] << "  ";
}





