#include <iostream>
#include <vector>
// C++ program for the
// above approach
 
//Function to count the number
// of LIS in the array a[]
int findNumberOfLIS(std::vector<int> a)
{
  //Base Case
  if (a.size() == 0)
    return 0;
 
  int n = a.size();
 
  std::vector<int> d(n, 1);
 
  std::vector<int> l(n, 1);
 
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < i; j++)
    {
      //If current element is
      // smaller
      if (a[i] <= a[j])
        continue;
 
      if  (d[j] + 1 > d[i])
      {
        d[i] = d[j] + 1;
        l[i] = l[j];
      }
      else if (d[j] + 1 == d[i])
        l[i] += l[j];
    }
  }
   for(int i = 0; i < n; i++)
  {
      std::cout << l[i] << " ";
  }
  //Store the maximum element
  // from d
  int max_length = 0;
 
  for (int i : d){
    
    max_length = std::max(i,max_length);}
 
  //Stores the count of LIS
  int count = 0;
 
  //Traverse d and l
  // simultaneously
  for(int i = 0; i < n; i++)
  {
    //Update the count
    if (d[i] == max_length)
      count += l[i];
  }
   
  //Return the count of LIS
  return count;
}
/////////
int main()
{
    int ex;
    std::cin >> ex;

    if(ex == 1) {
        std::vector<int> v = readInputVector();
        std::vector<int>a = longestIncreasingSubsequence(v);
        
        std::cout << a[0] << ' ' << a[1] << '\n';
        
        return 0;
    }
    
    else if (ex == 2) {
        std::vector<int> u = readInputVector();
        std::vector<int> v = readInputVector();

        std::vector<int> b = longestCommonIncreasingSubsequence(u, v);

        std::cout << b[0] << '\n';

        return 0;
    }

    return -1;
}
 
// This code is contributed by Mohit Kumar 29