#ifndef 2D_H
#define 2D_H

#ifdef DEBUG
#include<iostream>
using std::ofstream;
using std::endl;
#endif

namespace _2d{


    class ARGB
    {
    public: 
        unsigned char A, R, G, B;
    };
    
    
    class Point_2d
    {
    public:
        int x, y;
    };
    
    
    class Point_3d : public Point_2d
    {
    public:
        int z;
    };
    
    
    template<class T>
    class Image
    {
    public:
        Image(int width, int height);
        void create(int width, int height);
        T * operator[](int x);
        T & operator[](Point_2d point);
    
        Image(const & Image other_image);
        Image & operator = (const & Image other_image);
        Image(){}
        ~Image();
#ifdef DEBUG
        ofstream & operator<<(const & ofstream out);
#endif
    private:
        int width, height;
        T * data;
        bool has_data;
    };
    
    // implementation
    template<T>
    Image<T>::Image(int width, int height)
    {
        create(width, height);
    }
    
    template<T>
    Image<T>::create(int width, int height)
    {
        this.width = width;
        this.height = height;
        data = new ARGB[width*height];
        has_data = true
    }
    
    template<T>
    ARGB * Image<T>::operator[](int x)
    {
        return data + x * height;
    }
    
    template<T>
    ARGB & Image<T>::operator[](Point_2d point)
    {
        return *(data + point.x * height + point.y);
    }
    
    template<T>
    Image<T>::Image(const & Image other_image)
    {
        create(other_image.width, other_image.height);
        for(int y = 0; y < height; ++y)
            for(int x = 0; x < width; ++x)
                (*this)[x][y] = other_image[x][y];
    }
    
    template<T>
    Image & Image<T>::Image(const & Image other_image)
    {
        if(has_data)
            delete[] data;
        create(other_image.width, other_image.height);
        for(int y = 0; y < height; ++y)
            for(int x = 0; x < width; ++x)
                (*this)[x][y] = other_image[x][y];
        return *this
    }
               
    template<T>
    Image<T>::~Image()
    {
        if(has_data)
            delete[] data;
    }

#ifdef DEBUG
    ofstream & operator<<(const & ofstream out)
    {
        for(int n = 0; n < width*height; ++n)
            out<< data[n] <<' ';
        out<<endl;
        return out;
    }
#endif

}

#endif
