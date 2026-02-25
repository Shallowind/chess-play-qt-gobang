#ifndef ITEM_H
#define ITEM_H
#include<QPoint>

class Item
{
public:
    QPoint p;
    char opr;
    Item(QPoint p,char opr);
    bool operator ==(const Item &t1) const
        {
            return (opr == t1.opr && p == t1.p);
        }
    Item();
};

#endif // ITEM_H
