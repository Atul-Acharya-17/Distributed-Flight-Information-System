package entities;

public interface FlightFactory {
    void createFlight(String flightID, String source, String destination, int seatsAvailable, int seatsBooked, float price);
    void bookSeat(String flightID);
    void sendNotification(String clientID);
    void registerClientCallback(String clientID);
    void unregisterClientCallback(String clientID);
    void populateFlights();
}
