#include "EMS.h"
using namespace std;

void EMS::run()
{
    Vendor v("Taiba", 101, "Anime", "taibaxali@gmail.com");

    Date eventDate = { 11, 6, 2025 };
    Event e("Comic Expo", 301, "Expo Center", eventDate, "Pop Culture", 1);
    Stall s1(1, "10x10", 0, 0, "Premium", 1000);
    e.add_stall(s1, 0);

    Package p("Starter", 201, "10x10", 1200);
    ExtraService wifi(301, "WiFi", "High speed 4G Internet", 100);
    ReservationExtraService res1(401, &wifi, 2);
    Booking b1(501, &v, e.get_stall(0));

    Date invoiceDate = { 11, 6, 2025 };
    Invoice inv(601, &b1, invoiceDate, 1300);
    Date paymentDate = { 11, 6, 2025 };
    Payment pay1(701, &inv, paymentDate, 1300, "Credit Card");

    b1.confirm();
    pay1.apply();

    cout << "VENDOR DETAILS: " << endl;
    v.get_details();

    cout << "\nEVENT DETAILS: " << endl;
    e.show_event_details();

    cout << "\nSTALLS IN EVENT: " << endl;
    e.show_all_stalls();

    cout << "\nPACKAGE DETAILS: " << endl;
    p.get_package_details();

    cout << "\nEXTRA SERVICE DETAILS: " << endl;
    wifi.get_service_info();

    cout << "\nRESERVED SERVICE DETAILS: " << endl;
    res1.get_reservation_info();

    cout << "\nBOOKING DETAILS: " << endl;
    b1.get_booking_details();

    cout << "\nINVOICE DETAILS: " << endl;
    inv.get_invoice_details();

    cout << "\nPAYMENT DETAILS: " << endl;
    pay1.get_payment_info();
}
