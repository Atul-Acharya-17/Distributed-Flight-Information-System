package entities;

import java.time.LocalTime;
import java.util.ArrayList;

public interface FlightFactory {
    void createFlight(String flightID, String source, String destination, int seatsAvailable, int seatsBooked, float price, LocalTime departureTime, LocalTime duration);
    boolean bookSeat(String flightID, int numSeatsBooked);
    void cancelSeat(String flightID, int numSeatsBooked);
    void sendNotification(String clientID);
    public ArrayList<String> findFlights(String source, String destination);
    void registerClientCallback(String clientID);
    void unregisterClientCallback(String clientID);
    void populateFlights();
    void displayFlights();
}
