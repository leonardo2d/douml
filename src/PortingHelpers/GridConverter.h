#ifndef GRIDCONVERTER_H
#define GRIDCONVERTER_H

#include <QWidget>
#include <Q3Grid>
#include <QGridLayout>
#include <QLabel>
#include "data/HaveKeyValueData.h"
struct GridDataStack
{
    static QGridLayout* layout;
    static QWidget* parent;
    static int columnCounter;
    static int columns;
    static int rowCounter;
};


class GridConverter
{
public:
    GridConverter();
    ~GridConverter();

    static void InitNewGrid(QWidget*, int columns);

    static void PlaceWidget(QWidget* parent, QWidget* grid);



    static QList<GridDataStack> grids;
};

//struct Grid

#endif // GRIDCONVERTER_H
