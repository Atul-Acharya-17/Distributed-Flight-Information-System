package entities;

import java.time.LocalTime;
import java.util.ArrayList;

/*
 * Interface for Flight class factory to create and track flight objects.
 */
public interface FlightFactory {
    void createFlight(String flightID, String source, String destination, int seatsAvailable, int seatsBooked, float price, LocalTime departureTime, LocalTime duration);
    boolean bookSeat(String flightID, int numSeatsBooked);
    void cancelSeat(String flightID, int numSeatsBooked);
    public boolean checkFlight(String flightID);
    public Flight getFlight(String flightID);
    public ArrayList<String> findFlights(String source, String destination);
    public ArrayList<String> findFlights(String source);
    public ArrayList<TripServant> planTrip(String source, String destination, int numFlights, float maxCost);
    void populateFlights();
    void displayFlights();
}
