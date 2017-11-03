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
	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	inline void setMap(QMap<QString, QList<QString>>* map) { _map = map; }
	//void insertRow(QPair<QString, QList<QString>> row) { _map->insert() }

private:
	QMap<QString, QList<QString>>* _map;
};

#endif // MAPMODEL_H


