#ifndef DAYRESULTVIEWMODEL_H
#define DAYRESULTVIEWMODEL_H

#include <QObject>
#include <Core/ITableModel.h>
#include <Model/DayResult.h>

class DayResultViewModel : public ITableModel
{
	Q_OBJECT
public:
	explicit DayResultViewModel(QObject *parent = 0);
	int rowCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	
	
private:
	DayResult *r;
};

#endif // DAYRESULTVIEWMODEL_H
