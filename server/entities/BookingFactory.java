package entities;

public interface BookingFactory {
    void createBookingWithBookingId(String bookingId, String flightID, String clientId, int numSeatsBooked);
    String createBooking(String flightID, String clientId, int numSeatsBooked);
    boolean cancelBooking(String bookingid);
    void populateBookings();
}
