#include <iostream>
using namespace std;

#include "ExtraService.h"

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
    return quantity * service->get_price();
}

void ReservationExtraService::get_reservation_info() const
{
    cout << "Reservation ID: " << resID << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Total Cost: $" << get_total_cost() << endl;
}
