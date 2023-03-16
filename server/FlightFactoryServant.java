import java.io.File;
import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.Map;
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

    public void displayFlights() {
        Iterator<Map.Entry<String,Flight>> itr = flights.entrySet().iterator();
        Map.Entry<String, Flight> entry = null;
        while(itr.hasNext()) {
            entry = itr.next();
            System.out.println( entry.getKey() + "--->"); 
            entry.getValue().display();
        }
        System.out.println("\n" + flights.size());
    }

    @Override
    public void populateFlights() throws RemoteException {
        try
        {
            File fileObj = new File(System.getProperty("user.dir") + "/flights.txt");
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
    