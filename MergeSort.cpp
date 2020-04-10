#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

void mergeArrays(std::vector<int>* data, int start, int stop, int Middle)
{
   int i = start;
   int j = Middle;
   std::vector<int> c = {};
   while ((i < Middle) and (j < stop))
   {
     if ((*data)[i] < (*data)[j])
     {
       c.push_back((*data)[i]);
       i++;
     }

     if ((*data)[j] < (*data)[i])
     {
       c.push_back((*data)[j]);
       j++;
     }

     if ((*data)[i] == (*data)[j])
     {
       c.push_back((*data)[i]);
       i++;
     }
   }

   while (i < Middle)
   {
     c.push_back((*data)[i]);
     i++;
   }

   while (j < stop)
   {
     c.push_back((*data)[j]);
     j++;
   }

   j = 0;
   for (i = start; i < stop; i++)
   {
     (*data)[i] = c[j];
     j++;
   }
}


void mergeSort(std::vector<int>* data, int start, int stop)
{
  if (stop - start <= 1)
    return;
  int middle = (stop - start)/2;
  
  if ((start == 0) and(stop == data -> size()))
  {
    std::thread t2(mergeSort, data, start, start + middle);
    std::thread t3(mergeSort, data, start + middle, stop);
    t2.join();
    t3.join();
  }
  else
  {
    mergeSort(data, start, start + middle);
    mergeSort(data, start + middle, stop);
  }
  mergeArrays(data, start, stop, start + middle);
}

int main()
{
  std::vector<int> data = {};
  for (int i = 0; i < 100000; i++)
    data.push_back(100000 - i);

  int n = data.size();
  std::thread t1(mergeSort, &data, 0, n);
  t1.join();

  for (int i = 0; i < 20; i++)
    std::cout << data[i+50] << "  ";
  std::cout << '\n';
  
  for (int i = 0; i < n-1; i++)
    if (data[i] > data[i+1])
      std::cout << " false ";
  std::cout << '\n';


  return 0;
}
