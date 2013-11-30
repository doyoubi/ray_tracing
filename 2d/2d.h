#ifndef _2D_H
#define _2D_H

#define DEBUG

#ifdef DEBUG
#include<iostream>
using std::ofstream;
using std::cout;
using std::endl;
#endif

namespace _2d{


    class RGB
    { public: unsigned char r, g, b; };
    class ARGB:public RGB
    { public: unsigned char a; };
    
    template<class T>
    class Point_2d
    { 
        public: 
            int x, y;
            Point_2d(T _x, T _y):x(_x), y(_y) {}
            Point_2d(){}
            
            //  operator +  -  *   ==  =
            friend const Point_2d<T> operator + (const Point_2d<T> lhs, const Point_2d<T> rhs)
            { return Point_2d<T>(lhs.x+rhs.x, lhs.y+rhs.y); }

            const Point_2d<T> & operator += (const Point_2d<T> rhs)
            { 
                this->x += rhs.x;
                this->y += rhs.y;
                return *this;
            }

            friend const Point_2d<T> operator - (const Point_2d<T> lhs, const Point_2d<T> rhs)
            { return Point_2d<T>(lhs.x-rhs.x, lhs.y-rhs.y); }

            const Point_2d<T> & operator -= (const Point_2d<T> rhs)
            { 
                this->x -= rhs.x;
                this->y -= rhs.y;
                return *this;
            }

            friend const T operator * (const Point_2d<T> lhs, const Point_2d<T> rhs)
            { return lhs.x*rhs.x + lhs.y*rhs.y; }

            friend const Point_2d<T> operator * (const Point_2d<T> lhs, T rhs)
            { return Point_2d<T>(lhs.x*rhs, lhs.y*rhs); }

            const Point_2d<T> & operator *= (T rhs)
            { 
                this->x *= rhs;
                this->y *= rhs;
                return *this;
            }

            friend const Point_2d<T> operator * (T lhs, const Point_2d<T> rhs)
            { return rhs * lhs; }

            friend const bool operator == (const Point_2d<T> lhs, const Point_2d<T> rhs)
            { return lhs.x == rhs.x && lhs.y == rhs.y; }

            const Point_2d<T> & operator = (const Point_2d<T> rhs)
            {
                this->x = rhs.x; this->y = rhs.y;
                return *this;
            }

            operator Point_2d<double>()const
            { return Point_2d<double>(this->x, this->y); }
    };


    #define Vector_2d Point_2d
    //template<class T>
    //struct type_hack
    //{ typedef Point_2d<T> Vector_2d; };
    //template<class T>
    //using Vector_2d = Point_2d<T>;


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
