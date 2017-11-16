#include "model/FADataModel.h"
#include <QBrush> 

FADataModel::FADataModel(QObject *parent) :
	QAbstractTableModel(parent)
{
	
}

FADataModel::FADataModel(FA * fa, QObject * parent):
	FA(*fa),
	QAbstractTableModel(parent)
{
}

int FADataModel::rowCount(const QModelIndex& parent) const
{

		return _states.size();

}

int FADataModel::columnCount(const QModelIndex & parent) const
{

		return _terminals.size()+1;

}

QVariant FADataModel::data(const QModelIndex & index, int role) const
{
	//if (_terminals.size() == 0)
	//	return QVariant();
	if (role == Qt::DisplayRole) {

		if (index.column() == 0)
		{
			if (index.row() == 0)
			{
				return "States";
			}

			return _states[index.row()-1]._state_name;
			//return _map->keys().at(index.row());
		}
		if (index.column() > 0)
		{
			if (index.row() == 0)
			{
				return _terminals[index.column()-1];
			}
			TR transition = _states[index.row()-1]._transitions.at(index.column()-1);

			return transitionToStr(transition);
			//return _map->values().at(index.row()).at(index.column());
		}
	}
	else if (role == Qt::BackgroundRole)
	{
		if (_states[index.row()]._type & FINAL)  //change background only for cell(1,2)
		{
			QBrush redBackground(Qt::red);
			return redBackground;
		}
	}

	//if (index.column() == 0)
	//	return _map->values().at(index.row());
	//if (index.column() == 1)
	//	return _map->values().at(index.row());
	return QVariant();
}

bool FADataModel::setData(const QModelIndex & index, const QVariant & value, int role)
{

	//if (_terminals.size())
	//	return false;
	//if (index.row() < 0 ||
	//	index.row() >= _states.size()/* ||
	//	role != Qt::DisplayRole*/) {
	//	return false;
	//}

	if (role == Qt::EditRole)
	{
		
		if (index.column() == 0)
		{
			if (index.row() == 0)
			{

				_terminals[0] = value.toString();

				emit dataChanged(index, index);
				return true;
			}
			
			_states[index.row()]._state_name = value.toString();
			return true;
			//return _map->keys().at(index.row());
		}
		if (index.column() >= 0)
		{
			if (index.row() == 0)
			{
				_terminals[index.column()] = value.toString();
				emit dataChanged(index, index);

				return true;
			}
			value.toString().replace(" ", "");

			QList<QString> str_list = value.toString().split(",", QString::SkipEmptyParts);
			TR transition = str_list.toVector();
			_states[index.row()-1]._transitions[index.column()-1] = transition;
			emit dataChanged(index, index);

			return true;
			//return _map->values().at(index.row()).at(index.column());
		}
	}
	//if (index.column() == 0)
	//	return _map->values().at(index.row());
	//if (index.column() == 1)
	//	return _map->values().at(index.row());
	return false;
}

bool FADataModel::insertRows(int row, int count, const QModelIndex & parent)
{
	beginInsertRows(parent, row, row);
	QVector<TR> trans;
	trans.resize(_terminals.size());
	addState(FAState(NULL, "", trans, REGULAR)/*FAState(NULL, QString("teste"), { {QString("1")} }, 0x1)*/);
	endInsertRows();
	return true;
}

bool FADataModel::insertColumns(int column, int count, const QModelIndex & parent)
{
	beginInsertColumns(parent, column, column);
	addTerminal(""/*"a"+QString::number(column)*/);
	
	for (FAState& state : _states)
	{
		state._transitions.resize(_terminals.size());
	}
	endInsertColumns();
	return true;
}

bool FADataModel::removeRows(int row, int count, const QModelIndex & parent)
{
	beginRemoveRows(parent, row, row);
	_states.removeAt(row);
	endRemoveRows();
	return false;
}

bool FADataModel::removeColumns(int column, int count, const QModelIndex & parent)
{
	beginRemoveColumns(parent, column, column);
	_terminals.removeAt(column);
	for (FAState& state : _states)
	{
		state._transitions.removeAt(column);
	}
	endRemoveColumns();
	return false;
}

Qt::ItemFlags FADataModel::flags(const QModelIndex & /*index*/) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}
