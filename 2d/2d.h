#ifndef 2D_H
#define 2D_H

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

class Picture
{
public:
    Picture(int width, int height);
    void create(int width, int height);
    ARGB & get_ARGB_on(int x, int y);
    ARGB & get_ARGB_on(Point_2d point);

    Picture(const & Picture other_picure );
    Picture & operator = (const & Picture other_picure );
    Picture(){}
    ~Picture();
private:
    int width, height;
    ARGB * data;
    bool should_delete;
};

}

#endif
