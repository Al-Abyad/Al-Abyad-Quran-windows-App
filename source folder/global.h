#ifndef GLOBAL_H
#define GLOBAL_H



class Global
{
public:
    Global();
    enum DownloadState{DownloadAye,DownloadPage,DownloadSore,downloadOff};
    enum combosSignals{comboPage,comboSore,comboAye,comboJuz,allComboPSAJ};
    enum RepeatPlayerState{NoRepeat,PageRepeat,InfinityRepeat,LimitRepeat};
    enum PlayerState{BookmarkPlay,NormalPlay,ExamPlay};
    enum BookmarkOperation{SaveBookmark,UpdateBookmark,DeleteBookmark};
    enum qaryOperation{SaveQary,UpdateQary,DeleteQary};
    enum ThreadOperation{DBBookMarkThreadOP,DBQaryThreadOP,Download,Export,DBReadAye};
    enum KeyBoardLang{Persian,Arabic};

    enum ExamStatus{ExamListFull,ExamAyeExist,ExamAyeNotExist};

};

#endif // GLOBAL_H
