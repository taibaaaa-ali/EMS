#ifndef RESERVATIONEXTRASERVICE_H
#define RESERVATIONEXTRASERVICE_H

#include <iostream>
#include "ExtraService.h"
using namespace std;

class ReservationExtraService
{
    int resID;
    ExtraService* service;
    int quantity;

public:
    ReservationExtraService();
    ReservationExtraService(int id, ExtraService* s, int qty);

    float get_total_cost() const;
    void get_reservation_info() const;
};

ReservationExtraService::ReservationExtraService() : resID(0), service(nullptr), quantity(0) {}

ReservationExtraService::ReservationExtraService(int id, ExtraService* s, int qty)
    : resID(id), service(s), quantity(qty) {
}

float ReservationExtraService::get_total_cost() const
{
    return quantity * (service ? service->get_price() : 0.0f);
}

void ReservationExtraService::get_reservation_info() const
{
    cout << "Reservation ID: " << resID << endl;
    if (service)
        service->get_service_info();
    cout << "Quantity: " << quantity << endl;
    cout << "Total Cost: $" << get_total_cost() << endl;
}

#endif
