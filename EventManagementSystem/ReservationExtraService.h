#pragma once
#include "ExtraService.h"

class ReservationExtraService
{
protected:
    int resID;
    ExtraService* service;
    int quantity;

public:
    ReservationExtraService(int id = 0, ExtraService* s = nullptr, int qty = 0);
    float get_total_cost() const;
    void get_reservation_info() const;
};