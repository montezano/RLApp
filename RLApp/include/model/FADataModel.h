#ifndef __FADATAMODEL_H__
#define __FADATAMODEL_H__

#include <QAbstractTableModel>
#include "model/AF.h"

class FADataModel : public QAbstractTableModel, public FA
{
public:
	FADataModel(QObject *parent = 0);
	FADataModel(FA* fa, QObject *parent = 0);

	//~FADataModel();

	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex& parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

	virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
	virtual bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex());
	virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
	virtual bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex());
	Qt::ItemFlags flags(const QModelIndex & index) const;
private:

};


#endif // !__FADATAMODEL_H__







////////////////////////////////////////////////////////////
/// MAP MODEL FUNCTIONS
////////////////////////////////////////////////////////////
