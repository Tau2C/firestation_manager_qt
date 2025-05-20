#ifndef EMPTYLASTTABLEWIDGETITEM_H
#define EMPTYLASTTABLEWIDGETITEM_H

#include <QTableWidgetItem>

class EmptyLastTableWidgetItem : public QTableWidgetItem
{
  public:
    using QTableWidgetItem::QTableWidgetItem;

    bool operator<(const QTableWidgetItem& other) const override;
};
#endif
