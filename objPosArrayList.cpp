#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.
#define LISTSIZE 200
objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    sizeArray = ARRAY_MAX_CAP;
    sizeList = 0;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
    //optionally...
    sizeArray = 0;
    sizeList = 0;
}

int objPosArrayList::getSize() const
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
        if(sizeList == sizeArray)
    {
        //cout << "[WARNING] List is Full, No Insertion Allowed." << endl;
        return;
    }

    for(int i = sizeList; i > 0; i--)   
        aList[i] = aList[i - 1];  // shuffling towards the tail
    aList[0] = thisPos;
    sizeList++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(sizeList < sizeArray)
    {
        aList[sizeList++] = thisPos;        
    }
}

void objPosArrayList::removeHead()
{
        if(sizeList == 0)
    {
        //cout << "[WARNING] List is Empty, No Removal Allowed" << endl;
        return;
    }

    for(int i = 0; i < sizeList - 1; i++)   
        aList[i] = aList[i + 1];  // shuffling towards the head

    sizeList--;

}

void objPosArrayList::removeTail()
{
        if(sizeList > 0)
    {
        sizeList--;  // lazy delete

    }


}

objPos objPosArrayList::getHeadElement() const
{
    if(sizeList > 0)
    {
            return aList[0];
    }
    objPos empty;
    empty.setObjPos(-1, -1, ' '); // element outside of the board
    return empty;
}

objPos objPosArrayList::getTailElement() const
{
        if(sizeList > 0)
    {
         return aList[sizeList - 1];
    }

    objPos empty;
    empty.setObjPos(-1, -1, ' '); // element outside of the board
    return empty;

}

objPos objPosArrayList::getElement(int index) const
{
    if(index < 0 || index >= sizeArray)
    {
        objPos empty;
        empty.setObjPos(-1, -1, ' ');
        return empty;
    }
    return aList[index];
}