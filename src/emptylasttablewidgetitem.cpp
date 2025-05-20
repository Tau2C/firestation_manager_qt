#include "emptylasttablewidgetitem.h"

bool EmptyLastTableWidgetItem::operator<(const QTableWidgetItem& other) const
{
    const QString thisText  = text().trimmed();
    const QString otherText = other.text().trimmed();

    // Empty strings are always "greater"
    if (thisText.isEmpty() && !otherText.isEmpty())
        return false;
    if (!thisText.isEmpty() && otherText.isEmpty())
        return true;

    return QTableWidgetItem::operator<(other);
}
