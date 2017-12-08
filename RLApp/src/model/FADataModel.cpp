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
	if (determinized)
	{
		return _states_determinized.size() + 1;
	}
	else
	{
		return _states.size() + 1;
	}
	

}

int FADataModel::columnCount(const QModelIndex & parent) const
{
	//if (_terminals.size() < 1)
	//{
	//	return 1;
	//}
	return _terminals.size()+1;
		

}

QVariant FADataModel::data(const QModelIndex & index, int role) const
{

	if (determinized)
	{
		if (role == Qt::DisplayRole) {

			if (index.column() == 0)
			{
				if (index.row() == 0)
				{
					return "States";
				}

				return _states_determinized[index.row() - 1]._state_name;
				//return _map->keys().at(index.row());
			}
			if (index.column() > 0)
			{
				if (index.row() == 0)
				{
					return _terminals[index.column() - 1];
				}
				TR transition;
				if (_states_determinized[index.row() - 1]._transitions.size() > 0)
				{
					transition = _states_determinized[index.row() - 1]._transitions.at(index.column() - 1);

				}

				return transitionToStr(transition);
				//return _map->values().at(index.row()).at(index.column());
			}
		}
		else if (role == Qt::BackgroundRole)
		{
			if (index.row() != 0)
			{
				if (_states_determinized[index.row() - 1]._type & FINAL)  //change background only for cell(1,2)
				{
					QBrush redBackground(Qt::red);
					return redBackground;
				}
			}
		}

		return QVariant();
	}
	else
	{
		if (role == Qt::DisplayRole) {

			if (index.column() == 0)
			{
				if (index.row() == 0)
				{
					return "States";
				}

				return _states[index.row() - 1]._state_name;
				//return _map->keys().at(index.row());
			}
			if (index.column() > 0)
			{
				if (index.row() == 0)
				{
					return _terminals[index.column() - 1];
				}
				TR transition;
				if (_states[index.row() - 1]._transitions.size() > 0)
				{
					transition = _states[index.row() - 1]._transitions.at(index.column() - 1);

				}

				return transitionToStr(transition);
				//return _map->values().at(index.row()).at(index.column());
			}
		}
		else if (role == Qt::BackgroundRole)
		{
			if (index.row() != 0)
			{
				if (_states[index.row() - 1]._type & FINAL)
				{
					QBrush redBackground(Qt::red);
					return redBackground;
				}
			}

		}

		return QVariant();
	}
	
}

bool FADataModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (determinized)
	{
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

				_states_determinized[index.row()]._state_name = value.toString();
				return true;
				//return _map->keys().at(index.row());
			}
			if (index.column() > 0)
			{
				if (index.row() == 0)
				{
					_terminals[index.column()-1] = value.toString();
					emit dataChanged(index, index);

					return true;
				}
				value.toString().replace(" ", "");

				QList<QString> str_list = value.toString().split(",", QString::SkipEmptyParts);
				TR transition = str_list.toVector();
				if (_states[index.row() - 1]._transitions.size() > 0)
				{
					_states_determinized[index.row() - 1]._transitions[index.column() - 1] = transition;
				}
				emit dataChanged(index, index);

				return true;
				//return _map->values().at(index.row()).at(index.column());
			}
		}
		return false;
	}
	else
	{
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

				_states[index.row()-1]._state_name = value.toString();
				return true;
				//return _map->keys().at(index.row());
			}
			if (index.column() > 0)
			{
				if (index.row() == 0)
				{
					_terminals[index.column()-1] = value.toString();
					emit dataChanged(index, index);

					return true;
				}
				value.toString().replace(" ", "");

				QList<QString> str_list = value.toString().split(",", QString::SkipEmptyParts);
				TR transition = str_list.toVector();
				if (_states[index.row() - 1]._transitions.size() > 0)
				{
					_states[index.row() - 1]._transitions[index.column() - 1] = transition;
				}
				emit dataChanged(index, index);

				return true;
				//return _map->values().at(index.row()).at(index.column());
			}
		}
		return false;
	}

}

bool FADataModel::insertRows(int row, int count, const QModelIndex & parent)
{
	beginInsertRows(parent, row, row);
	QVector<TR> trans;
	trans.resize(_terminals.size());
	if (_states.size() == 0)
	{
		addState(FAState(NULL, "", trans, REGULAR | INITIAL)/*FAState(NULL, QString("teste"), { {QString("1")} }, 0x1)*/);
	}
	else
	{
		addState(FAState(NULL, "", trans, REGULAR)/*FAState(NULL, QString("teste"), { {QString("1")} }, 0x1)*/);
	}
	
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
