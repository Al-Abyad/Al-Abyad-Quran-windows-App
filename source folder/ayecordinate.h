#ifndef AYECORDINATE_H
#define AYECORDINATE_H


class AyeCordinate{

public:
    AyeCordinate();
    void setXb(int v);
    void setyb(int v);
    void setXe(int v);
    void setWidth(int v);
    void setHeight(int v);

    void setLine(int v);

    int getXb();
    int getyb();
    int getXe();
    int getWidth();
    int getHeight();

    int getLine();
private:
    int xb;
    int yb;
    int xe;
    int width;
    int height;

    int line;

};

#endif // AYECORDINATE_H
