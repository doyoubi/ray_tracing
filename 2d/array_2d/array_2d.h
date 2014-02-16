#ifndef ARRAY2D
#define ARRAY2D

#include<iterator>
#include"../point_2d/point_2d.h"

namespace _2d{

using _2d::Point_2d;

template<class T>
class array_2d
{
public:
    class iterator : public std::iterator<std::forward_iterator_tag, T>
    {
    public:
        iterator(){}
        iterator(T * const _ptr);
        iterator(const iterator & other);
        iterator & operator = (const iterator other);
        const iterator & operator ++ ();
        const iterator operator ++ (int);
        bool operator == (iterator other);
        bool operator != (iterator other);
        T & operator * ();
        T * operator -> ();
    private:
        T * ptr;
    };

    array_2d(int width, int height);

    T * const operator[](int x);
    const T * const operator[](int x)const;
    T & operator[](Point_2d<int> point);
    const T & operator[](Point_2d<int> point)const;

    bool is_valid_position(int x, int y);
    bool is_valid_position(Point_2d<int> p);
    bool is_border(int x, int y);
    bool is_border(Point_2d<int> p);
    int get_width()const;
    int get_height()const;

    // not implement const_iterator
    const iterator begin()const;
    const iterator end()const;

    array_2d(const array_2d<T> & other_image);
    array_2d & operator = (const array_2d<T> & other_image);

    ~array_2d();
private:
    int width, height;
    T * data;
};


// implementation

// iterator

template<class T>
array_2d<T>::iterator::iterator(T * const _ptr)
{ ptr = _ptr; }

template<class T>
array_2d<T>::iterator::iterator(const array_2d<T>::iterator & other)
{ ptr = other.ptr; }

template<class T>
typename array_2d<T>::iterator & array_2d<T>::iterator::operator = (const array_2d<T>::iterator other)
{ this->ptr = other.ptr; }

template<class T>
const typename array_2d<T>::iterator & array_2d<T>::iterator::operator ++ ()
{
    ptr++;
    return *this;
}

template<class T>
const typename array_2d<T>::iterator array_2d<T>::iterator::operator ++ (int)
{ 
    array_2d<T>::iterator temp = *this;
    ptr++;
    return temp;
}

template<class T>
bool array_2d<T>::iterator::operator == (array_2d<T>::iterator other)
{ return this->ptr == other.ptr; }

template<class T>
bool array_2d<T>::iterator::operator != (array_2d<T>::iterator other)
{ return this->ptr != other.ptr; }

template<class T>
T & array_2d<T>::iterator::operator * ()
{ return *ptr; }

template<class T>
T * array_2d<T>::iterator::operator -> ()
{ return ptr; }

// 
template<class T>
array_2d<T>::array_2d(int _width, int _height):
    width(_width), height(_height)
{ data = new T[width*height]; }

template<class T>
bool array_2d<T>::is_valid_position(int x, int y)
{
    return 0 <= x && x < width
        && 0 <= y && y < height;
}

template<class T>
bool array_2d<T>::is_valid_position(Point_2d<int> p)
{ return is_valid_position(p.x, p.y); }

template<class T>
bool array_2d<T>::is_border(int x, int y)
{
    return x == 0
        || y == 0
        || x == width-1
        || y == height-1;
}

template<class T>
bool array_2d<T>::is_border(Point_2d<int> p)
{ return is_border(p.x, p.y); }

template<class T>
int array_2d<T>::get_width()const
{ return width; }
template< class T>
int array_2d<T>::get_height()const
{ return height; }

template<class T>
T * const array_2d<T>::operator[](int x)
{ return data + x * height; }

template<class T>
const T * const array_2d<T>::operator [](int x)const
{ return data + x * height; }


template<class T>
T & array_2d<T>::operator [] (Point_2d<int> point)
{ return *(data + point.x * height + point.y); }

template<class T>
const T & array_2d<T>::operator [](Point_2d<int> point)const
{ return *(data + point.x * height + point.y); }

template<class T>
array_2d<T>::array_2d(const array_2d<T> & other_image):
    width(other_image.width), height(other_image.height)
{
    data = new T[width * height];
    for(int y = 0; y < height; ++y)
        for(int x = 0; x < width; ++x)
            (*this)[x][y] = other_image[x][y];
}

template<class T>
array_2d<T> & array_2d<T>::operator = (const array_2d<T> & other_image)
{
    T * temp = data;
    data = new T[other_image.width * other_image.height];
    width = other_image.width;
    height = other_image.height;
    for(int y = 0; y < height; ++y)
        for(int x = 0; x < width; ++x)
            (*this)[x][y] = other_image[x][y];
    delete[] temp;
    return *this;
}
           
template<class T>
array_2d<T>::~array_2d()
{
    delete[] data;
}

template<class T>
const typename array_2d<T>::iterator array_2d<T>::begin()const
{ return array_2d<T>::iterator(data); }

template<class T>
const typename array_2d<T>::iterator array_2d<T>::end()const
{ return array_2d<T>::iterator(data + width*height); }

}

#endif
