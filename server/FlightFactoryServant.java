package server;
import java.io.File;
import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
import java.util.Hashtable;
import java.util.Scanner;

public class FlightFactoryServant extends UnicastRemoteObject implements FlightFactory {
    private Hashtable<String, Flight> flights = new Hashtable<>();
    public FlightFactoryServant() throws java.rmi.RemoteException {
        super();
    }

    public void createFlight(String flightID, String source, String destination, int seatsAvailable, int seatsBooked, float price) throws java.rmi.RemoteException {
        Flight flight = new FlightServant(flightID, source, destination, seatsAvailable, seatsBooked, price);
        flights.put(flightID, flight);
    }

    public void bookSeat(String flightID) throws java.rmi.RemoteException {
        Flight flight = flights.get(flightID);
        flight.setSeatsAvailable(flight.getSeatsAvailable() - 1);
        flight.setSeatsBooked(flight.getSeatsBooked() + 1);
    }

    public void sendNotification(String clientID) throws java.rmi.RemoteException {
        //TODO: Which class is storing the clientID?
        
        // ClientCallback client = ClientCallbackFactory.getClientCallback(clientID);
        // client.notifyClient();
    }

    public void registerClientCallback(String clientID) throws java.rmi.RemoteException {
        // ClientCallback client = ClientCallbackFactory.getClientCallback(clientID);
        // client.registerClientCallback();
    }

    public void unregisterClientCallback(String clientID) throws java.rmi.RemoteException {
        // ClientCallback client = ClientCallbackFactory.getClientCallback(clientID);
        // client.unregisterClientCallback();
    }

    @Override
    public void populateFlights() throws RemoteException {
        // TODO: Test this method
        try
        {
            File fileObj = new File("flights.txt");
            Scanner scanner = new Scanner(fileObj);
            while(scanner.hasNextLine()){
                String line = scanner.nextLine();
                String[] flightDetails = line.split(",");
                createFlight(flightDetails[0], flightDetails[1], flightDetails[2], Integer.parseInt(flightDetails[3]), Integer.parseInt(flightDetails[4]), Float.parseFloat(flightDetails[5]));
            }
            scanner.close();
        }
        catch(Exception e)
        {
            System.out.println(e);
        }        
    }
}
    