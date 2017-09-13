#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QWidget>
#include <QTableView>

class TableView : public QTableView
{
	Q_OBJECT
public:
	explicit TableView(QWidget *parent = 0);

	// QWidget interface
protected:
	void keyPressEvent(QKeyEvent *event);
	
	// QAbstractItemView interface
public:
	void keyboardSearch(const QString &search);
};

#endif // TABLEVIEW_H
