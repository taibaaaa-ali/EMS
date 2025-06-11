#include "ReservationExtraService.h"

ReservationExtraService::ReservationExtraService(int id, ExtraService* s, int qty)
    : resID(id), service(s), quantity(qty) {}

float ReservationExtraService::get_total_cost()
{
    return quantity * service->get_price();
}

void ReservationExtraService::get_reservation_info()
{
    cout << "Reservation ID: " << resID << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Total Cost: $" << get_total_cost() << endl;
}
