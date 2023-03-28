package entities;

/*
 * Interface for Booking class factory to create and track Booking objects.
 */
public interface BookingFactory {
    void createBookingWithBookingId(String bookingId, String flightID, String clientId, int numSeatsBooked);
    String createBooking(String flightID, String clientId, int numSeatsBooked);
    boolean cancelBooking(String bookingid);
    void populateBookings();
    boolean checkBookingExists(String bookingId);
}
