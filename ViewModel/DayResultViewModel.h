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
	QVariant data(const QModelIndex &index, int role) const;

	void setDateFormat(QString value) { _format = value; }
	
	void loadByDay();
	void loadByWeek();
	void loadByMonth();
	
private:
	DayResult *r;
	QString _format;
};

#endif // DAYRESULTVIEWMODEL_H
