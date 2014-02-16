#ifndef _2D_H
#define _2D_H

#include"point_2d/point_2d.h"

#define DEBUG


#ifdef DEBUG
#include<iostream>
using std::ofstream;
using std::cout;
using std::endl;
#endif

namespace _2d{


    struct RGB
    { unsigned char r, g, b; };
    struct ARGB:public RGB
    { unsigned char a; };



    template<class T>
    class Image
    {
    public:
        Image();
        Image(int width, int height);
        // create() will check whether data has been allocated memory
        void create(int width, int height);

        T * const operator[](int x);
        const T * const operator[](int x)const;
        T & operator[](Point_2d<int> point);
        const T & operator[](Point_2d<int> point)const;

        bool is_valid_position(int x, int y);
        bool is_valid_position(Point_2d<int> p);
        int get_width()const;
        int get_height()const;
    
        Image(const Image<T> & other_image);
        Image & operator = (const Image<T> & other_image);
        virtual ~Image();
#ifdef DEBUG
        void output();
#endif
    private:
        int width, height;
        T * data;
        bool has_data;
    };
    
    // implementation
    template<class T>
    Image<T>::Image()
    { has_data = false; }

    template<class T>
    Image<T>::Image(int width, int height)
    {
        has_data = false;
        create(width, height);
    }
    
    template<class T>
    void Image<T>::create(int _width, int _height)
    {
        if(has_data)
            delete[] data;
        width = _width;
        height = _height;
        data = new T[width*height];
        has_data = true;
    }
    
    template<class T>
    bool Image<T>::is_valid_position(int x, int y)
    {
        return 0 <= x && x < width
            && 0 <= y && y < height;
    }
    template<class T>
    bool Image<T>::is_valid_position(Point_2d<int> p)
    {
        return is_valid_position(p.x, p.y);
    }

    template<class T>
    int Image<T>::get_width()const
    { return width; }
    template< class T>
    int Image<T>::get_height()const
    { return height; }

    template<class T>
    T * const Image<T>::operator[](int x)
    { return data + x * height; }
    
    template<class T>
    const T * const Image<T>::operator [](int x)const
    { return data + x * height; }


    template<class T>
    T & Image<T>::operator [] (Point_2d<int> point)
    { return *(data + point.x * height + point.y); }

    template<class T>
    const T & Image<T>::operator [](Point_2d<int> point)const
    { return *(data + point.x * height + point.y); }
    
    template<class T>
    Image<T>::Image(const Image<T> & other_image)
    {
        create(other_image.width, other_image.height);
        for(int y = 0; y < height; ++y)
            for(int x = 0; x < width; ++x)
                (*this)[x][y] = other_image[x][y];
    }
    
    template<class T>
    Image<T> & Image<T>::operator = (const Image<T> & other_image)
    {
        if(this == &other_image) return *this;
        create(other_image.width, other_image.height);
        for(int y = 0; y < height; ++y)
            for(int x = 0; x < width; ++x)
                (*this)[x][y] = other_image[x][y];
        return *this;
    }
               
    template<class T>
    Image<T>::~Image()
    {
        if(has_data)
            delete[] data;
    }

#ifdef DEBUG
    template<class T>
    void Image<T>::output()
    {
        for(int n = 0; n < width*height; ++n)
            cout<< data[n] <<' ';
        cout<<endl;
    }
#endif

}

#endif
