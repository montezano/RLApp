#ifndef MAPMODEL_H
#define MAPMODEL_H

#include <QAbstractTableModel>
#include <QMap>

class MapModel : public QAbstractTableModel
{
	Q_OBJECT
public:

	enum MapRoles {
		KeyRole = Qt::UserRole + 1,
		ValueRole
	};

	explicit MapModel(QObject *parent = 0);
	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex& parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	inline void setMap(QMap<QString, QList<QString>>* map) { _map = map; }
	//void insertRow(QPair<QString, QList<QString>> row) { _map->insert() }

protected:
	QMap<QString, QList<QString>>* _map;
};

#endif // MAPMODEL_H


