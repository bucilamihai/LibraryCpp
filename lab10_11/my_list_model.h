#include <QAbstractListModel>
#include <QFont>
#include <QList>


class MyListModel : public QAbstractListModel
{
private:
	QFont font_model;
	QList<QString> list;

public:
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const
	{
		if (!index.isValid())
			return QVariant();
		int row = index.row();
		if (role == Qt::DisplayRole) 
		{
			QString data = list.at(row);
			return QVariant(data);
		}
		return QVariant();
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return list.size();
	}

	void setFont(const QFont& font)
	{
		if (font_model != font)
		{
			font_model = font;
			// emit semnal pentru a actualiza fontul
			emit dataChanged(this->index(0), this->index(rowCount() - 1));
		}
	}

	QList<QModelIndex> selectedItems() const
	{
		QList<QModelIndex> selected;
		for (int row = 0; row < rowCount(); row++)
		{
			QModelIndex index = this->index(row);
			if (index.isValid() && index.data(Qt::CheckStateRole) == Qt::Checked)
				selected.append(index);
		}
		return selected;
	}

	void clear()
	{
		beginResetModel();
		list.clear();
		endResetModel();
	}


	void addItem(const QString& item)
	{
		beginInsertRows(QModelIndex(), rowCount(), rowCount());
		list.append(item);
		endInsertRows();
	}

	QModelIndexList findItems(const QString& searchString, Qt::MatchFlags flags) const
	{
		QModelIndexList matching_indexes;
		for (int row = 0; row < rowCount(); row++) 
		{
			QModelIndex index = this->index(row);
			QString data = index.data().toString();
			if (data.contains(searchString)) 
			{
				matching_indexes.append(index);
			}
		}
		return matching_indexes;
	}
};