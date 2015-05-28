#include "servicemodel.h"
#include <QListIterator>
#include <QDebug>

ServiceModel::ServiceModel() : QAbstractListModel()
{
    roles_[stationNameRole] = "stationName";
    roles_[stationCRSRole] = "stationCRS";
    roles_[destinationRole] = "destination";
    roles_[destinationCRSRole] = "destinationCRS";
    roles_[departureTimeRole] = "departureTime";
    roles_[amendedTimeRole] = "amendedTime";
    roles_[platformRole] = "platform";
    roles_[operatorRole] ="operator";
    roles_[operatorCodeRole] = "operatorCode";
    roles_[serviceIDRole] = "serviceID";
}


int ServiceModel::rowCount(const QModelIndex &) const
{
    return data_.size();
}

QVariant ServiceModel::data(const QModelIndex &index, int role) const
{

    int row = index.row();
    if (row < 0 || row > data_.size()) return QVariant();
    ServiceObject serviceObject = data_.at(row);
    switch (role)
    {

    case stationNameRole : return serviceObject.getStationName();
    case stationCRSRole : return serviceObject.getStationCRS();
    case destinationRole: return serviceObject.getDestination();
    case destinationCRSRole : return serviceObject.getDestinationCRS();
    case departureTimeRole : return serviceObject.getDepartureTime();
    case amendedTimeRole : return serviceObject.getAmendedTime();
    case platformRole : return serviceObject.getPlatform();
    case operatorRole : return serviceObject.getTrainOperator();
    case operatorCodeRole : return serviceObject.getOperatorCode();
    case serviceIDRole : return serviceObject.getServiceID();
    default: return QVariant();
    }

}
QHash<int, QByteArray> ServiceModel::roleNames() const

{
    return roles_;
}

void ServiceModel::appendRow(ServiceObject service)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    data_.append(service);
    endInsertRows();
}

void ServiceModel::populateModel(QList<ServiceObject> services){

    QListIterator<ServiceObject> iterator(services);
    while(iterator.hasNext()){
        appendRow(iterator.next());
    }
}