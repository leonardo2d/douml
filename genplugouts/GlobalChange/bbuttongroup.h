#ifndef BBUTTONGROUP_H
#define BBUTTONGROUP_H

#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
class BButtonGroup : public QGroupBox
{
    Q_OBJECT
public:
    explicit BButtonGroup(QWidget *parent = 0);
    explicit BButtonGroup(const QString &title, QWidget* parent=0);
    BButtonGroup( int strips, Qt::Orientation orientation, const QString & title, QWidget * parent = 0, QString = QString());
    void setExclusive(bool isEx);
    void addWidget(QWidget* widget);
    QHBoxLayout *m_hLayout;
    QHBoxLayout *m_vLayout;
    Qt::Orientation m_orientation;
signals:

public slots:

};

#endif // BBUTTONGROUP_H
