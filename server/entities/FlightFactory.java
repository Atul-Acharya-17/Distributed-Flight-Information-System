package entities;

import java.sql.Time;
import java.time.LocalTime;
import java.util.Date;

public interface FlightFactory {
    void createFlight(String flightID, String source, String destination, int seatsAvailable, int seatsBooked, float price, LocalTime departureTime, LocalTime duration);
    void bookSeat(String flightID);
    void sendNotification(String clientID);
    void registerClientCallback(String clientID);
    void unregisterClientCallback(String clientID);
    void populateFlights();
}
