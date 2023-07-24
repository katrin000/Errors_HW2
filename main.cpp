#include <iostream>
#include <fstream>
#include<string>


//вставлять в файл массив
void Insert_In_File_With_Const(double* new_array, size_t size, std::string name_file, double const_c)
{
  std::fstream str;
  str.open(name_file, std::fstream::in | std::fstream::out);

  if (str.is_open())
  {
    for (size_t i = 0; i < size; i++)
      str << new_array[i] << " ";

    str << "/n";
    str << const_c;
  }
  else
    throw"File not found";
  str.close();
}


size_t GetCount(std:: string name_file)
{
  std::ifstream file_in;
  size_t _size = 0;
  double tmp = 0.0;

  file_in.open(name_file);
  if (file_in.is_open())
  {
    while (!file_in.eof())
    {
      file_in >> tmp;
      _size++;
    }
  }
  else
    throw "file not found";
  file_in.close();
  _size--;
  return _size;
}


int main()
{
  std::string Good_Result = "GoodFile.txt";
  std::string Current_Result = "CompareWithGoodFile.txt";

  

  double tmp = 0.0;
  size_t size_GR = 0.0;
  size_t size_CR = 0.0;
  size_t Jacobian = 0;
  double max = 0.0;
  double temp=0.0;

  size_GR = GetCount(Good_Result);
  size_CR = GetCount(Current_Result);

  Jacobian = (size_GR - 1) / (size_CR - 1); 

  double* array_GR = new double[size_GR];
  double* array_CR = new double[size_CR];
  double* array_ABS = new double[size_CR];
  double* array_REL = new double[size_CR];


  std::ifstream str_in;

  str_in.open(Good_Result);

  if (str_in.is_open())
  {
    size_t i = 0.0;
    while (!str_in.eof())
    {
      str_in >> tmp;
      array_GR[i] = tmp;
      i++;
    }
  }
  else
    throw "file not found";
  str_in.close();



  str_in.open(Current_Result);
    if (str_in.is_open())
  {
    size_t i = 0.0;
    tmp = 0.0;
    while (!str_in.eof())
    {
      str_in >> tmp;
      array_CR[i] = tmp;
      i++;
    }
  }
  else
    throw "file not found";
  str_in.close();


  for (size_t i = 0; i < size_CR; i++)
  {
    array_ABS[i] = abs(array_GR[i * Jacobian] - array_CR[i]);
  }

 
  
  size_t max_number_abs = 0;
  for (size_t j = 0; j < size_CR; j++)
  {
    if (array_ABS[j] > max)
    {
      max = array_ABS[j];
      max_number_abs = j;
    }
       
  }
  std::cout << "max AbsError- " << max<<"\n Max number AbsError- "<<max_number_abs;
  
  //выведи максимальное значение массива абсолютной ошибки и его номер
  
  Insert_In_File_With_Const(array_ABS, size_CR, "ABS_file.txt", max);





  for (size_t p = 0; p < size_CR; p++)
  {
    double tmp = 0.0;
    if (array_GR[p * Jacobian] > array_CR[p]) 
      tmp = array_GR[p * Jacobian];
    else
      tmp = array_CR[p];
    array_REL[p] = (abs(array_GR[p * Jacobian] - array_CR[p]) / tmp);
  }
  
  size_t max_number_rel = 0;
  for (size_t i = 0; i < size_CR; i++)
  {
    if (array_REL[i] > max)

    {
      max = array_REL[i];
      max_number_rel = i;
    }
  }
  std::cout << "\n max RelError- " << max<<"\n max number RelError- "<< max_number_rel<<std::endl;
  /*выведи максимальное значение и его номер относительной ошибки*/
  Insert_In_File_With_Const(array_REL, size_CR, "REL_file.txt", max);
  /*delete[] array_GR;
  delete[] array_CR;
  delete[] array_ABS;
  delete[]array_REL;*/
  return 0;
}










