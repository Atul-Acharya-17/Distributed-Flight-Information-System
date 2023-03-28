package entities;

import marshall.Serialization;

/* 
    Interface for a Booking object used to make reservations in flight.
    Inherits from Serializable which allows to serialize objects.
*/
public interface Booking extends Serialization {
    public char[] getBookingId();
    public void setBookingId(char[] bookingId);

    public char[] getFlightId();
    public void setFlightId(char[] flightId);

    public char[] getClientId();
    public void setClientId(char[] clientId);

    public int getNumSeatsBooked();
    public void setNumSeatsBooked(int numSeatsBooked);
    
    public void display();
}
