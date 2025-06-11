#pragma once
#include <iostream>
#include <string>
#include "Date.h"
#include "Vendor.h"
#include "Stall.h"
#include "Package.h"
#include "ExtraService.h"
#include "ReservationExtraService.h"
#include "Booking.h"
#include "Invoice.h"
#include "Payment.h"
#include "Event.h"
using namespace std;

class EMS
{
protected:
    Event** events;
    int eventCount;

public:
    EMS();
    ~EMS();
    void run();
};