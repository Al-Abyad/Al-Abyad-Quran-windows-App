#ifndef BOOKMARKINFO_H
#define BOOKMARKINFO_H


class BookmarkInfo
{
public:
    BookmarkInfo();
    void setAye(int v);
    void setSore(int s);
    int getAye();
    int getSore();

private:
    int aye;
    int sore;
};

#endif // BOOKMARKINFO_H
