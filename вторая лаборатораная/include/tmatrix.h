// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//


#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:    
    // всякие конструкторы
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz <= 0)
        throw std::out_of_range("Vector size should be greater than zero");
    if (sz >= MAX_VECTOR_SIZE)
        throw std::out_of_range("Too large vector size");
    pMem = new T[sz]();// У типа T д.б. конструктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s)
  {
      sz = s;
      pMem = new T[sz];
      std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) /*: sz(v.sz)*/
  {           
      sz = v.sz;
      pMem = new T[sz];
      for (int i = 0; i < sz; i++)
          pMem[i] = v.pMem[i];
  }
  TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem) 
  {
      v.sz = 0;       // Обнуляем размер перемещаемого вектора
      v.pMem = nullptr; // Устанавливаем указатель на nullptr
  }
  ~TDynamicVector()
  {
      delete[]pMem;
  }
  //операторы разные
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v)
          return *this;
      if (sz != v.sz) {
          T* p = new T[v.sz];
          delete[] pMem;
          sz = v.sz;
          pMem = p;
      }
      for (int i = 0;i < sz;i++)
          this->pMem[i] = v.pMem[i];      
      return *this; 
  }

  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this != &v) {
          delete[] pMem; 
          pMem = v.pMem;
          sz = v.sz;

          v.pMem = nullptr; // зануляем перемещаемый объект
          v.sz = 0;
      }
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t index)
  {
      if (index >= sz)
          throw std::out_of_range("Too large index");
      else if (index < 0)
          throw std::out_of_range("Index must be more then zero");
      return pMem[index];
  }
  const T& operator[](size_t index) const
  {
      if (index >= sz)
          throw std::out_of_range("Too large index");
      else if (index < 0)
          throw std::out_of_range("Index must be more then zero");
      return pMem[index];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz)
          throw "Index out of range";
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz)
          throw "Index out of range";
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept 
  {
      if (sz != v.sz) {
          return false;
      }
      for (size_t i = 0; i < sz; i++)
          if (pMem[i] != v.pMem[i])
              return false;
      return true; // Если все элементы равны
  }

  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector res(sz); // новый вектор для результатов
      for (size_t i = 0; i < sz; i++)
          res[i] = pMem[i] + val;
      return res;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++)
          res[i] = pMem[i] - val;
      return res;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector res(sz); 
      for (size_t i = 0; i < sz; i++)
          res[i] = pMem[i] * val;
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw std::invalid_argument("Vectors must have the same size");
      TDynamicVector res(sz); 
      for (size_t i = 0; i < res.size(); i++)
          res[i] = pMem[i] + v.pMem[i];
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) 
          throw std::invalid_argument("Vectors must have the same size");
      TDynamicVector res(sz); 
      for (size_t i = 0; i < sz; i++)
          res[i] = pMem[i] - v.pMem[i]; 
      return res;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz)
          throw "Vectors must have the same size for multiplication";
      T res = T();
      for (size_t i = 0; i < sz; i++)
          res += pMem[i] * v.pMem[i];
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : public TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s >= MAX_MATRIX_SIZE)
          throw std::invalid_argument("Too large size of matrix");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }
  ~TDynamicMatrix() {
  }

 //using TDynamicVector<TDynamicVector<T>>::operator[];
 //using TDynamicVector<TDynamicVector<T>>::operator=;
  //операторы всякие
  //обращение к элементам через []
  TDynamicVector<T>& operator[](size_t index)
  {
      if (index >= this->size())
          throw std::out_of_range("Too large index");
      else if (index < 0)
          throw std::out_of_range("Index must be more then zero");
      return this->pMem[index];
  }
  const TDynamicVector<T>& operator[](size_t index) const
  {
      if (index >= this->size())
          throw std::out_of_range("Too large index");
      else if (index < 0)
          throw std::out_of_range("Index must be more then zero");
      return this->pMem[index];
  }
  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) 
          return false; // Сравниваем размеры
      for (size_t i = 0; i < sz; i++) 
          if (pMem[i] != m.pMem[i]) 
              return false; // Сравниваем строки
      return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix res(sz); // Создаем новый матричный объект
      for (size_t i = 0; i < sz; i++)
          for (size_t j = 0; j < sz; j++)
              res[i][j] = pMem[i][j] * val; // Умножаем элемент матрицы на скаляр
      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      TDynamicMatrix res(sz); // Создаем новый матричный объект
      for (size_t i = 0; i < sz; i++)
          for (size_t j = 0; j < sz; j++)
              res[i][j] = pMem[i][j] * val; // Умножаем элемент матрицы на скаляр
      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) 
          throw std::invalid_argument("Matrices must have the same size");
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++)
          for(int j=0;j<sz;j++)
            res[i][j] = pMem[i][j] + m.pMem[i][j]; // Сложение матриц
      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw std::invalid_argument("Matrices must have the same size");
      TDynamicMatrix<T> res(sz);
      for (size_t i = 0; i < sz; i++)
          for (int j = 0; j < pMem[i].size(); j++)
              res[i][j] = pMem[i][j] - m.pMem[i][j];
      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw std::invalid_argument("Matrix sizes are incompatible for multiplication");
      TDynamicMatrix res(sz); 
      for (size_t i = 0; i < sz; i++)
          for (size_t j = 0; j < sz; j++) {
              res[i][j] = 0;
              for (size_t k = 0; k < sz; k++)
                  res[i][j] += pMem[i][k] * m.pMem[k][j];
          }  
      return res;
  }

  TDynamicMatrix& operator=(const TDynamicMatrix& m) {
      if (this != &m) {
         // *this = TDynamicVector::operator=(*this, m);

          if (sz != m.sz)
              throw std::invalid_argument("size must be equal");
          for (int i = 0; i < sz; i++) {
                  pMem[i] = m.pMem[i];
          }
      }
      return *this;
  }
 
  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          istr >> v.pMem[i];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++) {
          for (size_t j = 0; j < v.sz; j++)
              ostr << v.pMem[i][j] << " ";
          ostr << "\n";
      }
      return ostr;
  }
};

#endif