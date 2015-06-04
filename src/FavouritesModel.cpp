#include "FavouritesModel.h"
#include "DatabaseOperations.h"

FavouritesModel::FavouritesModel() : QAbstractListModel()
{
    DatabaseOperations dbOp;
    _data = dbOp.getAllFavouriteStations();

    _roles[idRole] = "id";
    _roles[stationRole] = "station";
    _roles[favoritedRole] = "favorited";

}

int FavouritesModel::rowCount(const QModelIndex &) const
{
    return _data.size();
}

QVariant FavouritesModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if (row < 0 || row > _data.size()) return QVariant();
    StationObject stationObject = _data.at(row);
    switch (role)
    {
    case idRole: return stationObject.getID();
    case stationRole : return stationObject.getStation();
    case favoritedRole : return stationObject.getFavorited();
    default: return QVariant();
    }
}

bool FavouritesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch(role)
    {
    case stationRole:
        return false;
    case favoritedRole: {
        bool newVal = value.toBool();
        _data[index.row()].setFavorited(newVal);
        DatabaseOperations dbOp;
        dbOp.updateFavourite(newVal, index.row()+1);
        return true;
    }
    default:
        return false;
    }
}
