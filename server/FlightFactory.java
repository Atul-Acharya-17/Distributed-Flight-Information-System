import java.rmi.*;

public interface FlightFactory {
    void createFlight(String flightID, String source, String destination, int seatsAvailable, int seatsBooked, float price) throws RemoteException;
    void bookSeat(String flightID) throws RemoteException;
    void sendNotification(String clientID) throws RemoteException;
    void registerClientCallback(String clientID) throws RemoteException;
    void unregisterClientCallback(String clientID) throws RemoteException;
    void populateFlights() throws RemoteException;
}
